#include "UserManager.h"
#include <algorithm>
#include <iterator>
#include <set>

std::vector<std::shared_ptr<User>> UserManager::users = std::vector<std::shared_ptr<User>>();

UserManager::UserManager() = default;

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

void UserManager::AddUserToDepartment(const std::string& name, const std::string& department) {
    auto user = GetUser(name);
    if (user) {
        user->AddDepartment(department);
    }
}

void UserManager::RemoveUserFromDepartment(const std::string& name, const std::string& department) {
    auto user = GetUser(name);
    if (user) {
        user->RemoveDepartment(department);
    }
}

std::vector<std::string> UserManager::GetExistingDepartments() {
    std::set<std::string> uniqueDepartments;
    for (const auto& user : users) {
        const auto& departments = user->GetDepartments();
        uniqueDepartments.insert(departments.begin(), departments.end());
    }
    return std::vector<std::string>(uniqueDepartments.begin(), uniqueDepartments.end());
}

const std::vector<std::shared_ptr<User>>& UserManager::GetUsers() {
    return users;
}

std::shared_ptr<User> UserManager::GetUser(const std::string& name) {
    auto it = std::find_if(users.begin(), users.end(), [&name](const std::shared_ptr<User>& user) {
        return user->GetName() == name;
    });

    if (it != users.end()) {
        return *it;
    }
    return nullptr;
}



