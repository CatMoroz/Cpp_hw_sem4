#pragma once

#include <time.h>
#include <vector>
#include <iostream>

#define LOG_NORMAL 0
#define LOG_WARNING 1
#define LOG_ERROR 2

const std::vector<const char*> code_handler{"Normal", "Warning", "Error"};
struct LogNode
{
    time_t message_time;
    int message_code;
    const char* message;

    LogNode (int msg_code, const char* msg) : message_time(time(NULL)), message_code(msg_code), message(msg) {}
};

class Log
{
private:
    Log() {}
    ~Log() {}
    static Log* instance;
    static std::vector<LogNode> events;

public:
    static Log* Instance()
    {
        if (!instance)
        {
            instance = new Log();
        }
        return instance;
    }

    static void message(int msg_code, const char* msg)
    {
        events.push_back(LogNode(msg_code, msg));
    }

    static void print()
    {
        int begin = (events.size() <= 10) ? 0 : events.size() - 10;
        for (int i = begin; i < events.size(); i++)
        {
            std::cout << events[i].message_time << ": [" << code_handler[events[i].message_code] << "] " << events[i].message << '\n'; 
        }
    }

};

Log* Log::instance = nullptr;
std::vector<LogNode> Log::events = {};