//
// Created by kyven on 2024-03-06.
//

#ifndef TICKETMASTER_TICKETMANAGER_H
#define TICKETMASTER_TICKETMANAGER_H

#endif //TICKETMASTER_TICKETMANAGER_H

#include "Ticket.h"

class ticketManager {
    private:
        static std::vector<ticket> tickets;
    public:
        explicit ticketManager();
        static std::vector<ticket> GetUserTickets(std::string user);
        static std::vector<ticket> GetDeptTickets(std::string department);
        static void CreateTicket(std::string user, std::string department, std::string title, std::string message);

};