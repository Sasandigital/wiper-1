#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <string.h>

int main(void) {
	//  Main signals
	unsigned char wiperslowSW = 0;
	unsigned char wiperfastSW = 0;
    unsigned char wiperautoSW = 0;
    float sensorstatus = 0;
	float dutycyvle = 0;
	unsigned int keystatus = 0xff; // 0xff: invalid, 0x01: idle, 0x02: ACC, 0x03: RUN, 0x04: START
	unsigned int BCMwiperstatus = 0x02 // 0xff: invalid, 0x01:active, 0x02: not active
	
	// internal signals
	unsigned char ignitionSW = 0;
	unsigned char automode = 0;
	unsigned char slowmode = 0;
	unsigned char fastmode = 0;
	unsigned char keystatus_str ="invalid";
	unsigned char prevmode
	while(1)
	{
	    if(kbhit())
	    {
	       unsigned char c =getch()
	       if (c == '1')
	       switch (keystatus)
	       {
	           case 0xff:
	           case 0x04:
	           keystatus = 0x01;
	           strcpy(keystatus_str, "idle");
	           break:
	        
	           case 0x01:
	           keystatus = 0x02;
	           strcpy(keystatus_str, "ACC" );
	           break;
	        
	           case 0x02:
	           keystatus = 0x03;
	           strcpy(keystatus_str, "RUN");
	           break;
	        
	           case 0x03:
	           keystatus = 0x04
	           strcpy(keystatus_str, "START");
	           break;
	        
	           default:
	           break;
	       }
	   ignitionSW = (keystatus == 0x03) or (keystatus == 0x04);
    }

    else if ( c== 2)
    {
        if (fastmode) and (aoutomode) and (slowmode)  
        
        
        
        
        
        
        
        
        
        
        
        
	
