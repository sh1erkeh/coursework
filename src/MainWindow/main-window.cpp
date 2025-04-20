#include "main-window.h"

#include <QApplication>
#include <QComboBox>
#include <QDebug>
#include <QDir>
#include <QGraphicsDropShadowEffect>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
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
#include <QStyle>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>
#include <stdexcept>

#include "data-fetcher.h"
#include "degree-saturation.hpp"
#include "dsatur-util.h"
#include "graph.hpp"
#include "results-printer.h"
// #include "tabu-search.hpp"
// #include "tabuSearch-util.h"
#include "ui_main-window.h"

MainWindow::MainWindow(const QString& login, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->login = login;

    ui->widget_5->hide();
    ui->widget_3->show();
    ui->widget_8->show();
    ui->widget_9->hide();
    ui->widget_6->hide();
    int row = 0;

    QDir dir;
    QString path = dir.currentPath() + "/database";

    if (!dir.exists(path)) {
        dir.mkpath(path);
    }

    QString dbPath = path + '/' + login + "data.db";

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", dbPath);

    if (!db.open()) {
        throw std::runtime_error("Error creating DB: " +
                                 db.lastError().text().toStdString());
    }

    QSqlQuery query;

    QString createTableQuery =
        "CREATE TABLE IF NOT EXISTS GROUPS ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "amount INT, "
        "name TEXT, "
        "subjects TEXT,"
        "quantities TEXT)";

    if (!query.exec(createTableQuery)) {
        throw std::runtime_error("Error creating table: " +
                                 query.lastError().text().toStdString());
    } else {
        qDebug() << "Table GROUPS successfulliy initialized";
    }

    QString createTableSubjects =
        "CREATE TABLE IF NOT EXISTS SUBJECTS ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT UNIQUE)";

    if (!query.exec(createTableSubjects)) {
        throw std::runtime_error("Error creating table: " +
                                 query.lastError().text().toStdString());
    } else {
        qDebug() << "Table SUBJECTS successfulliy initialized";
    }

    connect(ui->pushButton_12, &QPushButton::clicked, this,
            &MainWindow::onButton12Clicked);
    connect(ui->pushButton_13, &QPushButton::clicked, this,
            &MainWindow::onButton13Clicked);
    connect(ui->pushButton_16, &QPushButton::clicked, this,
            &MainWindow::onButton16Clicked);

    auto* effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(10);
    effect->setOffset(0);
    effect->setColor(QColor(0, 0, 0, 100));
    ui->widget_20->setGraphicsEffect(effect);

    auto* effect1 = new QGraphicsDropShadowEffect;
    effect1->setBlurRadius(10);
    effect1->setOffset(0);
    effect1->setColor(QColor(0, 0, 0, 100));
    ui->widget_13->setGraphicsEffect(effect1);

    QWidget* scrollWidget = ui->scrollArea->widget();
    if (!scrollWidget) {
        scrollWidget = new QWidget;
        ui->scrollArea->setWidget(scrollWidget);
        ui->scrollArea->setWidgetResizable(true);
    }

    auto* scrollLayout = qobject_cast<QVBoxLayout*>(scrollWidget->layout());
    if (!scrollLayout) {
        scrollLayout = new QVBoxLayout(scrollWidget);
        scrollWidget->setLayout(scrollLayout);
    }
    ui->switch_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    spacer =
        new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    scrollLayout->addItem(spacer);

    QWidget* firstPage = ui->stackedWidget->widget(0);
    auto* layout1 = new QVBoxLayout(firstPage);
    layout1->addWidget(ui->show_8);
    layout1->setContentsMargins(0, 0, 0, 0);

    QWidget* firstPage1 = ui->stackedWidget->widget(1);
    auto* layout2 = new QVBoxLayout(firstPage1);
    layout2->setContentsMargins(0, 0, 0, 0);
    layout2->addWidget(ui->show_6);

    buttonToIndex[ui->pushButton_4] = 0;
    buttonToIndex[ui->pushButton_17] = 1;

    int count = 3;
    connect(ui->pushButton_5, &QPushButton::clicked, this,
            [this, count]() mutable {
                onSwitch4Clicked(QString::number(count));
                count++;
            });

    QWidget* scrollWidget_4 = ui->scrollArea_3->widget();
    if (!scrollWidget_4) {
        scrollWidget_4 = new QWidget;
        ui->scrollArea_3->setWidget(scrollWidget_4);
        ui->scrollArea_3->setWidgetResizable(true);
    }

    auto* scrollLayout_4 = qobject_cast<QVBoxLayout*>(scrollWidget_4->layout());
    if (!scrollLayout_4) {
        scrollLayout_4 = new QVBoxLayout(scrollWidget_4);
        scrollWidget_4->setLayout(scrollLayout_4);
    }

    spacer_4 =
        new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    scrollLayout_4->addItem(spacer_4);

    ui->switch_area->horizontalScrollBar()->setValue(
        ui->switch_area->horizontalScrollBar()->maximum());

    ui->scrollArea_3->verticalScrollBar()->setValue(
        ui->scrollArea_3->verticalScrollBar()->maximum());
    ui->scrollArea->verticalScrollBar()->setValue(
        ui->scrollArea->verticalScrollBar()->maximum());

    connect(ui->pushButton_6, &QPushButton::clicked, this,
            [this, scrollLayout]() {
                addNewWidget(scrollLayout, this->ui->scrollArea,
                             this->ui->pushButton_6);
            });
    connect(ui->pushButton_14, &QPushButton::clicked, this,
            [this, scrollLayout_4]() {
                addNewWidget(scrollLayout_4, this->ui->scrollArea_3,
                             this->ui->pushButton_14);
            });

    connect(ui->pushButton_4, &QPushButton::clicked, this,
            &MainWindow::switchPage);
    connect(ui->pushButton_17, &QPushButton::clicked, this,
            &MainWindow::switchPage);
    connect(ui->saveButton, &QPushButton::clicked, this,
            &MainWindow::on_saveButton_clicked);
    connect(ui->pushButton_15, &QPushButton::clicked, this,
            &MainWindow::on_saveButton_clicked);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_saveButton_clicked() {
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        throw std::runtime_error("Database is not open");
    }

    QSqlQuery query(db);
    QSqlQuery query1(db);
    QSqlQuery getIdQuery(db);

    if (!query.exec("DELETE FROM GROUPS")) {
        throw std::runtime_error("Could not clear database: " +
                                 query.lastError().text().toStdString());
    } else {
        qDebug() << "GROUPS table has been cleared";
    }

    query.clear();
    query.prepare(
        "INSERT INTO GROUPS (amount, name, subjects, quantities) VALUES "
        "(:amount, :name, :subjects, :quantities)");
    query1.prepare("INSERT INTO SUBJECTS (name) VALUES (:name)");

    int amountGroup = 0;
    int pageCount = ui->stackedWidget->count();

    for (int i = 0; i + 1 < pageCount; ++i) {
        QWidget* page = ui->stackedWidget->widget(i);

        QList<QPlainTextEdit*> textEdits =
            page->findChildren<QPlainTextEdit*>();
        QList<QSpinBox*> spinBoxes = page->findChildren<QSpinBox*>();

        QStringList subjectList;
        QStringList amountList;

        amountGroup = spinBoxes[0]->value();
        for (int j = 1; j < textEdits.size(); ++j) {
            QPlainTextEdit* textEdit = textEdits[j];
            QSpinBox* textSpin = spinBoxes[j];

            if (textEdit && textSpin) {
                QString content = textEdit->toPlainText().trimmed();
                int spin = textSpin->value();

                if (content.isEmpty()) {
                    qDebug()
                        << "Subject number " << j << " is empty. Skipping it";
                    continue;
                }

                getIdQuery.prepare(
                    "SELECT id FROM SUBJECTS WHERE name = :name");
                getIdQuery.bindValue(":name", content);

                if (!getIdQuery.exec()) {
                    throw std::runtime_error(
                        "Error finding subject: " +
                        getIdQuery.lastError().text().toStdString());
                }

                if (!getIdQuery.next()) {
                    query1.bindValue(":name", content);
                    if (!query1.exec()) {
                        throw std::runtime_error(
                            "Error saving subject: " +
                            query1.lastError().text().toStdString());
                    }
                }

                subjectList.append(content);
                amountList.append(QString::number(spin));
            }
        }

        if (!subjectList.isEmpty() && !amountList.isEmpty()) {
            qDebug() << "Decided to write page" << i;
            QString subject_list = subjectList.join(",");
            QString amount_list = amountList.join(",");

            query.bindValue(":amount", amountGroup);
            query.bindValue(":name", i);
            query.bindValue(":subjects", subject_list);
            query.bindValue(":quantities", amount_list);

            if (!query.exec()) {
                throw std::runtime_error(
                    "Error saving GROUPS: " +
                    query.lastError().text().toStdString());
            } else {
                qDebug() << "Written data to db";
            }
        } else {
            qDebug() << "Skipped empty page " << i;
        }
    }
}

void MainWindow::addNewWidget(QVBoxLayout* scrollLayout,
                              QScrollArea* scrollArea,
                              QPushButton* pushButton_6) {
    if (row >= 35) {
        return;
    }

    QPalette palette;
    palette.setColor(QPalette::Text, Qt::black);

    auto* newWidget = new QWidget();
    newWidget->setStyleSheet(
        "background-color: rgb(80, 80, 80); border-radius: 15px;");

    auto* textEdit = new QPlainTextEdit(newWidget);
    textEdit->setStyleSheet(
        "background-color: rgb(255, 255, 255); border-radius: 10px;color: "
        "black; padding:7px");
    textEdit->setMinimumHeight(40);

    auto* widget_spinbox = new QWidget();
    widget_spinbox->setStyleSheet(
        "background-color:rgb(200,200,200); border-radius: 10px;");
    widget_spinbox->setFixedSize(50, 40);

    auto* spinbox = new QSpinBox;
    auto* widget_spinbox_layout = new QHBoxLayout(widget_spinbox);
    widget_spinbox_layout->addWidget(spinbox);
    widget_spinbox->setLayout(widget_spinbox_layout);
    widget_spinbox_layout->setContentsMargins(7, 0, 3, 0);

    spinbox->setMinimumHeight(30);
    spinbox->setMinimumWidth(40);
    spinbox->setStyleSheet(ui->spinBox_3->styleSheet());
    spinbox->setRange(1, 10);
    spinbox->setPalette(palette);

    auto* newWidgetLayout = new QHBoxLayout(newWidget);
    auto* spacer_button =
        new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Minimum);
    newWidgetLayout->setContentsMargins(5, 5, 5, 5);
    newWidgetLayout->setSpacing(20);
    newWidgetLayout->addWidget(widget_spinbox);
    newWidgetLayout->addWidget(textEdit);
    newWidget->setLayout(newWidgetLayout);
    newWidget->setFixedHeight(50);

    scrollLayout->setSpacing(0);
    scrollLayout->insertWidget(scrollLayout->indexOf(pushButton_6), newWidget);

    if (checking_label[pushButton_6] == 0 &&
        pushButton_6 != ui->pushButton_14) {
        auto* newWidget1 = new QWidget();
        newWidget1->setStyleSheet(
            "background-color: rgb(80, 80, 80); border-radius: 15px;");

        auto* textEdit1 = new QPlainTextEdit(newWidget1);
        textEdit1->setStyleSheet(
            "background-color: rgb(5, 255, 255); border-radius: 10px;color: "
            "black; padding:7px");
        textEdit1->setPlaceholderText("Выберите количество групп");
        textEdit1->setEnabled(true);
        textEdit1->setMinimumHeight(40);

        auto* widget_spinbox1 = new QWidget();
        widget_spinbox1->setStyleSheet(
            "background-color:rgb(200,200,200); border-radius: 10px;");
        widget_spinbox1->setFixedSize(50, 40);

        auto* spinbox1 = new QSpinBox;
        auto* widget_spinbox_layout1 = new QHBoxLayout(widget_spinbox1);
        widget_spinbox_layout1->addWidget(spinbox1);
        widget_spinbox1->setLayout(widget_spinbox_layout1);
        widget_spinbox_layout1->setContentsMargins(7, 0, 3, 0);

        spinbox1->setMinimumHeight(30);
        spinbox1->setMinimumWidth(40);
        spinbox1->setStyleSheet(ui->spinBox_3->styleSheet());
        spinbox1->setRange(1, 10);
        spinbox1->setPalette(palette);

        auto* newWidgetLayout1 = new QHBoxLayout(newWidget1);
        auto* spacer_button1 =
            new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Minimum);
        newWidgetLayout1->setContentsMargins(5, 5, 5, 5);
        newWidgetLayout1->setSpacing(20);
        newWidgetLayout1->addWidget(widget_spinbox1);
        newWidgetLayout1->addWidget(textEdit1);
        newWidget1->setLayout(newWidgetLayout1);
        newWidget1->setFixedHeight(50);

        scrollLayout->setSpacing(0);
        scrollLayout->insertWidget(scrollLayout->indexOf(newWidget),
                                   newWidget1);
        scrollLayout->insertItem(scrollLayout->indexOf(newWidget),
                                 spacer_button1);

        auto* widget_tip = new QWidget;
        widget_tip->setFixedHeight(30);

        auto* gap = new QSpacerItem(10, 10, QSizePolicy::Expanding,
                                    QSizePolicy::Minimum);
        auto* gap1 =
            new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Minimum);

        auto* amount = new QLabel("Кол-во");
        amount->setStyleSheet("color:rgb(120,120,120);");

        auto* pairs = new QLabel("Название предмета");
        pairs->setStyleSheet("color:rgb(120,120,120);");

        auto* tip_layout = new QHBoxLayout;
        tip_layout->setContentsMargins(4, 5, 4, 0);
        tip_layout->addWidget(amount);
        tip_layout->addItem(gap1);
        tip_layout->addWidget(pairs);
        tip_layout->addItem(gap);
        widget_tip->setLayout(tip_layout);

        checking_label[pushButton_6] = 1;

        scrollLayout->insertWidget(scrollLayout->indexOf(newWidget),
                                   widget_tip);
    }
    scrollLayout->insertItem(scrollLayout->indexOf(pushButton_6),
                             spacer_button);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    row++;
    scrollArea->verticalScrollBar()->setValue(
        scrollArea->verticalScrollBar()->maximum());
}

void MainWindow::onSwitch4Clicked(const QString& buttonText) {
    if (count >= 80) {
        return;
    }

    row = 0;

    auto* new_switch = new QPushButton(buttonText);
    new_switch->setStyleSheet(
        "QPushButton {"
        "background-color: rgb(40,40,40);"
        "border-top-right-radius: 15px;"
        "border-top-left-radius: 15px;"
        "color: white;}"
        "QPushButton:hover {background-color: rgb(60,60,60);}"
        "QPushButton:pressed {background-color: rgb(30,30,30);}");
    new_switch->setFixedSize(60, 40);

    QWidget* switch_scroll_widget = ui->switch_area->widget();
    if (!switch_scroll_widget) {
        switch_scroll_widget = new QWidget;
        ui->switch_area->setWidget(switch_scroll_widget);
        ui->switch_area->setWidgetResizable(true);
    }

    QWidget* original = ui->show_8;
    auto* group = new QWidget;
    auto* page = new QWidget();

    page->setGeometry(original->geometry());
    page->setStyleSheet(original->styleSheet());
    ui->stackedWidget->addWidget(page);

    auto* effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(10);
    effect->setOffset(0);
    effect->setColor(QColor(0, 0, 0, 100));

    group->setFixedSize(100, 30);
    group->setContentsMargins(0, 0, 0, 0);
    group->setGraphicsEffect(effect);
    group->setStyleSheet(ui->widget_13->styleSheet());

    QStringList groupList;
    groupList.append(buttonText);
    groupList.append(" направление");

    auto* group_label = new QLabel(groupList.join(""));
    auto* group_layout = new QGridLayout;
    group_layout->setContentsMargins(0, 0, 0, 0);
    group_layout->addWidget(group_label);
    group_layout->setAlignment(Qt::AlignCenter);
    group->setLayout(group_layout);

    auto* page_scroll_area = new QScrollArea;
    auto* page_button_add = new QPushButton("Добавить пару");
    auto* page_button_save = new QPushButton("Сохранить");

    QWidget* page_scrollWidget = page_scroll_area->widget();
    if (!page_scrollWidget) {
        page_scrollWidget = new QWidget;
        page_scroll_area->setWidget(page_scrollWidget);
        page_scroll_area->setWidgetResizable(true);
    }

    page_scroll_area->setParent(page);
    page_scroll_area->setWidgetResizable(true);
    page_scroll_area->setSizePolicy(QSizePolicy::Minimum,
                                    QSizePolicy::Expanding);
    page_scroll_area->setStyleSheet(ui->scrollArea_3->styleSheet());
    page_scroll_area->setGeometry(ui->scrollArea_3->geometry());

    page_scroll_area->setStyleSheet(
        "QScrollBar:vertical {"
        "    border: none;"
        "    background: #2E2E2E;"
        "    width: 10px;"
        "    margin: 0px 0px 0px 0px;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: #555555;"
        "    min-height: 20px;"
        "    border-radius: 5px;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "    border: none;"
        "    background: none;"
        "    height: 0px;"
        "}"
        "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {"
        "    background: none;"
        "}");

    auto* page_vertical_layout = qobject_cast<QGridLayout*>(page->layout());
    if (!page_vertical_layout) {
        page_vertical_layout = new QGridLayout(page);
        page->setLayout(page_vertical_layout);
    }
    page_vertical_layout->addWidget(page_scroll_area);
    page_vertical_layout->setContentsMargins(20, 20, 20, 20);

    auto* page_layout = qobject_cast<QVBoxLayout*>(page_scrollWidget->layout());
    if (!page_layout) {
        page_layout = new QVBoxLayout(page_scrollWidget);
        page_scrollWidget->setLayout(page_layout);
    }

    page_button_add->setFixedHeight(40);
    page_button_add->setStyleSheet(ui->pushButton_14->styleSheet());
    page_button_save->setFixedHeight(30);
    page_button_save->setStyleSheet(ui->saveButton->styleSheet());

    auto* spacer =
        new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Minimum);
    page_layout->addItem(spacer);
    page_layout->setContentsMargins(12, 12, 12, 12);
    page_layout->addWidget(group);
    page_layout->addWidget(page_button_add);

    auto* spacer2 =
        new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Minimum);
    page_layout->addItem(spacer2);
    page_layout->addWidget(page_button_save);

    auto* spacer3 =
        new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding);
    page_layout->addItem(spacer3);
    page_scroll_area->verticalScrollBar()->setValue(
        page_scroll_area->verticalScrollBar()->maximum());
    ui->stackedWidget->addWidget(page);

    int index = ui->stackedWidget->indexOf(page);
    buttonToIndex[new_switch] = index;
    page->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto* switch_layout =
        qobject_cast<QHBoxLayout*>(switch_scroll_widget->layout());
    switch_layout->insertWidget(switch_layout->indexOf(ui->pushButton_5),
                                new_switch);
    (count)++;

    connect(new_switch, &QPushButton::clicked, this, &MainWindow::switchPage);
    connect(page_button_add, &QPushButton::clicked, this,
            [this, page_layout, page_scroll_area, page_button_add]() {
                addNewWidget(page_layout, page_scroll_area, page_button_add);
            });
    connect(page_button_save, &QPushButton::clicked, this,
            &MainWindow::on_saveButton_clicked);
}

void MainWindow::switchPage() {
    auto* button = qobject_cast<QPushButton*>(sender());
    if (button && buttonToIndex.contains(button)) {
        int index = buttonToIndex[button];
        ui->stackedWidget->setCurrentIndex(index);
    }
}

void MainWindow::onButton12Clicked() {
    QVector<Event> events = fetchEvents(login);
    clrAlgo::UndirectedGraph graph = constructGraph(events);

    std::cout << "Starting DSatur\n";
    std::vector<unsigned> coloring = clrAlgo::DSaturation<ColorChooser>(graph);
    std::cout << "Done DSatur\n";

    std::cout << "Starting tabu-search\n";
    // clrAlgo::tabuSearch<ObjectiveFunction, GetNeighbours>(graph, coloring,
    // 1000, 10);
    std::cout << "Done tabu-search\n";

    printEvents(events, coloring);
}

void MainWindow::onButton13Clicked() {
    ui->widget->show();
    ui->widget_5->hide();
    ui->widget_3->show();
    ui->widget_8->show();
    ui->widget_9->hide();
    ui->widget_6->hide();
}

void MainWindow::onButton16Clicked() { close(); }
