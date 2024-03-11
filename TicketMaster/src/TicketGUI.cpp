#include "TicketGUI.h"

#include <utility>

TicketGUI::TicketGUI(ticket  ticketData, QWidget *parent, bool showDepartment) : QPushButton(parent), data(std::move(ticketData)) {

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

    name->setText(data.getTitle().c_str());
    status->setText("Status");
    if(showDepartment)
        department->setText(data.getDepartment().c_str());
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
    popup->setWindowTitle(data.getTitle().c_str());
    popup->resize(400, 300);
    popup->show();

    popupGridLayout = std::make_unique<QGridLayout>(popup.get());

    // title
    popupTitle = std::make_unique<QLabel>(("Title: " + data.getTitle()).c_str(), popup.get());
    popupGridLayout->addWidget(popupTitle.get(), 0, 0, 1, 1);

    // department
    popupDepartment = std::make_unique<QLabel>(("Title: " + data.getDepartment()).c_str(), popup.get());
    popupGridLayout->addWidget(popupDepartment.get(), 1, 0, 1, 1);

    // message
    popupMessageLabel = std::make_unique<QLabel>("Messages: ", popup.get());
    popupGridLayout->addWidget(popupMessageLabel.get(), 2, 0, 1, 1);

    popupMessage = std::make_unique<QLabel>(data.getMessages()[0].message.c_str(), popup.get());
    popupGridLayout->addWidget(popupMessage.get(), 3, 0, 4, 1);
    popupMessage->setAlignment(Qt::AlignRight);
}
