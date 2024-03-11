#pragma once

#include <QtWidgets>
#include <QLabel>
#include <string>

#include "User.h"
#include "DepartmentTicketsGUI.h"

class UserWindow : public QWidget {
public:

    UserWindow() = delete;
    explicit UserWindow(const std::string& username);

private:

    void RefreshGUI();
    void NewTicket();

    std::shared_ptr<User> user;
    std::vector<std::unique_ptr<DepartmentTicketsGUI>> departmentsGUI;

    std::unique_ptr<QPushButton> newTicketButton;
    std::unique_ptr<QSpacerItem> spacer;

    std::unique_ptr<QGridLayout> gridLayout;
    std::unique_ptr<QGridLayout> scrollGridLayout;
    std::unique_ptr<QScrollArea> scrollArea;
    std::unique_ptr<QWidget> contents;

    bool popupOpen = false;
    std::unique_ptr<QWidget> popup;
};
