/*
 * MACOS - Malte, Água, Cevada Operating system
 * by ARA7562 - turma 2017/1
 * File: memory.h
 */

#ifndef MEMORY_H
#define	MEMORY_H

unsigned char * SRAMalloc(unsigned char nBytes);
void SRAMfree(unsigned char * pSRAM);
void SRAMInitHeap(void);

#endif	/* MEMORY_H */

