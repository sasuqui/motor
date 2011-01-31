#ifndef MOTOR_SERIAL
#define MOTOR_SERIAL

#include "derivative.h"

// Definiciones generales

#define ENABLE_INT_TX() 	SCC2_SCTIE = 1
#define DISABLE_INT_TX() 	SCC2_SCTIE = 0
#define ENABLE_INT_RX() 	SCC2_SCRIE = 1
#define DISABLE_INT_RX() 	SCC2_SCRIE = 0  

//ID de los motores,valores que no estaran en las tramas para los variadores 0x21 - 0x23 (!"#)
#define MOTOR_ID 0x21 //motor 1
//#define MOTOR_ID 0x22 //motor 2
//#define MOTOR_ID 0x23 //motor 3


//ASCII Codes
#define  NULL          0
#define  LF            10
#define  CR            13
//#define  LF            0x24     //testing value $
//#define  CR            0x25     //testing value %

#define  SP            32
#define  AT            64   //@
#define  QUESTION      63   //?
#define  ANSWER        62   //>

#define  READBIT       65   //A
#define  WRITEBIT      66   //B
#define  READMOT       67   //C
#define  WRITEMOT      68   //D
#define  MIRROR        77   //M

#define  CLEAR_SCREEN  12

#define  IDLE     0x01
#define  SELECTED 0x02
#define  RX       0x04
#define  TX       0x08

#define rxFlag  _events.BITS.bit0
#define txFlag  _events.BITS.bit1
#define timerOF _events.BITS.bit2

#define status _status.BYTE
#define events _events.BYTE


/* Variables de uso en el main*/
extern unsigned char* config;

                                                   
// Prototipos de funciones


void SCI_Init(void);
void RecibirDato(void);
void sendMessage(byte *message);
void sendChar(byte character);



byte* ValueToAscii(int value);
int   AsciiToValue(byte* string);


//  Data types

typedef union{
  
unsigned char BYTE;
struct{

  unsigned char bit0: 1;
  unsigned char bit1: 1;
  unsigned char bit2: 1;
  unsigned char bit3: 1;
  unsigned char bit4: 1;
  unsigned char bit5: 1;
  unsigned char bit6: 1;
  unsigned char bit7: 1;
  
  
}BITS;

}flagByte;

extern flagByte _events, _status; 
extern byte j;

#endif