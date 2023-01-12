#include <stdio.h>
#include <conio.h>
#include <string.h>

unsigned int wiperSpeedStat(float STAT);

unsigned int dutysetter(unsigned char Fast, unsigned char slow);

unsigned char BCMsetter(float STAT, unsigned char switched, unsigned char autoed);

int main(void)
{
	//external value
	unsigned char wiperslowSW = 0;
	unsigned char wiperfastSW = 0;
	unsigned char wiperautoSW = 0;
	float sensorstatus = 0;
	unsigned int keystatus = 0xff; // 0xff: invalid, 0x01: idle, 0x02: ACC, 0x03: RUN, 0x04: START
	unsigned int dutycyvle = 0;
	unsigned char BCMwiperstatus = 0x02; // 0xff: invalid, 0x01:active, 0x02: not active
	unsigned char BCMwiperstatus_stat[] = "not active";

	// internal signals
	unsigned char IgnitionSW = 0;
	unsigned char Automode = 0;
	unsigned char Slowmode = 0;
	unsigned char Fastmode = 0;
	
	while (1) //while loop (this runs until the chip turns off)
	{
		if (kbhit())//chesks for input
		{
			unsigned char c = _getch();
			if (c == '1')
			{
				switch (keystatus)
				{
					case 0xff:
					case 0x04:
						keystatus = 0x01;
						break;
					case 0x01:
						keystatus = 0x02;
						break;
					case 0x02:
						keystatus = 0x03;
						break;
					case 0x03:
						keystatus = 0x04;
						break;
					default:
						break;
				}

				IgnitionSW = ((keystatus == 0x03) || (keystatus == 0x04));
			}
			
			else if(c == '2')//Auto switch selection
			{
				if (wiperautoSW)
				{
					wiperautoSW = 0;
				}
				else
				{
					if (!wiperautoSW)
					{
						wiperautoSW = 1;
						wiperslowSW = 0;
						wiperfastSW = 0;
					}
				}
			}
			else if(c == '3')//Slow switch selection
			{
				if (wiperslowSW)
				{
					wiperslowSW = 0;
				}
				else
				{
					if (!wiperslowSW)
					{
						wiperautoSW = 0;
						wiperslowSW = 1;
						wiperfastSW = 0;
					}
				}
			}
			else if(c == '4')//Fast switch selection
			{
				if (wiperfastSW)
				{
					wiperfastSW = 0;
				}
				else
				{
					if (!wiperfastSW)
					{
						wiperautoSW = 0;
						wiperslowSW = 0;
						wiperfastSW = 1;
					}
				}
			}
			else if(c == '5')//rain mode
			{//this simulates sensor output (should be replaced)
				sensorstatus = sensorstatus + 1;
				if (sensorstatus > 5)
				{
					sensorstatus = 0;
				}
			}
			Automode = 0;
			Slowmode = 0;
			Fastmode = 0;
			if(IgnitionSW)
			{
				if(wiperautoSW)
				{
					Automode = 1;
				}
				if(wiperslowSW)
				{
					Slowmode = 1;
				}
				if(wiperfastSW)
				{
					Fastmode = 1;
				}
			}
			if(Automode)
			{
				switch(wiperSpeedStat(sensorstatus))
				{
					case 2:
						//OFF
						Slowmode = 0;
						Fastmode = 0;
						break;
					case 3:
						//SLOW
						Slowmode = 1;
						Fastmode = 0;
						break;
					case 4:
						//FAST
						Slowmode = 0;
						Fastmode = 1;
						break;
					case 1:
						//sensor failure (fail safe defaulted to fast)
						Fastmode = 1;
						Slowmode = 0;
						break;
					default:
						break;
				}
			}
			dutycyvle = dutysetter(Fastmode, Slowmode);
			BCMwiperstatus = BCMsetter(sensorstatus, (wiperfastSW || wiperslowSW), wiperautoSW);
			if (BCMwiperstatus == 0x01)//BCM value to massage
			{
				strcpy(BCMwiperstatus_stat, "active");
			}
			else if(BCMwiperstatus == 0x02)
			{
				//BCMwiperstatus_stat[] = "not active";
				strcpy(BCMwiperstatus_stat, "not active");
			}
			else
			{
				//BCMwiperstatus_stat[] = "invalid";
				strcpy(BCMwiperstatus_stat, "invalid");
			}
			//some text for debugging porpues
			printf("keystatus: %d " "ignition: %d " "Automode: %d " "Slowmode: %d " "Fastmode: %d " "sensorOutput: %.2f ""dutycycle: %i%c ""BCMState: %d : %5s\n",
			keystatus,
			IgnitionSW,
			Automode,
			Slowmode,
			Fastmode,
			sensorstatus,
			dutycyvle,
			37,
			BCMwiperstatus,
			BCMwiperstatus_stat);
		}
	}
	return 0;
}

unsigned int wiperSpeedStat(float STAT)//sensor value selection
{
	if (STAT >= 1.0f && STAT <= 2.0f)
	{
		return 2;
	}
	else if (STAT > 2.0f && STAT <= 3.0f)
	{
		return 3;
	}
	else if (STAT > 3.0f && STAT <= 4.0f)
	{
		return 4;
	}
	return 1;
}

unsigned int dutysetter(unsigned char Fast, unsigned char slow)//duty value setter
{
	if (Fast)
	{
		return 85;
	}
	if (slow)
	{
		return 35;
	}
	return 0;
}


unsigned char BCMsetter(float STAT, unsigned char switched, unsigned char autoed)//BCM checker
{
	if(switched)
	{
		return 0x01;
	}
	if(autoed)
	{
		if(wiperSpeedStat(STAT) == 1)
		{
			return 0xff;
		}
		return 0x01;
	}
	return 0x02;
}
