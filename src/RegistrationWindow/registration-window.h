#pragma once

#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class RegistrationWindow;
}
QT_END_NAMESPACE

class RegistrationWindow : public QWidget {
    Q_OBJECT
public:
    explicit RegistrationWindow(QWidget* parent = nullptr);
private slots:
    void onRegisterClicked();

private:
    Ui::RegistrationWindow* ui;
};
