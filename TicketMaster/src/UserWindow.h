#pragma once

#include <QtWidgets>
#include <QLabel>
#include <string>
#include <QCloseEvent>

#include "User.h"
#include "DepartmentTicketsGUI.h"

/**
 * @brief User Window is the user end of the program, allowing the user to create/manage tickets
 * @author Ryan Lambe
 */
class UserWindow : public QWidget {
public:

    /**
     * @brief Default constructor should never be used
     */
    UserWindow() = delete;

    /**
     * @brief Constructor for User Window, creates and displays GUI (Note: Only ONE User Window can be created)
     * @param username the name of the user that has been logged in
     */
    explicit UserWindow(const std::string& username);

    /**
     * @brief Ensures User Window is cleaned up properly
     */
    ~UserWindow() override;

    /**
     * @brief reloads all data within tickets being displayed
     */
    static void RefreshGUI();

    /**
     * @brief deletes and then recreates all ticketGUIs, adding new tickets and removing non-existent tickets (Note: Be careful when using in conjunction with TicketGUIs as it can cause a segmentation fault)
     */
    static void RegenerateGUI();

    /**
     * @brief deletes and then recreates ticketGUIs within the "My Tickets" department GUI, adding new tickets and removing non-existent tickets (Note: this action only sets a flag so that it will be regenerated)
     */
    static void RegenerateClaimedTickets();

    /**
     * @brief gets the name of the user that is currently signed in
     * @return a std::string containing the name of the signed in user
     */
    static std::string GetUsersName();

protected:

    /**
     * @brief override so that the "My Tickets" department GUI tickets will be regenerated safely when flag is set from RegenerateClaimedTickets
     * @param event is the parameter needed for the default functionality
     */
    void mousePressEvent(QMouseEvent *event) override;

private:

    /**
     * @brief Opens the new ticket popup (Used by the new ticket button)
     */
    void NewTicket();

    /**
     * @brief Creates a ticket using the values from the new ticket popup (Used by create ticket button)
     */
    void CreateTicket();

    /// a pointer to the instance of the User Window class (note: there will only be one instance)
    static UserWindow* userWindow;
    /// whether the claimed tickets should be regenerated next mousePressEvent
    static bool regenerateClaimedTickets;

    /// shared pointer of the user that is logged in
    std::shared_ptr<User> user;
    /// array of Department GUIs, plus one for the users created tickets
    std::vector<std::unique_ptr<DepartmentTicketsGUI>> departmentsGUI;

    /// button to create a new ticket
    std::unique_ptr<QPushButton> newTicketButton;
    /// spacer to ensure the new ticket button is on the left side
    std::unique_ptr<QSpacerItem> spacer;

    /// Grid layout to organize the window
    std::unique_ptr<QGridLayout> gridLayout;
    /// Grid layout to organize the department GUI's
    std::unique_ptr<QGridLayout> scrollGridLayout;
    /// Scroll area to ensure lower department GUI's can be read
    std::unique_ptr<QScrollArea> scrollArea;
    /// Contents of the scroll area
    std::unique_ptr<QWidget> contents;

    /// new ticket popup window
    std::unique_ptr<QWidget> popup = nullptr;
    /// grid layout to organize the popup window
    std::unique_ptr<QGridLayout> popupGridLayout;

    /// the label for the title field in the popup window
    std::unique_ptr<QLabel> titleFieldLabel;
    /// the title field in the popup window
    std::unique_ptr<QLineEdit> titleField;
    /// the label for the department field in the popup window
    std::unique_ptr<QLabel> departmentFieldLabel;
    /// the department field in the popup window
    std::unique_ptr<QComboBox> departmentField;
    /// the label for the message field in the popup window
    std::unique_ptr<QLabel> messageFieldLabel;
    /// the message field in the popup window
    std::unique_ptr<QTextEdit> messageField;
    /// the button to create the ticket after all fields are filled
    std::unique_ptr<QPushButton> createTicketButton;
};
