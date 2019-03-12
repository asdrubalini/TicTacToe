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
};

const int PLAYGROUND_LECTURE[PLAYGROUND_SIZE] = {
  A0, A1, A2,
  A3, A4, A5,
  A6, A7, A8
};*/

const int PLAYER_ONE = -1;
const int PLAYER_TWO = 1;
int playground[PLAYGROUND_SIZE] = {
  0, 0, 0,
  0, 0, 0,
  0, 0, 0
};

/*
 * We declare every single combination for a 3x3 playground
 * Then, check_tris() will sum each element for every combination. If the
 * sum results -3, player one has won
 * otherwise, if the sum results 3, player two has won
 * In any other case, nobody has won and the game will continue
 * 
 * TODO: check this. I usually code in Python and I never worked with pointers before,
 * so I don't really know if a stuff like this could works.
 * 
 * I'm creating an array of array of pointers, each pointer points to a playground cell.
 * Theoretically, we could extract the value from the pointer using a code like this:
 * 
 * int *address = COMBINATIONS[0][0];   // Here we get the memory address
 *                  first row  ^  ^ first cell
 * int value = *address;
 * 
 * But I'm not sure... will try soon
 *               
*/
const int *COMBINATIONS[8][3] = {
  // Rows
  {&playground[0], &playground[1], &playground[2]},
  {&playground[3], &playground[4], &playground[5]},
  {&playground[6], &playground[7], &playground[8]},

  // Columns
  {&playground[0], &playground[3], &playground[6]},
  {&playground[1], &playground[4], &playground[7]},
  {&playground[2], &playground[5], &playground[8]},

  // Diagonals
  {&playground[0], &playground[4], &playground[8]},
  {&playground[2], &playground[4], &playground[6]}
};


/*
 * I created this function so I can turn on/off every single LED I need without
 * messing the code too much. Tested in arduino emulator, should works in real life too
*/
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

/*
 * This function will check whether is there any tris or not on the current playground.
 * It is called once between one move and the other. It basically will sums all the combinations together
 * from `COMBINATIONS` var and checks if any sum is -3 or 3.
*/
void check_tris() {
  
}

/*
 * This function will be called when a player wins a match.
*/
void win_animation() {
  
}

void setup() {
  // We first need to set the PINs to OUTPUT
  for (int i = 0; i < PLAYGROUND_SIZE; i++) {
    pinMode(PLAYGROUND_LEDS_P1[i], OUTPUT);
    // pinMode(PLAYGROUND_LEDS_P2[i], OUTPUT);
    // pinMode(PLAYGROUND_LECTURE[i], OUTPUT);
  }

  // Debugging log
  Serial.begin(9600);
}

void loop() {
  // LED test
  set_led(0, PLAYER_ONE, HIGH);
  delay(1000);
  set_led(0, PLAYER_ONE, LOW);
  delay(1000);
}
