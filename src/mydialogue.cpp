#include "mydialogue.h"

MyDialog::MyDialog(QWidget *parent) : QDialog(parent) {
    QWidget *firstPage = new QWidget;
    QLabel *instructionLabel = new QLabel(tr("Instruction for user"));
    QLineEdit *userNameLineEdit = new QLineEdit;
    QPushButton *page2PushButton = new QPushButton(tr("Page 2"));
    QVBoxLayout *firstPageLayout = new QVBoxLayout(firstPage); // automatically set the layout on the widget
    firstPageLayout->addWidget(instructionLabel);
    firstPageLayout->addWidget(userNameLineEdit);
    firstPageLayout->addWidget(page2PushButton);

    // Create second widget
    QWidget *secondPage = new QWidget;
    // QLineEdit *firstNameLineEdit = new QLineEdit;
    QLineEdit *lastNameLineEdit = new QLineEdit;
    QPushButton *endPushButton = new QPushButton(tr("End"));
    QVBoxLayout *secondPageLayout = new QVBoxLayout(secondPage);
    secondPageLayout->addWidget(firstPage);
    secondPageLayout->addWidget(lastNameLineEdit);
    secondPageLayout->addWidget(endPushButton);

    _stackedWidget = new QStackedWidget;
    _stackedWidget->addWidget(firstPage);
    _stackedWidget->addWidget(secondPage);

    connect(page2PushButton, &QPushButton::clicked, this, &MyDialog::goToPage2);
}

void MyDialog::goToPage2()
{
   _stackedWidget->setCurrentIndex(1);
}

