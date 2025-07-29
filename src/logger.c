#include "logger.h"
#include <stdbool.h>
#include <stdio.h>

bool is_log_buffer_full(Logger* logger, LoggerLevel lv) {
    int tempcount = 0;
    
    switch (lv)
    {
    case INFO:
        tempcount = logger->logs_count_info;
        break;
    case DEBUG:
        tempcount = logger->logs_count_debug;
        break;
    case WARNING:
        tempcount = logger->logs_count_warning;
        break;
    default:
        tempcount = logger->logs_count_error;
        break;
    }
    
    if(tempcount >= MAX_LOGS) {
        return true;
    }

    return false;
}

void log_massage(Logger* logger, LoggerLevel loger_level, char* massage) {
    if(is_log_buffer_full(logger, loger_level)) {
        return;
    }
    
    FILE* f = fopen(LOG_FILE_PATH, "a");

    if(!f) {
        perror("log.txt");
        return;
    }

    


}