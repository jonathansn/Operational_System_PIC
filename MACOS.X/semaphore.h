/*
 * MACOS - Malte, Água, Cevada Operating system
 * by ARA7562 - turma 2017/1
 * File: semaphore.h
 */

#ifndef SEMAPHORE_H
#define	SEMAPHORE_H

#include "types.h"

typedef struct semaphore {
    u_int sem_value;
    u_int sem_queue[MAX_INSTALLED_TASKS];
    u_int sem_queue_size;
    u_int sem_queue_next_pos_to_block;
    u_int sem_next_task_to_unblock;
} t_semaphore;

void sem_create(u_int value, t_semaphore *s);
void sem_wait(t_semaphore *s);
void sem_post(t_semaphore *s);
u_int sem_get_value(t_semaphore s);


#endif	/* SEMAPHORE_H */

