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
    static std::shared_ptr<User> CreateUser(const std::string& name, const std::string& password);

    // Removes a user from the system by their name.
    static bool RemoveUser(const std::string& name);

    // Adds a user to a department.
    static void AddUserToDepartment(const std::string& name, const std::string& department);

    // Removes a user from a department.
    static void RemoveUserFromDepartment(const std::string& name, const std::string& department);

    // Retrieves a list of all existing departments by examining all users.
    static std::vector<std::string> GetExistingDepartments();

    // Gets a read-only reference to the list of users.
    static const std::vector<std::shared_ptr<User>>& GetUsers();

    // Helper function to find a user by name. Returns a shared pointer to the user if found.
    static std::shared_ptr<User> GetUser(const std::string& name);

    static std::vector<std::shared_ptr<User>> GetUsersInDepartment(const std::string& department);

private:
    static std::vector<std::shared_ptr<User>> users; // List of users

};

#endif // USER_MANAGER_H

