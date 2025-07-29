#ifndef LOGGER_H
#define LOGGER_H

#define MAX_LOGS 100
#define MAX_LOG_LENGHT 100
#define LOG_FILE_PATH "/home/nikita/MyProjects/CircuitEngineGit/logs/log.txt" 

typedef enum LoggerLevel {
    INFO,
    DEBUG,
    WARNING,
    ERROR,
    LOGGER_LEVEL_COUNT
} LoggerLevel;

typedef struct  Logger {
    char buffer[LOGGER_LEVEL_COUNT][MAX_LOGS][MAX_LOG_LENGHT];
    int logs_count_info;
    int logs_count_debug;
    int logs_count_warning;
    int logs_count_error;
} Logger;

void log_massage(Logger* logger, LoggerLevel loger_level, char* massage);
bool is_log_buffer_full(Logger* l, LoggerLevel lv);
void clear_logger_file(Logger* logger);

#endif //LOGGER_H