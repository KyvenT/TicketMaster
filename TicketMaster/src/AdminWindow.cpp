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

    this->show();
}
