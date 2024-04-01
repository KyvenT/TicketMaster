#pragma once

#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <memory>
#include <QComboBox>
#include <QScrollArea>
#include <QTextEdit>
#include <iostream>
#include "Ticket.h"
#include "MessageGUI.h"

/**
 * @brief Ticket GUI displays information about a ticket, meant to be used in a list of other TicketGUIs, and provides more details when clicked on
 * @author Ryan Lambe
 */
class TicketGUI : public QPushButton {
public:

    /**
     * @brief Default constructor should never be used
     */
    TicketGUI() = delete;

    /**
     * @brief creates a single Ticket GUI
     * @parameter ticketData pointer to the data to be shown within the ticket
     * @parameter parent the parent widget the GUI should be attached to
     * @parameter showDepartment if the department section should be shown (this means its being accessed by the user)
     * @parameter isAdmin if the user should have access to modify the tickets within this section
     */
    TicketGUI(Ticket* ticketData, QWidget* parent, bool showDepartment, bool isAdmin);

    /**
     * @brief Ensures Ticket GUI is cleaned up properly
     */
    ~TicketGUI() override;

    /**
     * @brief Refreshes the data being displayed in the ticket GUI and popup
     */
    void RefreshTicket();

private:

    /**
     * @brief Creates a popup with the details of the ticket (called when TicketGUI is clicked on)
     */
    void CreateTicketPopup();

    /**
     * @brief Changes the department rep to value of popupDepartmentRepAdmin, refreshes UserWindow, and regenerates "My Tickets" (called when popupDepartmentRepAdmin is changed)
     */
    void ChangeDeptRep();

    /**
     * @brief Changes the severity to value of popupSeverityAdmin and refreshes UserWindow (called when popupSeverityAdmin is changed)
     */
    void ChangeSeverity();

    /**
     * @brief Toggles if the ticket is marked as resolved or not, then refreshes UserWindow (called when resolvedButton is clicked)
     */
    void ToggleResolved();

    /**
     * @brief Sends message using messageContents from the logged in user, then refreshes UserWindow (called when sendButton is pressed)
     */
    void SendMessage();


    Ticket* data; /// pointer to the ticket data to display
    bool showDepartment; /// if the department section should be shown (this means its being accessed by the user)
    bool isAdmin; /// if the ticket should be able to be modified by the user when the popup is opened

    // button elements
    std::unique_ptr<QGridLayout> gridLayout; /// organizes the info within the ticket GUI
    std::unique_ptr<QLabel> name; /// displays the name of the ticket within the ticket GUI
    std::unique_ptr<QLabel> status; /// displays the status (and optionally the department) of the ticket within the ticket GUI

    // popup elements
    std::unique_ptr<QWidget> popup = nullptr; /// popup to access the ticket data
    std::unique_ptr<QWidget> popupHeader; /// header section of the popup
    std::unique_ptr<QWidget> scrollContents; /// the contents of the scroll area, contains the messages that have been sent
    std::unique_ptr<QScrollArea> scrollArea; /// the scroll area allowing more messages than would normally fit on the window to be seen

    std::unique_ptr<QGridLayout> popupGridLayout; /// organizes all the ticket data in the popup
    std::unique_ptr<QGridLayout> headerGridLayout; /// organizes all the header information
    std::unique_ptr<QGridLayout> scrollGridLayout; /// organizes all the messages to be one after the other

    // popup header
    std::unique_ptr<QLabel> popupTitle; /// displays the name of the ticket in the popup
    std::unique_ptr<QLabel> popupUser; /// displays the user that created the ticket
    std::unique_ptr<QLabel> popupDepartmentRep; /// displays the user within the department that claimed the ticket
    std::unique_ptr<QLabel> popupDepartment; /// displays the department of the ticket in the popup
    std::unique_ptr<QLabel> popupStatus; /// displays the status of the ticket
    std::unique_ptr<QLabel> popupSeverityUser; /// displays the severity of the ticket
    std::unique_ptr<QComboBox> popupDepartmentRepAdmin = nullptr; /// allows department rep to be changed, only shown when isAdmin == true
    std::unique_ptr<QComboBox> popupSeverityAdmin = nullptr; /// allows ticket severity to be changed, only shown when isAdmin == true

    // messages
    std::vector<std::unique_ptr<MessageGUI>> messageGUIs; /// all the message GUIs that are displayed
    std::unique_ptr<QSpacerItem> messageSpacer; /// spacer to keep all the message Guis at the top of the area

    // send message
    std::unique_ptr<QTextEdit> messageContents; /// area for new message to be typed before it is sent
    std::unique_ptr<QPushButton> sendButton; /// button to send the message created in messageContents to the ticket
    std::unique_ptr<QPushButton> resolvedButton; /// allows ticket to be marked as resolved by either the user or the admin, if already resolved it will unresolve it


    std::map<TicketStatus, std::string> ticketStatusToString = {
            {TicketStatus::WaitingForDepartment, "Waiting For Department"},
            {TicketStatus::WaitingForUser, "Waiting For User"},
            {TicketStatus::Resolved, "Resolved"}
    }; /// map to convert TicketStatus values to their names as a string

    std::map<TicketSeverity, std::string> ticketSeverityToString = {
            {TicketSeverity::Mild, "Mild"},
            {TicketSeverity::Moderate, "Moderate"},
            {TicketSeverity::Urgent, "Urgent"},
            {TicketSeverity::Unknown, "Unknown"}
    }; /// map to convert TicketSeverity values to their names as a string
};
