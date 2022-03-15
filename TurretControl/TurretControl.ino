#include<Servo.h>
#include<string.h>
#include <stdio.h>

#include "Coordinates.h"

#define LEFT 900
#define RIGHT 2100
#define CENTER 1500
#define ONE_DEGREE 7
#define X_PIN 5

Servo xServo;

int pos = CENTER;
void setup() {
  xServo.attach(X_PIN, LEFT, RIGHT);
  delay(500);

  Serial.begin(115200);
  Serial.setTimeout(1);
}
void loop() {
  while (!Serial.available());
  String coords = Serial.readString();
  Serial.print(coords);
  Serial.print("\n");
  delay(10);

  Coordinates coordinates = validateString(coords);
  int x = coordinates.xCoord;
}

Coordinates validateString(String str) {
  Coordinates coordinates;
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

void xServoWrite(int x) {
  
}
