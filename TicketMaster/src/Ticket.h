//
// Created by Kyven on 2024-03-06.
//
#ifndef TICKETMASTER_TICKET_H
#define TICKETMASTER_TICKET_H

#endif //TICKETMASTER_TICKET_H

#include <string>
#include <vector>
#include <chrono>

/** enum TicketSeverity
 * Indicates a ticket's severity
 * @param severity
 */
enum TicketSeverity { Urgent = 2, Moderate = 1, Mild = 0};

/** enum TicketStatus
 * Indicates a ticket's current status
 * @param status ticket's status
 */
enum TicketStatus { WaitingForDepartment, WaitingForUser, Resolved};

/** struct Message
 * a struct that contains a message, a sender, and a time of creation
 * @param message the message
 * @param sender the sender user
 */
struct Message {
    std::string message;
    std::string sender;
    std::chrono::time_point<std::chrono::system_clock> created = std::chrono::system_clock::now();
};

/** Ticket class holds all data needed for each ticket
 */
class ticket {
    public:
        /** Ticket Constructor
         * Needs title, user, message, severity, department
         * @param title a std::string representing title of ticket
         * @param user a weak_ptr<User> pointing to the user who created the ticket
         * @param message a std::string representing the initial message of the ticket
         * @param severity the ticket's severity
         * @param department a std::string of the name of the destination department
        */
        explicit ticket(std::string title, std::string user, std::string message, TicketSeverity severity, std::string department);

        /** Function to set a department representative to current ticket
         * @param user a weak_ptr<User> to the department representative
         */
        // void setDeptRep(weak_ptr<User> user);
        void setDeptRep(std::string user);

        /** Function to get department rep of ticket
         * @return std::string department representative
         */
        std::string getDeptRep();

        /** Function to add response messages to ticket
         * @param user the user who created the response message
         * @param message the response message
         */
        void addMessage(std::string user, std::string message);

        /** Function to get all messages associated with the ticket
         * @return a std::vector<Message> of the messages
         */
        std::vector<Message> getMessages();

        /** Function to get current ticket status
         * @return ticket status
         */
        TicketStatus getStatus();

        /** Function to set ticket status
         * @param newStatus the new ticket status
         */
        void setStatus(TicketStatus newStatus);

        /** Function to get current ticket severity
         * @return ticket severity
         */
        TicketSeverity getSeverity();

        /** Function to set ticket severity
         * @param newSeverity the new ticket severity
         */
        void setSeverity(TicketSeverity newSeverity);

        /** Function to get ticket creator user's name
         * @return ticket creator user
         */
        std::string getUser();

        /** Function to get ticket's destination department
         * @return department name
         */
        std::string getDepartment();

        /**
         * Function to get ticket's title
         * @return title
         */
        std::string getTitle();

        /**
         * Function to set ticket's title
         * @param title
         */
         void setTitle(std::string title);

         /**
          * Function to get ticket's last modified time
          * @return last modified time
          */
         std::chrono::time_point<std::chrono::system_clock> getModifiedTime();

         /**
          * Function to check if ticket has been assigned a department representative
          * @return True if ticket has a department representative, False otherwise
          */
         bool hasDepartmentRep();

    private:
        /// Ticket title
        std::string title;

        /// Ticket creator user
        // weak_ptr<User> user;
        std::string user;

        /// Ticket destination department
        std::string department;

        /// Assigned department representatitive
        // weak_ptr<User> departmentRep;
        std::string deptRep;

        /// Messages in ticket
        std::vector<Message> messages;

        /// Ticket status
        TicketStatus status;

        /// Ticket severity
        TicketSeverity severity;

        /// Ticket last modified time
        std::chrono::time_point<std::chrono::system_clock> lastModified;

        /// Boolean for if the ticket has an assigned department representative
        bool hasDeptRep;
};