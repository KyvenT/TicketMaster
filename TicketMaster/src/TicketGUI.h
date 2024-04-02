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
     * @param ticketData pointer to the data to be shown within the ticket
     * @param parent the parent widget the GUI should be attached to
     * @param showDepartment if the department section should be shown (this means its being accessed by the user)
     * @param isAdmin if the user should have access to modify the tickets within this section
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


    /// pointer to the ticket data to display
    Ticket* data;
    /// if the department section should be shown (this means its being accessed by the user)
    bool showDepartment;
    /// if the ticket should be able to be modified by the user when the popup is opened
    bool isAdmin;

    /*
     * Button Elements
     */
    /// organizes the info within the ticket GUI
    std::unique_ptr<QGridLayout> gridLayout;
    /// displays the name of the ticket within the ticket GUI
    std::unique_ptr<QLabel> name;
    /// displays the status (and optionally the department) of the ticket within the ticket GUI
    std::unique_ptr<QLabel> status;

    /*
     * Popup Elements
     */
    /// popup to access the ticket data
    std::unique_ptr<QWidget> popup = nullptr;
    /// header section of the popup
    std::unique_ptr<QWidget> popupHeader;
    /// the contents of the scroll area, contains the messages that have been sent
    std::unique_ptr<QWidget> scrollContents;
    /// the scroll area allowing more messages than would normally fit on the window to be seen
    std::unique_ptr<QScrollArea> scrollArea;

    /// organizes all the ticket data in the popup
    std::unique_ptr<QGridLayout> popupGridLayout;
    /// organizes all the header information
    std::unique_ptr<QGridLayout> headerGridLayout;
    /// organizes all the messages to be one after the other
    std::unique_ptr<QGridLayout> scrollGridLayout;

    /*
     * Popup Header
     */
    /// displays the name of the ticket in the popup
    std::unique_ptr<QLabel> popupTitle;
    /// displays the user that created the ticket
    std::unique_ptr<QLabel> popupUser;
    /// displays the user within the department that claimed the ticket
    std::unique_ptr<QLabel> popupDepartmentRep;
    /// displays the department of the ticket in the popup
    std::unique_ptr<QLabel> popupDepartment;
    /// displays the status of the ticket
    std::unique_ptr<QLabel> popupStatus;
    /// displays the severity of the ticket
    std::unique_ptr<QLabel> popupSeverityUser;
    /// allows department rep to be changed, only shown when isAdmin == true
    std::unique_ptr<QComboBox> popupDepartmentRepAdmin = nullptr;
    /// allows ticket severity to be changed, only shown when isAdmin == true
    std::unique_ptr<QComboBox> popupSeverityAdmin = nullptr;

    /*
     * Messages
     */
    /// all the message GUIs that are displayed
    std::vector<std::unique_ptr<MessageGUI>> messageGUIs;
    /// spacer to keep all the message Guis at the top of the area
    std::unique_ptr<QSpacerItem> messageSpacer;

    /*
     * Send Message
     */
    /// area for new message to be typed before it is sent
    std::unique_ptr<QTextEdit> messageContents;
    /// button to send the message created in messageContents to the ticket
    std::unique_ptr<QPushButton> sendButton;
    /// allows ticket to be marked as resolved by either the user or the admin, if already resolved it will unresolve it
    std::unique_ptr<QPushButton> resolvedButton;


    /// map to convert TicketStatus values to their names as a string
    std::map<TicketStatus, std::string> ticketStatusToString = {
            {TicketStatus::WaitingForDepartment, "Waiting For Department"},
            {TicketStatus::WaitingForUser, "Waiting For User"},
            {TicketStatus::Resolved, "Resolved"}
    };

    /// map to convert TicketSeverity values to their names as a string
    std::map<TicketSeverity, std::string> ticketSeverityToString = {
            {TicketSeverity::Mild, "Mild"},
            {TicketSeverity::Moderate, "Moderate"},
            {TicketSeverity::Urgent, "Urgent"},
            {TicketSeverity::Unknown, "Unknown"}
    };
};
