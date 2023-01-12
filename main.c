#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <string.h>

int main(void) {
	//  Main signals
	unsigned char wiperslowSW = 0;
	unsigned char wiperfastSW = 0;
    unsigned char wiperautoSW = 0;
    unsigned float sensorstatus = 0;
	unsigned int keystatus = 0xff; // 0xff: invalid, 0x01: idle, 0x02: ACC, 0x03: RUN, 0x04: START
	unsigned float dutycyvle = 0;
	unsigned char BCMwiperstatus = 0x02 // 0xff: invalid, 0x01:active, 0x02: not active
	
	// internal signals
	unsigned char
	unsigned char
	unsigned char
	unsigned char
	unsigned char
	
