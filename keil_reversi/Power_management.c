#include <LPC210x.H>                       /* LPC210x definitions */
// Set the processor into power down state 
// The watchdog cannot wake up the processor from power down
void PM_power_down (void)  {
	PLLCON = 0x01;
	PLLFEED = 0xAA;
	PLLFEED = 0x55;
	EXTWAKE = 7; // EXTINT0 will awake the processor
	PCON |= 0x01;
	Switch_to_PLL();
}
