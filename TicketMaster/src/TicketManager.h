/**
 * @brief Static class to organize and manipulate the individual tickets
 *
 * ticketManager stores tickets into a vector, reads created tickets from "tickets.json" at beginning of program
 * and writes saved tickets to "tickets.json" after window close, returns tickets according to a given user or
 * department or department representative, and creates and deletes tickets
 *
 * @author Kyven
 */

#pragma once

#include "Ticket.h"
#include <fstream>
#include <json/json.h>
#include <ctime>
#include <iostream>
#include <iomanip>

/** TicketManager class manages retrieving, storing, and filtering tickets
 */
class ticketManager {
    private:
        /// std::vector<ticket> of ALL created tickets
        static std::vector<Ticket> tickets;
    public:
        /**
         * @brief Default constructor
         */
        explicit ticketManager();
        /**
         * @brief Function to get tickets created by specified user
         * @param user user who created the tickets
         * @return std::vector<ticket> of tickets created by user
         */
        static std::vector<Ticket*> GetUserTickets(const std::string& user);
        /**
         * @brief Function to get tickets sent to specified department
         * @param department destination department of tickets
         * @return std::vector<ticket> of tickets associated with department
         */
        static std::vector<Ticket*> GetDeptTickets(const std::string& department);
        /**
        * @brief Function to get tickets sent to a department, and then claimed by the user
        * @param user user who claimed the tickets
        * @return std::vector<ticket> of tickets claimed by department representative
        */
        static std::vector<Ticket*> GetUserClaimedTickets(const std::string& user);

        /**
         * @brief Function to create a new ticket given user who created it, destination department, title of ticket, and initial ticket message
         * @param user user who created ticket
         * @param department destination department of ticket
         * @param title title of ticket
         * @param message initial message of ticket
         */
        static void CreateTicket(std::string user, std::string department, std::string title, std::string message);

        /**
         * @brief Function to delete a certain ticket, given the creator user, destination department, and ticket title
         * @param user user who created the ticket
         * @param department destination department of the ticket
         * @param title title of the ticket
         */
        static void DeleteTicket(std::string user, std::string department, std::string title);

        /**
         * @brief Function to save tickets vector into a tickets.json file
         */
        static void SaveTickets();

        /**
         * @brief Function to read a tickets.json file containing tickets into the tickets vector
         */
        static void ReadTickets();
};
