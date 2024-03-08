//
// Created by Kyven on 2024-03-06.
//
#include "Ticket.h"

/** Constructor
 * Needs title, creator user, destination department,
 * @param title a std::string representing title of ticket
 * @param user a weak_ptr<User> pointing to the user who created the ticket
 * @param message a std::string representing the initial message of the ticket
 * @param severity the ticket's severity
 * @param department a std::string of the name of the destination department
*/
ticket::ticket(std::string title, std::string user, std::string message, TicketSeverity severity, std::string department) {
    this->title = title;
    this->department = department;
    this->severity = severity;
    this->status = WaitingForDepartment;
    this->user = user;
    this->hasDeptRep = false;
    // convert message from std::string to Message struct
    Message firstMessage;
    firstMessage.message = message;
    firstMessage.sender = user;
    messages.push_back(firstMessage);

}

// void ticket::setDeptRep(weak_ptr<User> user)
/** Function to set a department representative to a ticket
 * @param user a std::string of department representative's name
 */
void ticket::setDeptRep(std::string user) {
    this->deptRep = user;
    this->hasDeptRep = true;
    if (this->deptRep == "none") {
        this->hasDeptRep = false;
    }
}

/** Function to return department representative of a ticket
 * @return department representative or "NO DEPARTMENT REPRESENTATIVE ASSIGNED"
 */
std::string ticket::getDeptRep() {
    if (this->hasDeptRep) {
        return this->deptRep;
    }
    return "NO DEPARTMENT REPRESENTATIVE ASSIGNED";
}

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

std::string ticket::getUser() {
    return this->user;
}

std::string ticket::getDepartment() {
    return this->department;
}

std::string ticket::getTitle() {
    return this->title;
}

void ticket::setTitle(std::string title) {
    this->title = title;
}

std::chrono::time_point<std::chrono::system_clock> ticket::getModifiedTime() {
    return this->lastModified;
}

bool ticket::hasDepartmentRep() {
    return this->hasDeptRep;
}










