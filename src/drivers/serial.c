#include <kernel/serial.h>
#include <kernel/panic.h>

#include <arch/plic.h>
#include <arch/csr.h>

void serial_init()
{	
	// enable appropriate interrupts in the Interrupt Enable Register (IER)
	volatile char * ier_address = (volatile char *)(SERIAL_BASE + SERIAL_IER);
	*ier_address = SERIAL_IER_ERBFI;

	// Enable FIFOs in the Fifo Control Register (FCR)
	volatile char * fcr_address = (volatile char *)(SERIAL_BASE + SERIAL_FCR);
	*fcr_address = SERIAL_FCR_FIFO_ENABLE;
}

// receive/send bytes to the serial port by reading/writing from the
// Receiver Buffer Register at SERIAL_BASE

void serial_irq_enable()
{
	// configure PLIC

	// claim the interrupt
	plic_irq_set_priority(IRQ_SERIAL, 1);
    plic_hart_set_threshold(0, 0);
    plic_hart_enable_irq(0, IRQ_SERIAL);

	// CPU to interruptions
	csr_set(CSR_SIE, CSR_SIE_SEIE);
}

void serial_irq_disable()
{
	/* not implemented */
	BUG();
}

void serial_irq()
{
	/* not implemented */
	BUG();
}

size_t serial_read(char *buf)
{
	/* not implemented */
	BUG();
}

void serial_puts(char *str)
{
	/* not implemented */
	BUG();
}

void serial_putc(char c)
{
	/* not implemented */
	BUG();
}
