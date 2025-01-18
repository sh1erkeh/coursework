#pragma once

#include <QtWidgets/QDialog>
#include <QtWidgets/QWidget>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QApplication>
#include <QtWidgets/qmainwindow.h>

class MyDialog : public QDialog {
Q_OBJECT

public:
    explicit MyDialog(QWidget *parent=0);

private slots:
    void goToPage2();

private:
    QStackedWidget *_stackedWidget;
};

