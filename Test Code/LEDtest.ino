// Test program for Arduino Uno and LED Strip connections

// constants for programs
int delayTime = 5
;

// constants for Arduino Uno output pins
#define BLUEPIN  9
#define REDPIN   10
#define GREENPIN 11

// initialized on Arduino Uno power on
void setup() {
  // no setup required as pinMode is not required for analogWrite
}

// cycle through available colors on LED strip
void loop() {
  // max value to be written to PWM pins
  int maxValue = 255;
  
  // ensure all pins are 0
  analogWrite(REDPIN,0);
  analogWrite(BLUEPIN,0);
  analogWrite(GREENPIN,0);
  
  for (int x = 0; x <= maxValue; x++){
    analogWrite(REDPIN,x);
    delay(delayTime);
  }
  for (int x = maxValue; x >= maxValue; x--) {
      analogWrite(REDPIN,x);
      delay(delayTime);
  }
 for (int x = 0; x <= maxValue; x++){
    analogWrite(BLUEPIN,x);
    delay(delayTime);
  }
  for (int x = maxValue; x >= maxValue; x--) {
      analogWrite(BLUEPIN,x);
      delay(delayTime);
  }
 for (int x = 0; x <= maxValue; x++){
    analogWrite(GREENPIN,x);
    delay(delayTime);
  }
  for (int x = maxValue; x >= maxValue; x--) {
      analogWrite(GREENPIN,x);
      delay(delayTime);
  } 
}
