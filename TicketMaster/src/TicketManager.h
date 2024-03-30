#pragma once

#include "Ticket.h"
#include <fstream>
#include <json/json.h>
#include <ctime>
#include <iostream>

/** TicketManager class manages retrieving, storing, and filtering tickets
 */
class ticketManager {
    private:
        /// std::vector<ticket> of ALL created tickets
        static std::vector<Ticket> tickets;
    public:
        /// Constructor
        explicit ticketManager();
        /**
         * Function to get tickets created by specified user
         * @param user user who created the tickets
         * @return std::vector<ticket> of tickets
         */
        static std::vector<Ticket*> GetUserTickets(const std::string& user);
        /**
         * Function to get tickets sent to specified department
         * @param department destination department of tickets
         * @return std::vector<ticket> of tickets
         */
        static std::vector<Ticket*> GetDeptTickets(const std::string& department);

        /**
         * Function to create a new ticket given user who created it, destination department, title of ticket, and initial ticket message
         * @param user user who created ticket
         * @param department destination department of ticket
         * @param title title of ticket
         * @param message initial message of ticket
         */
        static void CreateTicket(std::string user, std::string department, std::string title, std::string message);

        /**
         * Function to delete a certain ticket, given the creator user, destination department, and ticket title
         * @param user user who created the ticket
         * @param department destination department of the ticket
         * @param title title of the ticket
         */
        static void DeleteTicket(std::string user, std::string department, std::string title);

        /**
         * Function to save tickets vector into a json file
         */
        static void SaveTickets();

        /**
         * Function to read a json file containing tickets into the tickets vector
         */
        static void ReadTickets();
};
