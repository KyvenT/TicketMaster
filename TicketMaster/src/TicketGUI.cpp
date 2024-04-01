#include "TicketGUI.h"

#include "UserWindow.h"
#include "UserManager.h"

#include <utility>

TicketGUI::TicketGUI(Ticket* ticketData, QWidget *parent, bool showDepartment, bool isAdmin)
: QPushButton(parent), data(std::move(ticketData)), showDepartment(showDepartment), isAdmin(isAdmin)
{

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
    status->setText(ticketStatusToString[data->getStatus()].c_str());
    if(showDepartment)
        status->setText((data->getDepartment() + " | " + status->text().toStdString()).c_str());
}

TicketGUI::~TicketGUI() {
    if(!popup)
        return;

    scrollGridLayout->removeItem(messageSpacer.get());
    for(auto& message : messageGUIs){
        scrollGridLayout->removeWidget(message.get());
    }
    messageGUIs.clear();

    scrollGridLayout = nullptr;
    scrollContents = nullptr;
}

void TicketGUI::RefreshTicketPopup() {

    status->setText(ticketStatusToString[data->getStatus()].c_str());

    if(!popup)
        return;

    // header
    popupDepartment->setText(("Department: \t\t" + data->getDepartment()).c_str());
    popupStatus->setText(("Status: \t\t\t" + ticketStatusToString[data->getStatus()]).c_str());

    if(!isAdmin){
        popupDepartmentRep->setText(("Department Rep: \t\t" + data->getDeptRep()).c_str());
        popupSeverityUser->setText(("Severity: " + ticketSeverityToString[data->getSeverity()]).c_str());
    }
    else{
        popupDepartmentRepAdmin->setCurrentText(data->getDeptRep().c_str());
        popupSeverityAdmin->setCurrentIndex(data->getSeverity());
    }

    if(data->getStatus() == TicketStatus::Resolved) {
        resolvedButton->setText("Mark Unresolved");
    }
    else {
        resolvedButton->setText("Mark Resolved");
    }

    // delete messages
    scrollGridLayout->removeItem(messageSpacer.get());
    for(auto& message : messageGUIs){
        scrollGridLayout->removeWidget(message.get());
    }
    messageGUIs.clear();

    // create messages
    std::vector<Message> messages = data->getMessages();
    for(int i = 0; i < messages.size(); i++){
        messageGUIs.push_back(std::make_unique<MessageGUI>(messages[i], scrollContents.get()));
        scrollGridLayout->addWidget(messageGUIs.back().get(), i, 0, 1, 1);
    }
    scrollGridLayout->addItem(messageSpacer.get(), (int)messages.size(), 0, 1, 1);
}

void TicketGUI::CreateTicketPopup() {
    if(popup){
        popup->show();
        popup->resize(700, 600);
        UserWindow::RefreshGUI();
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
    popupGridLayout->addWidget(popupHeader.get(), 0, 0, 1, 2);
    headerGridLayout = std::make_unique<QGridLayout>(popupHeader.get());
    popupHeader->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);

    // title
    popupTitle = std::make_unique<QLabel>(data->getTitle().c_str(), popupHeader.get());
    popupTitle->setAlignment(Qt::AlignCenter);
    headerGridLayout->addWidget(popupTitle.get(), 0, 0, 1, 4);

    QFont font = popupTitle->font();
    font.setPointSize(18);
    popupTitle->setFont(font);

    // user
    popupUser = std::make_unique<QLabel>(("User: \t\t\t" + data->getUser()).c_str(), popupHeader.get());
    headerGridLayout->addWidget(popupUser.get(), 1, 0, 1, 4);

    // department rep
    if(!isAdmin){
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

    // department
    popupDepartment = std::make_unique<QLabel>(("Department: \t\t" + data->getDepartment()).c_str(), popupHeader.get());
    headerGridLayout->addWidget(popupDepartment.get(), 3, 0, 1, 4);

    // status
    popupStatus = std::make_unique<QLabel>(("Status: \t\t\t" + ticketStatusToString[data->getStatus()]).c_str(), popupHeader.get());
    headerGridLayout->addWidget(popupStatus.get(), 4, 0, 1, 2);

    // severity
    if(!isAdmin){
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
    popupGridLayout->addWidget(scrollArea.get(), 1, 0, 1, 2);

    scrollContents = std::make_unique<QWidget>();
    scrollArea->setWidget(scrollContents.get());

    QPalette pal = scrollContents->palette();
    pal.setColor(scrollContents->backgroundRole(), Qt::lightGray);
    scrollContents->setPalette(pal);

    scrollGridLayout = std::make_unique<QGridLayout>(scrollContents.get());

    // messages
    std::vector<Message> messages = data->getMessages();
    for(int i = 0; i < messages.size(); i++){
        messageGUIs.push_back(std::make_unique<MessageGUI>(messages[i], scrollContents.get()));
        scrollGridLayout->addWidget(messageGUIs.back().get(), i, 0, 1, 1);
    }

    messageSpacer = std::make_unique<QSpacerItem>(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    scrollGridLayout->addItem(messageSpacer.get(), (int)messages.size(), 0, 1, 1);

    // add message to ticket
    messageContents = std::make_unique<QTextEdit>(popup.get());
    messageContents->setMaximumHeight(100);
    messageContents->setPlaceholderText("Add Message");
    popupGridLayout->addWidget(messageContents.get(), 2, 0, 1, 2);

    sendButton = std::make_unique<QPushButton>("Send Message", popup.get());
    popupGridLayout->addWidget(sendButton.get(), 3, 1, 1, 1);
    connect(sendButton.get(), &QPushButton::clicked, this, &TicketGUI::SendMessage);

    resolvedButton = std::make_unique<QPushButton>("Mark Resolved", popup.get());
    popupGridLayout->addWidget(resolvedButton.get(), 3, 0, 1, 1);
    if(data->getStatus() == TicketStatus::Resolved)
        resolvedButton->setText("Mark Unresolved");
    connect(resolvedButton.get(), &QPushButton::clicked, this, &TicketGUI::ToggleResolved);
}

void TicketGUI::ChangeDeptRep() {
    data->setDeptRep(popupDepartmentRepAdmin->currentText().toStdString());
    UserWindow::RefreshGUI();
}

void TicketGUI::ChangeSeverity() {
    data->setSeverity((TicketSeverity)popupSeverityAdmin->currentIndex());
    UserWindow::RefreshGUI();
}

void TicketGUI::ToggleResolved() {
    if(data->getStatus() != TicketStatus::Resolved){
        data->setStatus(TicketStatus::Resolved);
    }
    else {
        data->setStatus(TicketStatus::WaitingForDepartment);
    }
    UserWindow::RefreshGUI();
}

void TicketGUI::SendMessage() {
    if(messageContents->toPlainText().isEmpty())
        return;
    if(data->getStatus() == TicketStatus::Resolved)
        return;

    data->addMessage(UserWindow::GetUsersName(), messageContents->toPlainText().toStdString());

    if(data->getStatus() == TicketStatus::WaitingForDepartment){
        data->setStatus(TicketStatus::WaitingForUser);
    }
    else{
        data->setStatus(TicketStatus::WaitingForDepartment);
    }

    messageContents->setText("");
    UserWindow::RefreshGUI();
}
