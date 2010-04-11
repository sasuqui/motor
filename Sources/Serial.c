#include "serial.h"
#include "fifo.h"

extern unsigned char* config="?D18 22\n\r"; //activa la comunicacion serian en el variador
extern unsigned char* question[17]="?D18 22\n\r";


byte  j=0;                 
byte  dato;   

flagByte _events, _status; 

void SCI_Init(void){  //frecuencia reloj de bus 2.4576 MHz
  CONFIG2_SCIBDSRC=1; //usar el bus interno para la comunicacion serial
  SCBR_SCR=2;         //rata de baudios dividida por 4 - 9600bps
  SCC1_PEN=1;          //habilita paridad
  SCC1_PTY=1;         //paridad impar
  SCC1_ENSCI=1;       //habilita transmision serial PTB2 y PTB3
  SCC2_TE=1;          //Habilita Tx
  SCC2_RE=1;          //Habilita Rx
  SCC2_SCRIE=1;       //HABILTA INTERRUPCION POR RECIBIR DATO
  //SCC2_SCTIE=1;       //habilita intrrupcion Tx
  
  status=IDLE;

}


interrupt VectorNumber_SCIReceive void SCI_Rx_Int(void){

  (void)SCS1;        
  dato=SCDR;        //RECONOCE LA INTERRUPCION
  rxFlag=1;
}



interrupt VectorNumber_SCITransmit void SCI_Tx_Int(void){

  (void)SCS1;        //RECONOCE LA INTERRUPCION
  
  //if ((Fifo_Get(&dato)==0)){
  if ((Fifo_Get(&SCDR)==0)){
  
    SCC2_SCTIE = 0;
    txFlag=1; //Tx complete 
  }
  /*else 
  
  SCDR=dato; */
}


void RecibirDato(void){
 
 // sendChar(dato);

  switch (status){
  
    case IDLE:
    
      if(dato==MOTOR_ID){
      
        status=SELECTED;
        
      }
    
      break;
      
    case SELECTED:
             
             
      if(Fifo_Put(dato)){
      
        
        
        if(dato==READMOT){ //SENSE QUESTION
          
          //queue enable variator response bit and timer at rx complete
          j=1;
          status=RX;
          
        }else if(dato==CR){
        
          status=IDLE;
          ENABLE_INT_TX();
        }
        
        
        
      }else{
      
        Fifo_Init();
        status=IDLE;
      
        
      }
    
      break;
      
    case RX:
    
        //FEED FIFO
        if(Fifo_Put(dato)){ 
          
          if(dato==CR){
          
            status=IDLE;
            ENABLE_INT_TX();

          }
        
        
        }else{
        
          Fifo_Init();
          status=IDLE;
        
        }
        

      break;

    default:
      break;
  }

 
}


/*** DEPRECATED FUNTIONS ***/

void sendChar(byte character){
  
  while(SCS1_SCTE==0);  //wait until the transmitter register is empty
  SCDR=character;
  
}

void sendMessage(byte *message){

  while(*message){
    sendChar(*message);
    message++;
  }
 
}

/*void ReadBit(byte bit){

}
void ReadWord(byte wordNum) {
  
}
void WriteBit(byte bit,byte value)  {
  
}
void WriteWord(byte bit,byte value){
}

byte* ValueToAscii(int value){
  
}
int   AsciiToValue(byte* string) {
  
}    */
