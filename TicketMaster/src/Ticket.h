//
// Created by Kyven on 2024-03-06.
//
#ifndef TICKETMASTER_TICKET_H
#define TICKETMASTER_TICKET_H

#endif //TICKETMASTER_TICKET_H

#include <string>
#include <vector>
#include <chrono>

/* enum TicketSeverity
 * Indicates a ticket's severity
 * @param severity
 */
enum TicketSeverity { Urgent = 2, Moderate = 1, Mild = 0};

/* enum TicketStatus
 * Indicates a ticket's current status
 * @param status
 */
enum TicketStatus { WaitingForDepartment, WaitingForUser, Resolved};

/* struct Message
 * a struct that contains a message, a sender, and a time of creation
 * @param message the message
 * @param sender the sender
 */
struct Message {
    std::string message;
    std::string sender;
    std::chrono::time_point<std::chrono::system_clock> created = std::chrono::system_clock::now();
};

class ticket {
    public:
        /* Ticket Constructor
         * Needs title, user, message, severity, department
         * @param title a std::string representing title of ticket
         * @param user a weak_ptr<User> pointing to the user who created the ticket
         * @param message a std::string representing the initial message of the ticket
         * @param severity the ticket's severity
         * @param department a std::string of the name of the destination department
        */
        explicit ticket(std::string title, std::string message, TicketSeverity severity, std::string department);

        /* Function to add a department representative to current ticket
         * @param user a weak_ptr<User> to the department representative
         */
        // void addDeptRep(weak_ptr<User> user);

        /* Function to add response messages to ticket
         * @param user the user who created the response message
         * @param message the response message
         */
        void addMessage(std::string user, std::string message);

        /* Function to get all messages associated with the ticket
         * @return a std::vector<Message> of the messages
         */
        std::vector<Message> getMessages();

        /* Function to get current ticket status
         * @return ticket status
         */
        TicketStatus getStatus();

        /* Function to set ticket status
         * @param newStatus the new ticket status
         */
        void setStatus(TicketStatus newStatus);

        /* Function to get current ticket severity
         * @return ticket severity
         */
        TicketSeverity getSeverity();

        /* Function to set ticket severity
         * @param newSeverity the new ticket severity
         */
        void setSeverity(TicketSeverity newSeverity);
    private:
        std::string title;
        // weak_ptr<User> user;
        std::string department;
        // weak_ptr<User> departmentRep;
        std::vector<Message> messages;
        TicketStatus status;
        TicketSeverity severity;
        std::chrono::time_point<std::chrono::system_clock> lastModified;
};