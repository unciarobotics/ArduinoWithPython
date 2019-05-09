int S2=7;
int S3=6;
int outPin=4;

int trigPin=9;
int echoPin=10;
int power=8;
int ground=11;

int rColorStrength;       //measured strength of red color
int gColorStrength;       //measured strength of green color
int bColorStrength;       //measured strength of blue color
unsigned int pulseWidth;  //for measuring color strength pulse width

float pingTime;           //time for ping to travel to target and back
float targetDistance;     //measured distance to target
float speedOfSound;       //speed of sound in miles per hour

void setup() {
 Serial.begin(115200);
 
//Color Sensor
pinMode(S2,OUTPUT);
pinMode(S3,OUTPUT);
pinMode(outPin, INPUT);

//Ultrasonic
pinMode(power,OUTPUT); pinMode(ground,OUTPUT);
digitalWrite(power,HIGH);digitalWrite(ground,LOW);
pinMode(trigPin,OUTPUT);
pinMode(echoPin,INPUT);
}

void loop() {
//measure red, S2 and S3 should be set low
digitalWrite(S2,LOW);
digitalWrite(S3,LOW);

pulseWidth=pulseIn(outPin,LOW);     //measure pulsewidth of low pulse at outPin on color sensor
rColorStrength = pulseWidth/400-1;   //convert measured pulsewidth to a number between 0 and 255
rColorStrength=(255-rColorStrength);//reverse so strong color is a large number

//measure green, S2 and S3 should be set high
digitalWrite(S2,HIGH);
digitalWrite(S3,HIGH);

pulseWidth=pulseIn(outPin,LOW);     //measure pulsewidth of low pulse at outPin on color sensor
gColorStrength = pulseWidth/400-1;   //convert measured pulsewidth to a number between 0 and 255
gColorStrength=(255-gColorStrength);//reverse so strong color is a large number

//measure blue, S2 LOW and S3 HIGH
digitalWrite(S2,LOW);
digitalWrite(S3,LOW);

pulseWidth=pulseIn(outPin,LOW);     //measure pulsewidth of low pulse at outPin on color sensor
bColorStrength = pulseWidth/400-1;   //convert measured pulsewidth to a number between 0 and 255
bColorStrength=(255-bColorStrength);//reverse so strong color is a large number

if ( rColorStrength>gColorStrength && gColorStrength>bColorStrength)  //red is strongest and blue is weakest
{   
  rColorStrength=255;
  gColorStrength=gColorStrength/2;
  bColorStrength=0;   
}

if ( rColorStrength>bColorStrength && bColorStrength>gColorStrength)  //red is strongest and green is weakest
{   
  rColorStrength=255;
  bColorStrength=bColorStrength/2;
  gColorStrength=0;   
}

if ( gColorStrength>rColorStrength && rColorStrength>bColorStrength)  //green is strongest and blue is weakest
{   
  gColorStrength=255;
  rColorStrength=rColorStrength/2;
  bColorStrength=0;   
}

if ( gColorStrength>bColorStrength && bColorStrength>rColorStrength)  //green is strongest and red is weakest
{   
  gColorStrength=255;
  bColorStrength=bColorStrength/2;
  rColorStrength=0;   
}

if ( bColorStrength>rColorStrength && rColorStrength>gColorStrength)  //blue is strongest and green is weakest
{   
  bColorStrength=255;
  rColorStrength=rColorStrength/2;
  gColorStrength=0;   
}

if ( bColorStrength>gColorStrength && gColorStrength>rColorStrength)  //blue is strongest and red is weakest
{   
  bColorStrength=255;
  gColorStrength=gColorStrength/2;
  rColorStrength=0;   
}

digitalWrite(trigPin,LOW);
delayMicroseconds(2000);
digitalWrite(trigPin,HIGH);
delayMicroseconds(15);
digitalWrite(trigPin,LOW);
delayMicroseconds(10);
pingTime = pulseIn(echoPin,HIGH); 
pingTime = pingTime/1000000.; //convert time to seconds
pingTime = pingTime/3600.;    //convert to hours

targetDistance = speedOfSound*pingTime; //distance travelled by ping to and from the target
targetDistance=targetDistance/2.;
targetDistance = targetDistance*63360;   //convert distance to inches

Serial.print(rColorStrength);
Serial.print(",  ");
Serial.print(gColorStrength);
Serial.print(",  ");
Serial.print(bColorStrength);
Serial.print(",  ");
Serial.println(targetDistance);
}
