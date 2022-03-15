#include<Servo.h>
#include<string.h>
#include <stdio.h>

#include "Coordinates.h"

#define LEFT 900
#define RIGHT 2100
#define CENTER 1500
#define ONE_DEGREE 7
#define X_PIN 5
#define PIXELS 320
#define BUFFER_SIZE 7

Servo xServo;

// FOV: 78 degrees: 39 degrees left or right.
// Frame: 320 x 320 px

int pos = CENTER;
char buf[BUFFER_SIZE];
void setup() {
  xServo.attach(X_PIN, LEFT, RIGHT);
  delay(500);

  Serial.begin(115200);
  Serial.setTimeout(1);
}
void loop() {
  while (!Serial.available());
//  int x = Serial.readString().toInt();
  int rlen = Serial.readBytes(buf, BUFFER_SIZE);
  for (int i = 0; i < rlen; ++i) {
    Serial.print(buf[i]);
  }
  Serial.print("\n");
  delay(10);

  int x = atoi(buf);

//  Coordinates coordinates = validateString(coords);
//  int x = coordinates.xCoord;

  int microseconds = (x / PIXELS) * RIGHT;
  if(microseconds >= LEFT) {
//    Serial.print(microseconds);
    Serial.print("\n");
    xServoWrite(microseconds);
  }
  memset(buf, 0, sizeof buf);
  delay(100);
}

Coordinates validateString(String str) {
  Coordinates coordinates = Coordinates();
  if (str != NULL) {
    int commaIdx = str.indexOf(",");
    if (commaIdx == -1) {
      return coordinates;
    }

    int xCoord = str.substring(0, commaIdx).toInt();
    int yCoord = str.substring(commaIdx+1).toInt();

    coordinates.xCoord = xCoord;
    coordinates.yCoord = yCoord;

    return coordinates;
  }
  return coordinates;
}

void xServoWrite(int ms) {
  xServo.writeMicroseconds(ms);
  // delay(10);
}
