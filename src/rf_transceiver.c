// This file defines the interface between the RF transmitter and the communication module

#include "includes/spi.h"
#include "includes/transmitter.h"
#include "includes/receiver.h"
#include "data_structures.h"
#include "rf_transceiver_interface.h"

// Function to initialize the RF transceiver as a transmitter
void rf_transmitter_init()
{	
	//Initialise RFM12B module to its transmitter mode.
	txInit();
}

// Function to initialize the RF transceiver as a receiver
void rf_receiver_init()
{
	//Initialise RFM12B module to its receiver mode.
	rxInit();	
}

// Function to send a data packet to the RF transmmitter using SPI
void send_rf_packet(rf_data_packet_t* rf_data_packet)
{
	//Loop variable.
	int i;
	
	//Read status register. Needed before we can start transmitting.
	writeCommand(0x0000);				
		
	//PREAMBLE. Not strictly required.
	sendByte(0xAA); 					
	sendByte(0xAA);
	sendByte(0xAA);
	
	//SYNC. Synchronises transmitter and receiver. 
	//These bytes are not picked up by 'receiveByte()' in the receiver.
	sendByte(0x2D); 					
	sendByte(0xD4);
	
	//DATA. Send the actual data packet.
	for(i=0; i<4; i++) 
	{
		sendByte(rf_data_packet->roll.bytes[i]);		//Send roll.
	}
	
	for(i=0; i<4; i++) 
	{
		sendByte(rf_data_packet->pitch.bytes[i]);		//Send pitch.
	}
	
	for(i=0; i<4; i++) 
	{
		sendByte(rf_data_packet->yaw_vel.bytes[i]);		//Send yaw velocity.
	}
	
	//DUMMY BYTES. Again, not required.
	sendByte(0xAA); 			
	sendByte(0xAA);
	sendByte(0xAA);	
}

// Declare a function to receive a data packet from the RF receiver using SPI
void receive_rf_packet(rf_data_packet_t* rf_data_packet)
{
	//Loop variable.
	uint8_t i;
	
	//Receive data bytes. 
	//The receiveByte command will only return data bytes, not the preamble/sync bytes.
	for(i=0 ; i<4 ; i++)
	{		
		rf_data_packet->roll.bytes[i] = receiveByte();		//Receive roll.
	}
	
	for(i=0 ; i<4 ; i++)
	{		
		rf_data_packet->pitch.bytes[i] = receiveByte();		//Receive pitch.
	}
	
	for(i=0 ; i<4 ; i++)
	{		
		rf_data_packet->yaw_vel.bytes[i] = receiveByte();	//Receive yaw velocity.
	}

	//Reset the FIFO buffer. Need to do this before receiving every packet.
	FIFO_reset();
}

// Declare a function to put the logging data into the data structure that will be send 
// to the communication module
void put_into_rf_packet(rf_data_packet_t* rf_data_packet, float roll, float pitch, float yaw_vel)
{
	rf_data_packet->roll.value = roll;
	rf_data_packet->pitch.value = pitch;
	rf_data_packet->yaw_vel.value = yaw_vel;
}

