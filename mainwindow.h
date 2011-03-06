#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGlobal>
#include <ctime>
#include <QMainWindow>
#include <QImage>
#include <QFileDialog>
#include <QString>
#include <QPixmap>
#include <QGraphicsScene>
#include "rendervideoframe.h"

namespace Ui {
    class MainWindow;
}

using namespace cv;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    enum ACTION {
        ENCRYPTION,
        DECRYPTION
    } action;
    QString directory;
    QGraphicsScene scene;
    QImage image;

private slots:
    void on_btnSave_clicked();
    void on_btnLoad_clicked();
    void on_rbEncryption_clicked();
    void on_rbDecryption_clicked();
    void on_btnFinished_clicked();
    void on_btnPlayPause_clicked();
    void on_webcam_stateChanged(int);
};

#endif // MAINWINDOW_H
