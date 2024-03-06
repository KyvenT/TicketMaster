//
// Created by Kyven on 2024-03-06.
//
#include "Ticket.h"

/* Constructor
 * Needs title, creator user, destination department,
 * @param title a std::string representing title of ticket
 * @param user a weak_ptr<User> pointing to the user who created the ticket
 * @param message a std::string representing the initial message of the ticket
 * @param severity the ticket's severity
 * @param department a std::string of the name of the destination department
*/
ticket::ticket(std::string title, std::string message, TicketSeverity severity, std::string department) {
    this->title = title;
    this->department = department;
    this->severity = severity;
    this->status = WaitingForDepartment;
    // convert message from std::string to Message struct
    Message firstMessage;
    firstMessage.message = message;

}

// void ticket::addDeptRep(weak_ptr<User> user)

// Adds a response message to the ticket
void ticket::addMessage(std::string user, std::string message) {
    Message newResponse(message, user);
    this->messages.push_back(newResponse);
    this->lastModified = newResponse.created;
}

std::vector<Message> ticket::getMessages() {
    return messages;
}

TicketStatus ticket::getStatus() {
    return this->status;
}

void ticket::setStatus(TicketStatus newStatus) {
    this->status = newStatus;
}

TicketSeverity ticket::getSeverity() {
    return this->severity;
}

void ticket::setSeverity(TicketSeverity newSeverity) {
    this->severity = newSeverity;
}





