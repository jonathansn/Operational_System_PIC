/*
 * MACOS - Malte, Água, Cevada Operating system
 * by ARA7562 - turma 2017/1
 * File: kernel.c
 */

#include "kernel.h"
#include <pic18f4520.h>

#define _XTAL_FREQ 4000000

// Variáveis globais
// Tarefa que está executando
u_int task_running = 0;
// Quantidade de tarefas instaladas
u_int tasks_installed = 0;
// Quantidade de tarefas inseridas na fila de delay
u_int tasks_delay_queue = 0;
// Fila de aptos
t_tcb READY_Queue[MAX_INSTALLED_TASKS];
// Fila de tarefas em delay
t_task_delay_queue DELAY_Queue[MAX_INSTALLED_TASKS];


// Delay
void macos_delay(u_int ms)
{
    macos_DI();
    
    // Insere a tarefa na fila de delay
    DELAY_Queue[tasks_delay_queue].task_pos_ready_queue = task_running;
    DELAY_Queue[tasks_delay_queue].delay_ms = ms;

    // Incrementa a variável de controle de tarefas em delay
    tasks_delay_queue++;

    // Chama o despachante
    despachante(WAITING);
    
    macos_EI();
}

// Criação de tarefas
void macos_create_task(u_int id, u_int prior, task_ptr t_ptr)
{
    // Dados da tarefa
    READY_Queue[tasks_installed].task_id = id;
    READY_Queue[tasks_installed].task_state = READY;
    READY_Queue[tasks_installed].task_prior = prior;
    READY_Queue[tasks_installed].task_prior_count = prior;
    READY_Queue[tasks_installed].func = t_ptr;
    READY_Queue[tasks_installed].ctx.task_stack[0].TOSU_reg = (uint32_t)t_ptr >> 16;
    READY_Queue[tasks_installed].ctx.task_stack[0].TOSH_reg = (uint32_t)t_ptr >> 8;
    READY_Queue[tasks_installed].ctx.task_stack[0].TOSL_reg = (uint32_t)t_ptr >> 0;
    READY_Queue[tasks_installed].ctx.task_stack_size = 1;

    // Incrementa o número de tarefas instaladas no SO
    tasks_installed++;
}

void macos_start()
{
    asm("GLOBAL _tarefa_um, _tarefa_dois,_tarefa_tres, _task_IDLE");
    macos_create_task(0, 0, task_IDLE);
  
    //configura timer
    T0CONbits.T0CS      = 0;
    T0CONbits.T08BIT    = OFF;                                                  // 16 Bits
    T0CONbits.PSA       = 0;
    T0CONbits.T0PS      = 0b010;                                                // 1:8
    INTCONbits.TMR0IE   = ON;
    INTCONbits.TMR0IF   = OFF;
    INTCONbits.PEIE     = ON;
    macos_EI();

}

u_int rr_scheduler()
{
    /*
    u_int next_task = IDLE;

    do {
        next_task = (task_running + 1) % tasks_installed;
    } while(READY_Queue[next_task].task_state != READY);

    // Retorna o endereço da tarefa que irá executar
    return next_task;
    */
    
    u_int i = task_running, next_task = 0; 
    
    do{
        i++;
        next_task = i % (tasks_installed);
    }while(READY_Queue[next_task].task_state != READY);
    
    return next_task;

}

u_int prior_scheduler()
{
    u_int next_task = IDLE, i;

    // Procurar pela tarefa de maior prioridade
    for (i = 1; i < tasks_installed; i++)
        if (READY_Queue[i].task_prior > READY_Queue[next_task].task_prior)
            if(READY_Queue[i].task_state == READY)
                next_task = i;
    
    --READY_Queue[next_task].task_prior;
    if(READY_Queue[1].task_prior == 0 && READY_Queue[2].task_prior == 0 && READY_Queue[3].task_prior == 0)
        for(u_int i = 1; i < tasks_installed; i++)
            READY_Queue[i].task_prior = READY_Queue[i].task_prior_count;
    // Retorna o endereço (posição na fila de aptos) da tarefa de maior prioridade
    return next_task;
}

// Rotina de tratamento das tarefas bloqueadas por tempo
void timer_delay()
{
    macos_DI();
  
    int i, size = tasks_delay_queue;
    for (i = 0; i < size; i++) {
        if (--DELAY_Queue[i].delay_ms <= 0) {
            READY_Queue[DELAY_Queue[i].task_pos_ready_queue].task_state = READY;
            tasks_delay_queue--;
        }    
    }
    macos_EI();
}

// Tarefa IDLE
TASK task_IDLE()
{
    asm("nop");
    asm("nop");
    asm("nop");
}

void despachante(t_state STATE)
{
    macos_DI();
    SAVE_CONTEXT();
    
    READY_Queue[task_running].task_state = STATE;
    
    #if RR_SCHED 
        task_running = rr_scheduler();
    #else
        task_running = prior_scheduler();
    #endif
    
    READY_Queue[task_running].task_state = RUNNING;
    
    RESTORE_CONTEXT();
    macos_EI();
}

void interrupt interrupt_handler()
{
    if(INTCONbits.T0IE && INTCONbits.T0IF)
    {
        INTCONbits.TMR0IF = OFF;
        //TMR0 = 64911; // 1 ms
        TMR0 = 59286;   // 10 ms
        //TMR0 = 3036;    // 100 ms
        despachante(READY);
    }
}
