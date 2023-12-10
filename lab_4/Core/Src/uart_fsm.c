/*
 * uart_fsm.c
 *
 *  Created on: Sep 28, 2023
 *      Author: ADMIN
 */
#include "uart_fsm.h"

#define INTERNAL_LINKAGE static

typedef enum {
    WAIT,
    SEND,
    REPEAT
} uart_state_t;

INTERNAL_LINKAGE uart_state_t state = WAIT;
INTERNAL_LINKAGE uint8_t temp_str[30];
extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart2;

void uart_communiation_fsm(void) {
    switch(state) {
    case WAIT:
        if(buffer_flag == 1) {
            buffer_flag = 0;
            if(buffer[0] == 'R' && buffer[1] == 'S' && buffer[2] == 'T') {
                HAL_ADC_Start(&hadc1);
                ADC_value = HAL_ADC_GetValue(&hadc1);
                HAL_ADC_Stop(&hadc1);
                state = SEND;
                setTimer1(300);
            }
            else {
                HAL_UART_Transmit(&huart2, (uint8_t *)"\r\n", 2, HAL_MAX_DELAY);
            }
        }
        break;
    case SEND:
        HAL_UART_Transmit(&huart2, temp_str, sprintf((char *)temp_str, "\r\n!ADC=%ld#\r\n", ADC_value), HAL_MAX_DELAY);
        state = REPEAT;
        break;
    case REPEAT:
        if(buffer_flag == 1) {
            buffer_flag = 0;
            if(buffer[0] == 'O' && buffer[1] == 'K') {
                HAL_UART_Transmit(&huart2, (uint8_t *)"\r\n", 2, HAL_MAX_DELAY);
                state = WAIT;
            }
            else {
                HAL_UART_Transmit(&huart2, (uint8_t *)"\r\n", 2, HAL_MAX_DELAY);
            }
        }
        if(timer1_flag) {
         state = SEND;
         setTimer1(300);
        }
    }
}
