
#define trigPin 9
#define echoPin 10
int power = 8;
int ground =11;

void setup()
{
  Serial.begin(9600);
  pinMode(power,OUTPUT);
  pinMode(ground,OUTPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  digitalWrite(power,HIGH); 
  digitalWrite(ground,LOW);

}

void loop()
{
  float duration, distance;
  
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin,HIGH);
  distance= (duration/2)/29.1;
  String py=String(distance,1);
  Serial.println(py);
  delay(100);

}

