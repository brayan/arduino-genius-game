#define RED_LED 2
#define YELLOW_LED 3
#define GREEN_LED 4

#define RED_BUTTON 10
#define YELLOW_BUTTON 9
#define GREEN_BUTTON 8

#define POTENTIOMETER 8

#define SEQUENCE_SIZE 3

#define UNDEFINED -1

#define INITIAL_LED_PIN 2
#define FINAL_LED_PIN 4

enum States {
    READY_FOR_NEXT_ROUND,
    USER_IS_RESPONDING,
    GAME_FINISHED_WITH_SUCCESS,
    GAME_FINISHED_WITH_FAILURE
};

int ledSequence[SEQUENCE_SIZE];
int gameRound = 0;
int ledsAnswered = 0;

void setup() {
    Serial.begin(9600);
    initPins();
    startGame();
}

void loop() {
    switch (getCurrentState()) {
        case READY_FOR_NEXT_ROUND:
            log("READY_FOR_NEXT_ROUND");
            startNewRound();
            break;

        case USER_IS_RESPONDING:
            log("USER_IS_RESPONDING");
            handleUserResponse();
            break;

        case GAME_FINISHED_WITH_SUCCESS:
            log("GAME_FINISHED_WITH_SUCCESS");
            blinkSequence2();
            break;

        case GAME_FINISHED_WITH_FAILURE:
            log("GAME_FINISHED_WITH_FAILURE");
            blinkLed(RED_LED);
            break;

        default:
            break;
    }
}

void startNewRound() {
    ledsAnswered = 0;
    gameRound++;

    if (gameRound <= SEQUENCE_SIZE) {
        blinkLeds();
    }
}

void handleUserResponse() {
    int response = checkAnsware();
    Serial.println(response);
    Serial.println(ledsAnswered);

    if (response == UNDEFINED) {
        return;
    }

    if (response == ledSequence[ledsAnswered]) {
        ledsAnswered++;
    } else {
        log("Wrong!!!!!!!!!!");
        gameRound = SEQUENCE_SIZE + 2;
    }
}

int getCurrentState() {
    if (gameRound <= SEQUENCE_SIZE) {
        if (ledsAnswered == gameRound) {
            return READY_FOR_NEXT_ROUND;
        } else {
            return USER_IS_RESPONDING;
        }

    } else if (gameRound == (SEQUENCE_SIZE + 1)){
        return GAME_FINISHED_WITH_SUCCESS;

    } else {
        return GAME_FINISHED_WITH_FAILURE;
    }
}

int checkAnsware() {
    if (digitalRead(RED_BUTTON) == LOW) {
        log("RED_BUTTON");
        blinkLed(RED_LED);
        return RED_LED;
    }

    if (digitalRead(YELLOW_BUTTON) == LOW) {
        log("YELLOW_BUTTON");
        blinkLed(YELLOW_LED);
        return YELLOW_LED;
    }

    if (digitalRead(GREEN_BUTTON) == LOW) {
        log("GREEN_BUTTON");
        blinkLed(GREEN_LED);
        return GREEN_LED;
    }

    return UNDEFINED;
}

void startGame() {
    randomSeed(analogRead(0));
    for (int i = 0; i < SEQUENCE_SIZE; i++) {
        ledSequence[i] = getRandomLed();
    }
}

int getRandomLed() { return random(INITIAL_LED_PIN, FINAL_LED_PIN + 1); }

void blinkSequence1() {
    blinkLed(RED_LED);
    blinkLed(YELLOW_LED);
    blinkLed(GREEN_LED);
}

void blinkSequence2() {
    digitalWrite(GREEN_LED, HIGH);  // HIGH -> 1; LOW -> 0;
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(RED_LED, HIGH);
    delay(1000);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);
    delay(500);
}

void blinkLeds() {
    for (int i = 0; i < gameRound; i++) {
        digitalWrite(ledSequence[i], HIGH);
        delay(1000);
        digitalWrite(ledSequence[i], LOW);
        delay(500);
    }
}

void initPins() {
    pinMode(GREEN_LED, OUTPUT);  // OUTPUT -> 1; INPUT -> 0;
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(RED_BUTTON, INPUT_PULLUP);
    pinMode(GREEN_BUTTON, INPUT_PULLUP);
    pinMode(YELLOW_BUTTON, INPUT_PULLUP);
}

int blinkLed(int ledNumber) {
    digitalWrite(ledNumber, HIGH);  // HIGH -> 1; LOW -> 0;
    delay(1000);
    digitalWrite(ledNumber, LOW);
    delay(500);
    return ledNumber;
}

void log(String text) { Serial.println(text); }
