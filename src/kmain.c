// #include <kernel/printf.h>
// #include <kernel/mm.h>
// #include <arch/timer.h>
// #include <kernel/trap.h>
// #include <kernel/serial.h>

// extern int _hartid[];
// void kmain()
// {
// 	printk_set_level(LOG_DEBUG);
// 	info("entered S-mode\n");
// 	info("booting on hart %d\n", _hartid[0]);
// 	info("setting up virtual memory...\n");
// 	vm_init();

// 	info("enabling traps...\n");
// 	trap_setup();
// 	info("enabling timer...\n");
// 	timer_irq_enable();
// 	info("enabling serial...\n");
// 	serial_init();
// 	serial_irq_enable();

// 	/* implement your shell here */
// }

#include <kernel/printf.h>
#include <kernel/mm.h>
#include <arch/timer.h>
#include <kernel/trap.h>
#include <kernel/serial.h>

extern int _hartid[];
void kmain()
{
    printk_set_level(LOG_DEBUG);
    info("entered S-mode\n");
    info("booting on hart %d\n", _hartid[0]);
    info("setting up virtual memory...\n");
    vm_init();

    info("enabling traps...\n");
    trap_setup();
    info("enabling timer...\n");
    timer_irq_enable();
    
    // --- ALTERAÇÃO: Comentado temporariamente para evitar Kernel Panic ---
    // info("enabling serial...\n");
    // serial_init();
    // serial_irq_enable();
    // ------------------------------------------------------------------

    // --- ALTERAÇÃO: Teste do Timer (Objetivos 1 e 2) ---
    
    // 1. Ligar as interrupções globais da CPU (essencial para o timer disparar)
    hart_irq_enable();

    /* implement your shell here */
    
    // 2. Configurar o alarme para 2 segundos no futuro
    info("Configurado alarme para 2 segundos. Aguardando...\n");
    timer_set_alarm(2);

    // 3. Loop infinito para manter a CPU ativa esperando o tempo passar
    while(1) {
        // CPU presa aqui até a interrupção do timer acontecer
    }
    // ------------------------------------------------------------------
}