#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QComboBox>
#include <QWidget>
#include <QVBoxLayout>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , row(5), col(0)
{
    ui->setupUi(this);
    switch_1 = ui->pushButton;
    show_1 = ui->show_3;
    switch_2 = ui->pushButton_2;
    show_2 = ui->show_4;
    switch_3 = ui->pushButton_3;
    show_3 = ui->show_5;
    switch_4 = ui->pushButton_4;
    show_4 = ui->show_6;
    show_2->hide();
    show_3->hide();
    show_4->hide();
    ui->widget_5->hide();
    ui->widget_3->show();
    ui->widget_8->show();
    ui->widget_6->hide();
    ui->widget_9->hide();
    switch_1->setStyleSheet("QPushButton {""background-color: rgb(40,40,40);"
                            "border-top-right-radius: 15px;"
                            "border-top-left-radius: 15px;""}");
    switch_2->setStyleSheet("QPushButton {""background-color: rgb(60,60,60);"
                            "border-top-right-radius: 15px;"
                            "border-top-left-radius: 15px;""}");
    switch_3->setStyleSheet("QPushButton {""background-color: rgb(60,60,60);"
                            "border-top-right-radius: 15px;"
                            "border-top-left-radius: 15px;""}");
    switch_4->setStyleSheet("QPushButton {""background-color: rgb(60,60,60);"
                            "border-top-right-radius: 15px;"
                            "border-top-left-radius: 15px;""}");
    connect(switch_1, &QPushButton::clicked, this, &MainWindow::onSwitch1Clicked);
    connect(switch_2, &QPushButton::clicked, this, &MainWindow::onSwitch2Clicked);
    connect(switch_3, &QPushButton::clicked, this, &MainWindow::onSwitch3Clicked);
    connect(switch_4, &QPushButton::clicked, this, &MainWindow::onSwitch4Clicked);
    connect(ui->pushButton_12, &QPushButton::clicked, this, &MainWindow::onButton12Clicked);
    connect(ui->pushButton_13, &QPushButton::clicked, this, &MainWindow::onButton13Clicked);
    connect(ui->pushButton_16, &QPushButton::clicked, this, &MainWindow::onButton16Clicked);
    grid_layout=qobject_cast<QGridLayout*>(ui->show_6->layout());
    connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::creating_new_subject);
    // Изначально скрываем все виджеты

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::creating_new_subject(){
    QWidget *new_widget = new QWidget;
    new_widget->setStyleSheet("background-color:rgb(80,80,80);"
                              "border-radius: 15px;");
    QPlainTextEdit *input_subj = new QPlainTextEdit(new_widget);
    new_widget->setMaximumHeight(50);
    input_subj->setStyleSheet("background-color:rgb(255,255,255);"
                              "border-radius: 10px;");
    input_subj->setMaximumHeight(40);
    QVBoxLayout *layout = new QVBoxLayout(new_widget);
    layout->addWidget(input_subj);
    new_widget->setLayout(layout);
    grid_layout->addWidget(new_widget,row,col);
    layout->setContentsMargins(5,5,5,5);
    row++;

}

// Слот для кнопки switch_1
void MainWindow::onSwitch1Clicked()
{
    hideAllWidgets();  // Скрываем все виджеты
    show_1->show();  // Показываем виджет show_1
    switch_1->setStyleSheet("QPushButton {""background-color: rgb(40,40,40);"
                            "border-top-right-radius: 15px;"
                            "border-top-left-radius: 15px;""}");
    switch_2->setStyleSheet("QPushButton {""background-color: rgb(60,60,60);"
                            "border-top-right-radius: 15px;"
                            "border-top-left-radius: 15px;""}");
    switch_3->setStyleSheet("QPushButton {""background-color: rgb(60,60,60);"
                            "border-top-right-radius: 15px;"
                            "border-top-left-radius: 15px;""}");
    switch_4->setStyleSheet("QPushButton {""background-color: rgb(60,60,60);"
                            "border-top-right-radius: 15px;"
                            "border-top-left-radius: 15px;""}");
}

// Слот для кнопки switch_2
void MainWindow::onSwitch2Clicked()
{
    hideAllWidgets();  // Скрываем все виджеты
    show_2->show();  // Показываем виджет show_2
    ui->plainTextEdit_13->setEnabled(true);
    ui->plainTextEdit_8->setEnabled(true);
    ui->plainTextEdit_9->setEnabled(true);
    switch_1->setStyleSheet("QPushButton {""background-color: rgb(60,60,60);"
                            "border-top-right-radius: 15px;"
                            "border-top-left-radius: 15px;""}");
    switch_2->setStyleSheet("QPushButton {""background-color: rgb(40,40,40);"
                            "border-top-right-radius: 15px;"
                            "border-top-left-radius: 15px;""}");
    switch_3->setStyleSheet("QPushButton {""background-color: rgb(60,60,60);"
                            "border-top-right-radius: 15px;"
                            "border-top-left-radius: 15px;""}");
    switch_4->setStyleSheet("QPushButton {""background-color: rgb(60,60,60);"
                            "border-top-right-radius: 15px;"
                            "border-top-left-radius: 15px;""}");
}

// Слот для кнопки switch_3
void MainWindow::onSwitch3Clicked()
{
    hideAllWidgets();  // Скрываем все виджеты
    show_3->show();  // Показываем виджет show_3
    ui->plainTextEdit_10->setEnabled(true);
    ui->plainTextEdit_11->setEnabled(true);
    ui->plainTextEdit_12->setEnabled(true);
    ui->plainTextEdit_10->setFocus();
    switch_1->setStyleSheet("QPushButton {""background-color: rgb(60,60,60);"
                            "border-top-right-radius: 15px;"
                            "border-top-left-radius: 15px;""}");
    switch_2->setStyleSheet("QPushButton {""background-color: rgb(60,60,60);"
                            "border-top-right-radius: 15px;"
                            "border-top-left-radius: 15px;""}");
    switch_3->setStyleSheet("QPushButton {""background-color: rgb(40,40,40);"
                            "border-top-right-radius: 15px;"
                            "border-top-left-radius: 15px;""}");
    switch_4->setStyleSheet("QPushButton {""background-color: rgb(60,60,60);"
                            "border-top-right-radius: 15px;"
                            "border-top-left-radius: 15px;""}");

}

// Слот для кнопки switch_4
void MainWindow::onSwitch4Clicked()
{
    hideAllWidgets();  // Скрываем все виджеты
    show_4->show();  // Показываем виджет show_4
    ui->plainTextEdit->setEnabled(true);
    ui->plainTextEdit->setFocus();
    switch_1->setStyleSheet("QPushButton {""background-color: rgb(60,60,60);"
                            "border-top-right-radius: 15px;"
                            "border-top-left-radius: 15px;""}");
    switch_2->setStyleSheet("QPushButton {""background-color: rgb(60,60,60);"
                            "border-top-right-radius: 15px;"
                            "border-top-left-radius: 15px;""}");
    switch_3->setStyleSheet("QPushButton {""background-color: rgb(60,60,60);"
                            "border-top-right-radius: 15px;"
                            "border-top-left-radius: 15px;""}");
    switch_4->setStyleSheet("QPushButton {""background-color: rgb(40,40,40);"
                            "border-top-right-radius: 15px;"
                            "border-top-left-radius: 15px;""}");
}

// Метод для скрытия всех виджетов
void MainWindow::hideAllWidgets()
{
    show_1->hide();
    show_2->hide();
    show_3->hide();
    show_4->hide();
}
void MainWindow::onButton12Clicked()
{
    ui->widget_3->hide();
    ui->widget_8->hide();
    ui->widget->hide();
    ui->widget_5->show();
    ui->widget_9->show();
    ui->widget_6->show();
}
void MainWindow::onButton13Clicked()
{
    ui->widget_3->show();
    ui->widget->show();
    ui->widget_5->hide();
    ui->widget_8->show();
    ui->widget_9->hide();
    ui->widget_6->hide();

}

void MainWindow::onButton16Clicked()
{
    close();

}
