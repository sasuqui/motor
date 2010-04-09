#ifndef MOTOR_SERIAL
#define MOTOR_SERIAL

#include "derivative.h"

// Definiciones generales

#define MOTOR_ID 0xF0    //valores que no estaran en las tramas para los variadores

//ASCII Codes
#define  NULL          0
#define  LF            10
#define  SP            32
#define  CR            13
#define  AT            64   //@
#define  QUESTION      63   //?
#define  ANSWER        62   //>

#define  READBIT       65   //A
#define  WRITEBIT      66   //B
#define  READMOT       67   //C
#define  WRITEMOT      68   //D
#define  MIRROR        77   //M

#define  CLEAR_SCREEN  12

#define  IDLE     1
#define  SELECTED 2
#define  RX       4
#define  TX       8


#define rxFlag  _events.BITS.bit0
#define txFlag  _events.BITS.bit1
#define timerOF _events.BITS.bit2

#define status _status.BYTE
#define events _events.BYTE


/* Variables de uso en el main*/
extern unsigned char* config;
extern unsigned char* question[17];


// Prototipos de funciones


void SCI_Init(void);
void BorrarPantalla(void);
void RecibirDato(void);
void sendMessage(byte *message);
void sendChar(byte character);

/*void ReadBit(byte bit);
void ReadWord(byte wordNum);
void WriteBit(byte bit,byte value);
void WriteWord(byte bit,byte value);
*/

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

flagByte _events,_status; 


#endif