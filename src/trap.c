#include <kernel/trap.h>
#include <kernel/panic.h>

#include <arch/csr.h>
#include <kernel/printf.h>
#include <arch/timer.h>

/* defined in src/trap_entry.S */
extern void trap_entry();

void handle_irq()
{
	/* not implemented */
	BUG();
}

void handle_exception()
{
	/* not implemented */
	BUG();
}

void trap_setup()
{
	// escreve o endereco do trap_entry.s no stvec
	// indica a cpu para pular para ca quando ocorrer um trap
	csr_write(CSR_STVEC, trap_entry);
}

void handle_trap()
{
	// stvec: VA of trap handler (function CPU will jump to when an exception happens)
	u64 cause = csr_read(CSR_SCAUSE);
	u64 tval = csr_read(CSR_STVAL);

	// look at bit 63 in scause: exception or interrupt
	u64 is_interrupt = cause >> 63;

	// read the exception code in scause (bits 0-62)
	u64 exception_code = cause & 0x7FFFFFFFFFFFFFFF;

	if(!is_interrupt){
		// read the value in stval in case of an access/page fault
		// 1: Instruction access fault, 5: Load access fault, 7: Store/AMO access fault
		// 12: Instruction page fault, 13: Load page fault, 15: Store/AMO page fault
		if (exception_code == 1 || exception_code == 5 || exception_code == 7 ||
            exception_code == 12 || exception_code == 13 || exception_code == 15) {

			// for debugging: pretty-print info about page faults
			error("--- PAGE / ACCESS FAULT ---\n");
			error("Exception Code: %lu\n", exception_code);
			error("stval: 0x%lx\n", tval);
			error("---------------------------\n");
		}
		else{
			error("Exception! Code: %lu, stval: 0x%lx\n", exception_code, tval);
		}
	}
	else{
		if (exception_code == 5){
			// timer interrupt
			timer_irq();			
		}
		// timer and serial interrupts
	}
}

void hart_irq_enable()
{
	csr_set(CSR_SSTATUS, CSR_SSTATUS_SIE);
}

u64 hart_irq_save()
{
	return csr_read_clear(CSR_SSTATUS, CSR_SSTATUS_SIE);
}

void hart_irq_restore(u64 flags)
{
	// flags: history (previous) from function hart_irq_save

	// restore sie bit if previously set
	if(flags & CSR_SSTATUS_SIE){
		csr_set(CSR_SSTATUS, CSR_SSTATUS_SIE);
	}
	
}

void hart_irq_disable()
{
	csr_clear(CSR_SSTATUS, CSR_SSTATUS_SIE);
}
