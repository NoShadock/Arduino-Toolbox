#include "TuningHandle.h"
#include <Arduino.h>


TuningHandle::TuningHandle(
	int pin_variator,
	int pin_push_button,
	float start_value,
	char state_on)
{
	_pin_variator = pin_variator;
	_pin_push_button = pin_push_button;
	_value_start = start_value;
	_value = start_value;

	setStateOn(state_on);
}

// Read the current value
void TuningHandle::updateValue(){
	_value = _value_min + (_value_max-_value_min) * readRatio();
}

// Center range on the current value
void TuningHandle::updateRange(){
	_value_max = _value / readRatio;
	_value_min = _value * readRatio;
}

// Update the TuningHandle state according to the push-button state change
void TuningHandle::updateState(){
	new_state = digitalRead(_pin_push_button);
	if(_push_button_state != new_state){
		_push_button_state = new_state;
		if(isOn()){
			// on state change from OFF to ON, use the stored value to recenter the variator range
			updateRange();
		}
		else{
			// on state change from ON to OFF, store the last value
			updateValue();
		}
	}
}

// Return the variator's current state
float TuningHandle::readRatio(){
	return ((float) analogRead(_pin_variator)) / _analog_max;
}

// Attach interrupt to the push button
void TuningHandle::activate(){
	attachInterrupt(digitalPinToInterrupt(_pin_variator), updateState, CHANGE);
	_activated=true;
}

// Detach interrupt
void TuningHandle::deactivate(){
	detachInterrupt(digitalPinToInterrupt(_pin_variator));
	_activated=false;
}

// Define which state of the push-button shall be the active state
void TuningHandle::setStateOn(char state){
	_push_button_state_on = state;
}

// Reset the value to the start value
void TuningHandle::resetValue(){
	_value = _value_start;
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

