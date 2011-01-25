#ifndef RENDERVIDEOFRAME_H
#define RENDERVIDEOFRAME_H

#include <QWidget>
#include <QImage>
#include <QString>
#include <QPainter>
#include <QTimer>
#include <opencv2/opencv.hpp>
using namespace cv;

class RenderVideoFrame : public QWidget
{
    Q_OBJECT

public:
    explicit RenderVideoFrame(QWidget *parent = 0);
    //~RenderVideoFrame();
    QString error;

protected:
    CvCapture *capture;
    QImage image;
    IplImage *frame;
    QTimer *timer;
    bool capturing;

    //circles settings
    int d, s1, s2;
    bool circles;

    void paintEvent(QPaintEvent *event);

signals:

public slots:
    void setCapture(int);
    void queryFrame();
    bool drawCircles();
    void drawCircles(bool);
    //void startCapturing();
    //void stopCapturing();
    void toggleCapturing();

};

#endif // RENDERVIDEOFRAME_H
