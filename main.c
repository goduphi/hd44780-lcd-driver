#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "wait.h"
#include "hd44780.h"

int main(void)
{
    initHd44780();
    resetDisplay();

    char s[] = "LCD Test";
    uint8_t sLen = (sizeof(s) / sizeof(char)) - 1;

    // LCD test
	while(true)
	{
	    uint8_t i;
	    /*
        for(i = 1; i <= 50; i++)
        {
            if(i % 25 == 0)
                sendCommand(NEW_LINE);
            putcLcd((i - 1) + ' ');
            waitMicrosecond(ONE_SECOND/2);
        }
        */
	    for(i = 0; i < sLen; i++)
	    {
	        putcLcd(s[i]);
            waitMicrosecond(ONE_SECOND/3);
	    }
        sendCommand(CLEAR_DISP);
        waitMicrosecond(ONE_SECOND/2);
        sendCommand(0x80);
	}
}
