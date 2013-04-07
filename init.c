/*
    File Name:      init.c
	Author:         zengweitotty
	Version:        V1.0
	Data:           2013/04/07
	Email:          zengweitotty@gmail.com
	Description     Initialize TQ2440 hardware 
*/
#define WTCON	(*(volatile unsigned long *)0x53000000)
void disable_watchdog(void){
	WTCON = (unsigned long)0x00;
}


