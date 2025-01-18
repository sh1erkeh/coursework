#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createFormInterior();
};

#endif // MAINWINDOW_H
