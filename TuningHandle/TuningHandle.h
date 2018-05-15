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
 *  Thus alternating ON and OFF states can be used to glide the value range until the desired value is accessible.
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

class TuningHandle {

	private:
		int _pin_variator;
		int _pin_push_button;

		bool _activated;
		char _push_button_state;
		char _push_button_state_on;

		float _value_start;
		float _value_min;
		float _value_max;
		float _value;

		float _analog_max = 1023.0f;
		void updateValue();
		void updateRange();
		void updateState();
		float readRatio();

	public:
		TuningHandle(int pin_variator, int pin_push_button, float start_value, char state_on=HIGH);
		void activate();
		void deactivate();
		void setStateOn(char state);
		void resetValue();
		float getValue();
		float getMin();
		float getMax();
		bool isActivated();
		bool isOn();

}

