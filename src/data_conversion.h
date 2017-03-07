// This file implements the data conversion between 8 bits data packets received from the 
// RF receiver and its corresponding floating point numbers. The data is further put into
// data structure that will be send to  the host computer for telemetry purposes.

#ifndef __DATA_CONVERSION_H
#define __DATA_CONVERSION_H

// Encode the data. For now we are just passing the data without any encryption
void encode_data(logg_data_packet* logg_data_packet, rf_data_packet* rf_data_packet);

// Decode the data. For now we are just passing the data from one structure to another
// without any decryption. 
void decode_data(&rf_data_packet, &host_data_packet);

#endif