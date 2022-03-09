String coords;
void setup() {
 Serial.begin(115200);
 Serial.setTimeout(1);

 pinMode(LED_BUILTIN, OUTPUT);
 digitalWrite(LED_BUILTIN, LOW);
}
void loop() {
 while (!Serial.available());
 coords = Serial.readString();
 delay(10);
}
