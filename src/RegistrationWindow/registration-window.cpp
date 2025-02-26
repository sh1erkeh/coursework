#include "registration-window.h"
#include "usersDB-handler.h"

RegistrationWindow::RegistrationWindow(QWidget* parent)
        : QWidget(parent) 
    {
        setupUI();
    }

void RegistrationWindow::onRegisterClicked() {
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

void RegistrationWindow::setupUI() {
    setWindowTitle("Register");
    setFixedSize(400, 200);

    QLabel* loginLabel = new QLabel("Login:", this);
    loginEdit = new QLineEdit(this);

    QLabel* passwordLabel = new QLabel("Password:", this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);

    QPushButton* registerButton = new QPushButton("Register", this);

    connect(registerButton, &QPushButton::clicked, this, &RegistrationWindow::onRegisterClicked);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(loginLabel);
    layout->addWidget(loginEdit);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordEdit);
    layout->addWidget(registerButton);
}

