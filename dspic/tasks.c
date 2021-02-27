/* 
 * File:   tasks.c
 * Author: oliver
 *
 * Created on 8. Januar 2021, 12:46
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../common/defines.h"

#include "../dspic/board.h"
#include "../drivers/encoder.h"
#include "../drivers/serial_uart.h"
#include "../drivers/motor.h"

#include "core.h"

#include "xc.h"
#include "tasks.h"

void unitTest(void)
{
    char str[30];
    char str2[30];
       
    driveM1(0.05);   
    driveM2(0.05);
    
    //sprintf(str, "BTN %d\n", BTN);    
    //sprintf(str, "POS1CNT %d\n", POS1CNT);
    //sprintf(str, "P1 %d\n", POS1CNT);
    //sprintf(str2, "P2 %d\n", POS2CNT);
        
    //uartWrite(str);
    //uartWrite(str2);
    
    if (BTN == 1)
    {          
        LED_W = LEDON;

    }

}
