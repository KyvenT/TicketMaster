#include <QApplication>
#include <QWidget>

#include "UserWindow.h"

int main(int argc, char *argv[ ])
{
    QApplication app(argc, argv);

    UserWindow test("");

    return app.exec();

}