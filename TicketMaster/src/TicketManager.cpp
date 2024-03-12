#include "TicketManager.h"

std::vector<Ticket> ticketManager::tickets;

// Constructor
ticketManager::ticketManager() = default;

std::vector<Ticket> ticketManager::GetUserTickets(std::string user) {
    std::vector<Ticket> userTickets;
    for (int i = 0; i < tickets.size(); i++) {
        if (tickets.at(i).getUser() == user) {
            userTickets.push_back(tickets.at(i));
        }
    }
    return userTickets;
}

std::vector<Ticket> ticketManager::GetDeptTickets(std::string department) {
    std::vector<Ticket> deptTickets;
    for (int i = 0; i < tickets.size(); i++) {
        if (tickets.at(i).getDepartment() == department) {
            deptTickets.push_back(tickets.at(i));
        }
    }
    return deptTickets;
}

void ticketManager::CreateTicket(std::string user, std::string department, std::string title, std::string message) {
    TicketSeverity initialSeverity = Mild;
    Ticket newTicket(title, user, message, initialSeverity, department);
    tickets.push_back(newTicket);
}

void ticketManager::DeleteTicket(std::string user, std::string department, std::string title) {
    for (int i = 0; i < tickets.size(); i++) {
        if (tickets.at(i).getUser() == user && tickets.at(i).getDepartment() == department && tickets.at(i).getTitle() == title) {
            tickets.erase(tickets.begin() + i);
        }
    }
}

