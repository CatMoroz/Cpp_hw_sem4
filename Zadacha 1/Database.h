#include "User.h"
#include "Group.h"
#include <map>

struct IdException
{
public:
    std::string message;
    IdException(std::string s) : message(s) {}
};

struct UnknownIdException : IdException
{
public:
    UnknownIdException(int id) : IdException("Error! Unknown id: " + std::to_string(id)) {}
};

struct ExistedIdException : IdException
{
public:
    ExistedIdException(int id) : IdException("Error! Id already exist: " + std::to_string(id)) {}
};

class Database
{
private:
    std::map<int, std::shared_ptr<User>> users;
    std::map<int, std::shared_ptr<Group>> groups;

    void printGroupInfo(std::shared_ptr<Group> group);
public:
    Database() {}
    void createUser(int id, std::string username);
    void deleteUser(int id);
    void allUsers();
    void getUser(int id);
    void createGroup(int id, std::string name);
    void deleteGroup(int id);
    void allGroups();
    void getGroup(int id);
    void addUserToGroup(int user_id, int group_id);
};