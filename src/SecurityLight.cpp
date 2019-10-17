#include "SecurityLight.h"

SecurityLight::SecurityLight(uint8_t pin, SecurityLightStateChangeCallback state_change_callback) {
	this->pin = pin;
	this->state_change_callback = state_change_callback;

	this->state = SecurityLightStateManualOff;

	pinMode(this->pin, OUTPUT);
}

void SecurityLight::state_machine(SecurityLightEvent event) {
	switch (this->state) {
		case SecurityLightStateManualOff:
			switch (event) {
				case SecurityLightEventEnableModect:
					this->state = SecurityLightStateModectMotionOffManualOff;
					break;
				case SecurityLightEventDisableModect:
					break;
				case SecurityLightEventManualOn:
					digitalWrite(this->pin, HIGH);
					this->state = SecurityLightStateManualOn;
					this->state_change_callback(this->pin, true);
					break;
				case SecurityLightEventManualOff:
					break;
				case SecurityLightEventModectOn:
					break;
				case SecurityLightEventModectOff:
					break;
			}
			break;
		case SecurityLightStateManualOn:
			switch (event) {
				case SecurityLightEventEnableModect:
					this->state = SecurityLightStateModectMotionOffManualOn;
					break;
				case SecurityLightEventDisableModect:
					break;
				case SecurityLightEventManualOn:
					break;
				case SecurityLightEventManualOff:
					digitalWrite(this->pin, LOW);
					this->state = SecurityLightStateManualOff;
					this->state_change_callback(this->pin, false);
					break;
				case SecurityLightEventModectOn:
					break;
				case SecurityLightEventModectOff:
					break;
			}
			break;
		case SecurityLightStateModectMotionOffManualOff:
			switch (event) {
				case SecurityLightEventEnableModect:
					break;
				case SecurityLightEventDisableModect:
					this->state = SecurityLightStateManualOff;
					break;
				case SecurityLightEventManualOn:
					digitalWrite(this->pin, HIGH);
					this->state = SecurityLightStateModectMotionOffManualOn;
					this->state_change_callback(this->pin, true);
					break;
				case SecurityLightEventManualOff:
					break;
				case SecurityLightEventModectOn:
					digitalWrite(this->pin, HIGH);
					this->state = SecurityLightStateModectMotionOnManualOff;
					this->state_change_callback(this->pin, true);
					break;
				case SecurityLightEventModectOff:
					break;
			}
			break;
		case SecurityLightStateModectMotionOffManualOn:
			switch (event) {
				case SecurityLightEventEnableModect:
					break;
				case SecurityLightEventDisableModect:
					this->state = SecurityLightStateManualOn;
					break;
				case SecurityLightEventManualOn:
					break;
				case SecurityLightEventManualOff:
					digitalWrite(this->pin, LOW);
					this->state = SecurityLightStateModectMotionOffManualOff;
					this->state_change_callback(this->pin, false);
					break;
				case SecurityLightEventModectOn:
					this->state = SecurityLightStateModectMotionOnManualOn;
					break;
				case SecurityLightEventModectOff:
					break;
			}
			break;
		case SecurityLightStateModectMotionOnManualOff:
			switch (event) {
				case SecurityLightEventEnableModect:
					break;
				case SecurityLightEventDisableModect:
					break;
				case SecurityLightEventManualOn:
					this->state = SecurityLightStateModectMotionOnManualOn;
					break;
				case SecurityLightEventManualOff:
					digitalWrite(this->pin, LOW);
					this->state = SecurityLightStateModectMotionOffManualOff;
					this->state_change_callback(this->pin, false);
					break;
				case SecurityLightEventModectOn:
					break;
				case SecurityLightEventModectOff:
					digitalWrite(this->pin, LOW);
					this->state = SecurityLightStateModectMotionOffManualOff;
					this->state_change_callback(this->pin, false);
					break;
			}
			break;
		case SecurityLightStateModectMotionOnManualOn:
			switch (event) {
				case SecurityLightEventEnableModect:
					break;
				case SecurityLightEventDisableModect:
					this->state = SecurityLightStateManualOn;
					break;
				case SecurityLightEventManualOn:
					break;
				case SecurityLightEventManualOff:
					this->state = SecurityLightStateModectMotionOnManualOff;
					break;
				case SecurityLightEventModectOn:
					break;
				case SecurityLightEventModectOff:
					this->state = SecurityLightStateModectMotionOffManualOn;
					break;
			}
			break;
	}
}

uint8_t SecurityLight::get_pin() {
	return this->pin;
}
