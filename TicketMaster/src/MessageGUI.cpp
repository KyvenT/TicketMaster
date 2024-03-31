#include "MessageGUI.h"

MessageGUI::MessageGUI(const Message &data, QWidget* parent) : QWidget(parent) {

    this->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
    this->setStyleSheet("QWidget { background-color: white; }");

    gridLayout = std::make_unique<QGridLayout>(this);

    sender = std::make_unique<QLabel>(data.sender.c_str(), this);


    message = std::make_unique<QLabel>(data.message.c_str(), this);
    gridLayout->addWidget(message.get(), 0, 0, 1, 1);

}
