int count=0;
void setup() {
Serial.begin(9600);

}

void loop() {
  Serial.print("Count: ");
  Serial.print(count);
  Serial.println();
  count=count+1;
  delay(300);
}
