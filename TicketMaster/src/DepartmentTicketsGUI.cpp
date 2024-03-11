#include <QLabel>
#include "DepartmentTicketsGUI.h"
#include "TicketGUI.h"
#include "TicketManager.h"

DepartmentTicketsGUI::DepartmentTicketsGUI(const std::string &departmentName, QWidget *parent) {

    userTickets = false;
    ticketSearchTerm = departmentName;

    const QString tempDepartmentName = departmentName.c_str();
    title = std::make_unique<QLabel>(tempDepartmentName + ": ", this);

    Setup();

    std::vector<ticket> tickets = ticketManager::GetDeptTickets(departmentName);
    for(int i = 0; i < tickets.size(); i++){
        ticketsGUI.push_back(std::make_unique<TicketGUI>(tickets[i], contents.get(), userTickets));
        scrollGridLayout->addWidget(ticketsGUI.back().get(), i, 0, 1, 1);
    }

    spacer = std::make_unique<QSpacerItem>(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    scrollGridLayout->addItem(spacer.get(), (int)tickets.size(), 0, 1, 1);
}

DepartmentTicketsGUI::DepartmentTicketsGUI(const std::string& sectionTitle, const std::string& userName, QWidget *parent) : QWidget(parent) {

    userTickets = true;
    ticketSearchTerm = userName;

    const QString tempSectionTitle = sectionTitle.c_str();
    title = std::make_unique<QLabel>(tempSectionTitle + ": ", this);

    Setup();

    std::vector<ticket> tickets = ticketManager::GetUserTickets(userName);
    for(int i = 0; i < tickets.size(); i++){
        ticketsGUI.push_back(std::make_unique<TicketGUI>(tickets[i], contents.get(), userTickets));
        scrollGridLayout->addWidget(ticketsGUI.back().get(), i, 0, 1, 1);
    }

    spacer = std::make_unique<QSpacerItem>(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    scrollGridLayout->addItem(spacer.get(), (int)tickets.size(), 0, 1, 1);
}

void DepartmentTicketsGUI::Setup() {
    QPalette pal = this->palette();
    pal.setColor(this->backgroundRole(), Qt::lightGray);
    this->setPalette(pal);

    this->setMinimumHeight(300);

    gridLayout = std::make_unique<QGridLayout>(this);
    gridLayout->addWidget(title.get(), 0, 0, 1, 1);

    QFont font = title->font();
    font.setPointSize(24);
    title->setFont(font);

    scrollArea = std::make_unique<QScrollArea>(this);
    scrollArea->setWidgetResizable(true);
    gridLayout->addWidget(scrollArea.get(), 1, 0, 1, 1);

    contents = std::make_unique<QWidget>();
    scrollArea->setWidget(contents.get());

    scrollGridLayout = std::make_unique<QGridLayout>(contents.get());
}

void DepartmentTicketsGUI::Refresh() {

    // delete currently displayed tickets
    scrollGridLayout->removeItem(spacer.get());
    for(auto& ticket : ticketsGUI){
        scrollGridLayout->removeWidget(ticket.get());
    }
    ticketsGUI.clear();

    // get tickets
    std::vector<ticket> tickets;
    if(userTickets)
        tickets = ticketManager::GetUserTickets(ticketSearchTerm);
    else
        tickets = ticketManager::GetDeptTickets(ticketSearchTerm);

    // create tickets
    for(int i = 0; i < tickets.size(); i++){
        ticketsGUI.push_back(std::make_unique<TicketGUI>(tickets[i], contents.get(), userTickets));
        scrollGridLayout->addWidget(ticketsGUI.back().get(), i, 0, 1, 1);
    }

    spacer = std::make_unique<QSpacerItem>(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    scrollGridLayout->addItem(spacer.get(), (int)tickets.size(), 0, 1, 1);
}
