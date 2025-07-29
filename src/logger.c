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

void log_massage(Logger* logger, LoggerLevel logger_level, char* massage) {
    if(is_log_buffer_full(logger, logger_level)) {
        return;
    }
    
    FILE* f = fopen(LOG_FILE_PATH, "a");

    if(!f) {
        perror("log.txt");
        return;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", t);
    
    const char* level_str[] = {"INFO", "DEBUG", "WARNING", "ERROR"};
    
    fprintf(f, "[%s] [%s] %s\n", time_str, level_str[logger_level], massage);
    
    int* count_ptr = NULL;
    switch (logger_level) {
        case INFO: count_ptr = &logger->logs_count_info; break;
        case DEBUG: count_ptr = &logger->logs_count_debug; break;
        case WARNING: count_ptr = &logger->logs_count_warning; break;
        case ERROR: count_ptr = &logger->logs_count_error; break;
        default: fclose(f); return;
    }
    
    int index = *count_ptr;
    snprintf(logger->buffer[logger_level][index], MAX_LOG_LENGHT, "[%s] %s", time_str, massage);
    (*count_ptr)++;
    
    fclose(f);
}

void clear_logger_file(Logger* logger) {
    FILE* f = fopen(LOG_FILE_PATH, "w");
    
    if(!f) {
        perror("log.txt");
        return;
    }
    
    fclose(f);
    
    logger->logs_count_info = 0;
    logger->logs_count_debug = 0;
    logger->logs_count_warning = 0;
    logger->logs_count_error = 0;
    
    for(int i = 0; i < LOGGER_LEVEL_COUNT; i++) {
        for(int j = 0; j < MAX_LOGS; j++) {
            logger->buffer[i][j][0] = '\0';
        }
    }
}