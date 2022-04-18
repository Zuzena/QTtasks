#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myclockwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->Reset,SIGNAL(released()),this,SLOT(reset()));
    connect(ui->SetDateTime,SIGNAL(released()),this,SLOT(customDateTime()));

    myClock.paintEvent(nullptr);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reset(){
   myClock.toggleMode(true);
}

void MainWindow::customDateTime(){
    myClock.toggleMode(false);
}

