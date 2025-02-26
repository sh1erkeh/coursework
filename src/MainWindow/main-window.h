#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QComboBox>
#include <QPlainTextEdit>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QStackedWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QSpinBox>
#include <QMap>
<<<<<<< HEAD:ui/mainwindow.h
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
||||||| 7ed7721:ui/mainwindow.h
#include <vector>
=======

>>>>>>> main:src/MainWindow/main-window.h
QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QString& user_login, QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void onSwitch4Clicked(const QString &buttonText);
    void onButton12Clicked();
    void onButton13Clicked();
    void onButton16Clicked();
    void addNewWidget(QVBoxLayout *scrollLayout, QScrollArea *scrollArea, QPushButton *pushButton_6);
    void switchPage();
<<<<<<< HEAD:ui/mainwindow.h
    void on_saveButton_clicked();

||||||| 7ed7721:ui/mainwindow.h

=======
>>>>>>> main:src/MainWindow/main-window.h
private:
    QString user_login;

    Ui::MainWindow *ui;
    QPushButton *switch_1;
    QPushButton *switch_2;
    QPushButton *switch_3;
    QPushButton *switch_4;
    QWidget *show_1;
    QWidget *show_2;
    QWidget *show_3;
    QWidget *show_4;
    QWidget *new_widget;
    QWidget *scrollWidget;
    QComboBox *comboBox;
    QPlainTextEdit *input_subj;
    QGridLayout *grid_layout;
    QVBoxLayout *layout;
    QSpacerItem *spacer;
    QSpacerItem *spacer1;
    QScrollArea *scrollArea;
    QVBoxLayout *scrollLayout;
    QHBoxLayout *widget_spinbox_layout;
    QHBoxLayout *newWidgetLayout;
    QWidget *widget_spinbox;
    QSpinBox *spinbox;
    QPushButton *new_switch;
    QWidget *switch_scroll_widget;
    QHBoxLayout *switch_layout;
    QSpacerItem *spacer_switch;
    QVBoxLayout *buttonsLayout;
    QStackedWidget *stackedWidget;
    QMap<QPushButton*, int> buttonToIndex;
    QPushButton *push_button_pairs;
    QScrollArea *page_scroll_area;
    QPushButton *page_button_add;
    QVBoxLayout *page_layout;
    QWidget *page_scrollWidget;
    QSpacerItem *spacer2;
    QSpacerItem *spacer_4;
    QVBoxLayout *layout1;
    QVBoxLayout *layout2;
    QWidget *firstPage1;
    QWidget *firstPage;
    QWidget *scrollWidget_4;
    QVBoxLayout* scrollLayout_4;
    QWidget *container;
    QPlainTextEdit *textEdit;
    QSpinBox *textSpin;
    QList<QWidget *> containers;
    QString *subject_names;
    QString *subject_spins;
    QWidget *page;
    QStringList subjectList;
    QStringList amountList;


    int row,col, count=2;
};

#endif // MAINWINDOW_H
