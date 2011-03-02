#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->image, SIGNAL(stateChanged(int)), SLOT(on_image_stateChanged(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if (ui->image->getState() == -1)
    {
        ui->image->startCapturing(0);
        //ui->image->setState(2);
    } else
    {
        ui->image->stopCapturing();
    }

    //ui->image->setState(2);
    ui->image->toggleCapturing();
}

void MainWindow::on_image_stateChanged(int v)
{
    switch (v)
    {
    case -1:
        ui->LState->setText("Uninitialized");
        break;
    case 0:
        ui->LState->setText("Get ready for tracking the object");
        break;
    case 1:
        ui->LState->setText("Selecting tracked object");
        break;
    case 2:
        //ui->LState->setText("Tracking object");
        ui->LState->setText(ui->image->error);
        break;
    }
}
