#include <QApplication>
#include "UserManager.h"
#include "Login.h"

int main(int argc, char *argv[ ])
{
    QApplication app(argc, argv);

    UserManager::CreateUser("test", "password");
    UserManager::AddUserToDepartment("test", "Admin");
    UserManager::AddUserToDepartment("test", "Information Technology");

    Login login(nullptr);

    return app.exec();

}