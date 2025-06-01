#pragma once

// Widgets
#include <QMainWindow>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QTableWidget>
#include <QHeaderView>

// DataBase
#include <QDir>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

// Debug
#include <QTimer>
#include <QMessageBox>

// Graph Coloring
#include "graph.hpp"
#include "degree-saturation.hpp"
#include "dsatur-util.h"
#include "data-fetcher.h"

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

private slots:
    void onAddInputBoxButtonClicked();
    void onSaveInputsButtonClicked();
    void onResultsButtonClicked();

private:
    Ui::MainWindow* ui;

    // General
    QString login;
    QVector<std::pair<QString, int>> subjectsData;

    // Results page
    QStackedWidget* stackedTables;
    QScrollArea* buttonScrollArea;

    size_t added_input_boxes = 0;
    int group_quantity = 0;

    void initializeDataBase();

    QWidget* createSubjectInputBox();

    void setupResultsPage(const QMap<int, QMap<unsigned, QString>>&, int);
};
