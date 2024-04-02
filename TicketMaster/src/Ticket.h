/**
 * @brief Class to store information about an individual ticket
 *
 * Each ticket stores title, user (who created the ticket), ticket severity, ticket status,
 * the department the ticket was sent to, the messages in the discussion of each ticket,
 * the last modified time of the ticket, and the assigned department representative user
 *
 * @author Kyven
 */
#pragma once

#include <string>
#include <vector>
#include <chrono>

/**
 * @brief enum for representing ticket severity
 * Indicates a ticket's severity
 * @param severity
 */
enum TicketSeverity { Unknown = 3, Urgent = 2, Moderate = 1, Mild = 0};

/**
 * @brief enum for representing ticket status
 * Indicates a ticket's current status
 * @param status ticket's status
 */
enum TicketStatus { WaitingForDepartment, WaitingForUser, Resolved};

/**
 * @brief struct for representing a message
 * a struct that contains a message, a sender, and a time of creation
 * @param message the message text
 * @param sender the user who sent the message
 */
struct Message {
    std::string message;
    std::string sender;
    std::chrono::time_point<std::chrono::system_clock> created = std::chrono::system_clock::now();
    Message() = default;
    Message(const std::string& message, const std::string& sender) : message(message), sender(sender) {}
};

/** Ticket class holds all data needed for each ticket
 */
class Ticket {
    public:
        /**
         * @brief Ticket Constructor for new tickets
         * Needs title, user, message, severity, department
         * @param title a std::string representing title of ticket
         * @param user a std::string of the user who created the ticket
         * @param message a std::string representing the initial message of the ticket
         * @param severity the ticket's severity
         * @param department a std::string of the name of the destination department
        */
        Ticket(std::string title, std::string user, std::string message, TicketSeverity severity, std::string department);

        /**
         * @brief Constructor for converting saved tickets
         * Needs all stored information about the ticket
         * @param title a std::string representing title of ticket
         * @param user a std::string of user who created ticket
         * @param messages a std::vector<Message> of messages
         * @param severity the ticket's severity
         * @param department a std::string of name of destination department
         * @param modifiedTime a std::chrono::time_point<std::chrono::system_clock> of last modified time of ticket
         * @param deptRep assigned department rep, or "None"
         * @param status ticket status
         */
        Ticket(std::string title, std::string user, std::vector<Message> messages, int severity, std::string department,
                        std::string deptRep, int status, std::chrono::time_point<std::chrono::system_clock> modifiedTime);

        /**
         * @brief Function to set a department representative to current ticket
         * @param user a std::string to the department representative
         */
        void setDeptRep(std::string user);

        /**
         * @brief Function to get department rep of ticket
         * @return std::string of department representative or "None"
         */
        std::string getDeptRep() const;

        /**
         * @brief Function to add response messages to ticket
         * @param user the user who created the response message
         * @param message the response message
         */
        void addMessage(std::string user, std::string message);

        /**
         * @brief Function to get all messages associated with the ticket
         * @return a std::vector<Message> of the messages
         */
        std::vector<Message> getMessages() const;

        /**
         * @brief Function to get current ticket status
         * @return ticket status
         */
        TicketStatus getStatus() const;

        /**
         * @brief Function to set ticket status
         * @param newStatus the new ticket status
         */
        void setStatus(TicketStatus newStatus);

        /**
         * @brief Function to get current ticket severity
         * @return ticket severity
         */
        TicketSeverity getSeverity() const;

        /**
         * @brief Function to set ticket severity
         * @param newSeverity the new ticket severity
         */
        void setSeverity(TicketSeverity newSeverity);

        /**
         * @brief Function to get ticket creator user's name
         * @return ticket creator user
         */
        std::string getUser() const;

        /**
         * @brief Function to get ticket's destination department
         * @return department name
         */
        std::string getDepartment() const;

        /**
         * @brief Function to get ticket's title
         * @return title
         */
        std::string getTitle() const;

        /**
         * @brief Function to set ticket's title
         * @param title
         */
         void setTitle(std::string title);

         /**
          * @brief Function to get ticket's last modified time
          * @return last modified time
          */
         std::chrono::time_point<std::chrono::system_clock> getModifiedTime() const;

         /**
          * @brief Function to check if ticket has been assigned a department representative
          * @return True if ticket has a department representative, False otherwise
          */
         bool hasDepartmentRep();

    private:
        /// Ticket title
        std::string title;

        /// User who created the ticket
        std::string user;

        /// Ticket destination department
        std::string department;

        /// Assigned department representative
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