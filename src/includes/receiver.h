//receiver.h
//Used for the RFM12B configured as a receiver.
//Based on source code from the official programming guide (https://www.sparkfun.com/datasheets/Wireless/General/RF12B_code.pdf)
//and an unofficial programming guide (http://dlehard.narod.ru/quick_start.pdf)

#include <avr/io.h>

void portInit(void);
uint16_t writeCommand(uint16_t cmd);
void rxInit(void);
uint8_t receiveByte(void);
void FIFO_reset(void);