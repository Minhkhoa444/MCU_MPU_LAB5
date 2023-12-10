/*
 * global.h
 *
 *  Created on: Sep 28, 2023
 *      Author: ADMIN
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "software_timer.h"
#include "parser_fsm.h"
#include "uart_fsm.h"
#include "scheduler.h"
#include "main.h"

#define MAX_BUFFER_SIZE 30

extern uint8_t temp;
extern uint8_t process_flag;
extern uint8_t buffer[MAX_BUFFER_SIZE];
extern uint8_t buffer_flag;
extern uint8_t index_buffer;
extern uint32_t ADC_value;

#endif /* INC_GLOBAL_H_ */
