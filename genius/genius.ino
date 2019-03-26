#define RED_LED 2

void setup() {
  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT); // OUTPUT -> 1; INPUT -> 0;
}

void loop() {
  blinkLed(RED_LED);
}

void blinkLed(int ledNumber) {
  digitalWrite(ledNumber, HIGH);// HIGH -> 1; LOW -> 0;
  delay(1000);
  digitalWrite(ledNumber, LOW);
  delay(500);
}
