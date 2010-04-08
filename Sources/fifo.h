#ifndef FIFO_1_FILE_HEADER_V_1_0
#define FIFO_1_FILE_HEADER_V_1_0       

#define ENABLE_INT_TX() 	SCC2_SCTIE = 1
#define DISABLE_INT_TX() 	SCC2_SCTIE = 0
#define ENABLE_INT_RX() 	SCC2_SCRIE = 1
#define DISABLE_INT_RX() 	SCC2_SCRIE = 0    

void Fifo_Rx_Init(void);
byte Fifo_Rx_Put(byte);
byte Fifo_Rx_Get(byte *);

void Fifo_Tx_Init(void);
byte Fifo_Tx_Put(byte);
byte Fifo_Tx_Get(byte *);
        

#endif