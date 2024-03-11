#include "AdminGUI.h"

void createWindow(int argc, char *argv[]) {
    QApplication app(argc, argv); 

    QWidget window; 
    window.setWindowTitle("Admin Page"); 
    window.resize(1500, 800); 

    //main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(&window);

    //users section
    QHBoxLayout *usersLabelLayout = new QHBoxLayout;
    QLabel *usersLabel = new QLabel("Users:");
    usersLabelLayout->addWidget(usersLabel);
    usersLabelLayout->setAlignment(Qt::AlignRight);

    QLineEdit *usersLineEdit = new QLineEdit;
    usersLineEdit->setFixedWidth(400);
    usersLabelLayout->addWidget(usersLineEdit);

    QPushButton *usersAddButton = new QPushButton("Add");
    usersAddButton->setFixedWidth(100);
    usersLabelLayout->addWidget(usersAddButton);

    //add userslayout to main layout
    mainLayout->addLayout(usersLabelLayout);

    QScrollArea *usersScrollArea = new QScrollArea;
    usersScrollArea->setWidgetResizable(true);
    mainLayout->addWidget(usersScrollArea);

    //departments section
    QHBoxLayout *departmentsLabelLayout = new QHBoxLayout;
    QLabel *departmentsLabel = new QLabel("Departments:");
    departmentsLabelLayout->addWidget(departmentsLabel);
    departmentsLabelLayout->setAlignment(Qt::AlignRight); //align to the right

    QLineEdit *departmentsLineEdit = new QLineEdit;
    departmentsLineEdit->setFixedWidth(400);
    departmentsLabelLayout->addWidget(departmentsLineEdit);

    QPushButton *departmentsAddButton = new QPushButton("Add");
    departmentsAddButton->setFixedWidth(100);
    departmentsLabelLayout->addWidget(departmentsAddButton);

    //add departments layout to the main layout
    mainLayout->addLayout(departmentsLabelLayout);

    QScrollArea *departmentsScrollArea = new QScrollArea;
    departmentsScrollArea->setWidgetResizable(true);
    mainLayout->addWidget(departmentsScrollArea);

    window.show(); 

    app.exec(); 
}
