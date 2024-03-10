#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include "User.h"
#include <vector>
#include <memory>
#include <string>
#include <set>

/**
 * The UserManager class manages a collection of users.
 * It provides functionality to manage users and their department associations.
 */
class UserManager {
public:
    UserManager();

    // Creates a new user and adds them to the system.
    std::shared_ptr<User> CreateUser(const std::string& name, const std::string& password);

    // Removes a user from the system by their name.
    bool RemoveUser(const std::string& name);

    // Adds a user to a department.
    void AddUserToDepartment(const std::string& name, const std::string& department);

    // Removes a user from a department.
    void RemoveUserFromDepartment(const std::string& name, const std::string& department);

    // Retrieves a list of all existing departments by examining all users.
    std::vector<std::string> GetExistingDepartments() const;

    // Gets a read-only reference to the list of users.
    const std::vector<std::shared_ptr<User>>& GetUsers() const;

private:
    std::vector<std::shared_ptr<User>> users; // List of users

    // Helper function to find a user by name. Returns a shared pointer to the user if found.
    std::shared_ptr<User> GetUser(const std::string& name);
};

#endif // USER_MANAGER_H

