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
#include "MultiSelectComboBox.h"

class AdminWindow : public QWidget {
    Q_OBJECT
public:
    explicit AdminWindow(QWidget *parent = nullptr);

private slots:
    void addDepartment();
    void deleteDepartment(QWidget *departmentWidget, const QString &departmentName);
    void populateDepartmentsScrollArea();
    void addDepartmentWidget(const QString& departmentName);
    void populateDepartmentsComboBox();
    void populateUsersScrollArea();
    void addUserWidget(const std::shared_ptr<User>& user);
    void deleteUser(QWidget *userWidget, const QString &username);
    void addUser();

private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *usersLabelLayout;
    QLabel *usersLabel;
    QHBoxLayout *usernameLayout;
    QLabel *usernameLabel;
    QLineEdit *usernameLineEdit;
    QHBoxLayout *passwordLayout;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QHBoxLayout *departmentLayout;
    QLabel *departmentLabel;
    MultiSelectComboBox *departmentComboBox;
    QPushButton *usersAddButton;
    QScrollArea *usersScrollArea;
    QHBoxLayout *departmentsLabelLayout;
    QLabel *departmentsLabel;
    QLineEdit *departmentsLineEdit;
    QPushButton *departmentsAddButton;
    QScrollArea *departmentsScrollArea;
    QVBoxLayout *departmentsListLayout;
    QSet<QString> departmentNames;
    QVBoxLayout *usersListLayout;
    std::vector<std::string> departmentNamesVector;
};

#endif // ADMINWINDOW_H
