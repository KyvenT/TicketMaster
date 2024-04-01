#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include "User.h"
#include <vector>
#include <memory>
#include <string>
#include <set>
#include <json/json.h>
#include <sodium.h>

/**
 * @brief Class to manage users and their department associations.
 * @author Jacob Price
 *
 * The UserManager class encapsulates methods for creating and managing users within a system.
 * It provides functionalities to add, remove, and manage users and their associations with
 * different departments.
 *
 * @note This class requires the 'jsoncpp' library for JSON processing and 'libsodium' for password hashing.
 */
class UserManager {
public:
    /**
     * @brief Constructor for UserManager.
     * 
     * Initializes the UserManager instance. Given that all operations are static,
     * the constructor is provided but not intended for direct use.
     */
    UserManager();

    /**
     * @brief Creates a new user and adds them to the system.
     * 
     * @param name The name of the new user.
     * @param password The password for the new user.
     * @return std::shared_ptr<User> A shared pointer to the newly created user.
     */
    static std::shared_ptr<User> CreateUser(const std::string& name, const std::string& password);

    /**
     * @brief Removes a user from the system by their name.
     * 
     * @param name The name of the user to remove.
     * @return bool True if the user was successfully removed; otherwise, false.
     */
    static bool RemoveUser(const std::string& name);

    /**
     * @brief Adds a user to a department.
     * 
     * @param name The name of the user to add to the department.
     * @param department The name of the department.
     */
    static void AddUserToDepartment(const std::string& name, const std::string& department);

    /**
     * @brief Removes a user from a department.
     * 
     * @param name The name of the user to remove from the department.
     * @param department The name of the department.
     */
    static void RemoveUserFromDepartment(const std::string& name, const std::string& department);

    /**
     * @brief Retrieves a list of all existing departments by examining all users.
     * 
     * @return std::vector<std::string> A list of unique department names.
     */
    static std::vector<std::string> GetExistingDepartments();

    /**
     * @brief Gets a read-only reference to the list of users.
     * 
     * @return const std::vector<std::shared_ptr<User>>& A constant reference to the vector of users.
     */
    static const std::vector<std::shared_ptr<User>>& GetUsers();

    /**
     * @brief Helper function to find a user by name.
     * 
     * @param name The name of the user to find.
     * @return std::shared_ptr<User> A shared pointer to the user if found; nullptr otherwise.
     */
    static std::shared_ptr<User> GetUser(const std::string& name);

    /**
     * @brief Gets a list of users in a specific department.
     * 
     * @param department The name of the department.
     * @return std::vector<std::shared_ptr<User>> A vector of shared pointers to users in the department.
     */
    static std::vector<std::shared_ptr<User>> GetUsersInDepartment(const std::string& department);
  
    /**
     * @brief Saves the current list of users to a file.
     * 
     * @param filename The path to the file where users will be saved.
     */
    static void SaveUsersToFile(const std::string& filename);

    /**
     * @brief Loads users from a file into the UserManager.
     * 
     * @param filename The path to the file from which users will be loaded.
     */
    static void LoadUsersFromFile(const std::string& filename);

    /**
     * @brief Verifies a user's password.
     * 
     * @param name The name of the user.
     * @param password The password to verify.
     * @return bool True if the password is correct; otherwise, false.
     */
    static bool VerifyUserPassword(const std::string& name, const std::string& password);

private:
    static std::vector<std::shared_ptr<User>> users; ///< Static list of users maintained by UserManager.
};

#endif // USER_MANAGER_H


