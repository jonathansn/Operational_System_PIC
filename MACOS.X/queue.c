/*
 * MACOS - Malte, Água, Cevada Operating system
 * by ARA7562 - turma 2017/1
 * File: queue.c
 */

#include "queue.h"

void create_queue(t_queue *q)
{
  q->queue_insert_pos = 0;
  q->queue_remove_pos = 0;
  q->queue_size = 0;
}

void write_queue(t_queue *q, queue_item item)
{
  q->queue_buffer[q->queue_insert_pos] = item;
  q->queue_insert_pos = (q->queue_insert_pos + 1) % MAX_QUEUE_SIZE;
  q->queue_size++;
}

queue_item read_queue(t_queue *q)
{
  queue_item item = q->queue_buffer[q->queue_remove_pos];
  q->queue_remove_pos = (q->queue_remove_pos + 1) % (q->queue_insert_pos + q->queue_size);
  
  return item;
}
