#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QComboBox>
#include <QDir>
#include <QGraphicsDropShadowEffect>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMap>
#include <QPalette>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QScreen>
#include <QScrollArea>
#include <QScrollBar>
#include <QSpacerItem>
#include <QSpinBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStackedWidget>
#include <QStyle>
#include <QVBoxLayout>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(const QString& login, QWidget* parent = nullptr);
    ~MainWindow() override;
    void centerWindow();
private slots:
    void onSwitch4Clicked(const QString& buttonText);
    void onButton12Clicked();
    void onButton13Clicked();
    void onButton16Clicked();
    void addNewWidget(QVBoxLayout* scrollLayout, QScrollArea* scrollArea,
                      QPushButton* pushButton_6);
    void switchPage();
    void on_saveButton_clicked();

private:
    Ui::MainWindow* ui;
    QString login;

    QPushButton* switch_1;
    QPushButton* switch_2;
    QPushButton* switch_3;
    QPushButton* switch_4;

    QWidget* show_1;
    QWidget* show_2;
    QWidget* show_3;
    QWidget* show_4;

    QWidget* new_widget;
    QWidget* scrollWidget;

    QComboBox* comboBox;
    QPlainTextEdit* input_subj;
    QGridLayout* grid_layout;
    QVBoxLayout* layout;
    QSpacerItem* spacer;
    QSpacerItem* spacer1;
    QScrollArea* scrollArea;
    QVBoxLayout* scrollLayout;
    QHBoxLayout* widget_spinbox_layout;
    QHBoxLayout* newWidgetLayout;
    QWidget* widget_spinbox;
    QSpinBox* spinbox;
    QPushButton* new_switch;
    QWidget* switch_scroll_widget;
    QHBoxLayout* switch_layout;
    QSpacerItem* spacer_switch;
    QVBoxLayout* buttonsLayout;
    QStackedWidget* stackedWidget;
    QMap<QPushButton*, int> buttonToIndex;
    QMap<QPushButton*, int> checking_label;
    QPushButton* push_button_pairs;
    QScrollArea* page_scroll_area;
    QPushButton* page_button_add;
    QVBoxLayout* page_layout;
    QWidget* page_scrollWidget;
    QSpacerItem* spacer2;
    QSpacerItem* spacer_4;
    QVBoxLayout* layout1;
    QVBoxLayout* layout2;
    QWidget* firstPage1;
    QWidget* firstPage;
    QWidget* scrollWidget_4;
    QVBoxLayout* scrollLayout_4;
    QWidget* container;
    QPlainTextEdit* textEdit;
    QSpinBox* textSpin;
    QList<QWidget*> containers;
    QString* subject_names;
    QString* subject_spins;
    QWidget* page;
    QStringList subjectList;
    QStringList amountList;
    QPalette* palette;
    QPushButton* page_button_save;
    QGraphicsDropShadowEffect* effect;
    QWidget* group;
    QGridLayout* group_layout;
    QLabel* group_label;
    QGraphicsDropShadowEffect* effect1;
    QSpacerItem* spacer_button;
    QWidget* widget_tip;
    QLabel* amount;
    QLabel* pairs;
    QHBoxLayout* tip_layout;
    QSpacerItem* gap;
    QSpacerItem* gap1;
    QSpacerItem* spacer3;

    int row = 0, col, count = 2;
};

#endif  // MAINWINDOW_H
