#include "TuningHandle.h"


TuningHandle::TuningHandle(
	int pin_variator,
	int pin_push_button,
	float start_max_value,
	byte state_on)
{
	_pin_variator = pin_variator;
	_pin_push_button = pin_push_button;
  	pinMode(_pin_variator, INPUT);
	pinMode(_pin_push_button, INPUT_PULLUP);

	_value_start = start_max_value;
	_value_max = start_max_value;

	setStateOn(state_on);
}

// Singleton implementation
TuningHandle* TuningHandle::singleton = NULL;
TuningHandle* TuningHandle::getInstance(){
	return singleton;
}
TuningHandle* TuningHandle::createInstance(int pin_variator, int pin_push_button, float start_max_value, byte state_on){
	if(singleton){
		delete singleton;
	}
	singleton = new TuningHandle(pin_variator, pin_push_button, start_max_value, state_on);
	return singleton;
}

void TuningHandle::update(){
	Serial.println("TuningHandle>> update static");
	if(singleton){
		singleton->updateState();
	}
}

// Read the current value
void TuningHandle::updateValue(){
	// _value = _value_min + (_value_max-_value_min) * readRatio();
	_value = _value_max * readRatio();
}

// Center range on the current value
void TuningHandle::updateRange(){
	float ratio = readRatio();
	_value_max = _value / ratio;
}

// Update the TuningHandle state according to the push-button state change
void TuningHandle::updateState(){
	Serial.println("TuningHandle>> updateState");
	float new_state = digitalRead(_pin_push_button);
	if(_push_button_state != new_state){
		Serial.println("TuningHandle>> updateState - state change");
		_push_button_state = new_state;
		if(isOn()){
			Serial.println("TuningHandle>> updateState - ON");
			// on state change from OFF to ON, use the stored value to recenter the variator range
			if(_init){
				// except on the first time -> init value instead
				updateValue();
				_init=false;
			}else{
				updateRange();
			}
		}
		else{
			Serial.println("TuningHandle>> updateState - OFF");
			// on state change from ON to OFF, store the last value
			updateValue();
		}
	}
}

// Return the variator's current state (value in [1/1024; 1])
float TuningHandle::readRatio(){
	int analogV = analogRead(_pin_variator);
	analogV++;
	return ((float) analogV) / _analog_max;
}

// Attach interrupt to the push button
void TuningHandle::activate(){
	Serial.println("TuningHandle>> activate1");
	_activated=true;
	Serial.println("TuningHandle>> activate2");
	attachInterrupt(digitalPinToInterrupt(_pin_push_button), TuningHandle::update, CHANGE);
	Serial.println("TuningHandle>> activate3");
}

// Detach interrupt
void TuningHandle::deactivate(){
	_activated=false;
	detachInterrupt(digitalPinToInterrupt(_pin_variator));
}

// Define which state of the push-button shall be the active state
void TuningHandle::setStateOn(byte state){
	_push_button_state_on = state;
}

// Reset the value to the start value
void TuningHandle::resetValue(){
	_value_max = _value_start;
	_init = true;
}

// Get the latest value
float TuningHandle::getValue(){
	if(isOn() && isActivated()){
		updateValue();
	}
	return _value;
}

// Getter range value min
float TuningHandle::getMin(){
	return _value_min;
}
// Getter range value max
float TuningHandle::getMax(){
	return _value_max;
}

// Return true if the interrupt is attached
bool TuningHandle::isActivated(){
	return _activated;
}

// Return true if the state of the push-button match the defined ON-state
bool TuningHandle::isOn(){
	return _push_button_state == _push_button_state_on;
}

