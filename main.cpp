#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2); 
DigitalIn but1(A1);        
DigitalIn but2(A2);        
DigitalIn but3(A3);         
AnalogOut Aout(PA_4);      
AnalogIn Ain(A0);           
int pre_freq = 100; 
int freq = 100;    
float rat = 0; 
float wtime = (1.0 / 700.0) / 50.0;
char step = 0; 
float ADCdata[128]; 

char sam = -1;     
char conf = 0;      

void display(void) { 
	uLCD.color(BLUE);
	uLCD.locate(0, 0);
	uLCD.printf("freq = %D\n", pre_freq);
	return;
}

void display_v2(void) {
	uLCD.color(WHITE); 
	uLCD.locate(0, 3);
	uLCD.printf("current freq = %D\n", freq);
	return;
}

int main(){
	int i; 
	int state_1=0;
	int state_2=0;
	
	but1.mode(PullNone);
	but2.mode(PullNone);
	but3.mode(PullNone);

	
	display();

    while (1) {

		
		if (but1 == 1&&state_1==0) {
			pre_freq -= 10;
			state_1=1;
			display();

		}
		else state_1=0;
		if (but2 == 1) {
			freq = pre_freq;
			conf = 1;
			display_v2();
		}

		if (but3 == 1&&state_2==0) {
			pre_freq += 10;
			state_2=1;
			display();
		}
		else state_2=0;

		if (step == 100) {
			rat = 0;
			step = 0;
		}
		else if (step < 70) {
			rat += 0.0142857;
			step++;
		}
		else {
			rat -= 0.0333333;
			step++;
		}
		Aout = rat;	
		wtime = 1000000.0/freq/100-30;
		wait_us(wtime);
		if (conf == 1) {
			if (sam >= 0) ADCdata[sam] = Ain;
			if (sam == 128) { 
				printf("%d\r\n", freq); 
				
				for (i = 0; i < 100; ++i){
					printf("%f\r\n", ADCdata[i]);
					ThisThread::sleep_for(1000ms/128);
				}
				sam = -1; 
				conf = 0;  
			}
			else ++sam; 
		}
    }
}