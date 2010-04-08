#include "derivative.h" /* include peripheral declarations */
#include "timer.h"
#include "serial.h"


// TIMER initialization
void TimerInit(void)
{
  
  T1SC_TRST = 1;      //resets and stops the timer counter
  
  T1SC_TOIE = 1;      //enable timer overflow interrupts
  
  T1MODH = (TIMERMOD >> 8) & 0xFF;
  T1MODL = (TIMERMOD) & 0xFF;
  
  T1SC_PS = PRESCALER;
  
}


//Timer Overflow Interrupt Subroutine
void interrupt VectorNumber_TIM1Ovr TIM1OV_ISR(void){
  
  (void)T1SC;         //clear interrupt
  T1SC_TOF=0;            
  
  timerOF=1;
  T1SC_TRST = 1;      //resets and stops the timer counter
   
}


