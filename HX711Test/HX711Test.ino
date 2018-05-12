#include <Wire.h>
#include "HX711.h"

#define NB_ECHANTILLON 10
unsigned int index_moyenne=0;

HX711 scale(10, 12); // HX711.DOUT = GPIO10 / HX711.PD_SCK = GPIO12

float resultat[NB_ECHANTILLON];

void setup() {
  Serial.begin(115200);
  Serial.println("Test HX711");

  scale.read();
  yield();  // Redonne la main à l'ESP8266

  /*
   * Le nombre ci dessous permet de calibrer la balance. Pour l'obtenir, voir le fichier README de la bibliothèque HX711
   */
  scale.set_scale(-20950.0);
  scale.tare();
  yield();
}

void loop() {
  float poids,total;
  unsigned int n;

  poids=scale.get_units(10);

  resultat[index_moyenne++]=poids;
  index_moyenne %= NB_ECHANTILLON;

  total=0;
  for(n=0;n<NB_ECHANTILLON;n++){
    total+=resultat[n];
  }
  Serial.print(poids);
  Serial.print("\t moyenne des 10 derniers poids = ");
  Serial.println(total/NB_ECHANTILLON, 2);
  delay(100);
}
