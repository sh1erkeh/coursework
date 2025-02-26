#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui {
    class RegistrationWindow;
}
QT_END_NAMESPACE

class RegistrationWindow : public QWidget {
    Q_OBJECT
public:
    RegistrationWindow(QWidget* parent = nullptr);
private slots:
    void onRegisterClicked(); 
private:
    Ui::RegistrationWindow* ui;
};
