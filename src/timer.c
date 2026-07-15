#include <arch/timer.h>
#include <kernel/panic.h>

#include <arch/csr.h>
#include <kernel/printf.h>

u64 timer_read()
{
	u64 now = csr_read(CSR_TIME);
	return now;
}

void timer_irq_enable()
{
	// enable interrupts for the hart: set to 1 bit sstatus[SIE] = sstatus[1]
	csr_set(CSR_SSTATUS, CSR_SSTATUS_SIE);

	// gate the timer interrupt: set to 1 bit sie[STIE]
	csr_set(CSR_SIE, CSR_SIE_STIE);

	// gate the external interrupts: sie[SEIE] -- enable when setting up the serial device driver
}

void timer_irq_disable()
{
	csr_clear(CSR_SSTATUS, CSR_SSTATUS_SIE);
	csr_clear(CSR_SIE, CSR_SIE_STIE);
}

void timer_set_alarm(u64 secs)
{
	u64 now = timer_read();
	u64 tick_in_secs = now + secs * TIMER_FREQ;
	csr_write(CSR_STIMECMP, tick_in_secs);
}

void timer_irq()
{
	info("--- ALARM ---\n");

	// call disable function to stop triggering alarm
	timer_irq_disable();
}
