#include "UserWindow.h"
#include "DepartmentTicketsGUI.h"

#include <QLabel>

UserWindow::UserWindow(const std::string &username) {

    //user = UserManager::GetUser(username);

    this->setWindowTitle("User Window");
    this->resize(1280, 720);
    this->show();

    // setup grid layout
    gridLayout = std::make_unique<QGridLayout>(this);
    spacer = std::make_unique<QSpacerItem>(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    gridLayout->addItem(spacer.get(), 0, 1, 1, 1);

    // setup new ticket button
    newTicketButton = std::make_unique<QPushButton>(this);
    gridLayout->addWidget(newTicketButton.get(), 0, 0, 1, 1);

    newTicketButton->setText("Create Ticket");
    QFont font = newTicketButton->font();
    font.setPointSize(24);
    newTicketButton->setFont(font);

    // setup scroll area
    scrollArea = std::make_unique<QScrollArea>(this);
    scrollArea->setWidgetResizable(true);
    gridLayout->addWidget(scrollArea.get(), 1, 0, 1, 2);

    contents = std::make_unique<QWidget>();
    scrollArea->setWidget(contents.get());

    scrollGridLayout = std::make_unique<QGridLayout>(contents.get());

    // set content
    // for each department

    DepartmentTicketsGUI* t = new DepartmentTicketsGUI(contents.get());
    scrollGridLayout->addWidget(t, 0, 0, 1, 1);

    DepartmentTicketsGUI* t1 = new DepartmentTicketsGUI(contents.get());
    scrollGridLayout->addWidget(t1, 1, 0, 1, 1);

    DepartmentTicketsGUI* t2 = new DepartmentTicketsGUI(contents.get());
    scrollGridLayout->addWidget(t2, 2, 0, 1, 1);

    DepartmentTicketsGUI* t3 = new DepartmentTicketsGUI(contents.get());
    scrollGridLayout->addWidget(t3, 3, 0, 1, 1);

    DepartmentTicketsGUI* t4 = new DepartmentTicketsGUI(contents.get());
    scrollGridLayout->addWidget(t4, 4, 0, 1, 1);

}

