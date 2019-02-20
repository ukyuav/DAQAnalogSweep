
/* Name: DAQAnalogSweep
 * Author: Matthew Miller
 * Updates by Isaac Rowe
 * Description: Reads DAQ analog values and prints them on a Character LCD
 *    where row 1 prints the analog channel and row 2 prints the analog value of that channel
 * 
 */

#include <LiquidCrystal.h>
#include <ExtendedADCShield.h>
#include <SPI.h>

//Initialize the ADC Shield with default pins and 16-bit ADC (LTC1859)
ExtendedADCShield extendedADCShield(16);

float ch0;

// change this number to the number of channels being sampled on the daq.
const int numDAQChan = 8;
// initialize the library with the required LCD interfaced pins.
const int rs = 24, en = 25, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
//initial sensor Value
int sensorValue = 0;
float sensorFloat = 0;
String sensorString;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
void setup() {
  SPI.begin(); 
  lcd.begin(16,2);
  extendedADCShield.analogReadConfigNext(0, SINGLE_ENDED, BIPOLAR, RANGE10V);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  for(int i = 0; i < numDAQChan; i++){
    //sensorValue = analogRead(i+14); //Analog channels start at pin 14
    sensorFloat = extendedADCShield.analogReadConfigNext((i+1)%8, SINGLE_ENDED, BIPOLAR, RANGE10V);//sensorValue*(5.0/1023.0);
    sensorString = String(sensorFloat);
    
    lcd.clear();
    lcd.print("Channel ");
    lcd.print(i);

    //newline
    lcd.setCursor(0,1);
    lcd.print(sensorFloat);
    delay(1000);
  }

}
