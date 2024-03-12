#pragma once

#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include "Ticket.h"

class TicketGUI : public QPushButton {
public:
    TicketGUI() = delete;
    TicketGUI(Ticket ticketData, QWidget* parent, bool showDepartment);

private:

    void CreateTicketPopup();
    void MarkResolved();
    void PassTicket();

    Ticket data;

    // button elements
    std::unique_ptr<QGridLayout> gridLayout;
    std::unique_ptr<QLabel> name;
    std::unique_ptr<QLabel> status;
    std::unique_ptr<QLabel> department;

    // popup elements
    std::unique_ptr<QWidget> popup = nullptr;
    std::unique_ptr<QGridLayout> popupGridLayout;
    std::unique_ptr<QLabel> popupTitle;
    std::unique_ptr<QLabel> popupDepartment;
    std::unique_ptr<QLabel> popupMessageLabel;
    std::unique_ptr<QLabel> popupMessage;

    std::unique_ptr<QPushButton> markResolved;
    std::unique_ptr<QPushButton> passTicket;
};
