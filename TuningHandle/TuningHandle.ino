/*
* The circuit:
*
* LCD: [VSS, VDD, V0, RS,   R, E, D4, D5, D6, D7,    A,    K ]
*      [GND, 5V,  1V,  9, GND, 8,  7,  6,  5,  4, 3.3V,  GND ]
* LCD V0 to ground via 1-10k resistor (contrast)
*
* Handle:
*  - potard to A0
*  - sw1 to D11
*  - sw2 to D12 (optional)
*  - push to D2
*
*/
#define LCD_RS 9
#define LCD_E 8
#define LCD_D4 7
#define LCD_D5 6
#define LCD_D6 5
#define LCD_D7 4

#define PIN_Variator 0
#define PIN_Switch 11
#define PIN_Switch2 12
#define PIN_PushButton 2

#include <LiquidCrystal.h>
#include "TuningHandle.h"
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
TuningHandle th(PIN_Variator, PIN_PushButton, 4, HIGH);

void setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0, 0);
  lcd.print("I am Handle !");
  delay(1000);
  th.activate();
}

void loop()
{
  printVal()
  delay(100);
}

void printVal(float v, float vmax, float vmin)
{
  lcd.setCursor(0, 0);
  lcd.print("Min: " + String(vmin, 2) + " Max: " + String(vmax, 2));
  lcd.setCursor(0, 1);
  lcd.print("Val= " + String(v));
}
