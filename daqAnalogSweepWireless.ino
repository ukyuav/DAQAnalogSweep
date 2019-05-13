/* Name: DAQAnalogSweep
 * Author: Matthew Miller
 * Description: Reads all 8 DAQ channels, sends data over serial as an array of 8 floats. 
 */

 #include <ExtendedADCShield.h>
 #include <SPI.h>

const int NUM_CHAN = 8;
const int IMET_TRIGGER_PIN = 13;

//Initialize ADC Shield with default pins and 16-bit ADC (LTC1959)
ExtendedADCShield extendedADCShield(16);

//array of sensorValues (floating point)
float sensorValues[NUM_CHAN], tempFloat;

//string that contains a CSV style list of all DAQ channel values
String chanList, tempStr;

 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  extendedADCShield.analogReadConfigNext(0, SINGLE_ENDED, BIPOLAR, RANGE10V);
  pinMode(IMET_TRIGGER_PIN, INPUT);
  
  //initialize all sensors to 0
  for(int i = 0; i < NUM_CHAN; i++){
    sensorValues[i] = 0;
  }
}


void loop() {
 while((digitalRead(IMET_TRIGGER_PIN)!=HIGH)){
}
  
  // put your main code here, to run repeatedly:
  for (int i = 0; i < NUM_CHAN; i++){
    sensorValues[i] = extendedADCShield.analogReadConfigNext((i+1)%8, SINGLE_ENDED, BIPOLAR, RANGE10V);//sensorValue*(5.0/1023.0);
  }
  
  chanList = ""; // clear chanList
  
  for(int i = 0; i < NUM_CHAN; i++){
   tempFloat = sensorValues[i];
   tempStr = String(tempFloat);
   tempStr= String(tempStr + ",");
   chanList += tempStr;  

  }

 Serial.print(chanList);

} 
