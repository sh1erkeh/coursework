#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QVBoxLayout>

class RegistrationWindow : public QWidget {
    Q_OBJECT
public:
    RegistrationWindow(QWidget* parent = nullptr);
private slots:
    void onRegisterClicked(); 
private:
    void setupUI();

    QLineEdit* loginEdit;
    QLineEdit* passwordEdit;
};
