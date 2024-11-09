/*
  Name- Shishir Ghorashainee
  Professor Richard K Fox
  Programming Assignment 4

  
  Description:

  This program implements a two-player board game called ( Chutte and Ladders ), where each position
  on the board containing special symbols that affects the player movements. Each Players take turns and
  roll a dice, and based on the result, they move forward on the board. If a player lands on certain symbols (For eg, 'H' for a haven,
  'B' for moving backwards, 'F' for moving forwards), they are redirected accordingly. Landing on a chute or ladder
  changes their position. Also, pointers are used to track player positions on the board and the current board state
  is updated after each move and printed to a file. The game keeps on going until one player reaches or goes beyond 
  the end of the board, and thus we know who the winner is.

 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100    // declaring size of the board

// Function prototypes
void printBoard(char* board, char* p1, char* p2, FILE* fptr);  // To print the game board and player positions
char* move(char* me, char* you, int player_num, char* board, FILE* fptr); // To handle a player's movement
char* findHaven(char* me, char* board, char direction); // To find the nearest haven (H) and move the player
char* chuteLadder(char* me, char* board, int player_num, FILE* fptr);   // To handle landing on a chute or ladder

int main() {

    // VARIABLES
    
    char board[] = "  mHk nH l B He Flq p H  hByHlho H B  jr H B ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHF hoH B  ";     //board chracters 
    char* p1 = board, * p2 = board;   // Initializing player1 and player2 at the start of the board

    FILE* fptr = fopen("Output.txt", "w");   // opens a file and writes the game output.
    if (fptr == NULL) {
        printf("Error opening file!\n");    // show error message if there's an error while opening the file. 
        return 1;
    }

    srand(time(NULL));  // random number generator to get different results every time we play

    // Game keeps on iterating until one player wins by going beyond the end of the board size
    while (p1 < board + SIZE && p2 < board + SIZE) {
        p1 = move(p1, p2, 1, board, fptr);    // Player 1's turn
        p2 = move(p2, p1, 2, board, fptr);        // Player 2's turn

        // Print and store the board state after each move.
        printBoard(board, p1, p2, fptr);
    }

    // Determine winner based on whoever is ahead on the board  
    if (p1 > p2) {
        printf("Player 1 wins!\n");
    }
    else {
        printf("Player 2 wins!\n");
    }

    fclose(fptr);  // close the output file 
    return 0;
}

// Move function to handle player movement based on dice rolls bounded by the game rules.
char* move(char* me, char* you, int player_num, char* board, FILE* fptr) {
    int roll = (rand() % 6) + 1;   // random value is generated from 1 to 6 and stored to roll. 
    me += roll;  // move forward based on whatever value we get after rolling the die

    printf("Player %d moves %d to %ld", player_num, roll, me - board);  //print Player's move and the place he moves on to 

    if (me == you) {   // Checks for the collision
        me--;      // If a collision occurs the player goes back one step
        printf(" collision, moving back to %ld", me - board);  // after the collision, new postition is printed  
    }


    // Check if player lands on B or F 
    if (*me == 'B' || *me == 'F') {
        char direction = *me; // Store the direction ('B' for backward, 'F' for forward)
        me = findHaven(me, board, direction);  // Move the player to the nearest 'H' based on direction
        printf(" and lands on '%c', moving to %ld", direction, me - board); // Print new position after moving to H
    }
    // Check if player lands on a chute or ladder
    else if (*me >= 'a' && *me <= 'z') {
        me = chuteLadder(me, board, player_num, fptr);  // Call chuteLadder to find the new position
    }

    printf("\n");
    return me;  // returns the current position 
}

// Print the board to the output file and store it in board_states
void printBoard(char* board, char* p1, char* p2, FILE* fptr) {
    char* ptr = board;
    for (int i = 0; i < SIZE; i++, ptr++) {
        if (ptr == p1) {    // If it's the 1st player 
            fputc('1', fptr); // Player 1's position, write on the fil.

        }
        else if (ptr == p2) {  // If it's the 2nd player 
            fputc('2', fptr); // Player 2's position, write on the file.

        }
        else {      
           fputc(*ptr, fptr); // if not then write the board characters 
        }
    }
    fputc('\n', fptr);   // new line on the file 

}

// Find the nearest haven based on direction
char* findHaven(char* me, char* board, char direction) {
    char* new_position = me;      // to keep in track of the new position
    if (direction == 'B') {        // If direction is 'B' then backward search for 'H'
        // Search backwards for 'H' but not beyond the beginning of the board
        while (new_position >= board && *new_position != 'H') {
            new_position--;   // Go backwards
        }
    }
    else if (direction == 'F') {       // If direction is 'F', then forward search for 'H'
        // Search forward for 'H' but not past the end of the board
        while (new_position < board + SIZE && *new_position != 'H') {
            new_position++;      // Move Forward
        }
    }

    // Check if 'H' was found
    if (*new_position == 'H') {
        *new_position = '*';  // Mark haven as used
        return new_position;   // new position is returned
    }

    return me;  // No haven found so return the current position
}

// chutteLadder Function to move player to the one end of the ladder
char* chuteLadder(char* me, char* board, int player_num, FILE* fptr) {
    int offset = (int)(*me - 'n');  // Calculate move distance based on ASCII difference from 'n' 
    char* new_position = me + offset; // Once the offset is calculated, move the player.

    if (offset > 0) {
        printf(" and lands on a ladder, climbing up to %ld", new_position - board);       // Player climbs up the ladder

    }
    else {
        printf(" and lands on a chute, sliding down to %ld", new_position - board);       // Player slides down the chute
    }

    *me = '-';  // Replace chute/ladder with '-' to remove it. 
    return new_position;  // returns currrent players new positon 
}




/*


Player 1 moves 2 to 2 and lands on a chute, sliding down to 1
Player 2 moves 1 to 1 collision, moving back to 0
Player 1 moves 3 to 4 and lands on a chute, sliding down to 1
Player 2 moves 1 to 1 collision, moving back to 0
Player 1 moves 2 to 3
Player 2 moves 2 to 2
Player 1 moves 1 to 4
Player 2 moves 6 to 8
Player 1 moves 6 to 10
Player 2 moves 5 to 13
Player 1 moves 4 to 14 and lands on a chute, sliding down to 5
Player 2 moves 1 to 14
Player 1 moves 1 to 6 and lands on a chute, sliding down to 6
Player 2 moves 4 to 18 and lands on a ladder, climbing up to 21
Player 1 moves 3 to 9 and lands on a chute, sliding down to 7
Player 2 moves 3 to 24
Player 1 moves 6 to 13
Player 2 moves 5 to 29 and lands on a chute, sliding down to 27
Player 1 moves 4 to 17 and lands on a chute, sliding down to 15
Player 2 moves 1 to 28
Player 1 moves 6 to 21
Player 2 moves 3 to 31 and lands on a ladder, climbing up to 32
Player 1 moves 3 to 24
Player 2 moves 1 to 33
Player 1 moves 6 to 30 and lands on a chute, sliding down to 24
Player 2 moves 2 to 35 and lands on 'B', moving to 33
Player 1 moves 5 to 29
Player 2 moves 6 to 39 and lands on a ladder, climbing up to 43
Player 1 moves 2 to 31
Player 2 moves 6 to 49
Player 1 moves 6 to 37
Player 2 moves 2 to 51
Player 1 moves 3 to 40
Player 2 moves 1 to 52
Player 1 moves 3 to 43 and lands on 'B', moving to 41
Player 2 moves 2 to 54
Player 1 moves 6 to 47
Player 2 moves 5 to 59 and lands on a chute, sliding down to 49
Player 1 moves 2 to 49 collision, moving back to 48 and lands on a chute, sliding down to 44
Player 2 moves 6 to 55 and lands on a chute, sliding down to 52
Player 1 moves 3 to 47
Player 2 moves 5 to 57
Player 1 moves 2 to 49
Player 2 moves 6 to 63
Player 1 moves 3 to 52
Player 2 moves 6 to 69
Player 1 moves 2 to 54
Player 2 moves 4 to 73
Player 1 moves 5 to 59
Player 2 moves 1 to 74 and lands on 'B', moving to 69
Player 1 moves 4 to 63
Player 2 moves 2 to 71 and lands on a ladder, climbing up to 81
Player 1 moves 2 to 65 and lands on a chute, sliding down to 61
Player 2 moves 1 to 82 and lands on a chute, sliding down to 81
Player 1 moves 3 to 64 and lands on a ladder, climbing up to 66
Player 2 moves 4 to 85 and lands on 'B', moving to 79
Player 1 moves 1 to 67
Player 2 moves 4 to 83
Player 1 moves 1 to 68 and lands on a chute, sliding down to 67
Player 2 moves 3 to 86
Player 1 moves 1 to 68
Player 2 moves 5 to 91
Player 1 moves 5 to 73
Player 2 moves 3 to 94
Player 1 moves 2 to 75 and lands on 'F', moving to 87
Player 2 moves 5 to 99
Player 1 moves 4 to 91
Player 2 moves 2 to 101
Player 2 wins!

21-Hk nH l B He Flq p H  hByHlho H B  jr H B ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHF hoH B
21-H- nH l B He Flq p H  hByHlho H B  jr H B ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHF hoH B
  21- nH l B He Flq p H  hByHlho H B  jr H B ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHF hoH B
  -H1 nH2l B He Flq p H  hByHlho H B  jr H B ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHF hoH B
  -H- nH l1B 2e Flq p H  hByHlho H B  jr H B ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHF hoH B
  -H-1nH l B H2 Flq p H  hByHlho H B  jr H B ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHF hoH B
  -H- 1H l B H- Fl- p2H  hByHlho H B  jr H B ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHF hoH B
  -H- -1 - B H- Fl- p H 2hByHlho H B  jr H B ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHF hoH B
  -H- -H - B 1- Fl- p H  hB2H-ho H B  jr H B ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHF hoH B
  -H- -H - B H-1F-- p H  hBy2-ho H B  jr H B ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHF hoH B
  -H- -H - B H- F-- p1H  hByH-h-2H B  jr H B ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHF hoH B
  -H- -H - B H- F-- p H 1hByH-h- 2 B  jr H B ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHF hoH B
  -H- -H - B H- F-- p H 1hByH--- 2 B  jr H B ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHF hoH B
  -H- -H - B H- F-- p H  hByH1-- * B  j- H 2 ir j H  F ku gd  H pjB mH x  BF i H  m oB HlHF hoH B
  -H- -H - B H- F-- p H  hByH--1 * B  j- H B ir j2H  F ku gd  H pjB mH x  BF i H  m oB HlHF hoH B
  -H- -H - B H- F-- p H  hByH--- * B 1j- H B ir j H2 F ku gd  H pjB mH x  BF i H  m oB HlHF hoH B
  -H- -H - B H- F-- p H  hByH--- * B  j-1H B ir j H 2F ku gd  H pjB mH x  BF i H  m oB HlHF hoH B
  -H- -H - B H- F-- p H  hByH--- * B  j- 1 B ir j H  F2ku gd  H pjB mH x  BF i H  m oB HlHF hoH B
  -H- -H - B H- F-- p H  hByH--- * B  j- * B ir1j2H  F ku g-  H pjB mH x  BF i H  m oB HlHF hoH B
  -H- -H - B H- F-- p H  hByH--- * B  j- * B1ir - H 2F -u g-  H pjB mH x  BF i H  m oB HlHF hoH B
  -H- -H - B H- F-- p H  hByH--- * B  j- * B ir1- H  F -u2g-  H pjB mH x  BF i H  m oB HlHF hoH B
  -H- -H - B H- F-- p H  hByH--- * B  j- * B ir -1H  F -u g-  H2pjB mH x  BF i H  m oB HlHF hoH B
  -H- -H - B H- F-- p H  hByH--- * B  j- * B ir - H 1F -u g-  H pjB m2 x  BF i H  m oB HlHF hoH B
  -H- -H - B H- F-- p H  hByH--- * B  j- * B ir - H  F1-u g-  H pjB mH x 2BF i H  m oB HlHF hoH B
  -H- -H - B H- F-- p H  hByH--- * B  j- * B ir - H  F -u g1  H pjB m2 x  BF i H  m oB HlHF hoH B
  -H- -H - B H- F-- p H  hByH--- * B  j- * B ir - H  F -u g-  H1pjB m* -  BF i H 2m oB HlHF hoH B
  -H- -H - B H- F-- p H  hByH--- * B  j- * B ir - H  F -u g- 1H p-B m* -  BF i H 2- oB HlHF hoH B
  -H- -H - B H- F-- p H  hByH--- * B  j- * B ir - H  F -u g-  H --1 m* -  BF i 2  - oB HlHF hoH B
  -H- -H - B H- F-- p H  hByH--- * B  j- * B ir - H  F -u g-  H --B1m* -  BF i *  -2oB HlHF hoH B
  -H- -H - B H- F-- p H  hByH--- * B  j- * B ir - H  F -u g-  H --B1-* -  BF i *  - oB2HlHF hoH B
  -H- -H - B H- F-- p H  hByH--- * B  j- * B ir - H  F -u g-  H --B 1* -  BF i *  - oB HlHF2hoH B
  -H- -H - B H- F-- p H  hByH--- * B  j- * B ir - H  F -u g-  H --B -* - 1BF i *  - oB HlHF ho2 B
  -H- -H - B H- F-- p H  hByH--- * B  j- * B ir - H  F -u g-  H --B -* -  BF i *  - oB 1lHF hoH B  2
  -H- -H - B H- F-- p H  hByH--- * B  j- * B ir - H  F -u g-  H --B -* -  BF i *  - oB *lHF1hoH B

*/