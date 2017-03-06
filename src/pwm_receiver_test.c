#include <avr/io.h>
#include <avr/interrupt.h>
#include "debug.h"
#include "rc_receiver_interface.h"


int main(void) {

	receiver_init();
    init_debug_uart0();
	sei();

    while(1){
		printf("PC0 duty cycle: %d\n",duty_cycle[0]);
    	printf("PC1 duty cycle: %d\n",duty_cycle[1]);
    	printf("PC2 duty cycle: %d\n",duty_cycle[2]);
    	printf("PC3 duty cycle: %d\n\n",duty_cycle[3]);
	}
}