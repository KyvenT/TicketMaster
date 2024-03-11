#pragma once

#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include "Ticket.h"

class TicketGUI : public QPushButton {
public:
    TicketGUI() = delete;
    TicketGUI(ticket  ticketData, QWidget* parent);

private:

    void CreateTicketPopup();

    ticket data;

    // button elements
    std::unique_ptr<QGridLayout> gridLayout;
    std::unique_ptr<QLabel> name;
    std::unique_ptr<QLabel> status;
    std::unique_ptr<QLabel> otherTest;

    // popup elements
    bool popupOpen = false;
    std::unique_ptr<QWidget> popup;

};
