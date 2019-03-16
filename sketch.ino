/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * Code written by @unizLike (Giovanni Lena) and @Ferrar65 (Karim El Metkoul) (github)
 * https://github.com/unizLike/TicTacToe
 * https://github.com/unizLike/TicTacToe-CPP    (C++ version)
 * 
 * Contacts:
 * @unixlike.it @karim_elmet @informatica.it (instagram)
 * @756e69786c696b6 @Ferrar65 (twitter)
 * @unixLikee (telegram)
 * indirizzoemail@mail.com giovannilena@mail.com (email)
*/

#define PLAYGROUND_SIZE 9   // 3x3

/* 
 * We first create some custom types so we don't have to write
 * signed int every time. Just `cell` or `player` is enough and makes
 * the code way more readable from someone who doesn't know what the function or
 * the variable is supposed to do.
 * 
 * Per prima cosa creiamo alcuni tipi personalizzati, in questo modo
 * non abbiamo bisogno di scrivere signed int ogni volta. `cell` o `player` sono sufficienti e
 * rendono il codice molto più leggibile da qualcuno che non conosce l'utilizzo di una funzione
 * o di una variabile.
*/
typedef signed int cell;
typedef signed int player;

/*
 * Here we declare some constants. In memory, every player is saved as -1, 1 or 0.
 * With the aim to make the code more readable, in this code we are using constants like
 * PLAYER_ONE, PLAYER_TWO or NO_PLAYER.
 * 
 * Dichiariamo alcune costanti. In memoria, ogni giocatore è salvato come -1, 1 o 0.
 * Per rendere il codice più leggibile, in questo codice useremo costanti come
 * PLAYER_ONE, PLAYER_TWO o NO_PLAYER
*/
const cell PLAYER_ONE = -1;
const cell PLAYER_TWO = 1;
const cell NO_PLAYER = 0;

class TicTacToe {
private:
  /*
   * We first need to create and initialize the playground to empty.
   * Every single move will be saved in this array. 
   * This is private, it means that only the functions from this class
   * will be able to read and write on it.
   * 
   * Per prima cosa abbiamo bisogno di creare e inizializzare il campo di gioco come vuoto.
   * In questo array saranno salvate le mosse di ogni giocatore.
   * L'array è privato, il che significa che solo le funzioni in questa classe
   * saranno in grado di accedere ad esso.
  */
  cell playground[PLAYGROUND_SIZE] = {
    NO_PLAYER, NO_PLAYER, NO_PLAYER,
    NO_PLAYER, NO_PLAYER, NO_PLAYER,
    NO_PLAYER, NO_PLAYER, NO_PLAYER
  };

  /*
   * In this integer we memorize the total number of moves in the current game.
   * 
   * In questo intero memorizziamo il numero totale di mosse nel gioco corrente.
  */
  int moves = 0;
public:
  TicTacToe(int size) {
    
  }
  /*
   * All the combinations (which are 8) are hardcoded in this double-sized array.
   * Those integers are a playground[] indexes used by a bunch of function.
   * This is used by win_animation() function, so this is the reason why
   * this is public and not private.
   * 
   * Tutte le combinazioni (che sono 8) sono hardcodate in questo doppio array.
   * Questi interi sono degli indici per l'array playground[] usati da alcune funzioni.
   * Questo array viene usato dalla funzione win_animation(), ed è questo il motivo per cui
   * è stato dichiarato come pubblico e non privato.
  */
  int COMBINATIONS[8][3] = {
    // Rows
    {0, 1, 2},
    {3, 4, 5},
    {6, 7, 8},

    // Columns
    {0, 3, 6},
    {1, 4, 7},
    {2, 5, 8},

    // Diagonals
    {0, 4, 8},
    {2, 4, 6}
  };
  
  /*
   * Check whether or not someone won the game.
   * This should be called from one move and the following one.
   * 
   * Controlla se qualcuno ha vinto il gioco.
   * Questa funzione dovrebbe essere chiamata tra una mossa e l'altra.
  */
  player check_tris() {
    for (int i = 0; i < 8; i++) {
    int* combinations = COMBINATIONS[i];

    // Sum up all the combinations
    // Somma tutte le combinazioni
    int sum = 0;
    for (size_t i = 0; i < 3; i++) {
      sum += playground[combinations[i]];
    }

    switch (sum) {
      case -3:
        // Player one won, return it
        // Player uno ha vinto, ritornalo
        return PLAYER_ONE;
        break;
      case 3:
        // Player two won, return it
        // Player due ha vinto, ritornalo
        return PLAYER_TWO;
        break;
      }
    }

    // Nobody won. Return NO_PLAYER which is 0
    // Nessuno ha vinto. Ritorna NO_PLAYER che vale 0
    return NO_PLAYER;
  }
  
  /*
   * Check whether or not the game terminated in parity
   *  
   * Controlla se il gioco è terminato in parità
  */
  bool check_parity() {
    if (moves == 9 && check_tris() == NO_PLAYER) {
      return true;
    }

    return false;
  }
  
  /*
   * Check whether or not the desired move is valid.
   * Should be called before adding the move in memory
   * 
   * Controlla se la mossa desiderata è valida o no.
   * Questa funzione dovrebbe essere chiamata prima di aggiungere la mossa
   * in memoria
  */
  bool is_valid_move(int pos) {
    // Check if the required position is already taken or not
    signed int current = playground[pos];
    return (current == NO_PLAYER);
  }
  
  /*
   * Add the actual move in memory.
   * Please, call check_tris() and THEN add_move()
   * 
   * Aggiungi la mossa in memoria.
   * Per favore, chiama check_tris() e DOPO add_move()
  */
  void add_move(int pos, player player) {
    moves++;
    playground[pos] = player;
  }

   /*
   * When someone wins, we need to summon an animation.
   * This function is used to obtain the winner combination.
   * Note that this function should be called only when there is a winner,
   * otherwise it will return 0 causing a bug
   * 
   * Quando qualcuno vince, dobbiamo mostrare un'animazione.
   * Questa funzione è usata per ottenere la combinazione vincente.
   * Nota che questa funzione dovrebbe essere chiamata solamente quando c'è un vincitore,
   * altrimenti ritornerà zero cusando un bug
  */
  int get_winner_combination() {
    for (int i = 0; i < 8; i++) {
      int* combinations = COMBINATIONS[i];
  
      // Sum up all the combinations
      int sum = 0;
      for (size_t i = 0; i < 3; i++) {
        sum += playground[combinations[i]];
      }

      if (sum == 3 || sum == -3) {
        return i;
      }
    }

    return 0;
  }

  ~TicTacToe() {
    
  }
};

/*
 * The first player is the PLAYER_ONE
 * 
 * Il primo giocatore è il PLAYER_ONE
*/
player current_player = PLAYER_ONE;
TicTacToe tris(9);

/*
 * This function returns the opposite of the current player.
 * 
 * Questa funzione ritorna l'opposto del giocatore corrente.
*/
player exchange_player(cell player) {
  switch (player) {
    case PLAYER_ONE:
      return PLAYER_TWO;
      break;
    case PLAYER_TWO:
      return PLAYER_ONE;
      break;
  }
}

/*
 * We found that the ideal value is 850
 * 
 * Abbiamo scoperto che la soglia ideale è di 850
*/
const int threshold = 850;


/*
 * We declare the PINs for the first player. (RED)
 * 
 * Dichiariamo i PIN per il primo giocatore. (ROSSO)
*/
const int PLAYGROUND_LEDS_P1[PLAYGROUND_SIZE] = {
  10, 9, 8,
  7, 6, 5,
  4, 3, 2
};

/*
 * We declare the PINs for the second player. (BLUE)
 * 
 * Dichiariamo i PIN per il secondo giocatore. (BLU)
*/
const int PLAYGROUND_LEDS_P2[PLAYGROUND_SIZE] = {
  40, 39, 38,
  37, 36, 35,
  34, 33, 32
};

/*
 * We declare the analog pins which will be used to detect whether or not
 * someone wants to add a move.
 * 
 * Dichiariamo i pin analogici che verranno usati per rilevare se
 * qualcuno vuole aggiungere una mossa.
*/
const int PLAYGROUND_LECTURE[PLAYGROUND_SIZE] = {
  A0, A1, A2,
  A3, A4, A5,
  A6, A7, A8
};

/*
 * I created this function so I can turn on/off every single LED I need without
 * messing the code too much with digitalWrite()s
 * 
 * Ho creato questa funzione per poter accendere o spegnere i led più facilmente
 * senza sporcare troppo il codice con tanti digitalWrite()
*/
void set_led(int pos, player player, bool s) {
  switch (player) {
    case PLAYER_ONE:
      digitalWrite(PLAYGROUND_LEDS_P1[pos], s);
      break;
    case PLAYER_TWO:
      digitalWrite(PLAYGROUND_LEDS_P2[pos], s);
      break;
  }
}

/*
 * Light up all the leds from a specific player in one time.
 * 
 * Accendi tutti i led di un giocatore specifico in una volta sola.
*/
void set_led_all(int player, bool s) {
  for (size_t led = 0; led < PLAYGROUND_SIZE; led++) {
    set_led(led, player, s);
  }
}


/*
 * Shows a winning animation using LEDs
 * 
 * Mostra un'animazione di vittoria usando i LED
*/
void win_animation(player player) {
  set_led_all(PLAYER_ONE, LOW);
  set_led_all(PLAYER_TWO, LOW);
  int winner_combination_index = tris.get_winner_combination();
  Serial.print("win_animation() winner_combination_index = ");
  Serial.println(winner_combination_index);
  // Could be done in a better way using pointers
  // Potrebbe essere fatto in un modo migliore usando i puntatori
  int winner_combination[3] = {};

  for (int i = 0; i < 3; i++) {
    winner_combination[i] = tris.COMBINATIONS[winner_combination_index][i];
  }

  // TEST
  for (int k = 0; k < 30; k++) {
    // Turn the led on and then off, and then on, and the off..
    Serial.print("win_animation() turning LEDs ON");
    for (int i = 0; i < 3; i++) {
      set_led(winner_combination[i], player, HIGH);
    }
    delay(50);
    Serial.print("win_animation() turning LEDs OFF");
    for (int i = 0; i < 3; i++) {
      set_led(winner_combination[i], player, LOW);
    }
    delay(50); 
  }
}

/* Nobody won, the game finished with a parity
 * Show an animation
 * 
 * Nessuno ha vinto, il gioco è finito in parità.
 * Mostra un'animazione
*/
void parity_animation() {
  for (int i = 0; i < 10; i++) {
    Serial.print("parity_animation() turning LEDs OFF");
    set_led_all(PLAYER_ONE, LOW);
    set_led_all(PLAYER_TWO, LOW);
    delay(50);
    Serial.print("parity_animation() turning LEDs ON");
    set_led_all(PLAYER_ONE, HIGH);
    set_led_all(PLAYER_TWO, HIGH);
    delay(50);
  }
}

/* We first need to set the PINs to OUTPUT and INPUT
 * I am using a for loop so I don't have to write 30 lines of code.
 * 
 * Per prima cosa abbiamo bisogno di impostare i PIN in OUTPUT ed INPUT
 * Sto usando un ciclo for così non ho bisogno di scrivere 30 righe di codice.
*/
void setup() {  
  for (int i = 0; i < PLAYGROUND_SIZE; i++) {
    pinMode(PLAYGROUND_LEDS_P1[i], OUTPUT);
    pinMode(PLAYGROUND_LEDS_P2[i], OUTPUT);
    pinMode(PLAYGROUND_LECTURE[i], INPUT);
  }
  
  /*
   * Serial is being used to log some useful information
   * when we are debugging the code.
   * This helps a lot since arduino IDE doesn't have a builtin debugger
   * 
   * La console seriale verrà usata per mostrare alcune informazioni utili
   * quando dobbiamo debuggare il codice.
   * Questo aiuta molto visto che l'IDE di arduino non ha un debugger
  */
  Serial.begin(9600);
}

void loop() {
  // Read all the analog values
  // Leggi tutti i valori analogici
  for (int pos = 0; pos < PLAYGROUND_SIZE; pos++) {
  	int current_pin = PLAYGROUND_LECTURE[pos];
  	int value = analogRead(current_pin);
  	/*Serial.print("Lecture for ");
  	Serial.print(pos);
  	Serial.print(": ");
  	Serial.println(value);*/
  	if (value <= threshold) {
  		Serial.print("Pin ");
  		Serial.print(pos);
  		Serial.print(" seems to be pressed ");
  		if (tris.is_valid_move(pos)) {
  			Serial.println("and the move seems to be valid");
  			// Someone wants to add a move and the move is valid.
        // Qualcuno vuole aggiungere una mossa, ed essa è valida
  			tris.add_move(pos, current_player);
  			// Now we can turn the led ON
        // Ora possiamo accendere il LED
  			set_led(pos, current_player, HIGH);
  			// Now that someone added a move, we have to switch to another player
        // Ora che qualcuno ha aggiunto una mossa, dobbiamo passare all'altro giocatore
  			current_player = exchange_player(current_player);
  		} else {
        // Move not valid. It means that in the box there is already a move. Ignore it
        // Mossa non valida. Significa che nella casella c'è già una mossa. Ignoriamola
  			Serial.println("but the move is not valid");
  		}
  	}
  }
  
  // Check if someone has won
  // Controlla se qualcuno ha vinto
  player winner = tris.check_tris();
  if (winner != NO_PLAYER) {
    // Someone won, display win animation
    // Qualcuno ha vinto, mostra l'animazione di vittoria
    Serial.println("Someone won the game!");
    win_animation(winner);
  } 
  else if (tris.check_parity()) {
    // Parity, display parity animation
    // Parità, mostra l'animazione di pareggio
    Serial.println("The game ended with parity");
    parity_animation();
  }
}
