/**
 * MACOS - Malte, �gua, Cevada Operating system
 * by ARA7562 - turma 2017/1
 * File: macos_config.h
 */

#ifndef MACOS_CONFIG_H
#define	MACOS_CONFIG_H

#include "types.h"

#pragma config WDT = OFF                                                        // Desabilita Watch Dog Timer 
#pragma config OSC = HS   

// N�mero m�ximo de tarefas instaladas no SO
#define MAX_INSTALLED_TASKS 4
// Num�ro m�ximo de mensagens na fila de mensagens
#define MAX_QUEUE_SIZE 10
// Quantum do escalonador Round Robin (em ms)
#define QUANTUM 10
// Defini��o do escalonador de processos
// Round Robin - default ativo
#define RR_SCHED ON
// Prioridades - default desativado
#define PRIOR_SCHED OFF

#endif	/* MACOS_CONFIG_H */

