#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

#include "UserManager.h"
#include "UserWindow.h"

class Login : public QWidget {
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);

private:
    void handleLogin();

private:
    std::unique_ptr<UserWindow> userWindow;

    QLabel *nameLabel;
    QLineEdit *nameEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
};

#endif // LOGIN_H
