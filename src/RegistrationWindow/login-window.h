#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

class LoginWindow : public QWidget {
    Q_OBJECT
public:
    LoginWindow(QWidget* parent=nullptr);
private slots:
    void onLoginClicked();
    void onRegisterClicked();
private:
    void setupUI();

    QLineEdit* loginEdit;
    QLineEdit* passwordEdit;
};
