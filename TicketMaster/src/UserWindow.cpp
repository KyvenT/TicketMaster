#include "UserWindow.h"
#include "DepartmentTicketsGUI.h"
#include "UserManager.h"
#include "TicketManager.h"

#include <QLabel>

UserWindow::UserWindow(const std::string &username) {

    user = UserManager::GetUser(username);

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
    connect(newTicketButton.get(), &QPushButton::clicked, this, &UserWindow::NewTicket);

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

    departmentsGUI.push_back(std::make_unique<DepartmentTicketsGUI>("My Tickets", user->GetName(), contents.get()));
    scrollGridLayout->addWidget(departmentsGUI.back().get(), 0, 0, 1, 1);

    const std::vector<std::string>& departments = user->GetDepartments();
    for(int i = 0; i < departments.size(); i++){
        departmentsGUI.push_back(std::make_unique<DepartmentTicketsGUI>(departments[i], contents.get()));
        scrollGridLayout->addWidget(departmentsGUI.back().get(), i + 1, 0, 1, 1);
    }
}

void UserWindow::RefreshGUI() {
    for(auto& department : departmentsGUI){
        department->Refresh();
    }
}

int temp = 0;

void UserWindow::NewTicket() {
    /*if(popupOpen){
        popup->show();
        return;
    }
    popupOpen = true;

    popup = std::make_unique<QWidget>();
    popup->show();
    popup->setWindowTitle("New Ticket");*/

    ticketManager::CreateTicket(user->GetName(), "Admin", "New Ticket Temp Name: " + std::to_string(temp), "message");
    temp++;
    RefreshGUI();
}
