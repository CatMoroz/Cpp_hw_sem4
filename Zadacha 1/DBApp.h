#include "Database.h"
#include <sstream>

class DBapp
{
private:
    bool working = false;
    Database db;
    void handleInput(std::string input);
public:
    DBapp () {};
    void start();
};