//
// Created by kyven on 2024-03-06.
//

#ifndef TICKETMASTER_TICKETMANAGER_H
#define TICKETMASTER_TICKETMANAGER_H

#endif //TICKETMASTER_TICKETMANAGER_H

#include "Ticket.h"
#include <fstream>

/** TicketManager class manages retrieving, storing, and filtering tickets
 */
class ticketManager {
    private:
        /// std::vector<ticket> of ALL created tickets
        static std::vector<ticket> tickets;
    public:
        /// Constructor
        explicit ticketManager();
        /**
         * Function to get tickets created by specified user
         * @param user user who created the tickets
         * @return std::vector<ticket> of tickets
         */
        static std::vector<ticket> GetUserTickets(std::string user);
        /**
         * Function to get tickets sent to specified department
         * @param department destination department of tickets
         * @return std::vector<ticket> of tickets
         */
        static std::vector<ticket> GetDeptTickets(std::string department);

        /**
         * Function to create a new ticket given user who created it, destination department, title of ticket, and initial ticket message
         * @param user user who created ticket
         * @param department destination department of ticket
         * @param title title of ticket
         * @param message initial message of ticket
         */
        static void CreateTicket(std::string user, std::string department, std::string title, std::string message);

};
std::vector<ticket> ticketManager::tickets;