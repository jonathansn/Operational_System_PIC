/**
 * MACOS - Malte, Água, Cevada Operating system
 * by ARA7562 - turma 2017/1
 * File: main.c
 */

#include "kernel.h"
#include "queue.h"
#include "tasks.h"
#include <xc.h>

#define _XTAL_FREQ 4000000

int main(void)
{
    macos_start();

    // Criar/instalar as tarefas no sistema
    macos_create_task(1, 100, tarefa_um);
    macos_create_task(2, 100, tarefa_dois);
    macos_create_task(3, 100, tarefa_tres);

    T0CONbits.TMR0ON = ON;
    
    //TMR0 = 64911; // 1 ms
    TMR0 = 59286;   // 10 ms
    //TMR0 = 3036;    // 100 ms
    
    // Inicializa o kernel do SO
    while(1);
    return 0;
}
