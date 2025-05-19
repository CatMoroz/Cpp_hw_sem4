#include "Log.h"

int main()
{
    Log *log = Log::Instance(); 
    log->message(LOG_NORMAL, "program loaded");
    log->message(LOG_ERROR, "error happens! help me!"); 
    log->message(LOG_WARNING, "test warning!");
    log->print(); 
}