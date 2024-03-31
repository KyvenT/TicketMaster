#include "Ticket.h"

/** Constructor
 * Needs title, creator user, destination department,
 * @param title a std::string representing title of ticket
 * @param user a weak_ptr<User> pointing to the user who created the ticket
 * @param message a std::string representing the initial message of the ticket
 * @param severity the ticket's severity
 * @param department a std::string of the name of the destination department
*/
Ticket::Ticket(std::string title, std::string user, std::string message, TicketSeverity severity, std::string department) {
    this->title = title;
    this->department = department;
    this->severity = severity;
    this->status = WaitingForDepartment;
    this->user = user;
    this->hasDeptRep = false;
    this->lastModified = std::chrono::system_clock::now();
    // convert message from std::string to Message struct
    Message firstMessage;
    firstMessage.message = message;
    firstMessage.sender = user;
    messages.push_back(firstMessage);

}

/** Function to set a department representative to a ticket
 * @param user a std::string of department representative's name
 */
void Ticket::setDeptRep(std::string user) {
    this->deptRep = user;
    this->hasDeptRep = true;
    if (this->deptRep == "None") {
        this->hasDeptRep = false;
    }
}

/** Function to return department representative of a ticket
 * @return department representative or "None"
 */
std::string Ticket::getDeptRep() const {
    if (this->hasDeptRep) {
        return this->deptRep;
    }
    return "None";
}

// Adds a response message to the ticket
void Ticket::addMessage(std::string user, std::string message) {
    Message newResponse(message, user);
    this->messages.push_back(newResponse);
    this->lastModified = newResponse.created;
}

std::vector<Message> Ticket::getMessages() const {
    return messages;
}

TicketStatus Ticket::getStatus() const {
    return this->status;
}

void Ticket::setStatus(TicketStatus newStatus) {
    this->status = newStatus;
}

TicketSeverity Ticket::getSeverity() const {
    return this->severity;
}

void Ticket::setSeverity(TicketSeverity newSeverity) {
    this->severity = newSeverity;
}

std::string Ticket::getUser() const {
    return this->user;
}

std::string Ticket::getDepartment() const {
    return this->department;
}

std::string Ticket::getTitle() const {
    return this->title;
}

void Ticket::setTitle(std::string title) {
    this->title = title;
}

std::chrono::time_point<std::chrono::system_clock> Ticket::getModifiedTime() const {
    return this->lastModified;
}

bool Ticket::hasDepartmentRep() {
    return this->hasDeptRep;
}

Ticket::Ticket(std::string title, std::string user, std::vector<Message> messages, int severity,
               std::string department, std::string deptRep, int status, std::chrono::time_point<std::chrono::system_clock> modifiedTime) {
    this->title = title;
    this->department = department;
    this->severity = TicketSeverity(severity);
    this->status = TicketStatus(status);
    this->user = user;
    this->deptRep = deptRep;
    this->messages = messages;
    this->lastModified = modifiedTime;
    if (this->getDeptRep() == "None") {
        this->hasDeptRep = false;
    } else {
        this->hasDeptRep = true;
    }
}










