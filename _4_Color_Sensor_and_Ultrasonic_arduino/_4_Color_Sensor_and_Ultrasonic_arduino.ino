/*PINS ON COLOR SENSOR
 *OE    :   A high state on Output Enable (OE) places the output in a high-impedance state for multiple-unit sharing of amicrocontroller input line. Enable for fo (active low).
 *OUT   :   Output frequency (fo).
 *S0,S1 :   Output frequency scaling selection inputs:    S0-LOW  S1-LOW     POWER DOWN
 *                                                        S0-LOW  S1-HIGH    2%
 *                                                        S0-HIGH S1-LOW     20%
 *                                                        S0-HIGH S1-HIGH    100%
 *S2,S3 :   Photodiode type selection inputs:             S2-LOW  S3-LOW     Red
 *                                                        S2-LOW  S3-HIGH    Blue
 *                                                        S2-HIGH S3-LOW     Clear(no filter)
 *                                                        S2-HIGH S3-HIGH    Green
 */


int S0=2;     //Color sensor's S0 pin is connected to digital pin 2 of Arduino 
int S1=3;     //Color sensor's S1 pin is connected to digital pin 3 of Arduino
int S2=4;     //Color sensor's S2 pin is connected to digital pin 4 of Arduino
int S3=5;     //Color sensor's S3 pin is connected to digital pin 5 of Arduino
int outPin=6; //Color sensor's OUT pin is connected to digital pin 6 of Arduino
int OE=7;     //Color sensor's OE pin is connected to digital pin 6 of Arduino
int trigPin=9;
int echoPin=10;

int rColorStrength;       //measure strength of red color
int gColorStrength;       //measure strength of green color
int bColorStrength;       //measure strength of blue color
unsigned int pulseWidth;  //for measuring color strength pulse width

float pingTime ;          //time for ping to travel to target and back
float targetDistance;      //measure distance to target (we have to divide it by 2)
float speedOfSound=776.5; //speed of sound in miles per hour

void setup()
{
  Serial.begin(115200);                       //turn on serial port with baud rate 115200
  pinMode(8,OUTPUT);  digitalWrite(8,HIGH);   //i'm using pin 8 as VCC for ultrasonic sensor
  pinMode(11,OUTPUT); digitalWrite(11,LOW);   //i'm using pin 11 as GND for ultrasonic sensor
  pinMode(S2,OUTPUT); pinMode(S3,OUTPUT);
  pinMode(S0,OUTPUT); digitalWrite(S0,HIGH);
  pinMode(S1,OUTPUT); digitalWrite(S1,HIGH);
  pinMode(OE,OUTPUT); digitalWrite(OE,HIGH);
  
  pinMode(outPin,INPUT);                      //we will receive frequency as input from the sensor   
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  
}

void loop()
{
//Lets start by reading red component of color
//To read red S2 and S3 should be set low
digitalWrite(S3,LOW);
digitalWrite(S2,LOW);

pulseWidth=pulseIn(outPin,LOW); //measure pulsewidth of low pulse at outpin on color sensor
rColorStrength=pulseWidth/400.-1;//convert measured pulsewidth to a number between 0 and 255
rColorStrength=(255-rColorStrength);//reverse so strong color is large number

//green component of color
//To read green S2 and S3 should be set high
digitalWrite(S3,HIGH);
digitalWrite(S2,HIGH);

pulseWidth=pulseIn(outPin,LOW); //measure pulsewidth of low pulse at outpin on color sensor
gColorStrength=pulseWidth/400.-1;//convert measured pulsewidth to a number between 0 and 255
gColorStrength=(255-gColorStrength);//reverse so strong color is large number

//blue component of color
//To read blue S2=LOW and S3=HIGH 
digitalWrite(S3,LOW);
digitalWrite(S2,HIGH);

pulseWidth=pulseIn(outPin,LOW); //measure pulsewidth of low pulse at outpin on color sensor
bColorStrength=pulseWidth/400.-1;//convert measured pulsewidth to a number between 0 and 255
bColorStrength=(255-bColorStrength);//reverse so strong color is large number

//red is strongest and blue is weakest
if (rColorStrength>gColorStrength && gColorStrength>bColorStrength)
{rColorStrength=255;
 gColorStrength=gColorStrength/2;
 bColorStrength=0;}

//red is strongest and Green is weakest
if (rColorStrength>bColorStrength && bColorStrength>gColorStrength)
{rColorStrength=255;
 bColorStrength=bColorStrength/2;
 gColorStrength=0;}

//green is strongest and blue is weakest
if (gColorStrength>rColorStrength && rColorStrength>bColorStrength)
{gColorStrength=255;
 rColorStrength=rColorStrength/2;
 bColorStrength=0;}

//green is strongest and red is weakest
if (gColorStrength>bColorStrength && bColorStrength>rColorStrength)
{gColorStrength=255;
 bColorStrength=bColorStrength/2;
 rColorStrength=0;}

//blue is strongest and green is weakest
if (bColorStrength>rColorStrength && rColorStrength>gColorStrength)
{bColorStrength=255;
 rColorStrength=rColorStrength/2;
 gColorStrength=0;}

//blue is strongest and red is weakest
if (bColorStrength>gColorStrength && gColorStrength>rColorStrength)
{bColorStrength=255;
 gColorStrength=gColorStrength/2;
 rColorStrength=0;}

//Now we measure distance
digitalWrite(trigPin,LOW);
delayMicroseconds(2000);
digitalWrite(trigPin,HIGH);
delayMicroseconds(15);
digitalWrite(trigPin,LOW);
delayMicroseconds(10);

pingTime=pulseIn(echoPin,HIGH);   //looking for high pulse
pingTime=pingTime/1000000;        //convert pingTime to seconds
pingTime=pingTime/3600;           //convert pingTiem to hours

targetDistance = speedOfSound*pingTime;
targetDistance = targetDistance/2.;
targetDistance = targetDistance*63360; //1mile=63360 inches


//Now lets print the text on serial monitor
Serial.print(rColorStrength);
Serial.print(",");
Serial.print(gColorStrength);
Serial.print(",");
Serial.print(bColorStrength);
Serial.print(",");
Serial.println(targetDistance);
}
