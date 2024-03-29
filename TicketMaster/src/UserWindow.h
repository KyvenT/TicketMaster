#pragma once

#include <QtWidgets>
#include <QLabel>
#include <string>

#include "User.h"
#include "DepartmentTicketsGUI.h"

/**
 * User Window is the user end of the program, allowing the user to create/manage tickets
 */
class UserWindow : public QWidget {
public:

    UserWindow() = delete;

    /**
     * Constructor for User Window, creates and displays GUI
     * Note: Only ONE User Window can be created
     * @param username the name of the user that has been logged in
     */
    explicit UserWindow(const std::string& username);

    /**
     * Ensures User Window is cleaned up properly
     */
    ~UserWindow() override;

    /**
     * RefreshGUI reloads all DepartmentTicketsGUI's contained in the User Window
     */
    static void RefreshGUI();

private:

    /**
     * Opens the new ticket popup
     * Used by the new Ticket Button
     */
    void NewTicket();

    /**
     * Creates a ticket using the values from the new ticket popup
     * Used by create Ticket Button
     */
    void CreateTicket();

    static UserWindow* userWindow; /// a pointer to the instance of the User Window class (note: there will only be one instance)

    std::shared_ptr<User> user; /// shared pointer of the user that is logged in
    std::vector<std::unique_ptr<DepartmentTicketsGUI>> departmentsGUI; /// array of Department GUIs, plus one for the users created tickets

    std::unique_ptr<QPushButton> newTicketButton; /// button to create a new ticket
    std::unique_ptr<QSpacerItem> spacer; /// spacer to ensure the new ticket button is on the left side

    std::unique_ptr<QGridLayout> gridLayout; /// Grid layout to organize the window
    std::unique_ptr<QGridLayout> scrollGridLayout; /// Grid layout to organize the department GUI's
    std::unique_ptr<QScrollArea> scrollArea; /// Scroll area to ensure lower department GUI's can be read
    std::unique_ptr<QWidget> contents; /// Contents of the scroll area

    std::unique_ptr<QWidget> popup = nullptr; /// new ticket popup window
    std::unique_ptr<QGridLayout> popupGridLayout; /// grid layout to organize the popup window

    std::unique_ptr<QLabel> titleFieldLabel; /// the label for the title field in the popup window
    std::unique_ptr<QLineEdit> titleField; /// the title field in the popup window
    std::unique_ptr<QLabel> departmentFieldLabel; /// the label for the department field in the popup window
    std::unique_ptr<QComboBox> departmentField; /// the department field in the popup window
    std::unique_ptr<QLabel> messageFieldLabel; /// the label for the message field in the popup window
    std::unique_ptr<QTextEdit> messageField; /// the message field in the popup window
    std::unique_ptr<QPushButton> createTicketButton; /// the button to create the ticket after all fields are filled
};
