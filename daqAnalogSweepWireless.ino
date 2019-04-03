/* Name: DAQAnalogSweep
 * Author: Matthew Miller
 * Description: Reads all 8 DAQ channels, sends data over serial as an array of 8 floats. 
 */

 #include <ExtendedADCShield.h>
 #include <SPI.h>

 //Union of float and byte array; used to send floats over serial.
typedef union {
  float floatingPoint;
  byte binary[4];
} binaryFloat;

const int numDAQChan = 8;

//array of binaryFloats for all daq channels. Stores sample for exactly 1 DAQ sweep.
binaryFloat sensorValue[numDAQChan];  

 //Initialize ADC Shield with default pins and 16-bit ADC (LTC1959)
 ExtendedADCShield extendedADCShield(16);


 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  extendedADCShield.analogReadConfigNext(0, SINGLE_ENDED, BIPOLAR, RANGE10V);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < numDAQChan; i++){
    sensorValue[i].floatingPoint = extendedADCShield.analogReadConfigNext((i+1)%8, SINGLE_ENDED, BIPOLAR, RANGE10V);//sensorValue*(5.0/1023.0);
  }

  for (int i = 0; i < numDAQChan; i++){
    Serial.write(sensorValue[i].binary,4);
  }
  delay(5000);
} 
