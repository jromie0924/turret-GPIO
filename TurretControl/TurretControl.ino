#include <Servo.h>

#define BUF_SIZE 8
#define TIMEOUT 500
#define TRUE_LEFT 900
#define TRUE_RIGHT 2100
#define CENTER 1500
#define RIGHT 1773
#define LEFT 1227
#define ONE_DEGREE 7
#define X_PIN 5
#define X_PIXELS 640.0
#define Y_PIXELS 470.0
#define FOV 78.0
#define ZERO_DEGREES 51
#define MAX_DEGREES 129

// FOV: 78 degrees: 39 degrees left or right.
// Or 39 degrees center.

Servo xServo;

int pos = CENTER;

void setup() {
  xServo.attach(X_PIN, LEFT, RIGHT);
  xServo.writeMicroseconds(CENTER);
  delay(1000);
  Serial.begin(57600);
}

void loop() {
  char buf[BUF_SIZE];
  unsigned long timeout = millis() + TIMEOUT;
  uint8_t inIdx = 0;
  bool received = false;
  while (((uint32_t)(millis() - timeout) > 0) && (inIdx < (sizeof(buf)/sizeof(buf[0])))) {
    if (Serial.available() > 0) {
      received = true;
      char c = Serial.read();
      if (c == 'x') {
        break;
      }
      buf[inIdx++] = c;
    }
  }
  if (received) {
    int xCoord = atoi(buf);
    if (xCoord > 0) {
      xServoMove(xCoord);
    }
  }
}

void xServoMove(int coord) {
  float fovFraction = coord / X_PIXELS;
  float degreeMovementFromZero = fovFraction * FOV;
  int positionDegrees = ZERO_DEGREES + (int)degreeMovementFromZero;
  int microseconds = (positionDegrees * ONE_DEGREE) + TRUE_LEFT;
  if (microseconds >= LEFT && microseconds <= RIGHT) {
    xServo.writeMicroseconds(microseconds);
  }
}