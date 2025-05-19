#include "Database.h"

void Database::createUser(int id, std::string username)
{
    if (users.find(id) != users.end())
        throw ExistedIdException(id);
    
    users[id] = std::make_shared<User>(User(id, username));
}

void Database::deleteUser(int id)
{
    auto it = users.find(id);
    if (it == users.end())
        throw UnknownIdException(id);
    
    if (users[id]->getGroup() != nullptr)
        users[id]->getGroup()->deleteUser(users[id]);

    users.erase(it);
}

void Database::allUsers()
{
    std::cout << "Users count: " << users.size() << '\n';
    for (auto node: users)
        node.second->printInfo();
}

void Database::getUser(int id)
{
    auto it = users.find(id);
    if (it == users.end())
        throw UnknownIdException(id);
    
    users[id]->printInfo();
}

void Database::createGroup(int id, std::string name)
{
    if (groups.find(id) != groups.end())
        throw ExistedIdException(id);
    
    groups[id] = std::make_shared<Group>(Group(id, name));
}

void Database::deleteGroup(int id)
{
    auto it = groups.find(id);
    if (it == groups.end())
        throw UnknownIdException(id);
    
    for (auto user : groups[id]->getUsers())
        user->setGroup(nullptr);

    groups.erase(it);
}

void Database::printGroupInfo(std::shared_ptr<Group> group)
{
    std::cout << "Group id: " << group->getId() << ", name: " << group->getName() << '\n';
    for (auto user : group->getUsers())
    {
        std::cout << "  ";
        user->printInfo();
    }
}

void Database::getGroup(int id)
{
    auto it = groups.find(id);
    if (it == groups.end())
        throw UnknownIdException(id);
        
    printGroupInfo(groups[id]);
}

void Database::allGroups()
{
    std::cout << "Groups count: " << groups.size() << '\n';
    for (auto node : groups)
        printGroupInfo(node.second);
}

void Database::addUserToGroup(int user_id, int group_id)
{
    if (users.find(user_id) == users.end())
        throw UnknownIdException(user_id);

    if (groups.find(group_id) == groups.end())
        throw UnknownIdException(group_id);

    auto user = users[user_id];
    auto new_group = groups[group_id];

    std::shared_ptr<Group> group = user->getGroup();

    if (group == nullptr)
    {
        new_group->addUser(user);
        return;
    }

    group->deleteUser(user);
    new_group->addUser(user);
}