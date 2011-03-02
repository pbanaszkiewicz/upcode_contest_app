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
    int x,y;

protected:
    long long val;
    bool selected;
    //TODO: maybe add position or sth like that
};


class RenderVideoFrame : public QWidget
{
    Q_OBJECT

public:
    explicit RenderVideoFrame(QWidget *parent = 0);
    //~RenderVideoFrame();
    QString error;

protected:
    //capturing settings
    CvCapture *capture;
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

    //circles settings
    int d, s1, s2;
    bool draw_circles;
    int c_x, c_y;  // number of circles horizontally and vertically
    Vector<Circle> circles;

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:
    void stateChanged(int);

public slots:
    void startCapturing(int);
    void stopCapturing();
    void queryFrame();
    bool drawCircles();     // TODO: redundant?
    void drawCircles(bool); // TODO: redundant?
    int getState();
    void setState(int);
    //void startCapturing();
    //void stopCapturing();
    void toggleCapturing();

};

#endif // RENDERVIDEOFRAME_H
