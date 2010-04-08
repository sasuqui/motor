#include "derivative.h" /* include peripheral declarations */
#include "fifo.h"


// Size of the FIFOs
#define FIFO_SIZE_RX 20 
#define FIFO_SIZE_TX 20


// FIFO and leaders for Rx

volatile byte Fifo_Rx[FIFO_SIZE_RX];
volatile byte * GetPtr_Rx;
volatile byte * PutPtr_Rx;

// FIFO and leaders for Tx
volatile byte Fifo_Tx[FIFO_SIZE_TX];
volatile byte * GetPtr_Tx;
volatile byte * PutPtr_Tx;

// Boot FIFO of Rx
void Fifo_Rx_Init (void)
{
	GetPtr_Rx = &Fifo_Rx[0];
	PutPtr_Rx = &Fifo_Rx[0];
}

// Function to put data in FIFO of Rx
byte Fifo_Rx_Put (byte c)
{
	// To verify if PUT will not reach to GET and if it did not fill totally
	if ( ( (PutPtr_Rx + 1) == GetPtr_Rx) || ( (PutPtr_Rx - GetPtr_Rx) == (FIFO_SIZE_RX - 1) ) )

		return(0); // Fifo full
	else
	{
		*PutPtr_Rx = c;		// Save data in the tail
		
		// To update the pointer, watching if one is due to go at the outset
		if( PutPtr_Rx == &Fifo_Rx[FIFO_SIZE_RX - 1] )
			PutPtr_Rx = &Fifo_Rx[0];
		else
			PutPtr_Rx++;
		
		return(1);	
	}
}

// Function to take data from FIFO of Rx
byte Fifo_Rx_Get (byte * DataPtr)	
{
	if ( PutPtr_Rx == GetPtr_Rx ) //To verify if the tail is empty
		return(0); // Fifo empty
	else 
	{
		*DataPtr =  *GetPtr_Rx; 
		
	  // To update Pointer
		if( GetPtr_Rx == &Fifo_Rx[FIFO_SIZE_RX - 1] )
			GetPtr_Rx = &Fifo_Rx[0];
		else
			GetPtr_Rx++;
		
		return(1);
	}
}		

// Boot FIFO of Tx
void Fifo_Tx_Init ()
{
	GetPtr_Tx = &Fifo_Tx[0];
	PutPtr_Tx = &Fifo_Tx[0];
}

// Function to put data in FIFO of Tx
byte Fifo_Tx_Put (byte c)
{
	// To verify if PUT will not reach to GET and if it did not fill totally
	if ( ( (PutPtr_Tx + 1) == GetPtr_Tx) || ( (PutPtr_Tx - GetPtr_Tx) == (FIFO_SIZE_TX - 1)) )
//	if ( ( (PutPtr_Tx + 1) == GetPtr_Tx) || ( (PutPtr_Tx == &Fifo_Tx[FIFO_SIZE_TX - 1]) && (GetPtr_Tx == &Fifo_Tx[0]) ) )
		return(0);
	else
	{
		*PutPtr_Tx = c;		// To save data in the tail
		
		// To update the pointer, watching if one is due to go at the outset
		if( PutPtr_Tx == &Fifo_Tx[FIFO_SIZE_TX - 1] )
			PutPtr_Tx = &Fifo_Tx[0];
		else
			PutPtr_Tx++;
		
		ENABLE_INT_TX();    // Enable Interruptions of the TX
		
		return(1);	
	}
}

// Function to take data from FIFO of Tx
byte Fifo_Tx_Get (byte * DataPtr)	
{
	if ( PutPtr_Tx == GetPtr_Tx ) //Verify to erificar if the tail is empty
		return(0);
	else 
	{
		*DataPtr = *GetPtr_Tx; 
		
	    // To update Pointer
		if( GetPtr_Tx == &Fifo_Tx[FIFO_SIZE_TX - 1] )
			GetPtr_Tx = &Fifo_Tx[0];
		else
			GetPtr_Tx++;
		
		return(1);
	}
}	