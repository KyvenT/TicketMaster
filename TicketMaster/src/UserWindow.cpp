#include "UserWindow.h"
#include "DepartmentTicketsGUI.h"
#include "UserManager.h"
#include "TicketManager.h"

#include <QLabel>

UserWindow::UserWindow(const std::string &username) {

    user = UserManager::GetUser(username);

    this->setWindowTitle("User Window");
    this->resize(1280, 720);
    this->show();

    // setup grid layout
    gridLayout = std::make_unique<QGridLayout>(this);
    spacer = std::make_unique<QSpacerItem>(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    gridLayout->addItem(spacer.get(), 0, 1, 1, 1);

    // setup new ticket button
    newTicketButton = std::make_unique<QPushButton>(this);
    gridLayout->addWidget(newTicketButton.get(), 0, 0, 1, 1);
    connect(newTicketButton.get(), &QPushButton::clicked, this, &UserWindow::NewTicket);

    newTicketButton->setText("Create Ticket");
    QFont font = newTicketButton->font();
    font.setPointSize(24);
    newTicketButton->setFont(font);

    // setup scroll area
    scrollArea = std::make_unique<QScrollArea>(this);
    scrollArea->setWidgetResizable(true);
    gridLayout->addWidget(scrollArea.get(), 1, 0, 1, 2);

    contents = std::make_unique<QWidget>();
    scrollArea->setWidget(contents.get());

    scrollGridLayout = std::make_unique<QGridLayout>(contents.get());

    departmentsGUI.push_back(std::make_unique<DepartmentTicketsGUI>("My Tickets", user->GetName(), contents.get()));
    scrollGridLayout->addWidget(departmentsGUI.back().get(), 0, 0, 1, 1);

    const std::vector<std::string>& departments = user->GetDepartments();
    for(int i = 0; i < departments.size(); i++){
        departmentsGUI.push_back(std::make_unique<DepartmentTicketsGUI>(departments[i], contents.get()));
        scrollGridLayout->addWidget(departmentsGUI.back().get(), i + 1, 0, 1, 1);
    }
}

void UserWindow::RefreshGUI() {
    for(auto& department : departmentsGUI){
        department->Refresh();
    }
}

void UserWindow::NewTicket() {

    if(popup){
        popup->show();
        popup->resize(400, 300);
        return;
    }

    // create window
    popup = std::make_unique<QWidget>();
    popup->setWindowTitle("New Ticket");
    popup->resize(400, 300);
    popup->show();

    popupGridLayout = std::make_unique<QGridLayout>(popup.get());

    // title
    titleFieldLabel = std::make_unique<QLabel>("Title: ", popup.get());
    popupGridLayout->addWidget(titleFieldLabel.get(), 0, 0, 1, 1);
    titleFieldLabel->setAlignment(Qt::AlignRight);

    titleField = std::make_unique<QLineEdit>(popup.get());
    popupGridLayout->addWidget(titleField.get(), 0, 1, 1, 2);

    // department
    departmentFieldLabel = std::make_unique<QLabel>("Department: ", popup.get());
    popupGridLayout->addWidget(departmentFieldLabel.get(), 1, 0, 1, 1);
    departmentFieldLabel->setAlignment(Qt::AlignRight);

    departmentField = std::make_unique<QLineEdit>(popup.get());
    popupGridLayout->addWidget(departmentField.get(), 1, 1, 1, 2);

    // message
    messageFieldLabel = std::make_unique<QLabel>("Message: ", popup.get());
    popupGridLayout->addWidget(messageFieldLabel.get(), 2, 0, 1, 1);
    messageFieldLabel->setAlignment(Qt::AlignRight);

    messageField = std::make_unique<QTextEdit>(popup.get());
    popupGridLayout->addWidget(messageField.get(), 2, 1, 1, 2);

    // button
    createTicketButton = std::make_unique<QPushButton>("Create Ticket", popup.get());
    popupGridLayout->addWidget(createTicketButton.get(), 3, 1, 1, 1);
    connect(createTicketButton.get(), &QPushButton::clicked, this, &UserWindow::CreateTicket);
}

void UserWindow::CreateTicket() {

    if(!popup)
        return;
    if(titleField->text().isEmpty())
        return;
    if(departmentField->text().isEmpty())
        return;
    if(messageField->toPlainText().isEmpty())
        return;

    ticketManager::CreateTicket(user->GetName(), departmentField->text().toStdString(), titleField->text().toStdString(), messageField->toPlainText().toStdString());
    RefreshGUI();
}
