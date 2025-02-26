#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
    class LoginWindow;
}
QT_END_NAMESPACE

class LoginWindow : public QWidget {
    Q_OBJECT
public:
    LoginWindow(QWidget* parent=nullptr);
private slots:
    void onLoginClicked();
    void onRegisterClicked();
private:
    Ui::LoginWindow* ui;
};
