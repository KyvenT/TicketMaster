#include "User.h"
#include <algorithm>

User::User(const std::string& name, const std::string& password)
        : name(name), password(password) {
    // Constructor body left intentionally empty.
}

User::~User() {

}

std::string User::GetName() const {
    return name;
}

void User::SetName(const std::string& newName) {
    name = newName;
}

std::vector<std::string> User::GetDepartments() const {
    return departments;
}

void User::AddDepartment(const std::string& department) {
    // Check if the department is not already present
    if (std::find(departments.begin(), departments.end(), department) == departments.end()) {
        departments.push_back(department);
    }
}

void User::RemoveDepartment(const std::string& department) {
    auto it = std::remove(departments.begin(), departments.end(), department);
    departments.erase(it, departments.end());
}

std::string User::GetPassword() const {
    return password;
}

void User::SetPassword(const std::string& newPassword) {
    char hashed_password[crypto_pwhash_STRBYTES];
    if (crypto_pwhash_str(hashed_password, newPassword.c_str(), newPassword.length(),
                          crypto_pwhash_OPSLIMIT_INTERACTIVE, crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0) {

        throw std::runtime_error("Password hashing failed.");
    }
    password = hashed_password;
}

