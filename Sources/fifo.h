#ifndef FIFO_1_FILE_HEADER_V_1_0
#define FIFO_1_FILE_HEADER_V_1_0       

#define ENABLE_INT_TX() 	SCC2_SCTIE = 1
#define DISABLE_INT_TX() 	SCC2_SCTIE = 0
#define ENABLE_INT_RX() 	SCC2_SCRIE = 1
#define DISABLE_INT_RX() 	SCC2_SCRIE = 0  

void Fifo_Init(void);
byte Fifo_Put(byte);
byte Fifo_Get(byte *);
        

#endif