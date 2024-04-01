/**
 * @file UserManager.h
 * @brief Handles user management, including creation, deletion, and department management.
 *
 * provides functionality to manage user accounts within a system. It includes creating and deleting users, assigning users
 * to departments, and persisting user information to a file.
 *
 * @see User
 * @author Jacob Price
 */

#include "UserManager.h"
#include <algorithm> // for std::find_if
#include <iterator> 
#include <set> // for std::set to collect unique departments
#include <fstream> // for file operations

// Static vector to hold all users in the system.
std::vector<std::shared_ptr<User>> UserManager::users = std::vector<std::shared_ptr<User>>();

/**
 * @brief Default constructor.
 */
UserManager::UserManager() = default;

/**
 * @brief Creates a new user and adds them to the system.
 *
 * creates a new user with the provided name and password only if a user
 * with the same name does not already exist in the system.
 *
 * @param name The name of the user to be created.
 * @param password The password for the user to be created.
 * @return A shared pointer to the newly created User object if successful, nullptr otherwise.
 */
std::shared_ptr<User> UserManager::CreateUser(const std::string& name, const std::string& password) {
    auto it = std::find_if(users.begin(), users.end(), [&name](const std::shared_ptr<User>& user) {
        return user->GetName() == name;
    });

    if (it == users.end()) {
        auto newUser = std::make_shared<User>(name, password);
        users.push_back(newUser);
        return newUser;
    }
    return nullptr;
}

/**
 * @brief Removes a user from the system by name.
 *
 * Searches for a user with the specified name and removes them from the list of managed users
 * if found.
 *
 * @param name The name of the user to remove.
 * @return true if the user was successfully removed, false otherwise.
 */
bool UserManager::RemoveUser(const std::string& name) {
    auto it = std::find_if(users.begin(), users.end(), [&name](const std::shared_ptr<User>& user) {
        return user->GetName() == name;
    });

    if (it != users.end()) {
        users.erase(it);
        return true;
    }
    return false;
}

/**
 * @brief Adds a user to a specified department.
 *
 * Finds a user by name and adds them to the specified department. If the user is found,
 * their AddDepartment method is called with the specified department name.
 *
 * @param name The name of the user to add to the department.
 * @param department The name of the department to add the user to.
 */
void UserManager::AddUserToDepartment(const std::string& name, const std::string& department) {
    auto user = GetUser(name);
    if (user) {
        user->AddDepartment(department);
    }
}

/**
 * @brief Removes a user from a specified department.
 *
 * Finds a user by name and removes them from the specified department. If the user is found,
 * their RemoveDepartment method is called with the specified department name.
 *
 * @param name The name of the user to remove from the department.
 * @param department The name of the department to remove the user from.
 */
void UserManager::RemoveUserFromDepartment(const std::string& name, const std::string& department) {
    auto user = GetUser(name);
    if (user) {
        user->RemoveDepartment(department);
    }
}

/**
 * @brief Retrieves a list of unique department names.
 *
 * Scans through all users and collects a unique list of all departments
 * to which users have been assigned.
 *
 * @return A vector of unique department names.
 */
std::vector<std::string> UserManager::GetExistingDepartments() {
    std::set<std::string> uniqueDepartments;
    for (const auto& user : users) {
        const auto& departments = user->GetDepartments();
        uniqueDepartments.insert(departments.begin(), departments.end());
    }
    return std::vector<std::string>(uniqueDepartments.begin(), uniqueDepartments.end());
}

/**
 * @brief Gets the list of all users in the system.
 *
 * @return A const reference to the vector containing all users.
 */
const std::vector<std::shared_ptr<User>>& UserManager::GetUsers() {
    return users;
}

/**
 * @brief Finds a user by name.
 *
 * Searches for a user with the specified name and returns a shared pointer to the user
 * if found.
 *
 * @param name The name of the user to find.
 * @return A shared pointer to the User object if found, nullptr otherwise.
 */
std::shared_ptr<User> UserManager::GetUser(const std::string& name) {
    auto it = std::find_if(users.begin(), users.end(), [&name](const std::shared_ptr<User>& user) {
        return user->GetName() == name;
    });

    if (it != users.end()) {
        return *it;
    }
    return nullptr;
}

/**
 * @brief Gets a list of users belonging to a specified department.
 *
 * Iterates over all users and collects those who are assigned to the specified
 * department.
 *
 * @param department The name of the department.
 * @return A vector of shared pointers to User objects who are in the specified department.
 */
std::vector<std::shared_ptr<User>> UserManager::GetUsersInDepartment(const std::string& department) {
    std::vector<std::shared_ptr<User>> usersInDepartment;
    for (const auto& user : UserManager::users) {
        const auto& departments = user->GetDepartments();
        if (std::find(departments.begin(), departments.end(), department) != departments.end()) {
            usersInDepartment.push_back(user);
        }
    }
    return usersInDepartment;
}

/**
 * @brief Saves the current list of users to a file.
 *
 * Serializes the current list of users into a JSON format and writes
 * it to the specified file. Each user's name, password, and departments
 * are saved.
 *
 * @param filename The name of the file to save the users to.
 */
void UserManager::SaveUsersToFile(const std::string& filename) {
    Json::Value root;
    for (const auto& user : users) {
        Json::Value userJson;
        userJson["name"] = user->GetName();
        userJson["password"] = user->GetPassword();
        for (const auto& dept : user->GetDepartments()) {
            userJson["departments"].append(dept);
        }
        root.append(userJson);
    }

    std::ofstream file(filename);
    file << root;
}

/**
 * @brief Loads a list of users from a file.
 *
 * Reads a list of users from the specified file.
 * The current list of users is cleared and replaced with the users loaded
 * from the file.
 *
 * @param filename The name of the file to load the users from.
 */
void UserManager::LoadUsersFromFile(const std::string& filename) {
    Json::Value root;
    std::ifstream file(filename);
    file >> root;

    users.clear(); // Clear the existing users

    for (const auto& userJson : root) {
        auto user = std::make_shared<User>(userJson["name"].asString(),
                                           userJson["password"].asString());
        for (const auto& dept : userJson["departments"]) {
            user->AddDepartment(dept.asString());
        }
        users.push_back(user);
    }
}

/**
 * @brief Verifies a user's password.
 *
 * Checks if the specified user exists and verifies their password
 * using a secure hash function.
 *
 * @param name The name of the user whose password to verify.
 * @param password The password to verify.
 * @return true if the password is correct, false otherwise.
 */
bool UserManager::VerifyUserPassword(const std::string& name, const std::string& password) {
    auto it = std::find_if(users.begin(), users.end(), [&name](const std::shared_ptr<User>& user) {
        return user->GetName() == name;
    });

    if (it != users.end()) {
        return crypto_pwhash_str_verify((*it)->GetPassword().c_str(), password.c_str(), password.length()) == 0;
    }
    return false;
}





