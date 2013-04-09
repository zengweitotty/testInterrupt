/*
    File Name:      init.c
	Author:         zengweitotty
	Version:        V1.0
	Data:           2013/04/07
	Email:          zengweitotty@gmail.com
	Description     Initialize TQ2440 hardware 
*/
#define WTCON	(*(volatile unsigned long *)0x53000000)
/*LED related register*/
#define GPBCON  (*(volatile unsigned long *)0x56000010) //used virtual address
#define GPBDAT  (*(volatile unsigned long *)0x56000014)
#define GPBUP   (*(volatile unsigned long *)0x56000018)

/*Key related register*/
#define GPFCON  (*(volatile unsigned long *)0x56000050)
#define GPFDAT  (*(volatile unsigned long *)0x56000054)
#define GPFUP   (*(volatile unsigned long *)0x56000058)
#define EXTINT0	(*(volatile unsigned long *)0x56000088)
/*Interrupt controller related register*/
#define INTMSK	(*(volatile unsigned long *)0x4A000008)
#define PRIORITY	(*(volatile unsigned long *)0x4A00000C)
#define EINTMASK	(*(volatile unsigned long *)0x560000A4)
void disable_watchdog(void){
	WTCON = (unsigned long)0x00;
}
void ledinit(void){
	/*setup GPB5 GPB6 GPB7 GPB8 as output*/
	GPBCON &= ~(0x11 << 10 |
	            0x11 << 12 |
	            0x11 << 14 |
	            0x11 << 16
	            );
	GPBCON |= (0x01 << 10 |
	           0x01 << 12 |
	           0x01 << 14 |
	           0x01 << 16
	            );
}
void irqinit(void){
	/*setup GPF0,GPF1,GPF2,GPF4*/
	GPFCON = (0x02 << 0 |
	          0x02 << 2 |
	          0x02 << 4 |
	          0x02 << 8
	          );
	GPFUP &= ~(0x1 << 0 |
	           0x1 << 1 |
	           0x1 << 2 |
	           0x1 << 4
	          );
	EXTINT0 = (0x03 << 0 |
			   0x03 << 4 |
			   0x03 << 8 |
			   0x03 << 12 |
			   0x03 << 16 |
			   0x03 << 20 |
			   0x03 << 24 |
			   0x03 << 28
			   );
	/*Enable EINT0 EINT1 EINT2 EINT4*/
	INTMSK = ~(0x1 << 0 |
			   0x1 << 1 |
			   0x1 << 2 |
			   0x1 << 4
			   );
	/*default priority*/
	PRIORITY = 0x7f;
	/*Enable EINT4*/
	EINTMASK = ~(0x1 << 4);
}

