                                                                                           
int UVOUT = A0; //Output from the sensor
int REF_3V3 = A1; //3.3V power on the Arduino board
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

int frequency = 0;
int R = 0;
int G = 0;
int B = 0;
int T = 0;
int sen =0;

void setup()
{

  
  Serial.begin(9600);

  pinMode(UVOUT, INPUT);
  pinMode(REF_3V3, INPUT);
  //Serial.println("ML8511 example");
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
}

  void loop()
{
  
  Serial.println(sensorOut);
  delay(1000);
  
  int uvLevel = averageAnalogRead(UVOUT);
  int refLevel = averageAnalogRead(REF_3V3);

  //Use the 3.3V power pin as a reference to get a very accurate output value from sensor
  float outputVoltage = 3.3 / refLevel * uvLevel;

  float uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0); //Convert the voltage to a UV intensity level

  //Serial.print("output: ");
  //Serial.print(refLevel);

  //Serial.print("ML8511 output: ");
  //Serial.print(uvLevel);

  //Serial.print(" / ML8511 voltage: ");
  //Serial.print(outputVoltage);

  Serial.print(" / UV Intensity (mW/cm2): ");
  Serial.print(uvIntensity);
  delay(100);

  Serial.println();
  // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  R = frequency;
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  //++++++++++++++++++++++++++++6
  //Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  Serial.print(" Intensity:  ");
  Serial.println(0.856*frequency);
  delay(100);

  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  G = frequency;
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  //Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  Serial.print(" Intensity:  ");
  Serial.println(0.856*frequency);
  delay(100);

  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  G = frequency;
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  //Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  Serial.print(" Intensity:  ");
  Serial.println(0.856*frequency);
  delay(100);

  T = (0.21 * R) + (0.72 * G) + (0.07 * B);
  Serial.print(" Total Intensity :");
  Serial.println(T);
  delay(1000);
  
}
 

//Takes an average of readings on a given pin
//Returns the average
int averageAnalogRead(int pinToRead)
{
  byte numberOfReadings = 8;
  unsigned int runningValue = 0; 

  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;

  return(runningValue);  
}

//The Arduino Map function but for floats
//From: http://forum.arduino.cc/index.php?topic=3922.0
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{

  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;

}


  
  
  
