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
    // max = 2147483647
    // min = 8196
    qsrand(time(NULL));
    ui->sbNumber->setValue(qrand()-(RAND_MAX-2147483647-8196)+(8196));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnPlayPause_clicked()
{
    if (ui->webcam->getState() == -2 || ui->webcam->getState() == 3) {
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
    ui->sbNumber->setEnabled(true);
    ui->btnFinished->setEnabled(false);
    // what about the number?
    // we cannot set sbNumber.value to that number (int vs unsigned long long)
    //calculated = true = ui->webcam->getState()==2;
    //ui->statusBar->showMessage(QString("%1").arg(sizeof ui->webcam->getValue()));
}

void MainWindow::on_webcam_stateChanged(int v)
{
    ui->btnFinished->setEnabled(false);
    switch (v) {
    case -2:
        ui->statusBar->showMessage("Uninitialized");
        break;
    case -1:
        ui->statusBar->showMessage("Initialized");
        break;
    case 0:
        ui->statusBar->showMessage("Select object to track");
        break;
    case 1:
        ui->statusBar->showMessage("Tracking");
        ui->btnFinished->setEnabled(true);
        break;
    case 2:
        ui->statusBar->showMessage("Finished :)");
        //if ()
        break;
    case 3:
        ui->statusBar->showMessage("Interrupted :(");
        break;
    }
}

void MainWindow::on_rbEncryption_clicked()
{
    action = ENCRYPTION;
    ui->btnEncryptDecrypt->setText(tr("Encrypt"));
    ui->text->setReadOnly(false);
}

void MainWindow::on_rbDecryption_clicked()
{
    action = DECRYPTION;
    ui->btnEncryptDecrypt->setText(tr("Decrypt"));
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
