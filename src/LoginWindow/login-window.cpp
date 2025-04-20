#include "login-window.h"

#include "main-window.h"
#include "registration-window.h"
#include "ui_login-window.h"
#include "usersDB-handler.h"

LoginWindow::LoginWindow(QWidget* parent)
    : QWidget(parent), ui(new Ui::LoginWindow) {
    ui->setupUi(this);
    connect(ui->loginButton, &QPushButton::clicked, this,
            &LoginWindow::onLoginClicked);
    connect(ui->registerButton, &QPushButton::clicked, this,
            &LoginWindow::onRegisterClicked);
}

void LoginWindow::onLoginClicked() {
    QString login = ui->loginEdit->text();
    QString password = ui->passwordEdit->text();

    bool flag = false;
    try {
        flag = DatabaseManager::instance().validateUser(login, password);
    } catch (...) {
        QMessageBox::warning(this, "Login Failed", "Unknown reason");
    }

    if (flag) {
        auto mainWindow = new MainWindow(login);
        mainWindow->show();
        this->close();
    } else {
        QMessageBox::warning(this, "Login Failed",
                             "Incorrect login or password.");
    }
}

void LoginWindow::onRegisterClicked() {
    auto regWindow = new RegistrationWindow();
    regWindow->show();
}
