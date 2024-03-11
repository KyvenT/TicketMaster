#pragma once

#include <QScrollArea>
#include <QGridLayout>
#include "TicketGUI.h"

class DepartmentTicketsGUI : public QWidget {
public:
    DepartmentTicketsGUI() = delete;
    DepartmentTicketsGUI(const std::string& departmentName, QWidget* parent);
    DepartmentTicketsGUI(const std::string& sectionTitle, const std::string& userName, QWidget* parent);

    void Refresh();

private:

    void Setup();

    bool userTickets;
    std::string ticketSearchTerm;
    std::vector<std::unique_ptr<TicketGUI>> ticketsGUI;

    std::unique_ptr<QSpacerItem> spacer;
    std::unique_ptr<QLabel> title;
    std::unique_ptr<QGridLayout> gridLayout;
    std::unique_ptr<QGridLayout> scrollGridLayout;
    std::unique_ptr<QScrollArea> scrollArea;
    std::unique_ptr<QWidget> contents;

};
