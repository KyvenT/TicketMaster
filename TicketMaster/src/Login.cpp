#include "Login.h"
#include "UserManager.h"
#include "AdminWindow.h"

Login::Login(QWidget *parent) : QWidget(parent) {
    nameLabel = new QLabel("Name:", this);
    nameEdit = new QLineEdit(this);
    passwordLabel = new QLabel("Password:", this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    loginButton = new QPushButton("Login", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(nameLabel);
    layout->addWidget(nameEdit);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordEdit);
    layout->addWidget(loginButton);

    setLayout(layout);
    setWindowTitle("Login");
    show();

    connect(loginButton, &QPushButton::clicked, this, &Login::handleLogin);
}

void Login::handleLogin() {
    QString enteredName = nameEdit->text();
    QString enteredPassword = passwordEdit->text();

    if (enteredName.toStdString() == "admin" && enteredPassword.toStdString() == "admin") {
        adminWindow = std::make_unique<AdminWindow>();
        hide();
        return;
    }

    // Not an admin or username not found, proceed with normal user logic
    // Use UserManager to verify the user
    std::shared_ptr<User> user = UserManager::GetUser(enteredName.toStdString());
    if (user != nullptr && user->GetPassword() == enteredPassword.toStdString()) {

        userWindow = std::make_unique<UserWindow>(enteredName.toStdString());
        hide();

    } else {

        QMessageBox::information(this, "Error", "Username or Password not Recognized.",QMessageBox::Ok);
    }
}
