/*
 * hd44780.h
 *
 *  Created on: Feb 14, 2021
 *      Author: afrid
 */

#ifndef HD44780_H_
#define HD44780_H_

#include <stdint.h>
#include "gpio.h"

#define RS              PORTD,0
#define RW              PORTD,1
#define EN              PORTB,0
#define DB0             PORTE,0
#define DB1             PORTE,1
#define DB2             PORTE,2
#define DB3             PORTE,3
#define DB4             PORTE,4
#define DB5             PORTE,5
#define DB6             PORTD,2
#define DB7             PORTD,3

#define DB0_DB5_M       0x3F
#define DB6_M           0x40
#define DB7_M           0x80

#define RS_DATA_M       0x200
#define READ_M          0x100

typedef enum _commands
{
    CLEAR_DISP  =   0x01,
    NEW_LINE    =   0xC0
} commands;

void initHd44780(void);
void resetDisplay(void);
void sendCommand(uint16_t data);
void putcLcd(char c);
void putsLcd(const char* str);

#endif /* HD44780_H_ */
