#include <QApplication>
#include "UserManager.h"
#include "Login.h"
#include "AdminWindow.h"
#include "TicketManager.h"

int main(int argc, char *argv[ ])
{
    // setup
    if (sodium_init() == -1) {
        // Handle initialization failure
        return 1;
    }

    QApplication app(argc, argv);
    ticketManager::ReadTickets();
    UserManager::LoadUsersFromFile("users.json");

    //run
    Login login(nullptr);
    int exitCode = app.exec();

    // exit
    UserManager::SaveUsersToFile("users.json");
    return exitCode;

}