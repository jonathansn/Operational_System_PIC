/**
 * MACOS - Malte, Água, Cevada Operating system
 * by ARA7562 - turma 2017/1
 * File: tasks.c
 */

#include <xc.h>
#include "tasks.h"
#include "kernel.h"
#include <pic18f4520.h>

TASK tarefa_um()
{
    ADCON0 = 0b00000001;            // Select AN0 (channel 0) for Temp sensor, turn on ADC 
    ADCON1 = 0b00001110;            // Select AN0 as ANALOG input, internal voltage 
    ADCON2 = 0b00000100;            // Result Left justified, Manual acquisition time, Fosc/4 
    
    u_int value, currentTemp, previousTemp=0, i=0;
    TRISAbits.RA0 = 1;
    
    while (1) 
    {
            ADCON0bits.GO_NOT_DONE = 1;
            while(ADCON0bits.GO_NOT_DONE == 1);
            value = ADRESH & 0xff;
            currentTemp = ((value/255.0) * 500);            
            
            if(i==10){
                i=0;
            }
            if(i==0){
                shared_memory[i] = currentTemp;
                ptr_shared_memory = &shared_memory[i];                
            }
            if(previousTemp != currentTemp){
                i++;
                shared_memory[i] = currentTemp;
                ptr_shared_memory = &shared_memory[i];
                previousTemp = currentTemp;
            }
            
        asm("nop");
        asm("nop");
        asm("nop");
    }
}

TASK tarefa_dois()
{   
    TRISBbits.RB0 = 0;
    PORTBbits.RB0 = 0;
    TRISBbits.RB1 = 0;
    PORTBbits.RB1 = 0;
    TRISBbits.RB2 = 0;
    PORTBbits.RB2 = 0;
    
    while (1) {
        
        PORTBbits.RB0 = 0;
        PORTBbits.RB1 = 0;
        PORTBbits.RB2 = 0;
        
        while((*ptr_shared_memory > 30) && (*ptr_shared_memory <= 40)){
            PORTBbits.RB0 = 1;
            PORTBbits.RB1 = 0;
            PORTBbits.RB2 = 0;
            shared_memory[11] = 100;
            ptr_speed = & shared_memory[11];
        }
        
        while((*ptr_shared_memory >= 40) && (*ptr_shared_memory <= 50)){
            PORTBbits.RB0 = 0;
            PORTBbits.RB1 = 1;
            PORTBbits.RB2 = 0;
            shared_memory[11] = 50;
            ptr_speed = & shared_memory[11];
        }
        
        while(*ptr_shared_memory >= 50){
            PORTBbits.RB0 = 0;
            PORTBbits.RB1 = 0;
            PORTBbits.RB2 = 1;
            shared_memory[11] = 0;
            ptr_speed = & shared_memory[11];
        }
        
        asm("nop");
        asm("nop");
        asm("nop");
    }
}

TASK tarefa_tres()
{
    TRISCbits.RC2 = 0;
    PORTCbits.RC2 = 0;
    CCP1CONbits.CCP1M = 0x0c;
    
    PR2 = 155;
    T2CONbits.T2CKPS = 0x02;
    T2CONbits.TMR2ON = 1;
    
    while (1) {
        while(*ptr_shared_memory > 30){
            PORTCbits.RC2 = 1;
                CCPR1 = *ptr_speed;
            
        }            
        while(*ptr_shared_memory <= 30){
            PORTCbits.RC2 = 0;
            CCPR1 = 155;
        }
        asm("nop");
        asm("nop");
        asm("nop");
    }
}