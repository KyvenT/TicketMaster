#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

/**
 * The User class represents a user in the system.
 * It stores information about the user's name, password, and departments they belong to.
 */
class User {
private:
    std::string name; ///< The name of the user.
    std::vector<std::string> departments; ///< The departments to which the user belongs.
    std::string password; ///< The password for the user's account.

public:
    /**
     * Constructor for the User class.
     * Initializes a new User object with a name and password.
     * Departments can be added later using the AddDepartment method.
     * @param name A std::string representing the name of the user.
     * @param password A std::string representing the password of the user.
     */
    User(const std::string& name, const std::string& password);

    /**
     * Destructor for the User class.
     */
    ~User();

    /**
     * Gets the name of the user.
     * @return The name of the user as a std::string.
     */
    std::string GetName() const;

    /**
     * Sets the name of the user.
     * @param newName The new name for the user.
     */
    void SetName(const std::string& newName);

    /**
     * Gets the departments of the user.
     * @return A std::vector<std::string> representing the departments of the user.
     */
    std::vector<std::string> GetDepartments() const;

    /**
     * Adds a department to the user.
     * @param department The department to add.
     */
    void AddDepartment(const std::string& department);

    /**
     * Removes a department from the user.
     * @param department The department to remove.
     */
    void RemoveDepartment(const std::string& department);

    /**
     * Gets the password of the user.
     * @return The password of the user as a std::string.
     */
    std::string GetPassword() const;

    /**
     * Sets the password for the user.
     * @param newPassword The new password for the user.
     */
    void SetPassword(const std::string& newPassword);
};

#endif // USER_H


