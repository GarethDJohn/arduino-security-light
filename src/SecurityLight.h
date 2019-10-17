#ifndef SECURITY_LIGHT_H
#define SECURITY_LIGHT_H

#include "Arduino.h"

enum SecurityLightState {
	SecurityLightStateManualOff,
	SecurityLightStateManualOn,
	SecurityLightStateModectMotionOffManualOff,
	SecurityLightStateModectMotionOffManualOn,
	SecurityLightStateModectMotionOnManualOff,
	SecurityLightStateModectMotionOnManualOn
};

enum SecurityLightEvent {
	SecurityLightEventEnableModect,
	SecurityLightEventDisableModect,
	SecurityLightEventManualOn,
	SecurityLightEventManualOff,
	SecurityLightEventModectOn,
	SecurityLightEventModectOff
};

typedef void (* SecurityLightStateChangeCallback)(uint8_t pin, bool light_on);

class SecurityLight {
	private:
		uint8_t pin;
		SecurityLightStateChangeCallback state_change_callback;

		SecurityLightState state;

	public:
		SecurityLight(uint8_t pin, SecurityLightStateChangeCallback state_change_callback);

		void state_machine(SecurityLightEvent event);

		uint8_t get_pin();
};

#endif /* SECURITY_LIGHT_H */
