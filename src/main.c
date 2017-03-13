#include "clock.h" // to be consider as a way for handling the timing
#include "comms_interface.h"
#include "rc_receiver_interface.h"
#include "rf_transceiver_interface.h"
#include "data_conversion.h"
#include <avr/interrupt.h>
#include <stdio.h>
#include "debug.h"

// Define the data packets that will flow through the communication module
// as global variables
rf_data_packet_t rf_data_packet;
logg_data_packet_t logg_data_packet;
rc_data_packet_t rc_data_packet; // data pocket with the input signals from the RC receiver

int main() {
  //Initialize all the submodules
   init_debug_uart0();
	printf("HELOO????.\n");
  receiver_init();			//Initialise RC receiver.
  rf_transmitter_init();
  comms_master_init(); 		//Initialise communication with the control module. SPI initialised in here.
  sei(); 					//Enable interrupts.
  
  //Setup the uplink and downlink clock
  clock_init();
  clock_time_t uplink_clock_prev = 0, uplink_clock_current;
  clock_time_t downlink_clock_prev = 0, downlink_clock_current;
  
  printf("Successfully initialised.\n");

  // We need to consider timing - at what frequency each communication link
  // operates. We can handle some of the functions in the interrupts.
  // Alternatively, we can set up a clock that will keep track of the internal
  // time in the module and execute the functions at decided frequencies accordingly
  
  while (1) {

	// The uplink communication is performed at 50Hz frequency. It obtaines the four values 
	// of the PWM inputs from the RC receiver. The 4 channels' values are then send in a 
	// rc_data_packet to the control module.
    /////////////////////////////////////// UPLINK COMMUNICATION ///////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////
    
	uplink_clock_current = clock_get_time();
	
	//printf("%d\n", uplink_clock_current);
	//printf("Current clock diff: %d\n", (int)clock_diff(uplink_clock_current, uplink_clock_prev));
		
	if(clock_diff(uplink_clock_prev, uplink_clock_current)>=20){
		//printf("Receiving RC PWM data...\n");
		
		// Obtain the inputs from the Remote Control receiver		
		receive_rc_packet(&rc_data_packet);
		
		//printf("Received PWM data: %d, %d, %d, %d\n",  rc_data_packet.channel_0, rc_data_packet.channel_1, rc_data_packet.channel_2, rc_data_packet.channel_3);
		
		// Communicate with the control module to send the input sinals
		send_master_data_packet(&rc_data_packet);
		
		// Record the time point at the end of last data transmission.
		uplink_clock_prev = clock_get_time();
	}
    ////////////////////////////////////////////////////////////////////////////////////////////

	// The downlink communication is performed at 25Hz frequency. Here, the logging data is received
	// and then it is propagated to the host computer.
    ///////////////////////////////////// DOWNLINK COMMUNICATION ///////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////
    
	downlink_clock_current = clock_get_time();
	
	if(clock_diff(downlink_clock_prev, downlink_clock_current)>=40){
		// Communicate with control module to obtain the logging data.
		receive_master_data_packet(&logg_data_packet);

		// Encode the data. Here is the place for some encryption algorithm
		encode_data(&logg_data_packet, &rf_data_packet);

		//printf("encode: %d, %d, %d\n done: %d, %d, %d\n", (int)logg_data_packet.roll.value, (int)logg_data_packet.pitch.value, (int)logg_data_packet.yaw_vel.value,
		//													(int)rf_data_packet.roll.value,   (int)rf_data_packet.pitch.value,   (int)rf_data_packet.yaw_vel.value);

		// Send data to the RF module to wirelessly transmit the logging data to the host computer.
		//rf_data_packet.pitch.value = 0.5;
		//rf_data_packet.roll.value = -3.5;
		//rf_data_packet.yaw_vel.value = 3.1415;
		send_rf_packet(&rf_data_packet);
		
		// Record the time point at the end of last data transmission.
		downlink_clock_prev = clock_get_time();
	}
    /////////////////////////////////////////////////////////////////////////////////////////////
  }
}

