const int threshold = 100; // will change
const int PLAYGROUND_SIZE = 9;
// PINs for the first player (RED)
const int PLAYGROUND_LEDS_P1[PLAYGROUND_SIZE] = {
  10, 9, 8,
  7, 6, 5,
  4, 3, 2
};

//PINs for the second player (BLUE)
const int PLAYGROUND_LEDS_P2[PLAYGROUND_SIZE] = {
  40, 39, 38,
  37, 36, 35,
  34, 33, 32
};

const int PLAYGROUND_LECTURE[PLAYGROUND_SIZE] = {
  A0, A1, A2,
  A3, A4, A5,
  A6, A7, A8
};

/*
 * Player constants
*/
unsigned const int PLAYER_ONE = -1;
unsigned const int PLAYER_TWO = 1;
unsigned const int NO_PLAYER = 0;

int current_player = PLAYER_ONE;

/*
 * This is the place where moves are saved in ram
*/
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


void set_led(int pos, int player, bool s) {
  /*
   * I created this function so I can turn on/off every single LED I need without
   * messing the code too much. Tested in arduino emulator, should works in real life too
  */
  // TODO: check this function
  switch (player) {
    case PLAYER_ONE:
      digitalWrite(PLAYGROUND_LEDS_P1[pos], s);
      break;
    case PLAYER_TWO:
      digitalWrite(PLAYGROUND_LEDS_P2[pos], s);
      break;
  }
}

void set_led_all(int player, bool s) {
  /*
   * Light up all the leds in one time
  */
  for (size_t led = 0; led < PLAYGROUND_SIZE; led++) {
    set_led(led, player, s);
  }
}

int check_tris() {
  /*
   * This function will check whether is there any tris or not on the current playground.
   * It is called once between one move and the other. It basically will sums all the combinations together
   * from `COMBINATIONS` var and checks if any sum is -3 or 3.
  */
  unsigned int winner = NO_PLAYER;

  for (int i = 0; i < 8; i++) {
    /*
     * We get the current combinations from array
     * current should be an array btw using [] it returns an error
     * so fuck off the system I am not using that shit
     * using that shit it does not work either so fuck off
     * 
     * ok I am using this fucking line that works but it is a crap and I will
     * change it
    */
    unsigned const int *current[3] = {*COMBINATIONS[0], *COMBINATIONS[1], *COMBINATIONS[2]};
    // We sum up all the combinations in 'current' var
    unsigned int sum = *current[0] + *current[1] + *current[2];

    switch (sum) {
      case -3:
        winner = PLAYER_ONE;
        break;
      case 3:
        winner = PLAYER_TWO;
        break;
    }
  }

  return winner;
}


bool is_valid_move(size_t pos) {
  /*
   * Check whether the move is valid or not.
   * 
   * If the position is empty, we return true
   * otherwise, false
  */
  unsigned int current = playground[pos];
  return (current == NO_PLAYER);
}


int add_move(size_t pos, size_t player) {
  /*
   * We already know that the move is valid, so we can proceed to turn on the led
   * and save the move in memory
  */
  playground[pos] = player;
  set_led(pos, player, HIGH);
}


void win_animation(size_t player) {
  /*
   * This function will be called when a player wins a match.
  */
  Serial.print(player);
  Serial.println(" has won. Animation will start asap");

  for (size_t i = 0; i < 10; i++) {
    set_led_all(player, HIGH);
    delay(100 - (2 * i));
    set_led_all(player, LOW);
    delay(100 - (10 * i)); 
  }
  set_led_all(player, HIGH);
}

void setup() {
  // We first need to set the PINs to OUTPUT
  for (size_t i = 0; i < PLAYGROUND_SIZE; i++) {
    pinMode(PLAYGROUND_LEDS_P1[i], OUTPUT);
    pinMode(PLAYGROUND_LEDS_P2[i], OUTPUT);
    pinMode(PLAYGROUND_LECTURE[i], OUTPUT);
  }

  // Debugging log
  Serial.begin(9600);
}


void loop() {
  /*
  set_led_all(PLAYER_ONE, HIGH);
  set_led_all(PLAYER_TWO, HIGH);
  //win_animation(PLAYER_ONE);
  //in_animation(PLAYER_TWO);
  
  for (size_t i = 0; i < 9; i++) {
    set_led(i, PLAYER_ONE, HIGH);
  }
  Serial.println("Rosso");
  delay(1000);
  for (size_t i = 0; i < 9; i++) {
    set_led(i, PLAYER_ONE, LOW);
  }

  for (size_t i = 0; i < 9; i++) {
    set_led(i, PLAYER_TWO, HIGH);
  }
  Serial.println("Blu");
  delay(1000);
  for (size_t i = 0; i < 9; i++) {
    set_led(i, PLAYER_TWO, LOW);
  }*/
  
  for (size_t analog = 0; analog < 9; analog++) {
    size_t value = analogRead(PLAYGROUND_LECTURE[analog]);
    if (value >= threshold) {
      if (is_valid_move(analog)) {
        /*
         * We detected that someone wants to add a move
         * We detected that the move is valid, it means that the desired
         * box is empty, so we can proceed to save the new move and turn the led on
        */
        add_move(analog, current_player);
      }
    }
  }

  int tris_result = check_tris();
  switch (tris_result) {
    case NO_PLAYER:
      /*
       * Nobody won, do nothing
      */
      break;
    case PLAYER_ONE:
    case PLAYER_TWO:
      /*
       * Someone has won, launch animation and exit the program
      */
      win_animation(tris_result);
      //EXIT
      break;
  }
}
