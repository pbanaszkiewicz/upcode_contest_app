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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->webcam, SIGNAL(stateChanged(int)), SLOT(on_webcam_stateChanged(int)));
    action = ENCRYPTION;
    ui->rbEncryption->setChecked(true);

    // set sbNumber some random value
    qsrand(time(NULL));
    ui->sbNumber->setValue(qrand()); // the value will always respect boundaries (8169, 217.....)
    calculated = false;

    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnPlayPause_clicked()
{
    calculated = false;
    if (ui->webcam->getState() == -2 || ui->webcam->getState() == 3 ||
            ui->webcam->getState() == 2) {
        ui->webcam->setState(-1); // let's initialize
        // we're starting
        ui->btnPlayPause->setText(tr("Stop"));
        ui->sbNumber->setEnabled(false);
    } else {
        ui->webcam->setState(3); // it's 'interruping'
        // we're pausing
        ui->btnPlayPause->setText(tr("Launch"));
        ui->sbNumber->setEnabled(true);
    }
}

void MainWindow::on_btnFinished_clicked()
{
    ui->webcam->setState(2);
    ui->btnPlayPause->setText(tr("Launch"));
    ui->sbNumber->setEnabled(false);
    ui->btnFinished->setEnabled(false);
    // what about the number?
    // we cannot set sbNumber.value to that number (int vs unsigned long long)
    calculated = true;// = ui->webcam->getState()==2;
    //ui->statusBar->showMessage(QString("%1").arg(ui->webcam->getValue()));
}

void MainWindow::on_webcam_stateChanged(int v)
{
    ui->btnFinished->setEnabled(false);
    switch (v) {
    case -2:
        ui->statusBar->showMessage(tr("Uninitialized"));
        break;
    case -1:
        ui->statusBar->showMessage(tr("Initialized"));
        break;
    case 0:
        ui->statusBar->showMessage(tr("Select object to track"));
        break;
    case 1:
        ui->statusBar->showMessage(tr("Tracking"));
        ui->btnFinished->setEnabled(true);
        break;
    case 2:
        ui->statusBar->showMessage(tr("Finished"));
        //if ()
        break;
    case 3:
        ui->statusBar->showMessage(tr("Interrupted"));
        break;
    }
}

void MainWindow::on_rbEncryption_clicked()
{
    action = ENCRYPTION;
    ui->btnEncryptDecrypt->setText(tr("Encrypt"));
	ui->text->setPlainText(QString());
    ui->text->setReadOnly(false);
}

void MainWindow::on_rbDecryption_clicked()
{
    action = DECRYPTION;
    ui->btnEncryptDecrypt->setText(tr("Decrypt"));
	ui->text->setPlainText(QString());
    ui->text->setReadOnly(true);
}

void MainWindow::on_btnLoad_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, tr("Open image"),
        directory, tr("Bitmaps (*.bmp)"));

    if (file_name.length()) {
        image.load(file_name);

        // check if the file has at least 24bits
        if (image.depth()>=24) {
            // I have no idea why "-8" is needed, but I surely know that this
            // ugly hack prevents QGraphicsView from showing about 8px wide
            // border on the bottom and on the right
            ui->image->setSceneRect(0, 0, image.width()-8, image.height()-8);
            scene.addPixmap(QPixmap::fromImage(image));
            ui->image->setScene(&scene);
            ui->statusBar->showMessage(tr("Loaded %1").arg(file_name));

            ui->btnEncryptDecrypt->setEnabled(true);

        } else {
            ui->statusBar->showMessage(tr("Cannot load %1 - too little depth").arg(file_name));
        }
        // set directory==filename.directory
    }
}

void MainWindow::on_btnSave_clicked()
{
    QString file_name = QFileDialog::getSaveFileName(this, tr("Save image"),
        directory, tr("Bitmaps (*.bmp)"));

    if (file_name.length()) {
        if (image.save(file_name)) {
            ui->statusBar->showMessage(tr("Saved %1").arg(file_name));
        } else {
            ui->statusBar->showMessage(tr("Cannot save %1").arg(file_name));
        }
    }
}

void MainWindow::on_btnEncryptDecrypt_clicked()
{
    XORImage x(512, image);

    if (calculated) {
        x.setNumber(ui->webcam->getValue());
        //ui->statusBar->showMessage(QString("%1").arg(ui->webcam->getValue()));
    } else {
        x.setNumber(ui->sbNumber->value());
    }

    if (action == ENCRYPTION) {
        QString t1 = ui->text->toPlainText();
        t1.truncate(512);
        x.setText(t1);
        ui->text->setPlainText(t1);
        x.write();
        scene.addPixmap(QPixmap::fromImage(image));
        ui->image->setScene(&scene);

        ui->statusBar->showMessage(tr("Encryption done"));
    } else {
        x.read();
        ui->text->setPlainText(x.getText());

        ui->statusBar->showMessage(tr("Decryption done"));
    }
    //ui->statusBar->showMessage(QString("%1").arg(x.getError()));

    switch (x.getError()) {
    case 0:
        // no errors
        ui->btnSave->setEnabled(true);
        break;
    case 1:
        // image bad format
        ui->statusBar->showMessage(tr("Input image has bad format"));
        break;
    case 2:
        // text too long
        ui->statusBar->showMessage(tr("Input text is too long"));
        break;
    case 3:
        // image too small
        ui->statusBar->showMessage(tr("Input image is too small. Should be at least 46*46px"));
        break;
    case 4:
        // number not set
        ui->statusBar->showMessage(tr("Input number is not set"));
        break;
    }
}

void MainWindow::on_text_textChanged()
{
    QString t = ui->text->toPlainText();
    if (t.length() > 512) {
        ui->statusBar->showMessage(tr("Too much characters! The text will be stripped to 512 chars"));
    } else if (t.contains(QRegExp("[^abcdefghijklmnopqrstuvwyxz .,:;]+", Qt::CaseInsensitive, QRegExp::RegExp2))) {
        ui->statusBar->showMessage(tr("The text contains disallowed characters!"));
    } else {
        ui->statusBar->clearMessage();
    }
}
