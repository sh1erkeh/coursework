#include "login-window.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char** argv) {
    QApplication a(argc, argv);

    LoginWindow loginWindow;
    loginWindow.show();

    return a.exec();
}
