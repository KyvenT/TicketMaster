#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include "Ticket.h"

class MessageGUI : public QWidget {
public:
    MessageGUI() = delete;
    MessageGUI(const Message& data, QWidget* parent);

private:

    std::unique_ptr<QGridLayout> gridLayout;

    std::unique_ptr<QLabel> sender;
    std::unique_ptr<QLabel> message;
    std::unique_ptr<QLabel> time;
};
