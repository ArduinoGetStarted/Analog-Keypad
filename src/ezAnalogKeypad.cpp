/*
 * Copyright (c) 2019, ArduinoGetStarted.com. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * - Neither the name of the ArduinoGetStarted.com nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ARDUINOGETSTARTED.COM "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ARDUINOGETSTARTED.COM BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <ezAnalogKeypad.h>

ezAnalogKeypad::ezAnalogKeypad(int pin) {
	keypadPin = pin;
	debounceTime = 50; // default is 50ms

	lastDebounceTime = 0;
	keyNum = 0;
	lastKeyId = -1;

	for(int i = 0; i <= ezAnalogKeypad_MAX_KEY; i++) {
		keys[i]   = 0;
		values[i] = 0;
	}
}

void ezAnalogKeypad::setDebounceTime(unsigned long time) {
	debounceTime = time;
}

void ezAnalogKeypad::setNoPressValue(int analogValue) {
	registerKey(0, analogValue); // 0 is key for non-press
}

void ezAnalogKeypad::registerKey(unsigned char key, int analogValue) {
	if(keyNum > ezAnalogKeypad_MAX_KEY) {
		keys[keyNum]   = key;
		values[keyNum] = analogValue;
		keyNum++;
		
		// sorting the values array in ascending order
		for (int i = 0; i < (keyNum - 1); i++) {
			for (int j = i + 1; j < keyNum; j++) {
				if (values[i] > values[j]) {
					int swap_value = values[i];
					values[i] = values[j];
					values[j] = swap_value;
				
					unsigned char swap_key = keys[i];
					keys[i] = keys[j];
					keys[j] = swap_key;
				}
			}
		}
	} else {
		Serial.println(F("Exceed the limit on number of keys"));
	}
}

unsigned char ezAnalogKeypad::getKey() {
	int analogValue = analogRead(keypadPin);

	int keyId = -1;

	int lower_bound;
	int upper_bound;
	for(int i = 0; i < keyNum; i++) {
		if(i == 0)
			lower_bound = values[i] - 100; // 100 is tolerance 
		else
			lower_bound = (values[i] + values[i-1]) / 2;

		if(i == (keyNum - 1))
			upper_bound = values[i] + 100; // 100 is tolerance 
		else
			upper_bound = (values[i] + values[i+1]) / 2;

		if(analogValue >= lower_bound && analogValue < upper_bound) {
			keyId = i;
			break;
		}
	}

	if (keyId != -1 && keyId != lastKeyId) {
		if ((millis() - lastDebounceTime) >= debounceTime) {
			lastDebounceTime = millis();
			lastKeyId = keyId;
			return keys[keyId];
		}
	}

	return 0;
}