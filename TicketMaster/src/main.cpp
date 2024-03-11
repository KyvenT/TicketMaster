#include <QApplication>
#include <QWidget>

#include "UserWindow.h"
#include "UserManager.h"

int main(int argc, char *argv[ ])
{
    QApplication app(argc, argv);

    UserManager::CreateUser("test", "password");
    UserManager::AddUserToDepartment("test", "Admin");
    UserManager::AddUserToDepartment("test", "Information Technology");

    UserWindow test("test");

    return app.exec();

}