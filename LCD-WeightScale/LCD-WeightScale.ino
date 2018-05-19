/*
 * The circuit:
 * LCD: [VSS, VDD, V0, RS,   R, E, D4, D5, D6, D7,    A,    K ]
 *      [GND, 5V,  1V,  9, GND, 8,  7,  6,  5,  4, 3.3V,  GND ]
 * LCD V0 to ground via 1-10k resistor (contrast)
 *
 * HX711 GND to ground
 * HX711 DouT to digital pin 10
 * HX711 PD_SCK to digital pin 11
 * HX711 VCC to 5V
 *
 *
*/

#include <Wire.h>
#include "HX711.h"
#include <LiquidCrystal.h>

#define NB_ECHANTILLON 5

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(9,8,7,6,5,4);
HX711 scale(10, 11); // HX711.DOUT = GPIO10 / HX711.PD_SCK = GPIO11

unsigned int index_moyenne=0;

float resultat[NB_ECHANTILLON];


void setup() {

  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0, 0);
  lcd.print("hello !");

  // ?
  scale.read();
  yield();  // Redonne la main à l'ESP8266

  /*
   * Le nombre ci dessous permet de calibrer la balance. Pour l'obtenir, voir le fichier README de la bibliothèque HX711
   */
  scale.set_scale(-20950.0);
  scale.tare();
  yield();

  delay(1000);
  printWeight(0, 0);

}


void loop() {

  // measure
  float poids,total;
  unsigned int n;

  poids=scale.get_units(10);

  resultat[index_moyenne++]=poids;
  index_moyenne %= NB_ECHANTILLON;

  total=0;
  for(n=0;n<NB_ECHANTILLON;n++){
    total+=resultat[n];
  }

  // display
  printWeight(poids, total/NB_ECHANTILLON);

  delay(50);
}


void printWeight(float instant, float avg){
  lcd.setCursor(0, 0);
  lcd.print("Weight: " + String(instant));
  lcd.setCursor(0, 1);
  lcd.print("Average: " + String(avg));
}
