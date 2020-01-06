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

typedef void (* SecurityLightStateChangeCallback)(uint8_t pin, bool lightOn);

class SecurityLight {
	private:
		/**
		 * The GPIO pin to which the SecurityLight is attached.
		 */
		uint8_t pin;

		/**
		 * Callback that is used to report changes in the light state.
		 */
		SecurityLightStateChangeCallback stateChangeCallback;

		/**
		 * The current state of the SecurityLight.
		 */
		SecurityLightState state;

		/**
		 * The internal state machine that controls the SecurityLight.
		 */
		void stateMachine(SecurityLightEvent event);

	public:
		/**
		 * Creates a new SecurityLight object.
		 */
		SecurityLight(uint8_t pin, SecurityLightStateChangeCallback stateChangeCallback);

		/**
		 * Enable motion-detection mode.
		 */
		void enableModect();

		/**
		 * Disables motion-detection mode.
		 */
		void disableModect();

		/**
		 * Turn the security light on with reason 'motion detected'.
		 */
		void setModectOn();

		/**
		 * Turn the security light off with reason 'no motion detected'.
		 */
		void setModectOff();

		/**
		 * Turn the manual override of the security light on.
		 */
		void setManualOn();

		/**
		 * Turn the manual override of the security light off.
		 */
		void setManualOff();

		/**
		 * Get the pin to which the SecurityLight is attached.
		 */
		uint8_t getPin();

		/**
		 * Trigger an immediate invocation of the SecurityLight callback with
		 * the current state of the light.
		 */
		void reportStatus();
};

#endif /* SECURITY_LIGHT_H */
