SECTIONS{
	first 0x00000000 : AT(0) {Start.o init.o interrupt_isr.o main.o}	
}
