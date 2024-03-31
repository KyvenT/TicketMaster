#include "AdminWindow.h"

AdminWindow::AdminWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Admin Page");
    resize(1500, 800);

    mainLayout = new QVBoxLayout(this);

    //users section
    usersLabelLayout = new QHBoxLayout;
    usersLabel = new QLabel("Users:");
    usersLabelLayout->addWidget(usersLabel);
    usersLabelLayout->setAlignment(Qt::AlignRight);

    usersLineEdit = new QLineEdit;
    usersLineEdit->setFixedWidth(400);
    usersLabelLayout->addWidget(usersLineEdit);

    usersAddButton = new QPushButton("Add");
    usersAddButton->setFixedWidth(100);
    usersLabelLayout->addWidget(usersAddButton);

    mainLayout->addLayout(usersLabelLayout);

    usersScrollArea = new QScrollArea;
    usersScrollArea->setWidgetResizable(true);
    mainLayout->addWidget(usersScrollArea);

    //departments section
    departmentsLabelLayout = new QHBoxLayout;
    departmentsLabel = new QLabel("Departments:");
    departmentsLabelLayout->addWidget(departmentsLabel);
    departmentsLabelLayout->setAlignment(Qt::AlignRight);

    departmentsLineEdit = new QLineEdit;
    departmentsLineEdit->setFixedWidth(400);
    departmentsLabelLayout->addWidget(departmentsLineEdit);

    departmentsAddButton = new QPushButton("Add");
    departmentsAddButton->setFixedWidth(100);
    departmentsLabelLayout->addWidget(departmentsAddButton);

    mainLayout->addLayout(departmentsLabelLayout);

    departmentsScrollArea = new QScrollArea;
    departmentsScrollArea->setWidgetResizable(true);
    mainLayout->addWidget(departmentsScrollArea);

    departmentsListLayout = new QVBoxLayout;
    QWidget *departmentsListWidget = new QWidget;
    departmentsListWidget->setLayout(departmentsListLayout);
    departmentsScrollArea->setWidget(departmentsListWidget);

    departmentNames = QSet<QString>();

    connect(departmentsAddButton, &QPushButton::clicked, this, &AdminWindow::addDepartment);

    this->show();
}

void AdminWindow::addDepartment() {
    QString departmentName = departmentsLineEdit->text();
    if (!departmentName.isEmpty()) {
        if (!departmentNames.contains(departmentName)) { 
            QPushButton *deleteButton = new QPushButton("Delete");
            deleteButton->setFixedSize(100, 20); 
            QLabel *departmentLabel = new QLabel(departmentName);
            QWidget *departmentWidget = new QWidget;
            QHBoxLayout *departmentLayout = new QHBoxLayout(departmentWidget);
            departmentLayout->addWidget(departmentLabel);
            departmentLayout->addWidget(deleteButton);

            departmentsListLayout->addWidget(departmentWidget);

            connect(deleteButton, &QPushButton::clicked, this, [=]() {
                deleteDepartment(departmentWidget, departmentName);
            });

            departmentsLineEdit->clear();
            
            departmentNames.insert(departmentName);
        } else {
            QMessageBox::warning(this, "Duplicate Department", "This department already exists.");
        }
    }
}


void AdminWindow::deleteDepartment(QWidget *departmentWidget, const QString &departmentName) {
    QLayout *layout = departmentsListLayout->layout();
    if (layout) {
        layout->removeWidget(departmentWidget);
        departmentWidget->deleteLater();

        departmentNames.remove(departmentName);
    }
}
