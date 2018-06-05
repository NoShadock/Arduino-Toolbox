#include <IBT2MotorsController.h>

IBT2MotorsController mc = IBT2MotorsController(5,6,10,11);
int s = 10;
int i = 100;

void setup(){
	mc.init();
}

void loop(){
	mc.go(i-100);
	i+=s;
	i%=200;
	delay(300);
}