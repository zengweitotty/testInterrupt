@***********************************
@File: Start.s
@Description: first boot section
@***********************************
.text 
.global _start
_start:
	b reset	@0x00 reset
HandleUndef:
	b HandleUndef	@0x04 undef abort
HandleSWI:
	b HandleSWI	@0x08 SWI 
HandlePrefetchAbort:
	b HandlePrefetchAbort	@0x0c fetch abort
HandleDataAbort:
	b HandleDataAbort	@0x10	data abort
HandleNotUsed:
	b HandleNotUsed	@0x14 reserved
	b HandleIRQ	@0x18 interrupt mode
HandleFIQ:
	b HandleFIQ	@0x1c fast interrupt mode
reset:
	ldr sp,=4096
	bl disable_watchdog
	msr cpsr_c,#0xd2 @enter interrupt mode
	ldr sp,=3072	@settup sp pointer
	msr cpsr_c,#0xdf	@enter sys mode
	ldr sp,=4096	@setup sp pointer
	bl ledinit
	bl irqinit
	msr cpsr_c,#0x5f	@open global Interrupt
	bl main
halt_loop:
	b halt_loop
HandleIRQ:
	sub lr,lr,#4	@interrupt mode lr = lr -4
	stmdb sp!,{r0-r12,lr}
	ldr lr,=INTReturn	@specify return address
	ldr pc,=EINT_Handle
INTReturn:
	ldmia sp!,{r0-r12,pc}^	



