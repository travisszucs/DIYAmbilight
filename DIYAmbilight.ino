const int delayTime = 2;
int colorBuffer[3] = {0}; // used to store old color data

// initialized on Arduino Uno power on
void setup() {
  Serial.begin(9600);   // enable Serial at 9600 bps
  delay(200);
}

// read values from Serial for port number and color value, then set values
void loop() {
  // initialize Serial buffer arrays full of 0s
  char serialBuffer_Pin[2] = "";
  char serialBuffer_Color[4] = "";

  int ledPin = 0;
  int ledColor = 0;
  while (Serial.available() < 4) {} // wait for atleast 5 bytes to be received

  Serial.readBytes(serialBuffer_Pin, 1); // read 1 byte from Serial into char array for Pin
  Serial.readBytes(serialBuffer_Color, 3); // similarly 3 bytes for color

  serialBuffer_Pin[1] = '\0';  // must add a terminator to each buffer manually for atoi
  serialBuffer_Color[3] = '\0';

  ledPin = atoi(serialBuffer_Pin); // convert char[] arrays to integers to be sent to LED driver via PWM
  ledColor = atoi(serialBuffer_Color);

  // fade the previous color to the current color
  for (int i = colorBuffer[ledPin]; i < ledColor; i++) {
    analogWrite(ledPin+9, i); // add 9 to LED pin as physical connections are pins 9-11
    delay(delayTime);
  }

  for (int i = colorBuffer[ledPin]; i > ledColor; i--) {
    analogWrite(ledPin+9, i);
    delay(delayTime);
  }

  colorBuffer[ledPin] = ledColor;
}
