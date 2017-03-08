#include "includes/spi.h"

ISR(SPI_STC_vect)
{
	uint8_t tempByte = spi_read_data_register();
	switch(tempByte)
	{
		case CMD_RECEIVE_RC_INPUTS: 
			receive_slave_data_packet(&rc_data_packet);		//May need to modify argument name.
			break;
		case CMD_SEND_LOGGING_DATA:
			send_slave_data_packet(&logg_data_packet);		//May need to modify argument name.
			break;
		default:
			//This should NOT happen. Maybe print an error?
			break;
	}
}