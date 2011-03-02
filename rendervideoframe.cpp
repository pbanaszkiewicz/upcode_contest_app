#include "rendervideoframe.h"
#include <cmath>

Circle::Circle() {}
Circle::Circle(int x, int y, int id) {
    this->x = x; this->y = y;
    this->val = (long long)pow((long double)2, id);
    this->selected = false;
}
bool Circle::getSelected() {
    return selected == true;
}
void Circle::setSelected(bool v) {
    selected = v;
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

    for (int i=0, id=(64-c_x*c_y); i<c_x; i++) {
        for (int j=0; j<c_y; j++, id++) {
            //Circle c(i, j, id);
            Circle c(i*(d+s1),j*(d+s2), id);
            circles.push_back(c);
        }
    }

    //selected point
    point_x = point_y = -1;
    point_diameter = 16;

    capturing = false;
    setState(-1);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(queryFrame()) );
}

void RenderVideoFrame::startCapturing(int n) {
    //this->capture = new VideoCapture(n);
    capture = cvCreateCameraCapture(n);

    if (!capture) {
        //some error occured
        error = "Cannot set camera.";
    }
    setState(0);

    //grab one frame to set appropriate size (?)
    frame = cvQueryFrame(capture);
    image = QImage(QSize(frame->width, frame->height),QImage::Format_RGB888);
    prev_frame = cvCreateImage(cvSize(frame->width, frame->height), frame->depth,
                               frame->nChannels);
}

void RenderVideoFrame::stopCapturing() {
    cvReleaseCapture(&capture);
    setState(-1);
}

bool RenderVideoFrame::drawCircles() {
    return draw_circles;
}

void RenderVideoFrame::drawCircles(bool v) {
    draw_circles = v;
}

int RenderVideoFrame::getState() {
    return state;
}

void RenderVideoFrame::setState(int v) {
    if (v != state  &&  -1 <= v  &&  v <= 2) {
        state = v;
        emit stateChanged(v);
    }
}

void RenderVideoFrame::toggleCapturing() {
    if (!capturing) {
        capturing = true;
        timer->start(20); //manipulating this value may cause the video smoother
                          //but also it may cause it vanish
    } else {
        capturing = false;
        timer->stop();
    }
}

void RenderVideoFrame::queryFrame() {
    cvCopy(frame, prev_frame);
    frame = cvQueryFrame(capture);

    if (!frame) {
        this->error = "Cannot get frame.";
        return;
    }

    //make mirror reflection
    //it's more natural
    cvFlip(frame, NULL, 1);

    if (point_x != -1 && point_y != -1) {
        // let's run optical flow!

        in.clear(); out.clear(); status.clear(); errors.clear();
        in.push_back(Point2f(point_x, point_y));

        // monochrome are not as good as true color images for tracking
        // but they speed up the algorithm a lot
        IplImage *frame1_mono = cvCreateImage(cvSize(frame->width, frame->height), IPL_DEPTH_8U, 1),
                 *frame2_mono = cvCreateImage(cvSize(frame->width, frame->height), IPL_DEPTH_8U, 1);
        cvConvertImage(prev_frame, frame1_mono);
        cvConvertImage(frame, frame2_mono);

        calcOpticalFlowPyrLK(frame1_mono, frame2_mono, in, out, status, errors);
        for (unsigned int i=0; i < status.size(); i++) {
            if (status[i] == 1) {
                point_x = out[i].x;
                point_y = out[i].y;
            }
        }
        // draw a point at (point_x, point_y) -> done in paintEvent()
        // check if the point is in some circle
    }

    image = QImage(
                (const uchar *)frame->imageData,
                frame->width,
                frame->height,
                QImage::Format_RGB888
            ).rgbSwapped();
    this->update();
}

void RenderVideoFrame::paintEvent(QPaintEvent * /*event*/) {
    QPainter painter(this);
    painter.drawImage(QPoint(0, 0), image);

    if (state==0 || state==-1 || state==2) {
        //get ready for tracking object
        // or
        //uninitialized phase
        // or
        //finished phase
        //
        // honestly, nothing is expected to happen in here

    } else if (state==1) {
        // draw circles on the frame
        QBrush selected(QColor(127,127,255,40));
        QBrush not_selected(QColor(127,127,127,40));

        for (unsigned int i=0; i<circles.size(); i++) {
            if (circles[i].getSelected())
                painter.setBrush(selected);
            else
                painter.setBrush(not_selected);
            painter.drawEllipse(circles[i].x, circles[i].y, d, d);
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
    point_x = event->x();
    point_y = event->y();
    setState(2);
}
