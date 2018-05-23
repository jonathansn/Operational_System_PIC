/*
 * MACOS - Malte, Água, Cevada Operating system
 * by ARA7562 - turma 2017/1
 * File: queue.h
 */

#ifndef QUEUE_H
#define	QUEUE_H

#include "macos_config.h"

typedef void* queue_item;

typedef struct queue {
    queue_item queue_buffer[MAX_QUEUE_SIZE];
    u_int queue_insert_pos;
    u_int queue_remove_pos;
    u_int queue_size;
} t_queue;

void create_queue(t_queue *q);
void write_queue(t_queue *q, queue_item item);
queue_item read_queue(t_queue *q);


#endif	/* QUEUE_H */

