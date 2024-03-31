#include "TicketManager.h"

std::vector<Ticket> ticketManager::tickets;

// Constructor
ticketManager::ticketManager() = default;

std::vector<Ticket*> ticketManager::GetUserTickets(const std::string& user) {
    std::vector<Ticket*> userTickets;
    for (int i = 0; i < tickets.size(); i++) {
        if (tickets[i].getUser() == user) {
            userTickets.push_back(&tickets[i]);
        }
    }
    return userTickets;
}

std::vector<Ticket*> ticketManager::GetDeptTickets(const std::string& department) {
    std::vector<Ticket*> deptTickets;
    for (int i = 0; i < tickets.size(); i++) {
        if (tickets[i].getDepartment() == department) {
            deptTickets.push_back(&tickets[i]);
        }
    }
    return deptTickets;
}

void ticketManager::CreateTicket(std::string user, std::string department, std::string title, std::string message) {
    TicketSeverity initialSeverity = TicketSeverity::Unknown;
    Ticket newTicket(title, user, message, initialSeverity, department);
    tickets.push_back(newTicket);
}

void ticketManager::DeleteTicket(std::string user, std::string department, std::string title) {
    for (int i = 0; i < tickets.size(); i++) {
        if (tickets[i].getUser() == user && tickets[i].getDepartment() == department && tickets[i].getTitle() == title) {
            tickets.erase(tickets.begin() + i);
        }
    }
}

void ticketManager::SaveTickets() {
    std::ofstream file;
    file.open("tickets.json");
    Json::Value ticketsVec;
    Json::StyledWriter writer;
    for (int i = 0; i < tickets.size(); i++) {
        std::time_t modifiedTime = std::chrono::system_clock::to_time_t(tickets[i].getModifiedTime());
        std::tm modifTime = *std::localtime(&modifiedTime);
        char buffer[50];
        if (!strftime(buffer, sizeof(buffer), "%c", &modifTime)) {
            std::cout << "strftime failed" << std::endl;
        }

        Json::Value messageVec;
        for (int j = 0; j < tickets[i].getMessages().size(); j++) {
            Json::Value message;
            message["sender"] = tickets[i].getMessages()[j].sender;
            message["text"] = tickets[i].getMessages()[j].message;
            messageVec.append(message);
        }

        Json::Value ticketJson;
        ticketJson["title"] = tickets[i].getTitle();
        ticketJson["user"] = tickets[i].getUser();
        ticketJson["department"] = tickets[i].getDepartment();
        ticketJson["deptRep"] = tickets[i].getDeptRep();
        ticketJson["status"] = tickets[i].getStatus();
        ticketJson["severity"] = tickets[i].getSeverity();
        ticketJson["modifiedTime"] = buffer;
        ticketJson["messages"] = messageVec;
        ticketsVec.append(ticketJson);
    }
    Json::Value root;
    root["tickets"] = ticketsVec;
    file << writer.write(root);
    file.close();
}

void ticketManager::ReadTickets() {
    std::cout << "Read Tickets" << std::endl;
    std::ifstream ticketFile("tickets.json");
    Json::Reader reader;
    Json::Value readTicket;
    std::cout << "test" << std::endl;
    reader.parse(ticketFile, readTicket);
    Json::Value ticketsJson = readTicket;
    std::cout << "Before Tickets" << std::endl;
    std::cout << ticketsJson["tickets"].size() << std::endl;

    for (int i = 0; i < ticketsJson["tickets"].size(); i++) {
        std::cout << ticketsJson["tickets"][i]["title"].asString() << std::endl;

        std::tm tm;
        std::string modifTime = ticketsJson["tickets"][i]["modifiedTime"].asString();
        std::stringstream stringStream(modifTime);
        stringStream >> std::get_time(&tm, "%a %b %d %H:%M:%S %Y");
        std::time_t time = mktime(&tm);
        std::chrono::time_point<std::chrono::system_clock> modifiedTime = std::chrono::system_clock::from_time_t(time);

        // Parse messages from Json file to std::vector<Message>
        std::vector<Message> messagesVec;
        std::cout << ticketsJson["tickets"][i]["messages"].size() << std::endl;
        for (int j = 0; j < ticketsJson["tickets"][i]["messages"].size(); j++) {
            Message tempMessage;
            std::cout << ticketsJson["tickets"][i]["messages"][j]["sender"].asString() << std::endl;
            std::cout << ticketsJson["tickets"][i]["messages"][j]["text"].asString() << std::endl;
            tempMessage.sender = ticketsJson["tickets"][i]["messages"][j]["sender"].asString();
            tempMessage.message = ticketsJson["tickets"][i]["messages"][j]["text"].asString();
            messagesVec.push_back(tempMessage);
        }


        std::string title = ticketsJson["tickets"][i]["title"].asString();
        std::string user = ticketsJson["tickets"][i]["user"].asString();
        int severity = ticketsJson["tickets"][i]["severity"].asInt();
        std::string department = ticketsJson["tickets"][i]["department"].asString();
        std::string deptRep = ticketsJson["tickets"][i]["deptRep"].asString();
        int status = ticketsJson["tickets"][i]["status"].asInt();
        Ticket tempTicket(title, user, messagesVec, severity, department, deptRep, status, modifiedTime);

        tickets.push_back(tempTicket);
        std::time_t modifyTime = std::chrono::system_clock::to_time_t(tickets[i].getModifiedTime());
        std::cout << std::put_time(std::localtime(&modifyTime), "%c") << std::endl;
    }


    //std::cout << ticketsJson << std::endl;
    ticketFile.close();
}

