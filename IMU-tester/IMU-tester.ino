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
#include <LiquidCrystal.h>
#include <TimedAction.h>

// choose an IMU board
// #include "Sparkfun6DOF.h"
// IMUmanager imu = Sparkfun6DOF();
#include "LSM9DS0_9DOF.h"
LSM9DS0_9DOF imu = LSM9DS0_9DOF();

// initialize the lcd with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
float tilt = 0.0f;


// define actions
void measureTilt();
void printTilt();
TimedAction measure = TimedAction(50, measureTilt);
TimedAction display = TimedAction(500, printTilt);


void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0, 0);
  lcd.print("I am Tiltmeter.");

  // init IMU
  imu.init();
  // yaw=0 pitch=1 roll=2
  imu.setAxis(1);

  delay(1000);
  lcd.clear();
}


void loop() {
  // measure
  measure.check();
  // display
  display.check();

  delay(10);
}


/**
 * Refresh tilt measure
 */
void measureTilt(){
 tilt = imu.getTilt();
}

/**
 * Print the value on the LCD, nicely.
 */
void printTilt(){
  lcd.setCursor(0, 0);
  lcd.print("Tilt= " + String(tilt));
}

























