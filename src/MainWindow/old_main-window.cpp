#include "main-window.h"
#include "ui_main-window.h"

#include "graph.hpp"
#include "degree-saturation.hpp"
#include "tabu-search.hpp"

#include "data-fetcher.h"
#include "dsatur-util.h"
#include "tabuSearch-util.h"
#include "results-printer.h"

#include <QPushButton>
#include <QWidget>
#include <QComboBox>
#include <QPlainTextEdit>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QScrollArea>
#include <QScrollBar>
#include <QSpinBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>
#include <QPalette>
#include <QGraphicsDropShadowEffect>
#include <QLabel>
#include <QStyle>
#include <QApplication>
#include <QScreen>


MainWindow::MainWindow(const QString& login, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), count(2), row(0) {
    ui->setupUi(this);
    this->login = login;
    centerWindow();

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

    if (!db.open()){
        qDebug() <<"Ошибка открытия базы данных: "<< db.lastError().text();
        return;
    }

    QSqlQuery query;
    QString createTableQuery =
        "CREATE TABLE IF NOT EXISTS GROUPS ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT, "
        "subjects TEXT,"
        "quantities TEXT)";

    if (!query.exec(createTableQuery)) {
        qDebug() << "Ошибка создания таблицы: " << query.lastError().text();
    } else {
        qDebug() << "База данных успешно инициализирована!";
        qDebug() << dbPath;
    }

    QString createTableSubjects =
        "CREATE TABLE IF NOT EXISTS SUBJECTS ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT UNIQUE)";

    if (!query.exec(createTableSubjects)) {
        qDebug() << "Ошибка создания таблицы: " << query.lastError().text();
    } else {
        qDebug() << "База данных успешно инициализирована!";
    }

    //связываю свитчи с переключением окна
    connect(ui->pushButton_12, &QPushButton::clicked, this, &MainWindow::onButton12Clicked);
    connect(ui->pushButton_13, &QPushButton::clicked, this, &MainWindow::onButton13Clicked);
    connect(ui->pushButton_16, &QPushButton::clicked, this, &MainWindow::onButton16Clicked);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(10);
    effect->setOffset(0);
    effect->setColor(QColor(0,0,0,100));
    ui->widget_20->setGraphicsEffect(effect);

    QGraphicsDropShadowEffect *effect1 = new QGraphicsDropShadowEffect;
    effect1->setBlurRadius(10);
    effect1->setOffset(0);
    effect1->setColor(QColor(0,0,0,100));

    ui->widget_13->setGraphicsEffect(effect1);

    QWidget *scrollWidget = ui->scrollArea->widget();
    if (!scrollWidget){
        scrollWidget = new QWidget;
        ui->scrollArea->setWidget(scrollWidget);
        ui->scrollArea->setWidgetResizable(true);
    }

    QVBoxLayout* scrollLayout = qobject_cast<QVBoxLayout*>(scrollWidget->layout());
    if (!scrollLayout){
        scrollLayout = new QVBoxLayout(scrollWidget);
        scrollWidget->setLayout(scrollLayout);
    }
    ui->switch_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    spacer = new QSpacerItem(20,40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    scrollLayout->addItem(spacer);

    QWidget *firstPage = ui->stackedWidget->widget(0);
    QVBoxLayout *layout1 = new QVBoxLayout(firstPage);
    layout1->addWidget(ui->show_8);
    layout1->setContentsMargins(0,0,0,0);

    QWidget *firstPage1 = ui->stackedWidget->widget(1);
    QVBoxLayout *layout2 = new QVBoxLayout(firstPage1);
    layout2->setContentsMargins(0,0,0,0);
    layout2->addWidget(ui->show_6);

    buttonToIndex[ui->pushButton_4] = 0;
    buttonToIndex[ui->pushButton_17] = 1;

    int count = 3;
    connect(ui->pushButton_5, &QPushButton::clicked, this, [this, count]() mutable {
        onSwitch4Clicked(QString::number(count));
        count++;
    });

    QWidget *scrollWidget_4 = ui->scrollArea_3->widget();
    if (!scrollWidget_4){
        scrollWidget_4 = new QWidget;
        ui->scrollArea_3->setWidget(scrollWidget_4);
        ui->scrollArea_3->setWidgetResizable(true);
    }

    QVBoxLayout* scrollLayout_4 = qobject_cast<QVBoxLayout*>(scrollWidget_4->layout());
    if (!scrollLayout_4){
        scrollLayout_4 = new QVBoxLayout(scrollWidget_4);
        scrollWidget_4->setLayout(scrollLayout_4);
    }

    spacer_4 = new QSpacerItem(20,40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    scrollLayout_4->addItem(spacer_4);

    ui->switch_area->horizontalScrollBar()->setValue(ui->switch_area->horizontalScrollBar()->maximum());

    ui->scrollArea_3->verticalScrollBar()->setValue(ui->scrollArea_3->verticalScrollBar()->maximum());
    ui->scrollArea->verticalScrollBar()->setValue(ui->scrollArea->verticalScrollBar()->maximum());
    connect(ui->pushButton_6, &QPushButton::clicked, this, [this, scrollLayout]() {
        addNewWidget(scrollLayout, this->ui->scrollArea, this->ui->pushButton_6);
    });
    connect(ui->pushButton_14, &QPushButton::clicked, this, [this, scrollLayout_4]() {
        addNewWidget(scrollLayout_4, this->ui->scrollArea_3, this->ui->pushButton_14);
    });
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::switchPage);
    connect(ui->pushButton_17, &QPushButton::clicked, this, &MainWindow::switchPage);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::on_saveButton_clicked);
    connect(ui->pushButton_15, &QPushButton::clicked, this, &MainWindow::on_saveButton_clicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::centerWindow() {
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();

    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;

    // Устанавливаем позицию окна
    move(x, y);
}

void MainWindow::on_saveButton_clicked() {
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qDebug() << "Ошибка: база данных не открыта";
        return;
    }

    QSqlQuery query(db);
    QSqlQuery query1(db);
    QSqlQuery getIdQuery(db);

    if (!query.exec("DELETE FROM GROUPS")) {
        qDebug() << "Ошибка очистки таблицы" << query.lastError().text();
        return;
    } else {
        qDebug() << "Таблица GROUPS успешно очищена";
    }

    query.clear();
    query.prepare("INSERT INTO GROUPS (name, subjects, quantities) VALUES (:name, :subjects, :quantities)");
    query1.prepare("INSERT INTO SUBJECTS (name) VALUES (:name)");

    int nameCount = ui->stackedWidget->count();
    for (int i = 0; i < nameCount; ++i) {
        QWidget *name = ui->stackedWidget->widget(i);

        QList<QPlainTextEdit *> textEdits = name->findChildren<QPlainTextEdit *>();
        QList<QSpinBox *> spinBoxes = name->findChildren<QSpinBox *>();

        QStringList subjectList;
        QStringList quantitiesList;

        for (int j = 0; j < textEdits.size(); ++j) {
            // if (j == 0) {
            //     
            // }

            QPlainTextEdit *textEdit = textEdits[j];
            QSpinBox *textSpin = spinBoxes[j];

            if (textEdit && textSpin) {
                QString content = textEdit->toPlainText().trimmed();
                int spin = textSpin->value();

                if (content.isEmpty()) {
                    qDebug() << "Пропущен пустой предмет";
                    continue;
                }

                // Проверяем, существует ли предмет в базе
                getIdQuery.prepare("SELECT id FROM SUBJECTS WHERE name = :name");
                getIdQuery.bindValue(":name", content);

                if (!getIdQuery.exec()) {
                    qDebug() << "Ошибка поиска предмета: " << getIdQuery.lastError().text();
                    continue;
                }

                if (!getIdQuery.next()) {
                    // Если предмет не найден, добавляем его
                    query1.bindValue(":name", content);
                    if (!query1.exec()) {
                        qDebug() << "Ошибка сохранения предмета: " << query1.lastError().text();
                        continue;
                    }
                }

                // Добавляем в списки для группового сохранения
                subjectList.append(content);
                quantitiesList.append(QString::number(spin));
            }
        }

        if (!subjectList.isEmpty() && !quantitiesList.isEmpty()) {
            QString subject_list=subjectList.join(",");
            QString quantities_list = quantitiesList.join(",");
            query.bindValue(":name", i);
            query.bindValue(":subjects", subject_list);
            query.bindValue(":quantities", quantities_list);

            if (!query.exec()) {
                qDebug() << "Ошибка сохранения GROUPS: " << query.lastError().text();
            }
        } else {
            qDebug() << "Пропущена страница " << i << ", так как нет данных для сохранения.";
        }
    }
}

void MainWindow::addNewWidget(QVBoxLayout *scrollLayout, QScrollArea *scrollArea, QPushButton *pushButton_6) {
    if (row >= 35) {
        return;
    }

    QPalette palette;
    palette.setColor(QPalette::Text, Qt::black);

    // Создаем новый виджет
    QWidget *newWidget = new QWidget();
    newWidget->setStyleSheet("background-color: rgb(80, 80, 80); border-radius: 15px;");

    // Создаем текстовое поле
    QPlainTextEdit *textEdit = new QPlainTextEdit(newWidget);
    textEdit->setStyleSheet("background-color: rgb(255, 255, 255); border-radius: 10px;color: black; padding:7px");


    textEdit->setMinimumHeight(40);
    //создаем виджет для спин бокса
    QWidget *widget_spinbox = new QWidget();
    widget_spinbox->setStyleSheet("background-color:rgb(200,200,200); border-radius: 10px;");
    widget_spinbox->setFixedSize(50,40);

    //создаем спинбокс и грид для виджета под спинбокс
    QSpinBox *spinbox = new QSpinBox;
    QHBoxLayout *widget_spinbox_layout = new QHBoxLayout(widget_spinbox);
    widget_spinbox_layout->addWidget(spinbox);
    widget_spinbox->setLayout(widget_spinbox_layout);
    widget_spinbox_layout->setContentsMargins(7,0,3,0);

    spinbox->setMinimumHeight(30);
    spinbox->setMinimumWidth(40);
    spinbox->setStyleSheet(ui->spinBox_3->styleSheet());
    spinbox->setRange(1,10);
    spinbox->setPalette(palette);

    QHBoxLayout *newWidgetLayout = new QHBoxLayout(newWidget);
    QSpacerItem *spacer_button= new QSpacerItem(10,10, QSizePolicy::Minimum, QSizePolicy::Minimum);
    newWidgetLayout->setContentsMargins(5,5,5,5);
    newWidgetLayout->setSpacing(20);
    newWidgetLayout->addWidget(widget_spinbox);
    newWidgetLayout->addWidget(textEdit);
    newWidget->setLayout(newWidgetLayout);
    newWidget->setFixedHeight(50);

    scrollLayout->setSpacing(0);
    scrollLayout->insertWidget(scrollLayout->indexOf(pushButton_6),newWidget);
    if (checking_label[pushButton_6]==0 && pushButton_6!=ui->pushButton_14){
        QWidget *widget_tip = new QWidget;
        widget_tip->setFixedHeight(30);
        QSpacerItem *gap = new QSpacerItem(10,10, QSizePolicy::Expanding, QSizePolicy::Minimum);
        QSpacerItem *gap1 = new QSpacerItem(10,10, QSizePolicy::Minimum, QSizePolicy::Minimum);
        QLabel *quantities = new QLabel("Кол-во");
        quantities->setStyleSheet("color:rgb(120,120,120);");
        QLabel *pairs = new QLabel("Название предмета");
        QHBoxLayout *tip_layout = new QHBoxLayout;
        pairs->setStyleSheet("color:rgb(120,120,120);");

        tip_layout->setContentsMargins(4,5,4,0);
        // tip_layout->addItem(gap);
        tip_layout->addWidget(quantities);
        tip_layout->addItem(gap1);
        tip_layout->addWidget(pairs);
        tip_layout->addItem(gap);
        widget_tip->setLayout(tip_layout);

        checking_label[pushButton_6]=1;

        scrollLayout->insertWidget(scrollLayout->indexOf(newWidget), widget_tip);
    }
    scrollLayout->insertItem(scrollLayout->indexOf(pushButton_6),spacer_button);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    // Увеличиваем количество виджетов
    row++;

    // Обновляем прокрутку
    scrollArea->verticalScrollBar()->setValue(scrollArea->verticalScrollBar()->maximum());
}
// Слот для кнопки switch_4
void MainWindow::onSwitch4Clicked(const QString &buttonText) {
    if (count >= 80) {
        return;
    }

    row = 0;
    //создаю новую кнопку
    
    QPushButton *new_switch = new QPushButton(buttonText);
    new_switch->setStyleSheet("QPushButton {""background-color: rgb(40,40,40);"
                         "border-top-right-radius: 15px;"
                          "border-top-left-radius: 15px;"
                          "color: white;}"
                          "QPushButton:hover {background-color: rgb(60,60,60);}"
                          "QPushButton:pressed {background-color: rgb(30,30,30);}");
    new_switch->setFixedSize(60,40);

    QWidget *switch_scroll_widget = ui->switch_area->widget();
    if (!switch_scroll_widget){
        switch_scroll_widget = new QWidget;
        ui->switch_area->setWidget(switch_scroll_widget);
        ui->switch_area->setWidgetResizable(true);
    }

    QWidget *original = ui->show_8; // Исходный виджет
    QWidget *group = new QWidget;
    QWidget *name = new QWidget(); // Создаём копию

    // Копируем свойства
    name->setGeometry(original->geometry());
    name->setStyleSheet(original->styleSheet());
    ui->stackedWidget->addWidget(name);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(10);
    effect->setOffset(0);
    effect->setColor(QColor(0,0,0,100));

    group->setFixedSize(100,30);
    group->setContentsMargins(0,0,0,0);
    group->setGraphicsEffect(effect);
    group->setStyleSheet(ui->widget_13->styleSheet());

    QStringList groupList;
    groupList.append(buttonText);
    groupList.append(" группа");

    QLabel *group_label = new QLabel(groupList.join(""));
    QGridLayout *group_layout = new QGridLayout;
    group_layout->setContentsMargins(0,0,0,0);
    group_layout->addWidget(group_label);
    group_layout->setAlignment(Qt::AlignCenter);
    group->setLayout(group_layout);

    QScrollArea *name_scroll_area  = new QScrollArea;
    QPushButton *name_button_add = new QPushButton("Добавить пару");
    QPushButton *name_button_save = new QPushButton("Сохранить");

    QWidget *name_scrollWidget = name_scroll_area->widget();
    if (!name_scrollWidget){
        name_scrollWidget = new QWidget;
        name_scroll_area->setWidget(name_scrollWidget);
        name_scroll_area->setWidgetResizable(true);
    }

    name_scroll_area->setParent(name);
    name_scroll_area->setWidgetResizable(true);
    name_scroll_area->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    name_scroll_area->setStyleSheet(ui->scrollArea_3->styleSheet());
    name_scroll_area->setGeometry(ui->scrollArea_3->geometry());

    name_scroll_area->setStyleSheet(
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

    QGridLayout *name_vertical_layout = qobject_cast<QGridLayout*>(name->layout());
    if (!name_vertical_layout){
        name_vertical_layout = new QGridLayout(name);
        name->setLayout(name_vertical_layout);
    }
    name_vertical_layout->addWidget(name_scroll_area);
    name_vertical_layout->setContentsMargins(20,20,20,20);
    //получаю лейаут из скролл виджета
    QVBoxLayout *name_layout = qobject_cast<QVBoxLayout*>(name_scrollWidget->layout());
    if (!name_layout){
        name_layout = new QVBoxLayout(name_scrollWidget);
        name_scrollWidget->setLayout(name_layout);
    }

    name_button_add->setFixedHeight(40);
    name_button_add->setStyleSheet(ui->pushButton_14->styleSheet());
    name_button_save->setFixedHeight(30);
    name_button_save->setStyleSheet(ui->saveButton->styleSheet());

    QSpacerItem *spacer = new QSpacerItem(0,0, QSizePolicy::Minimum, QSizePolicy::Minimum);
    name_layout->addItem(spacer);
    name_layout->setContentsMargins(12,12,12,12);
    name_layout->addWidget(group);
    name_layout->addWidget(name_button_add);
    QSpacerItem *spacer2 = new QSpacerItem(10,10, QSizePolicy::Minimum, QSizePolicy::Minimum);
    name_layout->addItem(spacer2);
    name_layout->addWidget(name_button_save);
    QSpacerItem *spacer3 = new QSpacerItem(10,10, QSizePolicy::Expanding, QSizePolicy::Expanding);
    name_layout->addItem(spacer3);
    name_scroll_area->verticalScrollBar()->setValue(name_scroll_area->verticalScrollBar()->maximum());
    ui->stackedWidget->addWidget(name);
    //добавляю скролл area для name
    int index = ui->stackedWidget->indexOf(name);
    buttonToIndex[new_switch] = index;
    qDebug()<<index;
    name->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QHBoxLayout *switch_layout = qobject_cast<QHBoxLayout*>(switch_scroll_widget->layout());
    switch_layout->insertWidget(switch_layout->indexOf(ui->pushButton_5), new_switch);
    (count)++;

    connect(new_switch, &QPushButton::clicked, this, &MainWindow::switchPage);

    connect(name_button_add, &QPushButton::clicked, this, [this, name_layout, name_scroll_area, name_button_add]() {
        addNewWidget(name_layout, name_scroll_area, name_button_add);
    });

    connect(name_button_save, &QPushButton::clicked, this, &MainWindow::on_saveButton_clicked);

}

void MainWindow::switchPage(){
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button&&buttonToIndex.contains(button)){
        int index = buttonToIndex[button];
        qDebug()<<index;
        ui->stackedWidget->setCurrentIndex(index);
    }
}

void MainWindow::onButton12Clicked() {
    QVector<Event> events = fetchEvents(login);
    clrAlgo::UndirectedGraph graph = constructGraph(events);
    std::vector<unsigned> coloring = clrAlgo::DSaturation<ColorChooser>(graph);
    clrAlgo::tabuSearch<ObjectiveFunction, GetNeighbours>(graph, coloring, 1000, 10);
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

void MainWindow::onButton16Clicked() {
    close();

}
