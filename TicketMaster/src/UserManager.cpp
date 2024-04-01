#include "UserManager.h"
#include <algorithm>
#include <iterator>
#include <set>
#include <fstream>


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

bool UserManager::VerifyUserPassword(const std::string& name, const std::string& password) {
    auto it = std::find_if(users.begin(), users.end(), [&name](const std::shared_ptr<User>& user) {
        return user->GetName() == name;
    });

    if (it != users.end()) {
        return crypto_pwhash_str_verify((*it)->GetPassword().c_str(), password.c_str(), password.length()) == 0;
    }
    return false;
}




