#pragma once

#include <QtWidgets>
#include <QLabel>
#include <string>

class UserWindow : public QWidget {
public:

    UserWindow() = delete;
    explicit UserWindow(const std::string& username);

private:

    //std::shared_ptr<User> user;

    std::unique_ptr<QSpacerItem> spacer;
    std::unique_ptr<QPushButton> newTicketButton;

    std::unique_ptr<QGridLayout> gridLayout;
    std::unique_ptr<QGridLayout> scrollGridLayout;
    std::unique_ptr<QScrollArea> scrollArea;
    std::unique_ptr<QWidget> contents;

};
