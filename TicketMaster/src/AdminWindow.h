#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H
#include <iostream>

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QApplication>
#include <QSet>
#include <QMessageBox>
#include <QComboBox>
#include "UserManager.h"

/**
 * @brief AdminWindow displays the existing users and departments and also provides functionality for an admin to add/delete users and departments
 * @author Deanna Chen
*/

class AdminWindow : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief constructor
    */
    explicit AdminWindow(QWidget *parent = nullptr);

private slots:
    /**
     * @brief adds department to the GUI
    */
    void addDepartment();

    /**
     * @brief deletes department from the GUI
     * @param the widget of the department
     * @param the name of the department
    */
    void deleteDepartment(QWidget *departmentWidget, const QString &departmentName);

    /**
     * @brief populates the scroll area with existing departments
    */
    void populateDepartmentsScrollArea();

    /**
     * @brief creates a department widget to be added
     * @param the name of the department
    */
    void addDepartmentWidget(const QString& departmentName);

    /**
     * @brief fills the combobox with the names of the departments
    */
    void populateDepartmentsComboBox();

    /**
     * @brief fills user scroll area with the names of the users
    */
    void populateUsersScrollArea();

    /**
     * @brief adds the user widget to the GUI
     * @param the user object
    */
    void addUserWidget(const std::shared_ptr<User>& user);

    /**
     * @brief deletes a user to GUI
     * @param the user widget to be deleted
     * @param the username to be deleted
    */
    void deleteUser(QWidget *userWidget, const QString &username);

    /**
     * @brief adds a user to GUI
    */
    void addUser();

private:
    // main layout of the gui
    QVBoxLayout *mainLayout;

    // layout for the user label
    QHBoxLayout *usersLabelLayout;

    // user label
    QLabel *usersLabel;

    // layout for username
    QHBoxLayout *usernameLayout;
    
    // label for username
    QLabel *usernameLabel;

    // line edit area for username
    QLineEdit *usernameLineEdit;

    // layout for password
    QHBoxLayout *passwordLayout;

    // label for password
    QLabel *passwordLabel;

    // line edit area for password
    QLineEdit *passwordLineEdit;

    // layout for department
    QHBoxLayout *departmentLayout;

    // label for department
    QLabel *departmentLabel;

    // combobox for departments
    QComboBox *departmentComboBox;

    // button to add users
    QPushButton *usersAddButton;
    
    // scroll area to show all users
    QScrollArea *usersScrollArea;

    // label layout for departments
    QHBoxLayout *departmentsLabelLayout;

    // department label
    QLabel *departmentsLabel;

    // line edit for departments
    QLineEdit *departmentsLineEdit;

    // button to add departments
    QPushButton *departmentsAddButton;

    // scroll area to show list of departments
    QScrollArea *departmentsScrollArea;

    // layout for the departments list
    QVBoxLayout *departmentsListLayout;

    // list of department names
    QSet<QString> departmentNames;

    // layout for users list
    QVBoxLayout *usersListLayout;

    // vector of department names
    std::vector<std::string> departmentNamesVector;
};

#endif // ADMINWINDOW_H
