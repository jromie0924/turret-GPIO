String x;
void setup() {
 Serial.begin(115200);
 Serial.setTimeout(1);
}
void loop() {
 while (!Serial.available());
 x = Serial.readString();
// Serial.print("(" + x + ")");
// delay(10);
}
