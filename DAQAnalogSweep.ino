/* Name: DAQAnalogSweep
 * Author: Matthew Miller
 * Description: Reads DAQ analog values and prints them on a Character LCD
 *    where row 1 prints the analog channel and row 2 prints the analog value of that channel
 * 
 */

#include <LiquidCrystal.h>
// change this number to the number of channels being sampled on the daq.
const int numDAQChan = 8;
// initialize the library with the required LCD interfaced pins.
const int rs = 12, en = 11, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
//initial sensor Value
int sensorValue = 0;
float sensorFloat = 0;
String sensorString;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
void setup() {
  lcd.begin(16,2);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < numDAQChan; i++){
    sensorValue = analogRead(i+14); //Analog channels start at pin 14
    sensorFloat = sensorValue*(5.0/1023.0);
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
