#include "rendervideoframe.h"

RenderVideoFrame::RenderVideoFrame(QWidget *parent) :
    QWidget(parent)
{
    // circles settings
    //computed for 6x5 circles on 640x480 surface
    // 640 = 6*d + 5*s1
    // 480 = 5*d + 4*s2
    //there cannot be more circles, unless one wants to use huge integers
    //(more than 2^64)
    d = 80;  //circle diameter
    s1 = 32; //space between circles on X-axis
    s2 = 20; //space between circles on Y-axis

    capturing = false;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(queryFrame()) );
}

void RenderVideoFrame::setCapture(int n) {
    //this->capture = new VideoCapture(n);
    this->capture = cvCreateCameraCapture(n);

    if (!this->capture) {
        //some error occured
        this->error = "Cannot set camera.";
    }

    //grab one frame to set appropriate size
    this->frame = cvQueryFrame(this->capture);
    image = QImage(QSize(frame->width,frame->height),QImage::Format_RGB888);
}

bool RenderVideoFrame::drawCircles() {
    return circles;
}

void RenderVideoFrame::drawCircles(bool v) {
    circles = v;
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
    frame = cvQueryFrame(capture);

    //make mirror reflection
    //it's more natural
    cvFlip(frame, NULL, 1);

    if (circles) {
        //draw circles on the frame
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
    //QPainter painter(this);
    QPainter painter;
    painter.begin(this);
    painter.drawImage(QPoint(0, 0), image);
}
