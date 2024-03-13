#include <QApplication>
#include "UserManager.h"
#include "Login.h"
#include "AdminWindow.h"

int main(int argc, char *argv[ ])
{
    QApplication app(argc, argv);

    UserManager::CreateUser("test", "password");
    UserManager::AddUserToDepartment("test", "Admin");
    UserManager::AddUserToDepartment("test", "Information Technology");

    Login login(nullptr);
    AdminWindow adminWindow;

    return app.exec();

}