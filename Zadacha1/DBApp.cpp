#include "DBApp.h"

std::vector<std::string> get_tokens(std::string input)
{
    std::vector<std::string> tokens;
    std::stringstream s(input);
    std::string token;

    while (s >> token)
        tokens.push_back(token);
    return tokens;
}

void DBapp::start()
{
    working = 1;
    std::string input;
    std::string word;
    while (working)
    {
        std::cout << "Enter your command: ";
        getline(std::cin, input);

        handleInput(input);
    }
}

void DBapp::handleInput(std::string input)
{
    std::vector<std::string> tokens = get_tokens(input);
    try
    {
        if (tokens.size() == 1)
        {
            if (tokens[0] == "exit")
                working = 0;
            else if (tokens[0] == "allUsers")
                db.allUsers();
            else if (tokens[0] == "allGroups")
                db.allGroups();
            else throw std::invalid_argument("Wrong command or number of arguments!");
        }
        else if (tokens.size() == 2)
        {
            if (tokens[0] == "deleteUser")
                db.deleteUser(stoi(tokens[1]));
            else if (tokens[0] == "getUser")
                db.getUser(stoi(tokens[1]));
            else if (tokens[0] == "deleteGroup")
                db.deleteGroup(stoi(tokens[1]));
            else if (tokens[0] == "getGroup")
                db.getGroup(stoi(tokens[1]));
            else throw std::invalid_argument("Wrong command or number of arguments!");
        }
        else if (tokens.size() == 3)
        {
            if (tokens[0] == "createUser")
                db.createUser(stoi(tokens[1]), tokens[2]);
            else if (tokens[0] == "createGroup")
                db.createGroup(stoi(tokens[1]), tokens[2]);
            else if (tokens[0] == "addUserToGroup")
                db.addUserToGroup(stoi(tokens[1]), stoi(tokens[2]));
            else throw std::invalid_argument("Wrong command or number of arguments!");
        }
        else
            throw std::invalid_argument("Wrong command or number of arguments!");
    }
    catch(std::invalid_argument a)
    {
        std::cout << "Error! Wrong command or number of arguments!\n";
    }
    catch(IdException a)
    {
        std::cout << a.message << '\n';
    }
}