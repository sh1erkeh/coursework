#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QVBoxLayout>

#include "usersDB-handler.h"

class RegistrationWindow : public QWidget {
    Q_OBJECT
public:
    RegistrationWindow(QWidget *parent = nullptr)
            : QWidget(parent) {
        setupUI();
    }

private slots:
    void onRegisterClicked() {
        QString login = loginEdit->text();
        QString password = passwordEdit->text();

        if (login.isEmpty() || password.isEmpty()) {
            QMessageBox::warning(this, "Registration Failed", "Please fill in all fields.");
            return;
        }

        try {
            DatabaseManager::instance().registerUser(login, password);
            QMessageBox::information(this, "Success", "Registration successful!");
            this->close();
        } catch (...) {
            QMessageBox::warning(this, "Registration Failed", "User already exists or database error.");
        }
    }

private:
    void setupUI() {
        setWindowTitle("Register");
        setFixedSize(300, 200);

        QLabel *loginLabel = new QLabel("Login:", this);
        loginEdit = new QLineEdit(this);

        QLabel *passwordLabel = new QLabel("Password:", this);
        passwordEdit = new QLineEdit(this);
        passwordEdit->setEchoMode(QLineEdit::Password);

        QPushButton *registerButton = new QPushButton("Register", this);

        connect(registerButton, &QPushButton::clicked, this, &RegistrationWindow::onRegisterClicked);

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(loginLabel);
        layout->addWidget(loginEdit);
        layout->addWidget(passwordLabel);
        layout->addWidget(passwordEdit);
        layout->addWidget(registerButton);
    }

    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;
};
