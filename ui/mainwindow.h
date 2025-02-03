#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QComboBox>
#include <QPlainTextEdit>
#include <QGridLayout>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { 
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
private slots:
    void onSwitch1Clicked();
    void onSwitch2Clicked();
    void onSwitch3Clicked();
    void onSwitch4Clicked();
    void onButton12Clicked();
    void onButton13Clicked();
    void onButton16Clicked();
    void hideAllWidgets();
    void creating_new_subject();
private:
    Ui::MainWindow* ui;
    QPushButton* switch_1;
    QPushButton* switch_2;
    QPushButton* switch_3;
    QPushButton* switch_4;
    QWidget* show_1;
    QWidget* show_2;
    QWidget* show_3;
    QWidget* show_4;
    QWidget* new_widget;
    QComboBox* comboBox;
    QPlainTextEdit* input_subj;
    QGridLayout* grid_layout;
    QVBoxLayout* layout;
    int row,col;
};

#endif // MAINWINDOW_H
