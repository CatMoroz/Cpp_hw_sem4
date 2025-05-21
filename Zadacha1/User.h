#pragma once

#include <string>
#include <memory>
#include <iostream>

class Group;

class User
{
private:
    int id;
    std::shared_ptr<Group> group;
    std::string username;    
public:
    User(int id, std::string username, std::shared_ptr<Group> group = nullptr) : id(id), username(username), group(group) {}
    int getId() { return id; }
    void printInfo() { std::cout << " id: " << id <<  ", username: " << username << '\n'; }
    std::shared_ptr<Group> getGroup() { return group; }
    void setGroup(std::shared_ptr<Group> group) { this->group = group; }
};