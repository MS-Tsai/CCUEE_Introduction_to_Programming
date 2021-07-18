/*********************************************
 * Author: Meng-Shiun, Tsai
 * Date: 2016/04/15
 * Program: A poker card game named fishing
*********************************************/

#include <stdio.h>
#include <string.h>
#include <time.h>

void shuffle_deck(char deck[]);
void show_deck(char deck[]);

int main() {
    char deck[52]={'1', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K',
                   '1', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K',
                   '1', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K',
                   '1', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
    int choose=0;

    srand((unsigned)time(NULL)); // Set random number to be different per game

    while(choose != 4) {
        char deck_back[52]={'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H',
                            'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H',
                            'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H',
                            'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H'};
        char character;
        int round=1, counter_win=0;
        int number=0, row_current=0, col_current=0, col_previous=0, row_previous=0;

        // User interface
        printf("==============================\n");
        printf("Welcome to the game center !!\n");
        printf("==============================\n");
        printf("1) Shuffling\n");
        printf("2) Play!!\n");
        printf("3) Show all\n");
        printf("4) Exit\n");
        printf("Please choose an item: ");
        scanf("%d", &choose);
        printf("==============================\n");

        if(choose == 1) {
            // CASE_1: Shuffling a deck
            shuffle_deck(deck);

            printf("Shuffling is completed !!\n");
            printf("===============================================================\n\n\n");

        } else if(choose == 2) {
            // CASE_2: Playing a Fishing Game
            printf("GAME START !!\n");

            // Reset all displayed cards to 'H'
            show_deck(deck_back);

            while(counter_win != 26) {
                printf("Choose a card (number,character): ");
                scanf("%d%c", &number, &character);

                // Check if the user wants to quit the game
                if(character == 'q' || character == 'Q') {
                    break;
                }

                // Check if the user enters the valid input
                if(character != 'a' && character != 'A' && character != 'b' && character != 'B' &&
                   character != 'c' && character != 'C' && character != 'd' && character != 'D' || (number > 13 && number < 0)) {
                    printf("Wrong inputted ~~ Please type in again !!\n\n");

                } else {
                    // Start to play the game
                    col_current = number;
                    if(character == 'a' || character == 'A')    row_current = 0;
                    if(character == 'b' || character == 'B')    row_current = 1;
                    if(character == 'c' || character == 'C')    row_current = 2;
                    if(character == 'd' || character == 'D')    row_current = 3;

                    if(deck_back[row_current*13 + col_current - 1] == 'H') {
                        deck_back[row_current*13 + col_current - 1] = deck[row_current*13 + col_current - 1];

                        if(round % 2 == 1) {
                            row_previous = row_current;
                            col_previous = col_current;
                            printf("\n");

                        } else {
                            if(deck_back[row_current*13 + col_current - 1] == deck_back[row_previous*13 + col_previous - 1]) {
                                deck_back[row_current*13 + col_current - 1] = ' ' ;
                                deck_back[row_previous*13 + col_previous - 1] = ' ';

                                counter_win++;

                                if(counter_win == 26) {
                                    printf("You find them !!\n");
                                    printf("Congratulations !! You have complete the mission !!\n");
                                    printf("===============================================================\n\n\n");
                                    break;

                                } else {
                                    printf("You find them !!\n\n");
                                }
                            } else {
                                deck_back[row_current*13 + col_current - 1] = 'H' ;
                                deck_back[row_previous*13 + col_previous - 1] = 'H';
                                printf("That one is %c\n\n", deck[row_current*13 + col_current - 1]);
                            }
                        }
                        show_deck(deck_back);
                        round++;
                    } else {
                        printf("Wrong inputted ~~ Please type in again !!\n\n");
                    }
                }
            }

            if(counter_win != 26) {
                printf("That's ok ~ Maybe yo will make it next time ...\n");
                printf("===============================================================\n\n\n");
            }
        } else if(choose == 3) {
            // CASE_3: Showing current deck
            printf("SHOW ALL !!\n");
            show_deck(deck);

            printf("THAT'S THE RESULT !!\n");
            printf("===============================================================\n\n\n");

        } else if(choose < 1 || choose > 4) {
            // ANOTHER CASE: Invalid input
            printf("Wrong inputted ~~ Please type in again !!\n");
            printf("===============================================================\n\n\n");
        }
    }

    printf("Goodbye my friend ~ !!\n");
    printf("===============================================================\n");

    return 0;
}

void shuffle_deck(char deck[]) {
    char sorted_deck[52]={'1', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K',
                          '1', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K',
                          '1', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K',
                          '1', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
    int is_shuffled[52]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int idx_deck=0, idx_shuffling=0;

    while(idx_deck != 52) {
        idx_shuffling = rand() % 52;

        if(is_shuffled[idx_shuffling] == 0) {
            deck[idx_deck] = sorted_deck[idx_shuffling] ;
            is_shuffled[idx_shuffling] = 1 ;
            idx_deck++ ;
        }
    }
}

void show_deck(char deck[]) {
    printf("============================================\n");
    printf("    1  2  3  4  5  6  7  8  9 10 11 12 13\n");
    printf("============================================");

    int i;

    for(i=0; i<52; i++) {
        if(i % 13 == 0) {
            printf("\n %c", i/13+65);
        }
        printf("%3c", deck[i]);
    }

    printf("\n============================================\n");
}

