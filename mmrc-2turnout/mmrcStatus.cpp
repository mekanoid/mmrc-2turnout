#include "Arduino.h"
#include "mmrcStatus.h"

mmrcStatus::mmrcStatus(byte pin) {
  // Use 'this->' to make the difference between the
  // 'pin' attribute of the class and the 
  // local variable 'pin' created from the parameter.
  this->pin = pin;
  init();
}

void mmrcStatus::init() {
  pinMode(pin, OUTPUT);
  // Always try to avoid duplicate code.
  // Instead of writing digitalWrite(pin, LOW) here,
  // call the function off() which already does that
  action = OFF;
}

void mmrcStatus::loop() {
  unsigned long currentMillis = millis();
  switch (action) {
    case OFF:
        digitalWrite(pin, LOW);
      break;
    case ON:
        digitalWrite(pin, HIGH);
      break;
    case BLINK:
      if(currentMillis - previousMillis > interval) {
        // Save the last time we blinked the LED 
        previousMillis = currentMillis;   
        // If the LED is off turn it on and vice-versa:
        if (state == 1) {
          digitalWrite(pin, HIGH);
          state = 0;
        } else {
          digitalWrite(pin, LOW);
          state = 1;
        }
      }
      break;
  }
}
    
    void mmrcStatus::on() {
      action = ON;
      if (debug == 1) {Serial.println(dbText+"Led pin"+pin+" ON");}
    }

    void mmrcStatus::off() {
      action = OFF;
      if (debug == 1) {Serial.println(dbText+"Led pin"+pin+" OFF");}
    }

    void mmrcStatus::blink(int time) {
      action = BLINK;
      this->interval = time;
      if (debug == 1) {Serial.println(dbText+"Led BLINK");}
    }

    boolean mmrcStatus::status() {
      if (debug == 1) {Serial.println(dbText+"Return status = "+action);}
      return action;
    }
