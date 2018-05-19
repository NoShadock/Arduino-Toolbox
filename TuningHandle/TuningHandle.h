/**
 * Tuning Handle - a bundle of analog inputs for easy manual parameters tweaking
 *
 * version: 1.0.0
 * date: 2018-05-15
 * author: NoShadock
 *
 *
 * The circuit:
 *   - push button to an interrupt digital pin
 *   - variable resistor to an analog pin
 *
 * Usage:
 *	The tool is used to find experimentally an optimal value for a numerical parameter(float).
 *	When activated, the button state changes (UP/DOWN) are watched:
 * 	  - the variator changes change the value when the button is pushed (powered ON).
 *    - the variator changes do not affect the value when the button is at rest (powered OFF).
 *    - when re-powered ON the range is recentered on the value: bottom stays 0, and top is
 *		updated to fit the variator state.
 *  Thus alternating ON and OFF states can be used to zoom in and out the window until the
 *  desired value is in range.
 *
 *
 * Example:
 *
 * TuningHandle th(PIN_V, PIN_PB, 3.0, HIGH);
 * th.activate();
 * loop(){
 *   if(th.isOn()){
 *     value = th.getValue();
 *     // use the evolving value 
 *   }
 * }
 *
 */
#include <Arduino.h>

class TuningHandle {

	private:
		static void update();
		static TuningHandle* singleton;

		int _pin_variator;
		int _pin_push_button;

		bool _init = true;
		bool _activated;
		volatile byte _push_button_state;
		byte _push_button_state_on;

		float _value_start;
		volatile const float _value_min = 0.0f;
		volatile float _value_max;
		volatile float _value = 0.0f;

		float _analog_max = 1024.0f;
		void updateValue();
		void updateRange();
		void updateState();
		float readRatio();
		TuningHandle(int pin_variator, int pin_push_button, float start_max_value, byte state_on=HIGH);

	public:
		static TuningHandle* createInstance(int pin_variator, int pin_push_button, float start_max_value, byte state_on=HIGH);
		static TuningHandle* getInstance();
		void activate();
		void deactivate();
		void setStateOn(byte state);
		void reset();
		void setValue(float);
		float getValue();
		float getMin();
		float getMax();
		bool isActivated();
		bool isOn();
};

