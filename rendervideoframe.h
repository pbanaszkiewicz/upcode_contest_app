#ifndef RENDERVIDEOFRAME_H
#define RENDERVIDEOFRAME_H

#include <QWidget>
#include <QImage>
#include <QString>
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>
#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;


class Circle {
public:
    Circle();
    Circle(int, int, int);
    bool getSelected();
    void setSelected(bool);
    unsigned long long getValue();
    int x,y;
    int id;

protected:
    unsigned long long val;
    bool selected;
};


class RenderVideoFrame : public QWidget
{
    Q_OBJECT

public:
    explicit RenderVideoFrame(QWidget *parent = 0);
    //~RenderVideoFrame();
    QString error;
    bool getCapturing() { return capturing; }
    unsigned long long getValue() { return value; }

protected:
    //capturing settings
    CvCapture *capture;
    //VideoCapture capture;
    QImage image;
    IplImage *frame;
    IplImage *prev_frame;
    QTimer *timer;
    bool capturing;

    //selected point
    //user selects a point by mouse-clicking on the image
    //here are coordinates
    int point_x, point_y;
    int point_diameter;

    //optical flow vectors
    vector<Point2f> in, out;
    vector<uchar> status;
    vector<float> errors;

    //state of the RenderVideoFrame
    //-1 -> webcam not set yet
    //0 -> get ready for selecting tracked obj
    //1 -> track obj && display circles && select circles
    //2 -> finished
    int state;
    unsigned long long value;
    void countValue();

    //circles settings
    int d, s1, s2;
    int c_x, c_y;  // number of circles horizontally and vertically
    vector<Circle> circles;

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

    void initCircles();
    void startCapturing(int);
    void stopCapturing();

signals:
    void stateChanged(int);

public slots:
    void queryFrame();
    int getState();
    void setState(int);

};

#endif // RENDERVIDEOFRAME_H
