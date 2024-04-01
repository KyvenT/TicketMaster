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

    std::vector<Ticket*> tickets = ticketManager::GetDeptTickets(departmentName);
    for(int i = 0; i < tickets.size(); i++){
        ticketsGUI.push_back(std::make_unique<TicketGUI>(tickets[i], contents.get(), userTickets, !userTickets));
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

    std::vector<Ticket*> tickets = ticketManager::GetUserTickets(userName);
    for(int i = 0; i < tickets.size(); i++){
        ticketsGUI.push_back(std::make_unique<TicketGUI>(tickets[i], contents.get(), userTickets, !userTickets));
        scrollGridLayout->addWidget(ticketsGUI.back().get(), i, 0, 1, 1);
    }

    spacer = std::make_unique<QSpacerItem>(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    scrollGridLayout->addItem(spacer.get(), (int)tickets.size(), 0, 1, 1);
}

DepartmentTicketsGUI::~DepartmentTicketsGUI() {
    scrollGridLayout->removeItem(spacer.get());
    for(auto& ticket : ticketsGUI){
        scrollGridLayout->removeWidget(ticket.get());
    }
    ticketsGUI.clear();
    scrollGridLayout = nullptr;
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

    sortType = std::make_unique<QComboBox>(this);
    gridLayout->addWidget(sortType.get(), 0, 1, 1, 1);
    sortType->addItem("Oldest First");
    sortType->addItem("Newest First");
    sortType->addItem("Highest Priority");
    connect(sortType.get(), &QComboBox::currentTextChanged, this, &DepartmentTicketsGUI::ChangeSortType);

    scrollArea = std::make_unique<QScrollArea>(this);
    scrollArea->setWidgetResizable(true);
    gridLayout->addWidget(scrollArea.get(), 1, 0, 1, 2);

    contents = std::make_unique<QWidget>();
    scrollArea->setWidget(contents.get());

    scrollGridLayout = std::make_unique<QGridLayout>(contents.get());
}

void DepartmentTicketsGUI::Refresh() {
    for(auto& ticket : ticketsGUI){
        ticket->RefreshTicketPopup();
    }
}

void DepartmentTicketsGUI::Regenerate() {

    // delete currently displayed tickets
    scrollGridLayout->removeItem(spacer.get());
    for(auto& ticket : ticketsGUI){
        scrollGridLayout->removeWidget(ticket.get());
    }
    ticketsGUI.clear();

    // get tickets
    std::vector<Ticket*> tickets;
    if(userTickets)
        tickets = ticketManager::GetUserTickets(ticketSearchTerm);
    else
        tickets = ticketManager::GetDeptTickets(ticketSearchTerm);

    // sort tickets
    if(currentSortType == "Highest Priority"){
        std::sort(tickets.begin(), tickets.end(), [](const Ticket* a, const Ticket* b) {
            return a->getSeverity() > b->getSeverity();
        });
    }
    else if(currentSortType == "Newest First"){
        std::sort(tickets.begin(), tickets.end(), [](const Ticket* a, const Ticket* b) {
            return a->getModifiedTime() > b->getModifiedTime();
        });
    }
    else { // "Oldest First"
        std::sort(tickets.begin(), tickets.end(), [](const Ticket* a, const Ticket* b) {
            return a->getModifiedTime() < b->getModifiedTime();
        });
    }

    // create tickets
    for(int i = 0; i < tickets.size(); i++){
        ticketsGUI.push_back(std::make_unique<TicketGUI>(tickets[i], contents.get(), userTickets, !userTickets));
        scrollGridLayout->addWidget(ticketsGUI.back().get(), i, 0, 1, 1);
    }

    spacer = std::make_unique<QSpacerItem>(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    scrollGridLayout->addItem(spacer.get(), (int)tickets.size(), 0, 1, 1);
}

void DepartmentTicketsGUI::ChangeSortType(const QString& type) {
    currentSortType = type.toStdString();
    Refresh();
}
