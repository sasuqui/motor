#ifndef MOTOR_TIMER
#define MOTOR_TIMER

#define TIMERMOD      30720     // 50ms
#define PRESCALER     0b010     // 0b010 Internal bus clock ÷ 4

#define StartTimer()  T1SC_TSTOP = 0;   //starts the timer counter

void TimerInit(void);

#endif 