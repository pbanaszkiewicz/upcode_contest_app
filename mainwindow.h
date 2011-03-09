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
#include <QRegExp>
#include <QTextCodec>
#include "rendervideoframe.h"
#include "xorimage.h"

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
    bool calculated; // whether or not was the number calculated using webcam

private slots:
    void on_text_textChanged();
    void on_btnEncryptDecrypt_clicked();
    void on_btnSave_clicked();
    void on_btnLoad_clicked();
    void on_rbEncryption_clicked();
    void on_rbDecryption_clicked();
    void on_btnFinished_clicked();
    void on_btnPlayPause_clicked();
    void on_webcam_stateChanged(int);
};

#endif // MAINWINDOW_H
