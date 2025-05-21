#pragma once

#include <vector>
#include <set>
#include <memory>
#include <string>
#include <iostream>

class User;

class Group
{
private:
    int id;
    std::string name;
    std::set<std::shared_ptr<User>> users;
public:
    Group(int id, std::string name) : id(id), name(name) {}
    void addUser(std::shared_ptr<User> user) { users.insert(user); }
    std::set<std::shared_ptr<User>> getUsers() { return users; }
    int getId() { return id; }
    std::string getName() { return name; }
    void deleteUser(std::shared_ptr<User> user) { users.erase(user); }
};
