#include <stdio.h>
#include <conio.h>
#include <string.h>

void statusTel(char what[]) {
	printf(what, "\n");
}

unsigned int wiperSpeedStat(float STAT)
{
	if (STAT > 1.0f && STAT < 2.0f)
	{
		return 2;
	}
	else if (STAT > 2.0f && STAT < 3.0f)
	{
		return 3;
	}
	else if (STAT > 3.0f && STAT < 4.0f)
	{
		return 4;
	}
	return 1;
}


int main(void)
{
	//external value
	unsigned char wiperslowSW = 0;
	unsigned char wiperfastSW = 0;
	unsigned char wiperautoSW = 0;
	float sensorstatus = 0;
	unsigned int keystatus = 0xff; // 0xff: invalid, 0x01: idle, 0x02: ACC, 0x03: RUN, 0x04: START
	float dutycyvle = 0;
	unsigned char BCMwiperstatus = 0x02; // 0xff: invalid, 0x01:active, 0x02: not active

	// internal signals
	unsigned char IgnitionSW = 0;
	unsigned char Automode = 0;
	unsigned char Slowmode = 0;
	unsigned char Fastmode = 0;
	unsigned int Sensorres = 0;
	while (1) 
	{
		if (kbhit())
		{
			unsigned char c = _getch();
			if (c == '1')
			{
				switch (keystatus)
				{
					case 0xff:
						//statusTel("invalid");
					case 0x04:
						//statusTel("switched status : IDLE");
						keystatus = 0x01;
						break;
					case 0x01:
						//statusTel("switched status : ACC");
						keystatus = 0x02;
						break;
					case 0x02:
						//statusTel("switched status : RUN");
						keystatus = 0x03;
						break;
					case 0x03:
					//	statusTel("switched status : START");
						keystatus = 0x04;
						break;
					default:
						//statusTel("well nothing");
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
			else if(c == '5')//Fast switch selection
			{
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
				//printf(wiperSpeedStat(sensorstatus));
				switch(wiperSpeedStat(sensorstatus))
				{
					case 2:
						printf("off");
						Slowmode = 0;
						Fastmode = 0;
						break;
					case 3:
						printf("slow");
						Slowmode = 1;
						Fastmode = 0;
						break;
					case 4:
						printf("Fast");
						Slowmode = 0;
						Fastmode = 1;
						break;
					case 1:
						printf("invalid");
						Fastmode = 1;
						Slowmode = 0;
						break;
					default:
						statusTel("data error");
						break;
				}
			}
			printf("keystatus: %d " "ignition: %d " "Automode: %d " "Fastmode: %d " "Slowmode: %d " "sensorOutput: %f\n",
			keystatus,
			IgnitionSW,
			Automode,
			Fastmode,
			Slowmode,
			sensorstatus);
			
			
		}
	}
	return 0;
}
