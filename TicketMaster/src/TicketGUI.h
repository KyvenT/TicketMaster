#pragma once

#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include "Ticket.h"

/**
 * Ticket GUI displays information about a ticket, meant to be used in a list of other TicketGUIs, and provides more details when clicked on
 */
class TicketGUI : public QPushButton {
public:
    TicketGUI() = delete;

    /**
     * creates a single Ticket GUI
     * @param ticketData pointer to the data to be shown within the ticket
     * @param parent the parent widget the GUI should be attached to
     * @param showDepartment if the department section should be shown (this means its being accessed by the user)
     */
    TicketGUI(Ticket* ticketData, QWidget* parent, bool showDepartment);

private:

    /**
     * Creates a popup with the details of the ticket
     * called when TicketGUI is clicked on
     */
    void CreateTicketPopup();

    /**
     * Marks the ticket as resolved, then refreshes GUI
     * called when mark resolved button is clicked on
     */
    void MarkResolved();

    /**
     * Marks the ticket as being passed on to either the user or department (depends on current state), then refreshes GUI
     * called when pass ticket button is clicked on
     */
    void PassTicket();


    Ticket* data; /// pointer to the ticket data to display
    bool showDepartment; /// if the department section should be shown (this means its being accessed by the user)

    // button elements
    std::unique_ptr<QGridLayout> gridLayout; /// organizes the info within the ticket GUI
    std::unique_ptr<QLabel> name; /// displays the name of the ticket within the ticket GUI
    std::unique_ptr<QLabel> status; /// displays the status (and optionally the department) of the ticket within the ticket GUI

    // popup elements
    std::unique_ptr<QWidget> popup = nullptr; /// popup to access the ticket data
    std::unique_ptr<QGridLayout> popupGridLayout; /// organizes all the ticket data in the popup
    std::unique_ptr<QLabel> popupTitle; /// displays the name of the ticket in the popup
    std::unique_ptr<QLabel> popupDepartment; /// displays the department of the ticket in the popup
    std::unique_ptr<QLabel> popupMessageLabel; /// displays the header for the ticket message in the popup
    std::unique_ptr<QLabel> popupMessage; /// displays the message of the ticket in the popup

    std::unique_ptr<QPushButton> markResolved; /// button to mark the ticket as resolved within popup
    std::unique_ptr<QPushButton> passTicket; /// button to pass the ticket to the other party within popup
};
