
#include<iostream>
#include<unistd.h>  // for the usleep() function
#include"GPIO.h"
#include <termios.h>
#include <wiringPi.h> 

using namespace exploringRPi;
using namespace std;

int main(){
   GPIO m1_p1(16), m1_p2(20),  m2_p1(19), m2_p2(26);    //m2 ......left with pwm1 
   int AENABLE_PWM1=23;                                 // m1 ......right with pwm0
   int BENABLE_PWM0=26;
   char k='y';  
/***********************************
to make m1 (right motor) forward p1 (16)... low  p2 (20) ...high 
to make m2 (right motor) forward p1 (19)... low  p2 (26) ...high 
********************************************/

/********************* PWM Setup ******************************/
   wiringPiSetup();
   pinMode(AENABLE_PWM1, PWM_OUTPUT);
   pinMode(BENABLE_PWM0, PWM_OUTPUT);
   pwmSetMode(PWM_MODE_MS);              // use a fixed frequency
   pwmSetRange(128);                     // range is 0-128
   pwmSetClock(1500000);                      // gives a precise 10kHz signal
//   pwmWrite(BENABLE_PWM0, 0);            // Motor B off - duty cycle of 0%

   m1_p1.setDirection(GOUTPUT);
   m1_p2.setDirection(GOUTPUT);
   m2_p1.setDirection(GOUTPUT);
   m2_p2.setDirection(GOUTPUT);


   m1_p1.streamOpen();            // fast write example
   m1_p2.streamOpen();            // fast write example
   m2_p1.streamOpen();            // fast write example
   m2_p2.streamOpen();            // fast write example

/* changing the terminal behavior so that getchar don't need an enter to read the character*/
static struct termios oldt, newt;
tcgetattr( STDIN_FILENO, &oldt);
newt = oldt;
newt.c_lflag &= ~(ICANON);
tcsetattr( STDIN_FILENO, TCSANOW, &newt);
/* end of terminal changing setup */

while(1)
{
while(getchar()!=27);

getchar();
k=(char)getchar();
if(k=='C')
{
printf("right arrow pressed, going right\n");
pwmWrite(BENABLE_PWM0, 16);           // duty cycle of 50% (64/128)
pwmWrite(AENABLE_PWM1, 128);           // duty cycle of 50% (64/128)
printf("right key pressed, going right\n");
m1_p1.streamWrite(GHIGH);
m1_p2.streamWrite(GLOW);
m2_p1.streamWrite(GLOW);
m2_p2.streamWrite(GHIGH);
usleep(30000);
pwmWrite(BENABLE_PWM0, 0);
pwmWrite(AENABLE_PWM1, 0);

}
else if(k=='D')
{
printf("left arrow pressed, going Left\n");
pwmWrite(BENABLE_PWM0, 128);           // duty cycle of 50% (64/128)
pwmWrite(AENABLE_PWM1, 16);           // duty cycle of 50% (64/128)
printf("right key pressed, going right\n");
m1_p1.streamWrite(GLOW);
m1_p2.streamWrite(GHIGH);
m2_p1.streamWrite(GHIGH);
m2_p2.streamWrite(GLOW);
usleep(30000);
pwmWrite(BENABLE_PWM0, 0);
pwmWrite(AENABLE_PWM1, 0);
}
else if(k=='B')
{
printf("right key pressed, going forward\n");
pwmWrite(BENABLE_PWM0, 127);           // duty cycle of 50% (64/128)
pwmWrite(AENABLE_PWM1, 127);           // duty cycle of 50% (64/128)
printf("right key pressed, going right\n");
m1_p1.streamWrite(GHIGH);
m1_p2.streamWrite(GLOW);
m2_p1.streamWrite(GHIGH);
m2_p2.streamWrite(GLOW);
usleep(30000);
pwmWrite(BENABLE_PWM0, 0);
pwmWrite(AENABLE_PWM1, 0);
}
else if(k=='A')
{
printf("left key pressed, going forward\n");
pwmWrite(BENABLE_PWM0, 127);           // duty cycle of 50% (64/128)
pwmWrite(AENABLE_PWM1, 127);           // duty cycle of 50% (64/128)
printf("right key pressed, going right\n");
m1_p1.streamWrite(GLOW);
m1_p2.streamWrite(GHIGH);
m2_p1.streamWrite(GLOW);
m2_p2.streamWrite(GHIGH);
usleep(30000);
pwmWrite(BENABLE_PWM0, 0);
pwmWrite(AENABLE_PWM1, 0);
}
}



/* restore the terminal behavior*/
 tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
return 0;






/*
   for (int i=0; i<1000000; i++){   // write 1 million cycles

printf("1\n");
   pwmWrite(BENABLE_PWM0, 127);           // duty cycle of 50% (64/128)
   pwmWrite(AENABLE_PWM1, 127);           // duty cycle of 50% (64/128)
      m1_p1.streamWrite(GLOW);    // high
      m1_p2.streamWrite(GHIGH);    // high
      m2_p1.streamWrite(GHIGH);    // high
      m2_p2.streamWrite(GLOW);    // high
      sleep(5);
 pwmWrite(BENABLE_PWM0, 0);
pwmWrite(AENABLE_PWM1, 0);
      sleep(1);
printf("2\n");
   pwmWrite(BENABLE_PWM0, 127);           // duty cycle of 50% (64/128)
   pwmWrite(AENABLE_PWM1, 127);           // duty cycle of 50% (64/128)
      m1_p1.streamWrite(GHIGH);    // high
      m1_p2.streamWrite(GLOW);    // high
      m2_p1.streamWrite(GLOW);    // high
      m2_p2.streamWrite(GHIGH);    // high
      sleep(5);
 pwmWrite(BENABLE_PWM0, 0);
pwmWrite(AENABLE_PWM1, 0);
      sleep(1);
   }
   m1_p1.streamClose();           // close the stream
   m1_p2.streamClose();           // close the stream
   m2_p1.streamClose();           // close the stream
   m2_p2.streamClose();           // close the stream
   return 0;*/
}
