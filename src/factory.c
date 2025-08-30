#include "factory.h"
#include "circuit.h"
#include "program.h"
#include "utils.h"
#include "globals.h"
#include "command_console.h"
#include <stdlib.h>
#include <ncurses.h>

/*CREATING ALL ENTITIES*/

CircuitComponent* create_component(ComponentType type, int x, int y, void (*action)(struct CircuitComponent*, int)) {
    //todo implement creating all components by switch


    /*CircuitComponent* component = malloc(sizeof(CircuitComponent));
    component->type = type;
    component->x = x;
    component->y = y;
    component->state.enabled = false;
    component->state.energized = false;
    component->action = none; // will use that in switch case

    /*
    switch (type)
    {
    case RESISTOR:
        component->value = 120; //OM
        return component;
        break;
    case WIRE:
        break;
    default: return;
    }
    */
}

Circuit* create_circuit() {
    Circuit* c = malloc(sizeof(Circuit));
    if(c == NULL) {
        return NULL;
    }
    c->enabled = false;
    c->components[0] = NULL;
    return c; 
}

Program* create_program() {
    Program* program = malloc(sizeof(Program));
    if(program == NULL) {
        return NULL;
    }

    program->circuit = init_circuit();
    program->program_state = ProgramStateMenu;
    program->program_running = true;
    program->current_window = MainWindow;
    program->main_window = stdscr;
    program->command_console = init_command_console();

    int width, height;
    width = get_current_window_size(GET_WIDTH);
    height = get_current_window_size(GET_HEIGHT);

    program->prev_frame_program_buffer = calloc(height, sizeof(char*));
    if (program->prev_frame_program_buffer == NULL) {
        free(program);
        return NULL;
    }

    for(int i = 0; i < height; i++) {
        program->prev_frame_program_buffer[i] = calloc(width, sizeof(char));
        if (program->prev_frame_program_buffer[i] == NULL) {
            for(int j = 0; j < i; j++) {
                free(program->prev_frame_program_buffer[j]);
            }
            free(program->prev_frame_program_buffer);
            free(program);
            return NULL;
        }
    }
    
    return program;
}

Button* create_button(int x, int y, char* name) {
    Button* b = malloc(sizeof(Button));

    if(b == NULL) {
        return NULL;
    }

    b->x = x;
    b->y = y;
    b->name = name;
    b->selected = false;

    return b;
}

MenuButtons* create_menu_buttons() {
    static MenuButtons* mb = NULL;  

    if (mb != NULL) {
        return mb; 
    }

    mb = malloc(sizeof(MenuButtons));
    if (mb == NULL) {
        return NULL;
    }

    int win_width = get_current_window_size(GET_WIDTH);
    int win_height = get_current_window_size(GET_HEIGHT);
    int center_width = win_width / 2;
    int center_height = win_height / 2;

    Button* start_button = create_button(center_width, center_height, "NEW CIRCUIT");
    Button* load_button = create_button(center_width, center_height, "LOAD CIRCUIT"); 
    Button* settings_button = create_button(center_width, center_height, "SETTINGS"); 
    Button* exit_button = create_button(center_width, center_height, "EXIT"); 
    start_button->selected = true;
    mb->buttons[0] = start_button;
    mb->buttons[1] = load_button;
    mb->buttons[2] = settings_button;
    mb->buttons[3] = exit_button;

    log_message(global_loger, INFO, "Menu initialized successfully..");

    return mb;
}

Logger* create_logger() {
    Logger* logger = malloc(sizeof(Logger));
    if (logger == NULL) {
        return NULL;
    }

    return logger;
}

/*FREE ALL ENTITIES*/
void free_button(Button* b) {
    if(b) {
        if(b->name) {
            free(b->name);
        }
        free(b);
    }
}
void free_menu_buttons(MenuButtons* mb) {
    if(mb) {
        for(int i = 0; i < MENU_BUTTONS_COUNT; i++) {
            if(mb->buttons[i]) {
                free_button(mb->buttons[i]);
            }
        }
        free(mb->buttons);
        free(mb);
    }
}
void free_circuit(Circuit* c) {
    if(c) {
        for(int i = 0; i < c->count_components; i++) {
            free_circuit_component(c->components[i]);
        }
        free(c);
    }
}
void free_circuit_component(CircuitComponent* cc) {
    if(cc) {
        free(cc->action);
        free(cc->name);
        free(cc);
    }
}
void free_program(Program* p) {
    if(p) {
        free_circuit(p->circuit);
        free(p);
    }
}

