#include "registration-window.h"

#include "ui_registration-window.h"
#include "usersDB-handler.h"

RegistrationWindow::RegistrationWindow(QWidget* parent)
    : QWidget(parent), ui(new Ui::RegistrationWindow) {
    ui->setupUi(this);
    connect(ui->registerButton, &QPushButton::clicked, this,
            &RegistrationWindow::onRegisterClicked);
}

void RegistrationWindow::onRegisterClicked() {
    QString login = ui->loginEdit->text();
    QString password = ui->passwordEdit->text();

    if (login.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Registration Failed",
                             "Please fill in all fields.");
        return;
    }

    try {
        DatabaseManager::instance().registerUser(login, password);
        QMessageBox::information(this, "Success", "Registration successful!");
        this->close();
    } catch (...) {
        QMessageBox::warning(this, "Registration Failed",
                             "User already exists or database error.");
    }
}
