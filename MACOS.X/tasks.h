/**
 * MACOS - Malte, Água, Cevada Operating system
 * by ARA7562 - turma 2017/1
 * File: tasks.h
 */

#ifndef TASKS_H
#define	TASKS_H

#include "types.h"

u_int shared_memory[11];
u_int *ptr_shared_memory;
u_int *ptr_speed;

TASK tarefa_um();
TASK tarefa_dois();
TASK tarefa_tres();

#endif	/* TASKS_H */

