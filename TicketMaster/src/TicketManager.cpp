//
// Created by kyven on 2024-03-06.
//
#include "TicketManager.h"

/** Constructor
 *
 */
ticketManager::ticketManager() = default;

std::vector<ticket> ticketManager::GetUserTickets(std::string user) {
    std::vector<ticket> userTickets;
    for (int i = 0; i < tickets.size(); i++) {
        if (tickets.at(i).getUser() == user) {
            userTickets.push_back(tickets.at(i));
        }
    }
    return userTickets;
}

std::vector<ticket> ticketManager::GetDeptTickets(std::string department) {
    std::vector<ticket> deptTickets;
    for (int i = 0; i < tickets.size(); i++) {
        if (tickets.at(i).getDepartment() == department) {
            deptTickets.push_back(tickets.at(i));
        }
    }
    return deptTickets;
}

void ticketManager::CreateTicket(std::string user, std::string department, std::string title, std::string message) {
    TicketSeverity initialSeverity = Mild;
    ticket newTicket(title, user, message, initialSeverity, department);
    tickets.push_back(newTicket);
}

