#define RED_LED 2
#define YELLOW_LED 3
#define GREEN_LED 4

#define SEQUENCE_SIZE 3

int ledSequence[SEQUENCE_SIZE];

void setup() {
  Serial.begin(9600);
  initPins();
  startGame();
}

void loop() {
   blinkSequence3();
}

void startGame() {
  ledSequence[0] = RED_LED;
  ledSequence[1] = YELLOW_LED;
  ledSequence[2] = GREEN_LED;
}

void blinkSequence1() {
   blinkLed(RED_LED);
   blinkLed(YELLOW_LED);
   blinkLed(GREEN_LED);
}

void blinkSequence2() {
   digitalWrite(GREEN_LED, HIGH);
   digitalWrite(YELLOW_LED, HIGH);
   digitalWrite(RED_LED, HIGH);
   delay(1000);
   digitalWrite(GREEN_LED, LOW);
   digitalWrite(YELLOW_LED, LOW);
   digitalWrite(RED_LED, LOW);
   delay(500);
}

void blinkSequence3() {
   for (int i = 0; i < SEQUENCE_SIZE; i++) {
      digitalWrite(ledSequence[i], HIGH);
      delay(1000);
      digitalWrite(ledSequence[i], LOW);
      delay(500);
   }
}

void initPins() {
  pinMode(GREEN_LED, OUTPUT); // OUTPUT -> 1; INPUT -> 0;
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
}

void blinkLed(int ledNumber) {
  digitalWrite(ledNumber, HIGH);// HIGH -> 1; LOW -> 0;
  delay(1000);
  digitalWrite(ledNumber, LOW);
  delay(500);
}
