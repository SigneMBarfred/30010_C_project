#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course

#include "jukebox.h"




int main()
{
	uart_init(9600);
	melody1();

}
