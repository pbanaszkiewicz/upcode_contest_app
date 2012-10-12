/*
* This file is part of Stecrypt.
*
* Stecrypt is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Stecrypt is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with Stecrypt.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "rendervideoframe.h"
#include <cmath>

Circle::Circle() {}
Circle::Circle(int x, int y, int id) {
    this->x = x; this->y = y;
    this->val = (unsigned long long)pow((long double)2, id);
    this->selected = false;
    this->id = id;
}
bool Circle::getSelected() {
    return selected == true;
}
void Circle::setSelected(bool v) {
    selected = v;
}
unsigned long long Circle::getValue() {
    return val;
}

RenderVideoFrame::RenderVideoFrame(QWidget *parent) :
    QWidget(parent)
{
    // circles settings
    //computed for 6x5 circles on 640x480 surface
    // 640 = 6*d + 5*s1
    // 480 = 5*d + 4*s2
    //there cannot be more circles, unless one wants to use huge integers
    //(more than 2^64)
    d = 80-1;  //circle diameter; '-1' is for the width of the circle
    s1 = 32; //space between circles on X-axis
    s2 = 20; //space between circles on Y-axis
    c_x = 6;
    c_y = 5;

    initCircles();

    //selected point
    point_diameter = 16;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(queryFrame()) );
    setState(-2);
}

void RenderVideoFrame::initCircles() {
    circles.clear();

    for (int i=0, id=(64-c_x*c_y); i<c_x; i++) {
        for (int j=0; j<c_y; j++, id++) {
            //Circle c(i, j, id);
            Circle c(i*(d+s1),j*(d+s2), id);
            circles.push_back(c);
        }
    }
}

void RenderVideoFrame::countValue() {
    value = 0;
    for (vector<Circle>::iterator i=circles.begin(); i!=circles.end(); i++) {
        if ((*i).getSelected()) {
            value += (*i).getValue();
            value += pow(2, (*i).id-32);
        }
    }
}

void RenderVideoFrame::startCapturing(int n) {
    capture = cvCreateCameraCapture(n);
    //capture.open(n);

    if (!capture) {
        //some error occured
        error = "Cannot set camera.";
    }
    capturing = true;

    //grab one frame to set appropriate size (?)
    // TODO: add 'selecting input video size 640x480'
    frame = cvQueryFrame(capture);
    image = QImage(QSize(frame->width, frame->height),QImage::Format_RGB888);
    prev_frame = cvCreateImage(cvSize(frame->width, frame->height), frame->depth,
                               frame->nChannels);

    timer->start(20);
}

void RenderVideoFrame::stopCapturing() {
    timer->stop();

    cvReleaseCapture(&capture);
    //capture.release();
    capturing = false;
}

int RenderVideoFrame::getState() {
    return state;
}

void RenderVideoFrame::setState(int v) {
    if (v != state  &&  -2 <= v  &&  v <= 3) {
        state = v;
        switch (state) {
        case -2:
            // uninitialized
            point_x = point_y = -1;
            value = 0;
            capturing = false;
            update();
            break;

        case -1:
            // initialized
            point_x = point_y = -1; // do it again in case of restarting
            value = 0;

            startCapturing(0);
            setState(0);
            break;

        case 0:
            // waiting for user to select the object to track
            break;

        case 1:
            // tracking object and selecting circles
            break;

        case 2:
            // finished everything :)
            stopCapturing();
            countValue();
            initCircles();
            update();
            break;

        case 3:
            // interrupted :(
            stopCapturing();
            initCircles();
            update();
            break;

        }

        emit stateChanged(v);
    }
}

void RenderVideoFrame::queryFrame() {
    cvCopy(frame, prev_frame);
    frame = cvQueryFrame(capture);
    //capture >> frame;

    if (!frame) {
        this->error = "Cannot get frame.";
        return;
    }

    //make mirror reflection
    //it's more natural
    cvFlip(frame, NULL, 1);

    // monochrome are not as good as true color images for tracking
    // but they speed up the algorithm a lot
    IplImage *frame1_mono = cvCreateImage(cvSize(frame->width, frame->height), IPL_DEPTH_8U, 1),
             *frame2_mono = cvCreateImage(cvSize(frame->width, frame->height), IPL_DEPTH_8U, 1);

    if (point_x != -1 && point_y != -1) {
        // let's run optical flow!

        out.clear(); status.clear(); errors.clear();

        cvConvertImage(prev_frame, frame1_mono);
        cvConvertImage(frame, frame2_mono);

        Mat mat1(frame1_mono);
        Mat mat2(frame2_mono);
//        Mat mat1 = cvCreateMat(frame1_mono->height, frame1_mono->width, CV_32FC3);
//        Mat mat2 = cvCreateMat(frame2_mono->height, frame2_mono->width, CV_32FC3);
//        cvConvert(frame1_mono, mat1);
//        cvConvert(frame2_mono, mat2);

        calcOpticalFlowPyrLK(mat1, mat2, in, out, status, errors);
//        calcOpticalFlowPyrLK(frame1_mono, frame2_mono, in, out, status, errors);

        // if the point has been found by PyrLK algorithm
        // set the new point's values
        for (unsigned int i=0; i<status.size(); i++) {
            if (status[i]==1) {
                in[i] = out[i];
            }
        }
        point_x = in[2].x;
        point_y = in[2].y;

        // check if the point is within any circle
        double r = d / 2, x, y, dist; // circle's radius
        vector<Circle>::iterator it;
        for (it=circles.begin(); it!=circles.end(); it++) {
            x=(*it).x+r;
            y=(*it).y+r;
            dist = sqrt(pow(x-point_x, 2) + pow(y-point_y, 2));
            if (dist<=r) {
                (*it).setSelected(true);
                break;
            }
        }
    }

    image = QImage(
                (const uchar *)frame->imageData,
                frame->width,
                frame->height,
                QImage::Format_RGB888
            ).rgbSwapped();
    this->update();
}

void RenderVideoFrame::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    if (state==-1 || state==0 || state==1)
        painter.drawImage(QPoint(0, 0), image);
    else {
        // draw black screen or something
        QImage tmp(image.width(), image.height(), QImage::Format_RGB888);
        tmp.fill(0);
        painter.drawImage(QPoint(0,0), tmp);
    }

    if (state==1) {
        // draw circles on the frame
        QBrush selected(QColor(64,64,255,200));
        QBrush not_selected(QColor(127,127,127,40));

        vector<Circle>::iterator it;
        for (it=circles.begin(); it!=circles.end(); it++) {
            if ((*it).getSelected())
                painter.setBrush(selected);
            else
                painter.setBrush(not_selected);

            painter.drawEllipse((*it).x, (*it).y, d, d);
            painter.drawText((*it).x+d/2-4, (*it).y+d/2+4, QString("%1").arg((*it).id));
        }

        // draw the tracking point
        painter.setBrush(QBrush(QColor(255, 0, 0, 200)));
        if (point_x != -1 && point_y != -1) {
            painter.drawEllipse(point_x-(point_diameter/2), point_y-(point_diameter/2),
                                point_diameter, point_diameter);
        }
    }
}

void RenderVideoFrame::mousePressEvent(QMouseEvent * event) {
    if (getState()==0 && point_x==-1 && point_y==-1) {
        // we set more points just in my curiosity
        point_x = event->x();
        point_y = event->y();
        Point2f p1(point_x-point_diameter*2, point_y-point_diameter*2),
                p2(point_x+point_diameter*2, point_y-point_diameter*2),
                p3(point_x, point_y),
                p4(point_x-point_diameter*2, point_y+point_diameter*2),
                p5(point_x+point_diameter*2, point_y+point_diameter*2);

        in.clear();
        in.push_back(p1); in.push_back(p2); in.push_back(p3); in.push_back(p4); in.push_back(p5);
        setState(1); // tracking
    }
}
