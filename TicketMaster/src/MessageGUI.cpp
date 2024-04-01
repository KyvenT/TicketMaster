#include "MessageGUI.h"

#include <sstream>
#include <iomanip>

MessageGUI::MessageGUI(const Message &data, QWidget* parent) : QWidget(parent) {

    this->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
    this->setStyleSheet("QWidget { background-color: white; }");

    gridLayout = std::make_unique<QGridLayout>(this);

    sender = std::make_unique<QLabel>((data.sender + ":").c_str(), this);
    gridLayout->addWidget(sender.get(), 0, 0, 1, 1);

    time = std::make_unique<QLabel>(TimePointToString(data.created).c_str(), this);
    time->setAlignment(Qt::AlignRight);
    gridLayout->addWidget(time.get(), 0, 1, 1, 1);

    message = std::make_unique<QLabel>(data.message.c_str(), this);
    gridLayout->addWidget(message.get(), 1, 0, 1, 2);

    QFont font = message->font();
    font.setBold(true);
    message->setFont(font);
}

std::string MessageGUI::TimePointToString(std::chrono::time_point<std::chrono::system_clock> timePoint) {

    time_t cTime = std::chrono::system_clock::to_time_t(timePoint);

    char buff[256];
    std::strftime(buff, 256, "%B %d, %Y - %I:%M%p", localtime(&cTime));

    std::string result(buff);
    return result;
}
