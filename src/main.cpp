#include "../include/users-db-handler.hpp"
#include "../ui/log-window.hpp"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char** argv) {
    QApplication a(argc, argv);

    LoginWindow loginWindow;
    loginWindow.show();

    return a.exec();
}
