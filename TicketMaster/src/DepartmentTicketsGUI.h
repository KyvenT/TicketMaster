#pragma once

#include <QScrollArea>
#include <QGridLayout>
#include <QComboBox>
#include "TicketGUI.h"

/**
 * @brief Department Tickets GUI displays all tickets in regards to a specific department (or user) as a list
 * @author Ryan Lambe
 */
class DepartmentTicketsGUI : public QWidget {
public:
    /**
     * @brief Default constructor should never be used
     */
    DepartmentTicketsGUI() = delete;

    /**
     * @brief Constructor for the given department, Not for User section
     * @parameter departmentName name of the department to include tickets for
     * @parameter parent the parent widget the GUI should be attached to
     */
    DepartmentTicketsGUI(const std::string& departmentName, QWidget* parent);

    /**
     * @brief Constructor for the given user, Not for Department section
     * @parameter sectionTitle the title that should be displayed for the section
     * @parameter userName the name of the user to display tickets for
     * @parameter if claimed tickets, then it will show the tickets where the user is the rep of the ticket, and can access ticket as admin
     * @parameter parent the parent widget the GUI should be attached to
     */
    DepartmentTicketsGUI(const std::string& sectionTitle, const std::string& userName, bool claimedTickets, QWidget* parent);

    /**
     * @brief Ensures Department Tickets GUI is cleaned up properly
     */
    ~DepartmentTicketsGUI() override;

    /**
     * @brief Refreshes the data displayed in the Tickets, no tickets will be added or removed
     */
    void Refresh();

    /**
     * @brief Regenerates the tickets being shows, tickets will be added and removed
     */
    void Regenerate();

private:

    /**
     * @brief common setup process for both constructor
     */
    void Setup();

    /**
     * @brief change the way tickets are sorted (called when sortType changed)
     * @parameter the new value of the sorting order as a QString
     */
    void ChangeSortType(const QString& type);


    bool userTickets; /// if the tickets displayed are for the user or department
    bool isAdmin; /// if is admin then the user should be able to modify the ticket
    bool claimedTickets; /// if claimed tickets then the tickets displayed should be ones where user is the department rep
    std::string ticketSearchTerm; /// the search term to be used when searching the Ticket Manager
    std::vector<std::unique_ptr<TicketGUI>> ticketsGUI; /// an array of the gui elements for each ticket
    std::string currentSortType; /// current method of sorting

    std::unique_ptr<QLabel> title; /// the title of the section
    std::unique_ptr<QComboBox> sortType; /// allows sorting TicketGUIs in different ways
    std::unique_ptr<QGridLayout> gridLayout; /// grid layout to organize the section
    std::unique_ptr<QGridLayout> scrollGridLayout; /// grid layout to organize the ticket GUI's
    std::unique_ptr<QScrollArea> scrollArea; /// the scroll area to allow more tickets to be accessed than would fit on screen
    std::unique_ptr<QWidget> contents; /// the contents of the scroll area
    std::unique_ptr<QSpacerItem> spacer; /// keep tickets to the top of the section

};
