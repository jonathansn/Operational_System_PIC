/**
 * MACOS - Malte, Água, Cevada Operating system
 * by ARA7562 - turma 2017/1
 * File: types.h
 */

#ifndef TYPES_H
#define	TYPES_H

#include "macos_config.h"                                                        // Oscilador de 4 MHz
#include <stdint.h>

#define ON                  1
#define OFF                 0
#define IDLE                0

// Quantidade de itens na pilha de hardware
#define MC_STACK_SIZE       31
// Desabilita as interrupções globais
#define macos_DI() INTCONbits.GIE = 0
// Habilita as interrupções globais
#define macos_EI() INTCONbits.GIE = 1

typedef unsigned char byte;
typedef unsigned u_int;
typedef enum {READY = 0, RUNNING, WAITING, FINISHED} t_state;
typedef void TASK;
typedef void(*task_ptr)(void);
typedef unsigned short long int uint24_t;

// Pilha de execução da tarefa
typedef struct task_queue {
    u_int TOSU_reg;
    u_int TOSH_reg;
    u_int TOSL_reg;
} t_task_queue;

// Contexto da tarefa
typedef struct task_ctx {
    byte WORK_reg;
    byte STAT_reg;
    byte BSR_reg;
    t_task_queue task_stack[MC_STACK_SIZE];
    u_int task_stack_size;
} t_task_ctx;

// Bloco de controle da tarefa
typedef struct tcb {
    u_int task_id;
    t_state task_state;
    u_int task_prior;
    u_int task_prior_count;
    task_ptr func;
    t_task_ctx ctx;
} t_tcb;

// Controle das tarefas em delay
typedef struct task_delay_queue {
    u_int task_pos_ready_queue;
    u_int delay_ms;
} t_task_delay_queue;

#endif	/* TYPES_H */

