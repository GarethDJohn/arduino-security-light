#include "SecurityLight.h"

SecurityLight::SecurityLight(uint8_t pin, SecurityLightStateChangeCallback stateChangeCallback) {
	this->pin = pin;
	this->stateChangeCallback = stateChangeCallback;
	this->state = SecurityLightStateManualOff;

	pinMode(this->pin, OUTPUT);
}

void SecurityLight::stateMachine(SecurityLightEvent event) {
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
					this->stateChangeCallback(this->pin, true);
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
					this->stateChangeCallback(this->pin, false);
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
					this->stateChangeCallback(this->pin, true);
					break;
				case SecurityLightEventManualOff:
					break;
				case SecurityLightEventModectOn:
					digitalWrite(this->pin, HIGH);
					this->state = SecurityLightStateModectMotionOnManualOff;
					this->stateChangeCallback(this->pin, true);
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
					this->stateChangeCallback(this->pin, false);
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
					this->stateChangeCallback(this->pin, false);
					break;
				case SecurityLightEventModectOn:
					break;
				case SecurityLightEventModectOff:
					digitalWrite(this->pin, LOW);
					this->state = SecurityLightStateModectMotionOffManualOff;
					this->stateChangeCallback(this->pin, false);
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
				case SecurityLightEventModectOn:
					break;
				case SecurityLightEventModectOff:
					this->state = SecurityLightStateModectMotionOffManualOn;
					break;
			}
			break;
	}
}

void SecurityLight::enableModect() {
	this->stateMachine(SecurityLightEventEnableModect);
}

void SecurityLight::disableModect() {
	this->stateMachine(SecurityLightEventDisableModect);
}

void SecurityLight::setModect(bool modect) {
	if (modect) {
		this->stateMachine(SecurityLightEventModectOn);
	} else {
		this->stateMachine(SecurityLightEventModectOff);
	}
}

void SecurityLight::setManual(bool manual) {
	if (manual) {
		this->stateMachine(SecurityLightEventManualOn);
	} else {
		this->stateMachine(SecurityLightEventManualOff);
	}
}

uint8_t SecurityLight::getPin() {
	return this->pin;
}

void SecurityLight::reportStatus() {
	if (this->state == SecurityLightStateManualOn ||
	    this->state == SecurityLightStateModectMotionOffManualOn ||
		this->state == SecurityLightStateModectMotionOnManualOn) {
		this->stateChangeCallback(this->pin, true);
	} else {
		this->stateChangeCallback(this->pin, false);
	}
}
