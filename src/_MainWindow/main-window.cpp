#include "main-window.h"
#include "ui_main-window.h"

MainWindow::MainWindow(const QString& login, QWidget* parent)
        : QMainWindow(parent), ui(new Ui::MainWindow), login(login) 
{
    ui->setupUi(this);

    initializeDataBase();
    
    connect(
        ui->add_input_box_button,
        &QPushButton::clicked,
        this,
        &MainWindow::onAddInputBoxButtonClicked
    );

    connect(
        ui->inputs_button,
        &QPushButton::clicked,
        this,
        [this]() { ui->main_pages->setCurrentIndex(0); }
    );

    connect(
        ui->save_inputs_button,
        &QPushButton::clicked,
        this,
        &MainWindow::onSaveInputsButtonClicked
    );

    connect(
        ui->results_button,
        &QPushButton::clicked,
        this,
        &MainWindow::onResultsButtonClicked
    );

    connect(
        ui->exit_button,
        &QPushButton::clicked,
        this,
        &QApplication::quit
    );
}

MainWindow::~MainWindow() { 
    delete ui;
}

void MainWindow::initializeDataBase() {
    QDir dir;
    QString path = dir.currentPath() + "/database";

    if (!dir.exists(path)) {
        dir.mkpath(path);
    }

    QString db_name =
         path + '/' + login + "data.db";
    QSqlDatabase db =
        QSqlDatabase::addDatabase("QSQLITE", db_name);

    if (!db.open()) {
        throw std::runtime_error("Error creating DB: " +
                                 db.lastError().text().toStdString());
    }

    QSqlQuery query;
    QString createTableSubjects =
        "CREATE TABLE IF NOT EXISTS SUBJECTS ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "quantity INT, "
        "name TEXT UNIQUE)";

    if (!query.exec(createTableSubjects)) {
        throw std::runtime_error("Error creating SUBJECTS table: " +
                                 query.lastError().text().toStdString());
    } else {
        qDebug() << "Table SUBJECTS successfulliy initialized";
    }
}

void MainWindow::onSaveInputsButtonClicked() {
    QWidget* scrollContent = ui->scroll_area_1_contents;
    QVBoxLayout* scrollLayout = qobject_cast<QVBoxLayout*>(scrollContent->layout());
    
    if (!scrollLayout) {
        qDebug() << "Error: Scroll content has no layout!";
        return;
    }

    group_quantity = ui->group_quantity_spinbox->value();
    subjectsData.clear();
    subjectsData.shrink_to_fit();

    for (int i = 0; i < scrollLayout->count(); ++i) {
        QLayoutItem* item = scrollLayout->itemAt(i);
        if (!item || !item->widget()) continue;

        QWidget* widget = item->widget();
        if (widget->objectName() == "subject_input_box") {
            QSpinBox* quantitySpinBox = widget->findChild<QSpinBox*>("subject_quantity_spinbox");
            QPlainTextEdit* nameTextEdit = widget->findChild<QPlainTextEdit*>("subject_name_input");

            if (quantitySpinBox && nameTextEdit) {
                QString name = nameTextEdit->toPlainText().trimmed();
                int quantity = quantitySpinBox->value();

                if (!name.isEmpty()) {
                    subjectsData.emplace_back(name, quantity);
                }
            }
        }
    }

    qDebug() << "Collected subjects data:";
    for (const auto& subject : subjectsData) {
        qDebug() << "Subject:" << subject.first << "Quantity:" << subject.second;
    }
}

void MainWindow::onResultsButtonClicked() {
    QVector<Event> events = fetchEvents(group_quantity, subjectsData);
    clrAlgo::UndirectedGraph graph = constructGraph(events);

    qDebug() << "Starting DSatur";
    std::vector<unsigned> coloring = clrAlgo::DSaturation<ColorChooser>(graph);
    qDebug() << "Done DSatur";

    QMap<int, QMap<unsigned, QString>> grouped_data;
    for (int i = 0; i < events.size(); ++i) {
        grouped_data[events[i].group_name][coloring[i]] = events[i].subject_name;
    }

    setupResultsPage(grouped_data, group_quantity);
    ui->main_pages->setCurrentIndex(1);
}

QWidget* MainWindow::createSubjectInputBox() {
    QWidget* inputBox = new QWidget();
    inputBox->setObjectName("subject_input_box");
    inputBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    inputBox->setMinimumSize(300, 50);
    inputBox->setMaximumSize(16777215, 50);
    inputBox->setStyleSheet("background-color: #7A7978; border-radius: 15px;");

    QGridLayout *gridLayout = new QGridLayout(inputBox);
    gridLayout->setContentsMargins(5, 5, 5, 5);
    gridLayout->setSpacing(0);

    QSpacerItem *leftSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);
    gridLayout->addItem(leftSpacer, 0, 1);

    QWidget *quantityWidget = new QWidget(inputBox);
    quantityWidget->setObjectName("subject_quantity_input");
    quantityWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    quantityWidget->setMinimumSize(50, 40);
    quantityWidget->setMaximumSize(50, 40);
    quantityWidget->setStyleSheet("background-color:#FDECEF; border-radius: 10px; color:rgb(40,40,40);");

    QHBoxLayout *quantityLayout = new QHBoxLayout(quantityWidget);
    quantityLayout->setContentsMargins(5, 0, 0, 0);

    QSpinBox *spinBox = new QSpinBox(quantityWidget);
    spinBox->setObjectName("subject_quantity_spinbox");
    spinBox->setMinimumSize(40, 30);
    spinBox->setMaximumSize(40, 30);
    spinBox->setMinimum(1);
    spinBox->setRange(1, 99);
    spinBox->setMaximum(4);
    spinBox->setStyleSheet("QSpinBox { background-color: #FDECEF; border-radius: 5px; }");
    spinBox->setAlignment(Qt::AlignCenter);
    spinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);

    quantityLayout->addWidget(spinBox);
    gridLayout->addWidget(quantityWidget, 0, 0);

    QPlainTextEdit *nameInput = new QPlainTextEdit(inputBox);
    nameInput->setObjectName("subject_name_input");
    nameInput->setMinimumSize(280, 20);
    nameInput->setStyleSheet("background-color: #FDECEF; color:rgb(40,40,40); border-radius: 10px; padding: 7px;");
    
    QFont font;
    font.setFamily("Arial");
    font.setPointSize(14);
    nameInput->setFont(font);

    gridLayout->addWidget(nameInput, 0, 2);

    return inputBox;
}

void MainWindow::onAddInputBoxButtonClicked() {
    QWidget* scrollContent = ui->scroll_area_1_contents;
    QVBoxLayout* scrollLayout = qobject_cast<QVBoxLayout*>(scrollContent->layout());
    
    if (!scrollLayout) {
        qDebug() << "Error: Scroll content has no layout!";
        return;
    }

    size_t insertPosition = scrollLayout->count() - 1 - added_input_boxes;
    QWidget *newInputBox = createSubjectInputBox();
    scrollLayout->insertWidget(insertPosition, newInputBox);

    scrollLayout->addStretch();
    added_input_boxes++;
}

void MainWindow::setupResultsPage(const QMap<int, QMap<unsigned, QString>>& grouped_data,
                                  int count) {
    if (ui->results_page->layout()) {
        QLayoutItem* item;
        while ((item = ui->results_page->layout()->takeAt(0))) {
            delete item->widget();
            delete item;
        }
        delete ui->results_page->layout();
    }

    QWidget* container = new QWidget(ui->results_page);
    container->setObjectName("results_page_intern");
    container->setStyleSheet(
        "background-color: rgb(122,121,120);"
        "border-radius: 40px;"
    );
    container->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    QVBoxLayout* mainLayout = new QVBoxLayout(container);
    mainLayout->setContentsMargins(9, 9, 9, 9);
    mainLayout->setSpacing(6);

    QLabel* titleLabel = new QLabel("Расписание", container);
    titleLabel->setStyleSheet(
        "font: bold 30pt 'Arial Black';"
        "color: #FDECEF;"
        "background: transparent;"
    );
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    QScrollArea* buttonScrollArea = new QScrollArea(container);
    buttonScrollArea->setFixedHeight(80);
    buttonScrollArea->setWidgetResizable(true);
    buttonScrollArea->setStyleSheet(
        "QScrollArea { background: transparent; border: none; }"
        "QScrollBar:horizontal { height: 10px; background: rgb(80,80,80); }"
    );
    
    QWidget* buttonContainer = new QWidget();
    QHBoxLayout* buttonLayout = new QHBoxLayout(buttonContainer);
    buttonLayout->setContentsMargins(5, 5, 5, 5);
    buttonLayout->setSpacing(15);

    // Create stacked widget
    QStackedWidget* stackedTables = new QStackedWidget(container);
    stackedTables->setStyleSheet(
        "background-color: rgb(40,40,40);"
        "border-radius: 30px;"
    );

    QStringList dayNames = {"Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота"};
    QStringList timeSlots = {"1 пара", "2 пара", "3 пара", "4 пара", "5 пара", "6 пара", "7 пара"};

    for (int i = 0; i < count; i++) {
        QWidget* page = new QWidget();
        QVBoxLayout* pageLayout = new QVBoxLayout(page);
        pageLayout->setContentsMargins(9, 9, 9, 9);
        
        QTableWidget* table = new QTableWidget(timeSlots.size(), dayNames.size(), page);
        table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        
        table->horizontalHeader()->setMinimumSectionSize(80);
        table->verticalHeader()->setMinimumSectionSize(40);

        table->setHorizontalHeaderLabels(dayNames);
        table->setVerticalHeaderLabels(timeSlots);
        table->setStyleSheet(
            "QTableWidget {"
            "   background: rgb(60,60,60);"
            "   color: white;"
            "   gridline-color: rgb(80,80,80);"
            "}"
            "QHeaderView::section {"
            "   background-color: rgb(80,80,80);"
            "   color: white;"
            "   padding: 5px;"
            "   border: none;"
            "   font: bold 11px 'Arial';"
            "}"
        );

        for (int row = 0; row < timeSlots.size(); ++row) {
            for (int col = 0; col < dayNames.size(); ++col) {
                QTableWidgetItem* item = new QTableWidgetItem();
                item->setText(grouped_data[i][row * 6 + col]);
                item->setTextAlignment(Qt::AlignCenter);
                table->setItem(row, col, item);
            }
        }

        pageLayout->addWidget(table);
        stackedTables->addWidget(page);

        QPushButton* btn = new QPushButton(QString("%1 группа").arg(i+1), buttonContainer);
        btn->setFixedSize(140, 50);
        btn->setStyleSheet(
            "QPushButton {"
            "   border: 2px solid rgb(80,80,80);"
            "   border-radius: 10px;"
            "   padding: 5px;"
            "   background: rgb(80,80,80);"
            "   color: white;"
            "   font: bold 12pt 'Arial';"
            "}"
            "QPushButton:hover {"
            "   background: rgb(100,100,100);"
            "}"
            "QPushButton:pressed {"
            "   background: rgb(60,60,60);"
            "}"
        );
        connect(btn, &QPushButton::clicked, [=](){ stackedTables->setCurrentIndex(i); });
        buttonLayout->addWidget(btn);
    }

    buttonScrollArea->setWidget(buttonContainer);
    buttonContainer->setStyleSheet("background: transparent;");
    
    mainLayout->addWidget(buttonScrollArea);
    mainLayout->addWidget(stackedTables, 1);
    
    QVBoxLayout* pageLayout = new QVBoxLayout(ui->results_page);
    pageLayout->setContentsMargins(9, 9, 9, 9);
    pageLayout->addWidget(container);
}
