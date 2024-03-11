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
    titleFieldLabel = std::make_unique<QLabel>("Title: ", popup.get());
    popupGridLayout->addWidget(titleFieldLabel.get(), 0, 0, 1, 3);

    // department
    departmentFieldLabel = std::make_unique<QLabel>("Department: ", popup.get());
    popupGridLayout->addWidget(departmentFieldLabel.get(), 1, 0, 1, 3);

    // message
    messageFieldLabel = std::make_unique<QLabel>("Messages: ", popup.get());
    popupGridLayout->addWidget(messageFieldLabel.get(), 2, 0, 1, 1);
    messageFieldLabel->setAlignment(Qt::AlignRight);

    messageField = std::make_unique<QLabel>(data.getMessages()[0].message.c_str(), popup.get());
    popupGridLayout->addWidget(messageField.get(), 2, 1, 1, 2);
}
