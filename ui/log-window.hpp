#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

#include "reg-window.hpp"
#include "mainwindow.h"
#include "../include/users-db-handler.hpp"

class LoginWindow : public QWidget {
    Q_OBJECT
public:
    LoginWindow(QWidget *parent = nullptr)
            : QWidget(parent) {
        setupUI();
    }

private slots:
    void onLoginClicked() {
        QString login = loginEdit->text();
        QString password = passwordEdit->text();

        try {
            DatabaseManager::instance().validateUser(login, password);
            MainWindow *mainWindow = new MainWindow();
            mainWindow->show();
            this->close();
        } catch (...) {
            QMessageBox::warning(this, "Login Failed", "Invalid login or password.");
        }
    }

    void onRegisterClicked() {
        RegistrationWindow* regWindow = new RegistrationWindow();
        regWindow->show();
    }
private:
    void setupUI() {
        setWindowTitle("Login");
        setFixedSize(300, 200);

        QLabel *loginLabel = new QLabel("Login:", this);
        loginEdit = new QLineEdit(this);

        QLabel *passwordLabel = new QLabel("Password:", this);
        passwordEdit = new QLineEdit(this);
        passwordEdit->setEchoMode(QLineEdit::Password);

        QPushButton *loginButton = new QPushButton("Login", this);
        QPushButton *registerButton = new QPushButton("Register", this);

        connect(loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);
        connect(registerButton, &QPushButton::clicked, this, &LoginWindow::onRegisterClicked);

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(loginLabel);
        layout->addWidget(loginEdit);
        layout->addWidget(passwordLabel);
        layout->addWidget(passwordEdit);
        layout->addWidget(loginButton);
        layout->addWidget(registerButton);
    }

    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;
};
