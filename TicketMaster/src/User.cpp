#include "User.h"
#include <algorithm> // For std::find and std::remove

/**
 * @brief Constructs a user with specified name and password.
 *
 * The constructor initializes a user object with a name and password.
 *
 * @author Jacob Price
 *
 * @param name User's name.
 * @param password User's hashed password.
 */
User::User(const std::string& name, const std::string& password)
        : name(name), password(password) {
    // Constructor body intentionally left empty.
}

/**
 * @brief Destructor for the User class.
 */
User::~User() {
    // Destructor body intentionally left empty.
}

/**
 * @brief Returns the name of the user.
 *
 * @return User's name as a std::string.
 */
std::string User::GetName() const {
    return name;
}

/**
 * @brief Sets the user's name to a new value.
 *
 * @param newName The new name for the user.
 */
void User::SetName(const std::string& newName) {
    name = newName;
}

/**
 * @brief Retrieves the departments associated with the user.
 *
 * @return A vector of strings representing the departments.
 */
std::vector<std::string> User::GetDepartments() const {
    return departments;
}

/**
 * @brief Adds a department to the user's list of departments.
 *
 * This method checks if the department is not already associated with the user
 * before adding it to prevent duplicates.
 *
 * @param department Department to be added to the user.
 */
void User::AddDepartment(const std::string& department) {
    if (std::find(departments.begin(), departments.end(), department) == departments.end()) {
        departments.push_back(department); // Add department if not already present
    }
}

/**
 * @brief Removes a department from the user's list of departments.
 *
 * @param department Department to be removed from the user.
 */
void User::RemoveDepartment(const std::string& department) {
    auto it = std::remove(departments.begin(), departments.end(), department);
    departments.erase(it, departments.end()); // Erase the removed elements
}

/**
 * @brief Retrieves the hashed password of the user.
 *
 * @return User's hashed password as a std::string.
 */
std::string User::GetPassword() const {
    return password;
}

/**
 * @brief Sets the user's password after hashing it.
 *
 * The method hashes the new password. If password hashing fails, an exception
 * is thrown.
 *
 * @param newPassword The new password for the user.
 * @throw std::runtime_error if password hashing fails.
 */
void User::SetPassword(const std::string& newPassword) {
    char hashed_password[crypto_pwhash_STRBYTES];
    if (crypto_pwhash_str(hashed_password, newPassword.c_str(), newPassword.length(),
                          crypto_pwhash_OPSLIMIT_INTERACTIVE, crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0) {
        throw std::runtime_error("Password hashing failed."); // Error handling for failed password hashing
    }
    password = hashed_password; // Update user's password with the hashed version
}


