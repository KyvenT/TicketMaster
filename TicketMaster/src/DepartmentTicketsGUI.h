#pragma once

#include <QScrollArea>
#include <QGridLayout>
#include "TicketGUI.h"

/**
 * Department Tickets GUI displays all tickets in regards to a specific department (or user) as a list
 */
class DepartmentTicketsGUI : public QWidget {
public:
    DepartmentTicketsGUI() = delete;

    /**
     * Constructor for the given department, Not for User section
     * @param departmentName name of the department to include tickets for
     * @param parent the parent widget the GUI should be attached to
     */
    DepartmentTicketsGUI(const std::string& departmentName, QWidget* parent);

    /**
     * Constructor for the given user, Not for Department section
     * @param sectionTitle the title that should be displayed for the section
     * @param userName the name of the user to display tickets for
     * @param parent the parent widget the GUI should be attached to
     */
    DepartmentTicketsGUI(const std::string& sectionTitle, const std::string& userName, QWidget* parent);

    /**
     * Reloads Tickets displayed for the Department/User
     */
    void Refresh();

private:

    /**
     * common setup process for both constructor
     */
    void Setup();

    bool userTickets; /// if the tickets displayed are for the user or department
    std::string ticketSearchTerm; /// the search term to be used when searching the Ticket Manager
    std::vector<std::unique_ptr<TicketGUI>> ticketsGUI; /// an array of the gui elements for each ticket

    std::unique_ptr<QLabel> title; /// the title of the section
    std::unique_ptr<QGridLayout> gridLayout; /// grid layout to organize the section
    std::unique_ptr<QGridLayout> scrollGridLayout; /// grid layout to organize the ticket GUI's
    std::unique_ptr<QScrollArea> scrollArea; /// the scroll area to allow more tickets to be accessed than would fit on screen
    std::unique_ptr<QWidget> contents; /// the contents of the scroll area
    std::unique_ptr<QSpacerItem> spacer; /// keep tickets to the top of the section

};
