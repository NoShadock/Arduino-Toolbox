/*
 * We want to measure Vin (0-30V).
 * 
 * The circuit:
 * 
 * R1, R2 serial resistors (10k and 1k Ohms)
 * R1 to +Vin and A
 * R2 to A and B
 * A is Analog pin 1
 * B is ground and -Vin
 * 
 * LCD VSS to ground
 * LCD VDD to 5V
 * LCD V0 to ground via 1-10k resistor (contrast)
 * LCD RS pin to digital pin 7
 * LCD R/W pin to ground
 * LCD Enable pin to digital pin 6
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD A to 3.3V (medium high brightness)
 * LCD K to ground
 *
 *
*/
#define R1 10000.0
#define R2 1000.0
#define analogInput 1

#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
float ratio = (R1+R2)/R2;

void setup() {
  pinMode(analogInput, INPUT);
  
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 1);
  // Print a message to the LCD.
  lcd.setCursor(0, 0);
  lcd.print("I am Voltmeter.");
  delay(1000);
  lcd.clear();
}


void loop() {
  // measure
  float Vin = (analogRead(analogInput) * 5.0) / 1024.0 * ratio;
  
  // display
  printVoltage(Vin);

  delay(500);
}

/**
 * Print the value on the LCD, nicely.
 */
void printVoltage(float instant){
  lcd.setCursor(0, 0);
  lcd.print("Vin= " + String(instant));
}
