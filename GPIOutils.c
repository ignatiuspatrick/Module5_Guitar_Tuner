#include <stdio.h>
#include <wiringPi.h>
#include "GPIOmap.c"

int setRead(void)
{
	int i;
	for(i = 1; i < 17; i = i + 1)
	{
		pinMode(GPIOchange(i),INPUT);
	}
};

float readGPIO(void)
{
	//setRead();
	float ans = 0;
	int i;
	for(i = 1; i < 17; i = i + 1 )	//From D1 to D16, this is correct as D0 is the clock
					//D1 is most significant
	{
		int j = GPIOchange(i);
		int current = digitalRead(j);
		ans = ans * 2;
		if (current == 1){
			ans = ans + 1;
			//printf("%fhoi\n",ans);
		};
		//printf("%d", current);
	}
	//printf("\n");
	//printf("%f\n",ans);
	//ans = ans / 100;
	return ans;
};

int writeGPIO(double output1)
{
	int output = (int) (output1 * 100);
	if (output > 65535)
	{
		printf("number is to high");
		return -1;
	}
	if (output < 0)
	{
		printf("number is to low");
		return -1;
	}
	int i;
	for(i = 16; i > 0; i = i - 1)	//From D16 to D1
					//D16 is least significant
	{
		int j = GPIOchange(i);
		pinMode(j,OUTPUT);
		if(output % 2 == 0)
		{
			digitalWrite(j,0);
		} else {
			output = output - 1;
			digitalWrite(j,1);
		}
		output = output / 2;
	}
};

int clockPin = 0;
int clockPinNr = 0;

void changeClock (void){
	if (clockPin){
		digitalWrite(clockPinNr,0);
		clockPin = 0;
		float ans = readGPIO();
		printf("read: %f\n",ans);
	} else {
		digitalWrite(clockPinNr,1);
		clockPin = 1;
		//printf("writing...\n");
	}
};

int runComBool = 1;

void *runCommunication (void *vargp)
{
	//setRead();
	wiringPiSetup();
	clockPinNr = GPIOchange(0);
	pinMode(clockPinNr,OUTPUT);
	do {
		delay(25);
		changeClock();
	} while (runComBool);
};

/*int main (void)
{
	run();
	return 0;
};*/
/*
int main (void)
{
	//printf("Start changing ping 3\n");
	//if (wiringPiSetupGpio() == -1)
	//	printf("wiringPiSetup == -1");
	//	return 1;
	wiringPiSetup();
	pinMode(GPIOchange(3),OUTPUT);
	printf("value is now:");
	int value = digitalRead(GPIOchange(3));
	printf("%d", value);
	printf("\nchanging\n");
	if (value==1)
		digitalWrite(GPIOchange(3),0);
	else
		digitalWrite(GPIOchange(3),1);
	printf("value is now:");
	printf("%d", digitalRead(GPIOchange(3)));
	printf("\n");
	printf("%f\n",read());
	write(5.1);
	printf("%f\n",read());
	return 0;
};
*/
