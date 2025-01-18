#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("Something Title"));

    createFormInterior();
}

MainWindow::~MainWindow()
{   
}

void MainWindow::createFormInterior()
{
    QWidget * wgt = new QWidget(this);
    setCentralWidget(wgt);
}
