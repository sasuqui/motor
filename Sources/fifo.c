#include "derivative.h" /* include peripheral declarations */
#include "fifo.h"


// Size of the FIFOs
#define FIFO_SIZE 20

// FIFO and leaders
volatile byte Fifo[FIFO_SIZE];
volatile byte * GetPtr;
volatile byte * PutPtr;


// Boot FIFO
void Fifo_Init ()
{
	GetPtr = &Fifo[0];
	PutPtr = &Fifo[0];
}

// Function to put data in FIFO
byte Fifo_Put (byte c)
{
	// To verify if PUT will not reach to GET and if it did not fill totally
	if ( ( (PutPtr + 1) == GetPtr) || ( (PutPtr - GetPtr) == (FIFO_SIZE - 1)) )
//	if ( ( (PutPtr + 1) == GetPtr) || ( (PutPtr == &Fifo[FIFO_SIZE - 1]) && (GetPtr == &Fifo[0]) ) )
		return(0);
	else
	{
		*PutPtr = c;		// To save data in the tail
		
		// To update the pointer, watching if one is due to go at the outset
		if( PutPtr == &Fifo[FIFO_SIZE - 1] )
			PutPtr = &Fifo[0];
		else
			PutPtr++;
		
		ENABLE_INT_TX();    // Enable Interruptions of the TX
		
		return(1);	
	}
}

// Function to take data from FIFO
byte Fifo_Get (byte * DataPtr)	
{
	if ( PutPtr == GetPtr ) //Verify to erificar if the tail is empty
		return(0);
	else 
	{
		*DataPtr = *GetPtr; 
		
	    // To update Pointer
		if( GetPtr == &Fifo[FIFO_SIZE - 1] )
			GetPtr = &Fifo[0];
		else
			GetPtr++;
		
		return(1);
	}
}	