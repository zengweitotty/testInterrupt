interrupt.bin : Start.o init.o interrupt_isr.o main.o
	arm-linux-ld -Tnand.lds -o interrupt_elf $^
	arm-linux-objcopy -O binary -S interrupt_elf $@
%.o : %.c
	arm-linux-gcc -nostdlib -c -o $@ $<
%.o : %.s
	arm-linux-gcc -nostdlib -c -o $@ $^
clean:
	rm -f *.o *.dis *_elf *.bin
