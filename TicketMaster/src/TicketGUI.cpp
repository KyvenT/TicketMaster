#include "TicketGUI.h"

#include <utility>

TicketGUI::TicketGUI(ticket  ticketData, QWidget *parent) : QPushButton(parent), data(std::move(ticketData)) {

    connect(this, &QPushButton::clicked, this, &TicketGUI::CreateTicketPopup);

    gridLayout = std::make_unique<QGridLayout>(this);
    this->setMinimumHeight(50);

    name = std::make_unique<QLabel>(this);
    status = std::make_unique<QLabel>(this);
    otherTest = std::make_unique<QLabel>(this);

    gridLayout->addWidget(name.get(), 0, 0, 1, 1);
    gridLayout->addWidget(status.get(), 0, 5, 1, 1);
    gridLayout->addWidget(otherTest.get(), 0, 1, 1, 4);

    name->setAlignment(Qt::AlignLeft);
    status->setAlignment(Qt::AlignRight);
    otherTest->setAlignment(Qt::AlignRight);

    QFont font = name->font();
    font.setPointSize(16);

    name->setFont(font);
    status->setFont(font);
    otherTest->setFont(font);

    name->setText(data.getTitle().c_str());
    status->setText("Status");
    otherTest->setText("Other Test");
}

void TicketGUI::CreateTicketPopup() {
    if(popupOpen){
        popup->show();
        return;
    }
    popupOpen = true;

    popup = std::make_unique<QWidget>();
    popup->show();
    popup->setWindowTitle("Ticket");
}
