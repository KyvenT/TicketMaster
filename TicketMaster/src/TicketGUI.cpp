#include "TicketGUI.h"

#include "UserWindow.h"

#include <utility>

TicketGUI::TicketGUI(Ticket* ticketData, QWidget *parent, bool showDepartment) : QPushButton(parent), data(std::move(ticketData)) {

    connect(this, &QPushButton::clicked, this, &TicketGUI::CreateTicketPopup);

    gridLayout = std::make_unique<QGridLayout>(this);
    this->setMinimumHeight(50);

    name = std::make_unique<QLabel>(this);
    status = std::make_unique<QLabel>(this);
    department = std::make_unique<QLabel>(this);

    gridLayout->addWidget(name.get(), 0, 0, 1, 1);
    gridLayout->addWidget(status.get(), 0, 5, 1, 1);
    gridLayout->addWidget(department.get(), 0, 1, 1, 4);

    name->setAlignment(Qt::AlignLeft);
    status->setAlignment(Qt::AlignRight);
    department->setAlignment(Qt::AlignRight);

    QFont font = name->font();
    font.setPointSize(16);

    name->setFont(font);
    status->setFont(font);
    department->setFont(font);

    name->setText(data->getTitle().c_str());

    if(data->getStatus() == TicketStatus::WaitingForUser)
        status->setText("Waiting for User");
    else if(data->getStatus() == TicketStatus::WaitingForDepartment)
        status->setText("Waiting for Department");
    else
        status->setText("Resolved");

    if(showDepartment)
        department->setText(data->getDepartment().c_str());
    else
        department->setText("");
}

void TicketGUI::CreateTicketPopup() {
    if(popup){
        popup->show();
        popup->resize(400, 300);
        return;
    }

    // create window
    popup = std::make_unique<QWidget>();
    popup->setWindowTitle(data->getTitle().c_str());
    popup->resize(400, 300);
    popup->show();

    popupGridLayout = std::make_unique<QGridLayout>(popup.get());

    // title
    popupTitle = std::make_unique<QLabel>(("Title: " + data->getTitle()).c_str(), popup.get());
    popupGridLayout->addWidget(popupTitle.get(), 0, 0, 1, 4);

    // department
    popupDepartment = std::make_unique<QLabel>(("Title: " + data->getDepartment()).c_str(), popup.get());
    popupGridLayout->addWidget(popupDepartment.get(), 1, 0, 1, 4);

    // message
    popupMessageLabel = std::make_unique<QLabel>("Messages: ", popup.get());
    popupGridLayout->addWidget(popupMessageLabel.get(), 2, 0, 1, 4);

    popupMessage = std::make_unique<QLabel>(data->getMessages()[0].message.c_str(), popup.get());
    popupGridLayout->addWidget(popupMessage.get(), 3, 0, 4, 4);
    popupMessage->setAlignment(Qt::AlignRight);

    // actions
    std::string passOn = "Pass to ";
    if(data->getStatus() == TicketStatus::WaitingForUser)
        passOn += "Department";
    else
        passOn += "User";

    passTicket = std::make_unique<QPushButton>(passOn.c_str(), popup.get());
    popupGridLayout->addWidget(passTicket.get(), 7, 1, 1, 1);
    connect(passTicket.get(), &QPushButton::clicked, this, &TicketGUI::PassTicket);

    markResolved = std::make_unique<QPushButton>("Mark as Resolved", popup.get());
    popupGridLayout->addWidget(markResolved.get(), 7, 2, 1, 1);
    connect(markResolved.get(), &QPushButton::clicked, this, &TicketGUI::MarkResolved);
}

void TicketGUI::MarkResolved() {
    data->setStatus(TicketStatus::Resolved);
    UserWindow::RefreshGUI();
}

void TicketGUI::PassTicket() {
    if(data->getStatus() == TicketStatus::WaitingForDepartment)
        data->setStatus(TicketStatus::WaitingForUser);
    else
        data->setStatus(TicketStatus::WaitingForDepartment);
    UserWindow::RefreshGUI();
}
