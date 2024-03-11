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

    static void RefreshGUI();

private:

    void NewTicket();
    void CreateTicket();

    static UserWindow* userWindow;

    std::shared_ptr<User> user;
    std::vector<std::unique_ptr<DepartmentTicketsGUI>> departmentsGUI;

    std::unique_ptr<QPushButton> newTicketButton;
    std::unique_ptr<QSpacerItem> spacer;

    std::unique_ptr<QGridLayout> gridLayout;
    std::unique_ptr<QGridLayout> scrollGridLayout;
    std::unique_ptr<QScrollArea> scrollArea;
    std::unique_ptr<QWidget> contents;

    std::unique_ptr<QWidget> popup = nullptr;
    std::unique_ptr<QGridLayout> popupGridLayout;

    std::unique_ptr<QLabel> titleFieldLabel;
    std::unique_ptr<QLineEdit> titleField;
    std::unique_ptr<QLabel> departmentFieldLabel;
    std::unique_ptr<QLineEdit> departmentField;
    std::unique_ptr<QLabel> messageFieldLabel;
    std::unique_ptr<QTextEdit> messageField;
    std::unique_ptr<QPushButton> createTicketButton;
};
