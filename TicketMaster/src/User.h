#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <sodium.h> // for encryption and password hashing functions

/**
 * @class User
 * @brief Represents a user in the system with credentials and department associations.
 *
 * This class encapsulates all necessary details of a user within the system, including
 * their name, password, and the departments they are associated with.
 *
 * @note The password is stored in a hashed format.
 * @author Jacob Price
 */
class User {
private:
    std::string name; ///< User's name.
    std::vector<std::string> departments; ///< Departments the user belongs to.
    std::string password; ///< Hashed password for user authentication.

public:
    /**
     * @brief Constructs a User with a name and password.
     *
     * Initializes the user's name and password. The password is expected to be passed
     * already hashed for security reasons. Departments can be added later using the
     * AddDepartment method.
     *
     * @param name A std::string representing the user's name.
     * @param password A std::string representing the user's hashed password.
     */
    User(const std::string& name, const std::string& password);

    /**
     * @brief Destructor for the User class.
     */
    ~User();

    /**
     * @brief Gets the user's name.
     *
     * @return The name of the user as a std::string.
     */
    std::string GetName() const;

    /**
     * @brief Sets the user's name.
     *
     * @param newName The new name for the user.
     */
    void SetName(const std::string& newName);

    /**
     * @brief Gets the departments the user belongs to.
     *
     * @return A std::vector<std::string> representing the departments of the user.
     */
    std::vector<std::string> GetDepartments() const;

    /**
     * @brief Adds a department to the user's list of departments.
     *
     * @param department The department to add to the user.
     */
    void AddDepartment(const std::string& department);

    /**
     * @brief Removes a department from the user's list.
     *
     * @param department The department to remove from the user.
     */
    void RemoveDepartment(const std::string& department);

    /**
     * @brief Gets the user's password.
     *
     * This method returns the hashed password of the user.
     *
     * @return The hashed password of the user as a std::string.
     */
    std::string GetPassword() const;

    /**
     * @brief Sets the user's password.
     *
     *
     * @param newPassword The new hashed password for the user.
     */
    void SetPassword(const std::string& newPassword);
};

#endif // USER_H


