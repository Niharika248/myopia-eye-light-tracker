/*
  IR Proximity Sensor interface code
  Turns on an LED on when obstacle is detected, else off.
  blog.circuits4you.com 2016
 */


int ProxSensor = A0;
 
void setup() {                
  
  pinMode(ProxSensor,INPUT);
}

void loop() {
  
  float v = analogRead(ProxSensor);
  Serial.print("value : ");
  Serial.print(v);
  delay(100);              // wait for a second
}
