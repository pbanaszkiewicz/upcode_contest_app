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
    if (ui->image->getState() == -2)
    {
        //ui->image->startCapturing(0);
        ui->image->setState(-1); // let's initialize
    } else
    {
        ui->image->setState(3); // it's 'interruping'
    }
    // NOTE: for "reset" button, setState(-1)

    //ui->image->setState(2);
    //ui->image->toggleCapturing();
}

void MainWindow::on_image_stateChanged(int v)
{
    switch (v)
    {
    case -2:
        ui->LState->setText("Uninitialized");
        break;
    case -1:
        ui->LState->setText("Initialized");
        break;
    case 0:
        ui->LState->setText("Select object to track");
        break;
    case 1:
        ui->LState->setText("Tracking");
        break;
    case 2:
        ui->LState->setText("Finished :)");
        break;
    case 3:
        ui->LState->setText("Interrupted :(");
        break;
    }
}
