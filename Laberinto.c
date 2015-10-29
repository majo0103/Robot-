/*
  Blank Simple Project.c
  http://learn.parallax.com/propeller-c-tutorials 
*/
#include <stdio.h>
#include "simpletools.h"                      // Include simple tools
#include "abdrive.h"                          // Include abdrive header
#include "ping.h"   
#define size 100
struct Stack {
   int s[size];
   int top;
};

void push(struct Stack *st,int item) {
   st->top=st -> top + 1;
   printf("\nprueba 1 %d",item);
   st->s[st->top] = item;
}
 


@Variables por referencia para stack
int pop(struct Stack *st) {
   int item;
   item = st->s[st->top];
   st->top=st->top-1;
   printf("\nprueba 2 %d",item);
   return item;
}
 


int paso;
int sensor;
int enfrente;
int derecha;
int izquierda;
int num;
int i;
int pasosalir;
struct Stack stack_1;
struct Stack stack_2;
int main()                                    // Main function
{
  stack_1.top=-1;
  stack_2.top=-1;
  i = 0;
  while (i < 100){
   stack_1.s[i]=0;
   stack_2.s[i]=0;
   i = i+1; 
  }    
  enfrente = 0;
  derecha = 0;
  izquierda = 0;
  paso = 10;
  num = 0;
  pasosalir = 12;
  while(1)
  {
    sensor=ping_cm(8); 
    if(sensor>15){
      enfrente = 1;
    }    
    else enfrente = 0;
    drive_goto(-25,26);
    sensor=ping_cm(8);
    if(sensor>15){
      izquierda = 1; 
    }            
    else izquierda = 0;
    
    drive_goto(51,-50);
    sensor=ping_cm(8);
    if(sensor>15){
      derecha = 1; 
    }            
    else derecha = 0;
    drive_goto(-25,26);
    
    //Parte de procesamiento de la informacion
    if((enfrente == 1)&&(derecha==0)&&(izquierda==0)){
      push(&stack_1,1);
      drive_goto(paso,paso);
    } 
    if((enfrente == 0)&&(derecha == 1)&&(izquierda==0)){
      push(&stack_1,3);
      push(&stack_1,1);
      drive_goto(pasosalir,pasosalir);
      drive_goto(26,-25);
      drive_goto(41,41);
    }
    if((enfrente == 0)&&(derecha == 0)&&(izquierda == 1)){
      push(&stack_1,2);
      push(&stack_1,1);
      drive_goto(pasosalir,pasosalir);
      drive_goto(-25,26);
      drive_goto(41,41);
    }     
    if((enfrente == 1)&&(derecha==1)&&(izquierda==0)){
      push(&stack_2,3);
      push(&stack_1,5);
      push(&stack_1,1);
      drive_goto(paso,paso);
    }
    if((enfrente == 1)&&(derecha==0)&&(izquierda==1)){
      push(&stack_2,1);
      push(&stack_1,5);
      push(&stack_1,1);
      drive_goto(paso,paso);
    }
    if((enfrente == 0)&&(derecha==1)&&(izquierda==1)){
      push(&stack_2,1);
      push(&stack_1,5);
      push(&stack_1,3);
      push(&stack_1,1);
      drive_goto(pasosalir,pasosalir);
      drive_goto(26,-25);
      drive_goto(38,38);
    }
    if((enfrente == 0)&&(derecha == 0)&&(izquierda == 0)){
      num = pop(&stack_1);
      while (num != 5){
         if(num == 1){
          drive_goto(-paso,-paso);  
         }           
         if(num == 2){
          drive_goto(-38,-38);
          drive_goto(26,-25);
          drive_goto(-pasosalir,-pasosalir); 
         }           
         if(num == 3){
          drive_goto(-38,-38);
          drive_goto(-25,26);
          drive_goto(-pasosalir,-pasosalir);
         }
         num = pop(&stack_1);           
      } 
      num = pop(&stack_2);  
      if(num == 1){
        drive_goto(pasosalir,pasosalir);
        drive_goto(-25,26);
        drive_goto(38,38);
      }
      if(num == 2){
        drive_goto(38,38);
      } 
      if(num == 3){
        drive_goto(pasosalir,pasosalir);
        drive_goto(26,-25);
        drive_goto(38,38);            
      }
    }               
  }
}
