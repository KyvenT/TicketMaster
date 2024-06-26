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

std::vector<Ticket*> ticketManager::GetUserClaimedTickets(const std::string &user) {
    std::vector<Ticket*> claimedTickets;
    for (int i = 0; i < tickets.size(); i++) {
        if (tickets[i].getDeptRep() == user) {
            claimedTickets.push_back(&tickets[i]);
        }
    }
    return claimedTickets;
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
        // convert time_point to string
        std::time_t modifiedTime = std::chrono::system_clock::to_time_t(tickets[i].getModifiedTime());
        std::tm modifTime = *std::localtime(&modifiedTime);
        char buffer[50];
        if (!strftime(buffer, sizeof(buffer), "%c", &modifTime)) {
            std::cout << "strftime failed" << std::endl;
        }

        // convert messages vector to Json::Value vector
        Json::Value messageVec;
        for (int j = 0; j < tickets[i].getMessages().size(); j++) {
            Json::Value message;
            message["sender"] = tickets[i].getMessages()[j].sender;
            message["text"] = tickets[i].getMessages()[j].message;
            messageVec.append(message);
        }

        // store info
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
    // close file
    file.close();
}

void ticketManager::ReadTickets() {
    // open tickets.json, initialize reader
    std::ifstream ticketFile("tickets.json");
    Json::Reader reader;
    Json::Value readTicket;
    reader.parse(ticketFile, readTicket);
    Json::Value ticketsJson = readTicket;

    for (int i = 0; i < ticketsJson["tickets"].size(); i++) {
        // Convert string of time to time_point
        std::tm tm;
        std::string modifTime = ticketsJson["tickets"][i]["modifiedTime"].asString();
        std::stringstream stringStream(modifTime);
        stringStream >> std::get_time(&tm, "%a %b %d %H:%M:%S %Y");
        std::time_t time = mktime(&tm);
        std::chrono::time_point<std::chrono::system_clock> modifiedTime = std::chrono::system_clock::from_time_t(time);

        // Parse messages from Json file to std::vector<Message>
        std::vector<Message> messagesVec;
        for (int j = 0; j < ticketsJson["tickets"][i]["messages"].size(); j++) {
            Message tempMessage;
            tempMessage.sender = ticketsJson["tickets"][i]["messages"][j]["sender"].asString();
            tempMessage.message = ticketsJson["tickets"][i]["messages"][j]["text"].asString();
            messagesVec.push_back(tempMessage);
        }

        // add values to ticket
        std::string title = ticketsJson["tickets"][i]["title"].asString();
        std::string user = ticketsJson["tickets"][i]["user"].asString();
        int severity = ticketsJson["tickets"][i]["severity"].asInt();
        std::string department = ticketsJson["tickets"][i]["department"].asString();
        std::string deptRep = ticketsJson["tickets"][i]["deptRep"].asString();
        int status = ticketsJson["tickets"][i]["status"].asInt();
        Ticket tempTicket(title, user, messagesVec, severity, department, deptRep, status, modifiedTime);

        tickets.push_back(tempTicket);
    }
    // close file
    ticketFile.close();
}
