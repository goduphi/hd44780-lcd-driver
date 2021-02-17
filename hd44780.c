/*
 * DB0 - DB5:   PE0 - PE5
 * DB6 - DB7:   PD0 - PD1
 *
 */
#include "clock.h"
#include "hd44780.h"
#include "wait.h"

// Refer to Page 17 of the Datasheet
uint8_t characterSet[] = {
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
    0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31,
    0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A,
    0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40,
    0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
    0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52,
    0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B,
    0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61, 0x62, 0x63, 0x64,
    0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D,
    0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76,
    0x77, 0x78, 0x79, 0x7A
};

void initHd44780(void)
{
    initSystemClockTo40Mhz();

    enablePort(PORTB);
    enablePort(PORTD);
    enablePort(PORTE);

    selectPinPushPullOutput(RS);
    selectPinPushPullOutput(RW);
    selectPinPushPullOutput(EN);

    selectPinPushPullOutput(DB0);
    selectPinPushPullOutput(DB1);
    selectPinPushPullOutput(DB2);
    selectPinPushPullOutput(DB3);
    selectPinPushPullOutput(DB4);
    selectPinPushPullOutput(DB5);
    selectPinPushPullOutput(DB6);
    selectPinPushPullOutput(DB7);

    // By default the enable pin should be disabled
    setPinValue(EN, 0);
}

void sendCommand(uint16_t data)
{
    setPinValue(RS, (data & RS_DATA_M));
    setPinValue(RW, (data & READ_M));
    // Set pins PE0 - PE5
    setPortValue(PORTE, (data & DB0_DB5_M));
    // Set pins PD2, PD3
    setPinValue(DB6, (data & DB6_M));
    setPinValue(DB7, (data & DB7_M));
    setPinValue(EN, 1);
    // The return home function takes the longest time.
    // It takes 1.52ms
    waitMicrosecond(1600);
    setPinValue(EN, 0);
}

void resetDisplay(void)
{
    // Refer to page 45 of the Datasheet
    // Wait time > 15ms
    waitMicrosecond(20000);
    sendCommand(0x30);
    waitMicrosecond(5000);
    sendCommand(0x30);
    waitMicrosecond(150);
    sendCommand(0x30);

    // Wait for internal operation to end
    // The busy flag will be set to 1 while internal operation
    // is being performed
    sendCommand(READ_M);
    while(getPinValue(DB7));

    // Refer to page 4 of the Datasheet
    // Display off, 2 line display, 5x8 character font
    sendCommand(0x38);
    // Turn display on
    sendCommand(0xC);
    // Clear display
    sendCommand(CLEAR_DISP);
    // Set entry mode, increment the cursor by 1
    sendCommand(0x6);
}

// Takes an ASCII character and prints it on to the LCD
void putcLcd(char c)
{
    // Select data register and write data
    sendCommand(RS_DATA_M | characterSet[c - ' ']);
}

// Takes string and prints it on to the LCD
void putsLcd(const char* str)
{
    uint8_t i = 0;
    while(str[i] != '\0')
    {
        putcLcd(str[i++]);
    }
}
