const int PLAYGROUND_SIZE = 9;
// PINs for the first player (RED)
const int PLAYGROUND_LEDS_P1[PLAYGROUND_SIZE] = {
  10, 9, 8,
  7, 6, 5,
  4, 3, 2
};

/* PINs for the second player (BLUE), to add with ARDUINO Mega
const int PLAYGROUND_LEDS_P2[PLAYGROUND_SIZE] = {
  10, 9, 8,
  7, 6, 5,
  4, 3, 2
};*/

/*const int PLAYGROUND_LECTURE[PLAYGROUND_SIZE] = {
  A0, A1, A2,
  A3, A4, A5,
  A6, A7, A8
};*/

const int PLAYER_ONE = 1;
const int PLAYER_TWO = 2;
int playground[PLAYGROUND_SIZE] = {
  0, 0, 0,
  0, 0, 0,
  0, 0, 0
};

void set_led(int pos, int player, bool s) {
  // TODO: check this function
  switch (player) {
    case PLAYER_ONE:
      digitalWrite(PLAYGROUND_LEDS_P1[pos], s);
      break;
    case PLAYER_TWO:
      //digitalWrite(PLAYGROUND_LEDS_P2[pos], s);
      break;
  }
}

void setup() {
  // We first need to set the PINs to OUTPUT
  for (int i = 0; i < PLAYGROUND_SIZE; i++) {
    pinMode(PLAYGROUND_LEDS_P1[i], OUTPUT);
    //pinMode(PLAYGROUND_LEDS_P2[i], OUTPUT);
    //pinMode(PLAYGROUND_LECTURE[i], OUTPUT);
  }

  // Debugging log
  Serial.begin(9600);
}

void loop() {
  set_led(0, PLAYER_ONE, HIGH);
  delay(1000);
  set_led(0, PLAYER_ONE, LOW);
  delay(1000);
}
