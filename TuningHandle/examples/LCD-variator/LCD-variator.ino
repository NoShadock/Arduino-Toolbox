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
TuningHandle* th = TuningHandle::createInstance(PIN_Variator, PIN_PushButton, 4, LOW);
float v=-1.0, mx=-1.0, mn=-1.0;

void setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0, 0);
  lcd.print("I am Handle !");

  Serial.begin(9600);
  
  delay(1000);
  Serial.println("Setup 1-step to done.");
  th->activate();

  Serial.print("Setup ");
  printState(th);
  Serial.println();
  Serial.println("Setup done.");
}

void loop()
{
  Serial.println("Loop1 Button="+String(digitalRead(PIN_PushButton))+" Vario="+analogRead(PIN_Variator));

  Serial.print("Loop2 ");
  printState(th);
  Serial.println();
  delay(1000);
}

void printState(TuningHandle* th)
{
   Serial.println("["+String(th->getMin())+", "+String(th->getValue())+", "+String(th->getMax())+
    "] - act="+String(th->isActivated())+", on="+String(th->isOn()));
  lcd.setCursor(0, 0);
  lcd.print(String(th->getMin(), 0) + "        " + String(th->getMax(), 3));
  lcd.setCursor(0, 1);
  lcd.print("Val=  " + String(th->getValue(), 4));
}
