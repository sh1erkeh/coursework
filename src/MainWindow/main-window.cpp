#include "main-window.h"
#include "ui_main-window.h"

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

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow), count(2) 
    {
    ui->setupUi(this);
    
    //обозначение переменных чтобы было более легкое понимание;
    switch_4 = ui->pushButton_4;
    
    ui->widget_5->hide();
    ui->widget_3->show();
    ui->widget_8->show();
    ui->widget_9->hide();
    ui->widget_6->hide();
    
    //устанавливаю разые акценты на свитчах
    switch_4->setStyleSheet("QPushButton {""background-color: rgb(60,60,60);"
                            "border-top-right-radius: 15px;"
                            "border-top-left-radius: 15px;""}");
    //слайд бар стиль
    ui->scrollArea->setStyleSheet(
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
        "}"
        );
    ui->switch_area->setStyleSheet(
        "QScrollBar:horizontal {"
        "    border: none;"
        "    border-radius: 5px;"
        "    background: #2E2E2E;"
        "    height: 10px;"
        "    margin: 0px 0px 0px 0px;"
        "}"
        "QScrollBar::handle:horizontal {"
        "    background: #5A5A5A;"
        "    border-radius: 5px;"
        "    min-width: 20px;"
        "}"
        "QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {"
        "    background: none;"
        "    width: 0px;"
        "}"
        "QScrollBar::left-arrow:horizontal, QScrollBar::right-arrow:horizontal {"
        "    background: none;"
        "}"
        "QScrollBar::handle:horizontal:hover {"
        "    background: #777777;"
        "}"
        "QScrollBar::handle:horizontal:pressed {"
        "    background: #AAAAAA;"
        "}"
        );
    //связываю свитчи с переключением окна
    connect(ui->pushButton_12, &QPushButton::clicked, this, &MainWindow::onButton12Clicked);
    connect(ui->pushButton_13, &QPushButton::clicked, this, &MainWindow::onButton13Clicked);
    connect(ui->pushButton_16, &QPushButton::clicked, this, &MainWindow::onButton16Clicked);
    //беру скролл виджет из гуишки чтобы получить из него лейаут и потом в лейаут пихаю элементы
    QWidget *scrollWidget = ui->scrollArea->widget();
    if (!scrollWidget){
        scrollWidget = new QWidget;
        ui->scrollArea->setWidget(scrollWidget);
        ui->scrollArea->setWidgetResizable(true);
    }
    //получаю лейаут из скролл виджета
    QVBoxLayout* scrollLayout = qobject_cast<QVBoxLayout*>(scrollWidget->layout());
    if (!scrollLayout){
        scrollLayout = new QVBoxLayout(scrollWidget);
        scrollWidget->setLayout(scrollLayout);
    }
    ui->switch_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->switch_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //создаем спейсер в скролл арея чтобы все элементы сверху были
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
    connect(ui->pushButton_5, &QPushButton::clicked, this, [this, count]()mutable {
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


    connect(ui->pushButton_6, &QPushButton::clicked, this, [this, scrollLayout]() {
        addNewWidget(scrollLayout, this->ui->scrollArea, this->ui->pushButton_6);
    });
    connect(ui->pushButton_14, &QPushButton::clicked, this, [this, scrollLayout_4]() {
        addNewWidget(scrollLayout_4, this->ui->scrollArea_3, this->ui->pushButton_14);
    });
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::switchPage);
    connect(ui->pushButton_17, &QPushButton::clicked, this, &MainWindow::switchPage);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::addNewWidget(QVBoxLayout *scrollLayout, QScrollArea *scrollArea, QPushButton *pushButton_6) {//прописать в аргумент что передедаю scrollLayout
    // Проверяем количество виджетов
    if (row >= 80) {
        return; // Если виджетов больше 80, не добавляем новые
    }

    // Создаем новый виджет
    QWidget *newWidget = new QWidget();
    newWidget->setStyleSheet("background-color: rgb(80, 80, 80); border-radius: 15px;");

    // Создаем текстовое поле
    QPlainTextEdit *textEdit = new QPlainTextEdit(newWidget);
    textEdit->setStyleSheet("background-color: rgb(255, 255, 255); border-radius: 10px;");
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
    widget_spinbox_layout->setContentsMargins(10,0,3,0);

    spinbox->setMinimumHeight(24);
    spinbox->setMinimumWidth(35);
    spinbox->setStyleSheet("QSpinBox::up-button{background-color:rgb(37,125,239);border-radius: 5px;width: 20px;height:12px;}"
        "QSpinBox::down-button{"
        "background-color:rgb(37,125,239);"
        "border-radius: 5px;"
        "width: 20px;"
        "height:12px;}"
        "QSpinBox::down-arrow{"
        "image:url(:/new/prefix1/arrow.png);"
        "width: 5px;"
        "height: 5px;}"
        "QSpinBox::up-arrow{"
        "image:url(:/new/prefix1/arrow_up.png);"
        "width: 5px;"
        "height: 5px;}"
        "QSpinBox::base{"
        "background-color: rgb(40,40,40);"
        "border-radius: 5px;}"
        "QSpinBox {color: black;}");
    spinbox->setRange(1,4);

    // Устанавливаем layout для нового виджета
    QHBoxLayout *newWidgetLayout = new QHBoxLayout(newWidget);
    newWidgetLayout->addWidget(widget_spinbox);
    newWidgetLayout->addWidget(textEdit);
    newWidget->setLayout(newWidgetLayout);
    newWidget->setFixedHeight(50);
    newWidgetLayout->setContentsMargins(5,5,5,5);
    newWidgetLayout->setSpacing(20);
    // Добавляем новый виджет в layout scrollWidget
    scrollLayout->insertWidget(scrollLayout->indexOf(pushButton_6),newWidget);

    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    // Увеличиваем количество виджетов
    row++;

    // Обновляем прокрутку
    scrollArea->verticalScrollBar()->setValue(scrollArea->verticalScrollBar()->maximum());
}
// Слот для кнопки switch_4
void MainWindow::onSwitch4Clicked(const QString &buttonText)//получается мне надо при создании page в основном экране также создавать page_alter с с пустями колонками пар
//во втором окне
{   if (count>=80){
        return;}

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
    QWidget *page = new QWidget(); // Создаём копию

    // Копируем свойства
    page->setGeometry(original->geometry());
    page->setStyleSheet(original->styleSheet());
    ui->stackedWidget->addWidget(page);

    //Теперь братик page создан и я постараюсь в него впихнуть здесь дочерние элементы по типу push_button и plaintextedit, scroll layout еще
    QScrollArea *page_scroll_area  = new QScrollArea;
    QPushButton *page_button_add = new QPushButton("Добавить предмет");

    QWidget *page_scrollWidget = page_scroll_area->widget();
    if (!page_scrollWidget){
        page_scrollWidget = new QWidget;
        page_scroll_area->setWidget(page_scrollWidget);
        page_scroll_area->setWidgetResizable(true);
    }
    page_scroll_area->setParent(page);
    page_scroll_area->setWidgetResizable(true);
    page_scroll_area->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
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


    QVBoxLayout *page_vertical_layout = qobject_cast<QVBoxLayout*>(page->layout());
    if (!page_vertical_layout){
        page_vertical_layout = new QVBoxLayout(page);
        page->setLayout(page_vertical_layout);
    }
    page_vertical_layout->addWidget(page_scroll_area);
    //получаю лейаут из скролл виджета
    QVBoxLayout *page_layout = qobject_cast<QVBoxLayout*>(page_scrollWidget->layout());
    if (!page_layout){
        page_layout = new QVBoxLayout(page_scrollWidget);
        page_scrollWidget->setLayout(page_layout);
    }

    page_button_add->setFixedHeight(50);
    page_button_add->setStyleSheet(ui->pushButton_14->styleSheet());

    QSpacerItem *spacer = new QSpacerItem(12,12, QSizePolicy::Minimum, QSizePolicy::Minimum);
    page_layout->addItem(spacer);
    page_layout->addWidget(page_button_add);
    QSpacerItem *spacer2 = new QSpacerItem(20,40, QSizePolicy::Expanding, QSizePolicy::Expanding);
    page_layout->addItem(spacer2);
    page_scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    page_scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    page_scroll_area->verticalScrollBar()->setValue(page_scroll_area->verticalScrollBar()->maximum());
    ui->stackedWidget->addWidget(page);
    //добавляю скролл area для page
    int index = ui->stackedWidget->indexOf(page);
    buttonToIndex[new_switch] = index;
    qDebug()<<index;
    page->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QHBoxLayout *switch_layout = qobject_cast<QHBoxLayout*>(switch_scroll_widget->layout());
    spacer_switch = new QSpacerItem(20,10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    switch_layout->addItem(spacer_switch);
    switch_layout->insertWidget(switch_layout->indexOf(ui->pushButton_5), new_switch);
    (count)++;

    ui->plainTextEdit->setEnabled(true);
    ui->plainTextEdit->setFocus();

    connect(new_switch, &QPushButton::clicked, this, &MainWindow::switchPage);

    connect(page_button_add, &QPushButton::clicked, this, [this, page_layout, page_scroll_area, page_button_add]() {
        addNewWidget(page_layout, page_scroll_area, page_button_add);
    });
}

void MainWindow::switchPage(){
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button&&buttonToIndex.contains(button)){
        int index = buttonToIndex[button];
        qDebug()<<index;
        ui->stackedWidget->setCurrentIndex(index);
    }
}
// Метод для скрытия всех виджетов
void MainWindow::onButton12Clicked()
{
    ui->widget->hide();
    ui->widget_5->show();
    ui->widget_3->hide();
    ui->widget_8->hide();
    ui->widget_9->show();
    ui->widget_6->show();
}
void MainWindow::onButton13Clicked()
{
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
