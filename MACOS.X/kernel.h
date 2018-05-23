/**
 * MACOS - Malte, Água, Cevada Operating system
 * by ARA7562 - turma 2017/1
 * File: kernel.h
 */

#ifndef KERNEL_H
#define	KERNEL_H

#include "types.h"

extern u_int task_running;
// Quantidade de tarefas instaladas
extern u_int tasks_installed;
// Quantidade de tarefas inseridas na fila de delay
extern u_int tasks_delay_queue;
// Fila de aptos
extern t_tcb READY_Queue[MAX_INSTALLED_TASKS];
// Fila de tarefas em delay
extern t_task_delay_queue DELAY_Queue[MAX_INSTALLED_TASKS];

 // Chamadas de sistema
 // Rotina de salvar contexto
#define SAVE_CONTEXT()\
do{\
    READY_Queue[task_running].ctx.WORK_reg  = WREG;\
    READY_Queue[task_running].ctx.BSR_reg   = BSR;\
    READY_Queue[task_running].ctx.STAT_reg  = STATUS;\
    do {\
        int pos_queue = READY_Queue[task_running].ctx.task_stack_size;\
        READY_Queue[task_running].ctx.task_stack[pos_queue].TOSU_reg = TOS >> 16;\
        READY_Queue[task_running].ctx.task_stack[pos_queue].TOSH_reg = TOS >> 8;\
        READY_Queue[task_running].ctx.task_stack[pos_queue].TOSL_reg = TOS >> 0;\
        READY_Queue[task_running].ctx.task_stack_size++;\
        asm("POP");\
    } while (STKPTR);\
}while(0)

// Rotina de restaurar contexto
#define RESTORE_CONTEXT()\
do{\
    WREG = READY_Queue[task_running].ctx.WORK_reg;\
    BSR = READY_Queue[task_running].ctx.BSR_reg;\
    STATUS = READY_Queue[task_running].ctx.STAT_reg;\
    STKPTR = 0;\
    do {\
        int pos_queue = --READY_Queue[task_running].ctx.task_stack_size;\
        asm("PUSH");\
        TOSU = READY_Queue[task_running].ctx.task_stack[pos_queue].TOSU_reg;\
        TOSH = READY_Queue[task_running].ctx.task_stack[pos_queue].TOSH_reg;\
        TOSL = READY_Queue[task_running].ctx.task_stack[pos_queue].TOSL_reg;\
    } while (READY_Queue[task_running].ctx.task_stack_size);\
}while(0)
    
// Chamadas de sistema
void macos_delay(u_int ms);
void macos_create_task(u_int id, u_int prior, task_ptr t_ptr);
void macos_start();
void despachante(t_state STATE);
void timer_delay();
void interrupt interrupt_handler();
u_int rr_scheduler();
u_int prior_scheduler();
TASK task_IDLE();

#endif	/* KERNEL_H */

