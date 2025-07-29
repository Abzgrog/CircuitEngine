#ifndef GLOBAL_H
#define GLOBAL_H

// Предварительные объявления вместо включения заголовочных файлов
struct Program;
struct Logger;

#define MAX_COMPONENTS 100
#define BUFFER_WIDTH 50
#define BUFFER_HEIGHT 30

extern struct Program* global_program;
extern struct Logger* global_logger;
void init_all_extern_globals();

#endif //GLOBAL_H