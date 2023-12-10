/*
 * parser_fsm.c
 *
 *  Created on: Sep 28, 2023
 *      Author: ADMIN
 */

#include "parser_fsm.h"

#define INTERNAL_LINKAGE static

typedef enum parser_state_t {
    WAIT_INPUT,
    WAIT_END
} parser_state_t;

INTERNAL_LINKAGE parser_state_t state = WAIT_INPUT;

void command_parser_fsm(void) {
    switch(state) {
    case WAIT_INPUT:
        if(temp == '!') {
            state = WAIT_END;
            index_buffer = 0;
            memset(buffer, 0, sizeof(buffer));
        }
        break;
    case WAIT_END:
        if(temp == '#') {
            state = WAIT_INPUT;
            buffer_flag = 1;
        }
        else {
            if(temp == '!') {
                index_buffer = 0;
                memset(buffer, 0, sizeof(buffer));
            }
            else {
                buffer[index_buffer] = temp;
                index_buffer += 1;
                if(index_buffer == MAX_BUFFER_SIZE) index_buffer = 0;
            }
        }
        break;
    default:
        break;
    }
}
