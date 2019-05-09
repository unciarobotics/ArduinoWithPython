const int s0=2; //Color sensor's S0 pin is connected to digital pin 2 of Arduino
const int s1=3;
const int s2=4;
const int s3=5;
const int sensorData=A0;
unsigned int data,dataR,dataG,dataB,valR,valG,valB = 0;

void setup()
{
  pinMode(s0,OUTPUT);pinMode(s1,OUTPUT);pinMode(s2,OUTPUT);pinMode(s3,OUTPUT);pinMode(sensorData,INPUT);
  Serial.begin(9600);
  //frequency scale 100%
  digitalWrite(s0,HIGH);digitalWrite(s1,HIGH);
}
void loop()
{
  //Getting Red color data s2 = LOW , s3 = LOW
  digitalWrite(s2,LOW);digitalWrite(s3,LOW);
  valR=pulseIn(sensorData,LOW);
          valR=constrain(valR,10,124);
          dataR=map(valR,10,124,255,0);
  Serial.print("R");Serial.print(dataR);
  Serial.print('\t');
  delay(100);


  //Getting Green color data s2 = HIGH , s3 = HIGH
  digitalWrite(s2,HIGH);digitalWrite(s3,HIGH);
  valG=pulseIn(sensorData,LOW);
          valG=constrain(valG,10,121);
          dataG=map(valG,10,121,255,0);
  Serial.print("G ");Serial.print(dataG);
  Serial.print('\t');
  //delay(100);

  //Getting Blue color data s2 = LOW , s3 = HIGH
  digitalWrite(s2,LOW);digitalWrite(s3,HIGH);
  valB=pulseIn(sensorData,LOW);
           valB=constrain(valB,9,110);
           dataB=map(valB,9,110,255,0);
  Serial.print("B ");Serial.print(dataB);
  Serial.print('\t');
  //delay(100);
  
  //Getting Clear filter data s2 = HIGH , s3 = LOW
  digitalWrite(s2,HIGH);digitalWrite(s3,LOW);
  data=pulseIn(sensorData,LOW);
  Serial.print("W ");Serial.print(data);
  Serial.println("");
  delay(100);
  
}
