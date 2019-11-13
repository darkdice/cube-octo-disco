/* David D - CSI 333 - Battleship program
This program is designed to play the game, Battleship by a game board of
size 10x10. Each game has random ship placements and the user
must input grid references to hit and sink the ships */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

#define SIZE 10
#define WATER '~'
#define HIT '*'
#define MISS 'o'
#define SHIP 'S' //debug symbol
#define PTRL 'p'
#define SUB 's'
#define DESTR 'd'
#define CARRIER 'c'
#define SUNK 'x'

//flags for game conditions: ships sank or user quits
bool flag_ship = false;
bool flag_quit = false;

//Grid reference struct
struct grid_ref {
  char letter;  //grid A - J, i = left to right
  int num;  //grid 0 - 9, j = top to bottom
}grid_ref;

struct Node {

  char data;
  struct Node *next;

};
struct Node *head = NULL;

/* Function to add grid call to hit_List */
void add_Node(char** board, char r, int c) {

  struct Node *call_List = (struct Node*)malloc(sizeof(struct Node));

  char str = ("%c %d", r, c);
  call_List->data = str;
  call_List->next = head;

  head = call_List;
}//add_Node

/* Function to print node list of grid calls made */
void print_List() {

  struct Node *ptr = head;

}//print_List

/* Function for initialization of game board */
char** initialization() {

  char** board = malloc(SIZE * sizeof(char *));

  for(int i = 0; i < SIZE; i++) {
    board[i] = malloc(SIZE * sizeof(char));
  }
  for(int i = 0; i < SIZE; i++) {
    for(int j = 0; j < SIZE; j++) {
      board[i][j] = WATER;
    }
  }
return board;
}

/* Function for resetting game board */
void teardown(char** board) {

  for(int i = 0; i < SIZE; i++)
    free(board[i]);
  free(board);
  printf("Gameboard has been cleared!\n");

  struct Node* tmp;

  while(head != NULL) {
    tmp = head;
    head = head-> next;
    free(tmp);
  }
}//teardown

/* Function to detect ship overlap */
int shipOverlap(char** board, int r, int c, int dir, int ship) {


}//shipOverlap

/* Function to generate direction point of ship */
int direction() {
  int dir = rand()%2;
  return dir;
}

/* Function to place ships on board */
void placeShips(char** board) {

  srand(time(NULL));
  int ship_p = 2, ship_s = 3, ship_d = 4, ship_c = 5;
  int i, j, dir, row, col;
  int ships = 5;

  //Direction = 1 is horizontal
  //Direction = 0 is vertical
  for(i = 0; i <= ships; i++) {
    switch(i) {
      //Create Patrol
      case 1:
      dir = direction();
      if(dir == 1) {
        col = rand()%9;
        row = rand()%10;
        for(j = 0; j < ship_p; j++) {
          board[row][col] = PTRL;
          col++;
        }
      } else {
        col = rand()%10;
        row = rand()%9;
        for(j = 0; j < ship_p; j++) {
          board[row][col] = PTRL;
          row++;
        }
      }break;

      //Create Sub
      case 2:
      dir = direction();
      if(dir == 1) {
        col = rand()%8;
        row = rand()%10;

        for(j = 0; j < ship_s; j++) {
          board[row][col] = SUB;
          col++;
          }
        }
        else {
        col = rand()%10;
        row = rand()%8;

        for(j = 0; j < ship_s; j++) {
          board[row][col] = SUB;
          row++;
        }
      }break;

      //Create Destroyer
      case 3:
      dir = direction();
      if(dir == 1) {
        col = rand()%7;
        row = rand()%10;
        for(j = 0; j < ship_d; j++) {
          board[row][col] = DESTR;
          col++;
          }
        }
        else {
        col = rand()%10;
        row = rand()%7;
        for(j = 0; j < ship_d; j++) {
          board[row][col] = DESTR;
          row++;
        }
      }break;

      //Create Carrier
      case 4:
      dir = direction();
      if(dir == 1) {
        col = rand()%6;
        row = rand()%10;
        for(j = 0; j < ship_c; j++) {
          board[row][col] = CARRIER;
          col++;
        }
      }
      else {
        col = rand()%10;
        row = rand()%6;
        for(j = 0; j < ship_c; j++) {
          board[row][col] = CARRIER;
          row++;
        }
      }break;

      //Create 2nd sub
      case 5:
      dir = direction();
      if(dir == 1) {
        col = rand()%7;
        row = rand()%10;
        for(j = 0; j < ship_s; j++) {
          board[row][col] = SUB;
          col++;
        }
      }
      else {
        col = rand()%10;
        row = rand()%7;
        for(j = 0; j < ship_s; j++) {
          board[row][col] = SUB;
          row++;
        }
      }break;

    }//end switch
  }//end ship loop

}//end placeShips

/* Function to detect if game is over */
void gameOver(char** board) {

  int i, j;

  for(i = 0; i <= SIZE; i++) {
    for(j = 0; j <= SIZE; j++) {
      if(board[i][j] != PTRL && board[i][j] != SUB &&
         board[i][j] != DESTR && board[i][j] != CARRIER) {
        flag_ship = true;
      }
      else {
        flag_ship = false;
      }
    }
  }
}//gameOver

/* Function for displaying game board */
void displayBoard(char** board) {

  //print top row of letters
  printf("   A B C D E F G H I J");

  for(int i = 0; i < SIZE; i++) { //row
    printf("\n %d|", i);
    for(int j = 0; j < SIZE; j++) { //col
    /*  if(board[i][j] == PTRL || board[i][j] == SUB ||
           board[i][j] == DESTR || board[i][j] == CARRIER) {
        printf("%c ", WATER);
      }
      else {
      printf("%c ", board[i][j]);
    } */
    //DEV DEBUG: print ships on board
    printf("%c ", board[i][j]);
    }
  }
  if(flag_ship == true) {
    printf("Game Over! You sank all the ships, good job!\n");
  }
  else if(flag_quit == true) {
    printf("Game Over, you decided to leave your comrads behind...\n");
  }
}//end displayBoard

/* Function for state of the world of the board*/
void stateOfWorld(char** board) {

  printf("Fire at: %c%d . . .\n", grid_ref.letter, grid_ref.num);

  char letter = toupper(grid_ref.letter);
  int col = letter - 'A';
  int row = grid_ref.num;

//Check grid reference on board to see if shot hits, misses or has been called
  if((board[row][col] == HIT) || (board[row][col] == MISS)) {
      printf("Grid: %c%d, has already been shot\n", letter, grid_ref.num);
    }
  else if(board[row][col] == SUNK) {
    printf("Grid: %c%d, this ship is sank! Don't be mean\n", letter, grid_ref.num);
  }
  else if(board[row][col] == WATER) {
      board[row][col] = MISS;
      printf("MISS!\n");
    }
  else if(board[row][col] == PTRL || board[row][col] == SUB ||
          board[row][col] == DESTR || board[row][col] == CARRIER) {
      board[row][col] = HIT;
      printf("HIT!\n");
    }
    gameOver(board);

}//end stateOfWorld


/* Main Program section */
int main() {

  int ships = 0;
  char** g_board = initialization();
  placeShips(g_board);

  //test print board, add inside loop when working
  displayBoard(g_board);

  //Welcome message to start playing
  printf("\nWelcome to... Battleship!\n");
  //printf("Enter 'Q' if you wish to stop playing.\n");

  //NEED WORKING LOOP TO QUIT WHEN FLAG IS ENTERED
  //DOUBLE PRINTS USER INPUT, PRINTS DOUBLE FIRE-ACTIONS
  do {
    printf("\nEnter grid reference to shoot at (i.e. A0): ");
    scanf("%c%d", &grid_ref.letter, &grid_ref.num);


    while(!((grid_ref.letter >= 'a' && grid_ref.letter <= 'j') ||
    (grid_ref.letter >= 'A' && grid_ref.letter <= 'J'))) {
      printf("\nEnter grid reference of A-J and 0-9: ");
      scanf("%c%d ", &grid_ref.letter, &grid_ref.num);
    }

    stateOfWorld(g_board);
    displayBoard(g_board);

  }while((flag_ship != true) || (flag_quit != true));

  teardown(g_board);

  return 0;
}
