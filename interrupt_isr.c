/*
    File Name:      interrupt_isr.c
	Author:         zengweitotty
    Version:        V1.0
    Data:           2013/04/08
    Email:          zengweitotty@gmail.com
    Description     interrupt isr
*/
#define EINTPEND	(*(volatile unsigned long *)0x560000A8)
#define EINTMASK	(*(volatile unsigned long *)0x560000A4)
#define SRCPND	(*(volatile unsigned long *)0x4A000000)
#define INTMSK	(*(volatile unsigned long *)0x4A000008)
#define INTPND	(*(volatile unsigned long *)0x4A000010)
#define INTOFFSET	(*(volatile unsigned long *)0x4A000014)
#define GPBDAT  (*(volatile unsigned long *)0x56000014)

void EINT_Handle(void){
	volatile unsigned long temp = GPBDAT;
	int flag = 0;
	/*disable intertupt*/
	EINTMASK = 0xff;
	INTMSK = 0xff;
	switch(INTOFFSET){
	case 0x01:
		if(temp & (0x1 << 8)){	//led_4
			GPBDAT &= ~(0x1 << 8);
		}else{
			GPBDAT |= (0x1 << 8);		
		}
		break;
	case 0x02:
		if(temp & (0x1 << 5)){	//led_1
			GPBDAT &= ~(0x1 << 5);
		}else{
			GPBDAT |= (0x1 << 5);		
		}
		break;
	case 0x04:
		if(temp & (0x1 << 7)){	//led_3
			GPBDAT &= ~(0x1 << 7);
		}else{
			GPBDAT |= (0x1 << 7);		
		}
		break;
	case 0x10:	//EINT4-EINT7
		if(EINTPEND & (0x1 << 4)){
			flag = 1;
			if(temp & (0x1 << 6)){	//led_2
				GPBDAT &= ~(0x1 << 6);
			}else{
				GPBDAT |= (0x1 << 6);		
			}
			break;
		}else{
			break;		
		}
	default:
		break;
	}
	if(flag == 1){	//ENIT4 -- EINT7
		EINTPEND = EINTPEND;
	}
	INTPND = INTPND;
	SRCPND = SRCPND;
	/*Enable EINT0 EINT1 EINT2 EINT4*/
	INTMSK = ~(0x1 << 0 |
	           0x1 << 1 |
	           0x1 << 2|
	           0x1 << 4
	           );
	/*Enable EINT4*/
	EINTMASK = ~(0x1 << 4);

}
