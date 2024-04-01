#include <QApplication>
#include "UserManager.h"
#include "Login.h"
#include "AdminWindow.h"
#include "TicketManager.h"

int main(int argc, char *argv[ ])
{

    if (sodium_init() == -1) {
        // Handle initialization failure
        return 1;
    }

    QApplication app(argc, argv);

    UserManager::CreateUser("test", "password");
    UserManager::AddUserToDepartment("test", "Admin");
    UserManager::AddUserToDepartment("test", "Information Technology");

    ticketManager::ReadTickets();

    Login login(nullptr);
    //AdminWindow adminWindow;

    return app.exec();

}