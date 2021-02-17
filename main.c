#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "wait.h"
#include "hd44780.h"

int main(void)
{
    initHd44780();
    sendCommand(0x0001);
    sendCommand(0x0038);
    sendCommand(0x000E);
    sendCommand(0x0006);
    putsLcd("LCD Test");
	while(true);
}
