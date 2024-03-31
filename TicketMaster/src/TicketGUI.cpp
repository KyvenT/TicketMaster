#include "TicketGUI.h"

#include "UserWindow.h"
#include "UserManager.h"

#include <utility>

TicketGUI::TicketGUI(Ticket* ticketData, QWidget *parent, bool showDepartment) : QPushButton(parent), data(std::move(ticketData)), showDepartment(showDepartment) {

    connect(this, &QPushButton::clicked, this, &TicketGUI::CreateTicketPopup);

    gridLayout = std::make_unique<QGridLayout>(this);
    this->setMinimumHeight(50);

    name = std::make_unique<QLabel>(this);
    status = std::make_unique<QLabel>(this);

    gridLayout->addWidget(name.get(), 0, 0, 1, 1);
    gridLayout->addWidget(status.get(), 0, 5, 1, 1);

    name->setAlignment(Qt::AlignLeft);
    status->setAlignment(Qt::AlignRight);

    QFont font = name->font();
    font.setPointSize(16);

    name->setFont(font);
    status->setFont(font);

    name->setText(data->getTitle().c_str());

    if(data->getStatus() == TicketStatus::WaitingForUser)
        status->setText("Waiting for User");
    else if(data->getStatus() == TicketStatus::WaitingForDepartment)
        status->setText("Waiting for Department");
    else
        status->setText("Resolved");

    if(showDepartment)
        status->setText((data->getDepartment() + " | " + status->text().toStdString()).c_str());
}

void TicketGUI::CreateTicketPopup() {
    if(popup){
        popup->show();
        popup->resize(700, 600);
        RefreshTicketPopup();
        return;
    }

    // create window
    popup = std::make_unique<QWidget>();
    popup->setWindowTitle(data->getTitle().c_str());
    popup->resize(700, 600);
    popup->show();

    popupGridLayout = std::make_unique<QGridLayout>(popup.get());

    // header
    popupHeader = std::make_unique<QWidget>(popup.get());
    popupGridLayout->addWidget(popupHeader.get(), 0, 0, 1, 1);
    headerGridLayout = std::make_unique<QGridLayout>(popupHeader.get());
    popupHeader->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);

    // title
    popupTitle = std::make_unique<QLabel>(data->getTitle().c_str(), popupHeader.get());
    popupTitle->setAlignment(Qt::AlignCenter);
    headerGridLayout->addWidget(popupTitle.get(), 0, 0, 1, 4);

    QFont font = popupTitle->font();
    font.setPointSize(18);
    popupTitle->setFont(font);

    // header info
    popupUser = std::make_unique<QLabel>(("User: \t\t\t" + data->getUser()).c_str(), popupHeader.get());
    headerGridLayout->addWidget(popupUser.get(), 1, 0, 1, 4);

    if(showDepartment){
        popupDepartmentRep = std::make_unique<QLabel>(("Department Rep: \t\t" + data->getDeptRep()).c_str(), popupHeader.get());
        headerGridLayout->addWidget(popupDepartmentRep.get(), 2, 0, 1, 4);
    }
    else{
        popupDepartmentRep = std::make_unique<QLabel>("Department Rep: ", popupHeader.get());
        headerGridLayout->addWidget(popupDepartmentRep.get(), 2, 0, 1, 1);

        popupDepartmentRepAdmin = std::make_unique<QComboBox>(popupHeader.get());
        headerGridLayout->addWidget(popupDepartmentRepAdmin.get(), 2, 1, 1, 3);

        popupDepartmentRepAdmin->addItem("None");
        auto users = UserManager::GetUsersInDepartment(data->getDepartment());
        for(const auto& user : users){
            popupDepartmentRepAdmin->addItem(user->GetName().c_str());
        }

        popupDepartmentRepAdmin->setCurrentText(data->getDeptRep().c_str());
        connect(popupDepartmentRepAdmin.get(), &QComboBox::currentTextChanged, this, &TicketGUI::ChangeDeptRep);
    }

    popupDepartment = std::make_unique<QLabel>(("Department: \t\t" + data->getDepartment()).c_str(), popupHeader.get());
    headerGridLayout->addWidget(popupDepartment.get(), 3, 0, 1, 4);

    popupStatus = std::make_unique<QLabel>(("Status: \t\t\t" + ticketStatusToString[data->getStatus()]).c_str(), popupHeader.get());
    headerGridLayout->addWidget(popupStatus.get(), 4, 0, 1, 2);

    if(showDepartment){
        popupSeverityUser = std::make_unique<QLabel>(("Severity: " + ticketSeverityToString[data->getSeverity()]).c_str(), popupHeader.get());
        popupSeverityUser->setAlignment(Qt::AlignCenter);
        headerGridLayout->addWidget(popupSeverityUser.get(), 4, 2, 1, 2);
    }
    else{
        popupSeverityUser = std::make_unique<QLabel>("Severity: ", popupHeader.get());
        popupSeverityUser->setAlignment(Qt::AlignRight);
        headerGridLayout->addWidget(popupSeverityUser.get(), 4, 2, 1, 1);

        popupSeverityAdmin = std::make_unique<QComboBox>(popupHeader.get());
        headerGridLayout->addWidget(popupSeverityAdmin.get(), 4, 3, 1, 1);

        popupSeverityAdmin->addItem("Mild");
        popupSeverityAdmin->addItem("Moderate");
        popupSeverityAdmin->addItem("Urgent");
        popupSeverityAdmin->addItem("Unknown");
        popupSeverityAdmin->setCurrentIndex(data->getSeverity());
        connect(popupSeverityAdmin.get(), &QComboBox::currentTextChanged, this, &TicketGUI::ChangeSeverity);
    }

    // messages scroll area
    scrollArea = std::make_unique<QScrollArea>(popup.get());
    scrollArea->setWidgetResizable(true);
    popupGridLayout->addWidget(scrollArea.get(), 1, 0, 1, 1);

    scrollContents = std::make_unique<QWidget>();
    scrollArea->setWidget(scrollContents.get());

    scrollGridLayout = std::make_unique<QGridLayout>(scrollContents.get());
}

void TicketGUI::RefreshTicketPopup() {
    popupDepartment->setText(("Department: \t\t" + data->getDepartment()).c_str());
    popupStatus->setText(("Status: \t\t\t" + ticketStatusToString[data->getStatus()]).c_str());

    if(showDepartment){
        popupDepartmentRep->setText(("Department Rep: \t\t" + data->getDeptRep()).c_str());
        popupSeverityUser->setText(("Severity: " + ticketSeverityToString[data->getSeverity()]).c_str());
    }
    else{
        popupDepartmentRepAdmin->setCurrentText(data->getDeptRep().c_str());
        popupSeverityAdmin->setCurrentIndex(data->getSeverity());
    }
}

void TicketGUI::ChangeSeverity() {
    data->setSeverity((TicketSeverity)popupSeverityAdmin->currentIndex());
}

void TicketGUI::ChangeDeptRep() {
    data->setDeptRep(popupDepartmentRepAdmin->currentText().toStdString());
}

