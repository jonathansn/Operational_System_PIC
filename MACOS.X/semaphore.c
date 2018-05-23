/*
 * MACOS - Malte, Água, Cevada Operating system
 * by ARA7562 - turma 2017/1
 * File: semaphore.c
 */

#include "semaphore.h"
#include "types.h"
#include <xc.h>

extern u_int task_running;
extern t_tcb READY_Queue[MAX_INSTALLED_TASKS];

void sem_create(u_int value, t_semaphore *s)
{
  s->sem_value = value;
  s->sem_queue_next_pos_to_block = 0;
  s->sem_next_task_to_unblock = 0;
  s->sem_queue_size = 0;
}

void sem_wait(t_semaphore *s)
{
  // Desabilita as interrupções
  macos_DI();
  
  if (--s->sem_value < 0) {
    // Insere a tarefa na fila de bloqueio do semáforo
    s->sem_queue[s->sem_queue_next_pos_to_block] = task_running;
    s->sem_queue_size++;
    s->sem_queue_next_pos_to_block = (s->sem_queue_next_pos_to_block + 1) % MAX_INSTALLED_TASKS;    
  }
  
  // Chama o despachante
  // Mudar o estado da tarefa que está sendo bloqueada
  READY_Queue[task_running].task_state = WAITING;
  
  
  // Habilita as interrupções
  macos_EI(); 
}

void sem_post(t_semaphore *s)
{
  u_int id_to_unblock;
  
  // Desabilita as interruopções
  macos_DI();
  
  // Testa o semáforo
  if (++s->sem_value <= 0) {
    id_to_unblock = s->sem_queue[s->sem_next_task_to_unblock];    
    // Altera o estado na fila de aptos
    READY_Queue[id_to_unblock].task_state = READY;
    s->sem_next_task_to_unblock = (s->sem_next_task_to_unblock + 1) % (s->sem_queue_next_pos_to_block + s->sem_queue_size);
    s->sem_queue_size--;
  }
  
  // Chama o despachante
  
  
  // Habilita as interrupções
  macos_EI();
}

u_int sem_get_value(t_semaphore s) 
{
  // Retorna o valor do semáforo
  return s.sem_value;
}
