#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

#include "UserManager.h"
#include "UserWindow.h"
#include "AdminWindow.h"

/**
 * @brief Login window which takes a username and password, checks if username is for a user or an admin
 * then redirects to the appropriate window
 * @author Martin Shaker
 */
class Login : public QWidget {
public:
    /**
     * @brief Constructor method for the login class
     * @parameter parent
     */
    explicit Login(QWidget *parent = nullptr);

private:
    /**
     * @brief Method to verify login credentials and redirect to the correct window (admin or user)
     */
    void handleLogin();

private:
    std::unique_ptr<UserWindow> userWindow;
    std::unique_ptr<AdminWindow> adminWindow;

    QLabel *nameLabel;
    QLineEdit *nameEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
};

#endif // LOGIN_H
