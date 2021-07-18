/*********************************************
 * Author: Meng-Shiun, Tsai
 * Date: 2016/04/29
 * Program: Vigenere and Morse Code
*********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Morse_to_character(); // Convert Morse code into character or number
void Vigenere_decode(char *keywords); // Use Vigenere table to decode a message
void Vigenere_encode(char *keywords, char *Vigenere_encode_result); // Use Vigenere table to encode a message
void character_to_Morse(char *Vigenere_encode_result); // Convert character or number into Morse code

int main() {
    char choose, keywords[20], Vigenere_encode_result[150];

    do {
        printf("Choose a function :\n");
        printf("1)Encode\n");
        printf("2)Decoder       : ");
        scanf("%s", &choose);
        printf("\n=============================\n");

        if(choose == '2') {
            // CASE_2: User choose to decode the message according to keywords
            printf("Keyword : ");
            scanf("%s", keywords);

            printf("\nThe data is : ");
            Morse_to_character();

            printf("\n\nResult : ");
            Vigenere_decode(keywords);

        } else if(choose == '1') {
            // CASE_1: User choose to encode the message according to keywords
            printf("Keyword : ");
            scanf("%s", keywords);

            printf("\nThe data is : ");
            Vigenere_encode(keywords, Vigenere_encode_result);

            character_to_Morse(Vigenere_encode_result);
        }
    }
    while(choose != '1' && choose != '2');

    return 0;
}

// Convert Morse code into character or number
void Morse_to_character() {
    FILE *file_Morse_table = fopen("mos.txt", "r");
    FILE *file_message = fopen("decode.txt", "r");
    FILE *file_Morse_decode_result = fopen("morse_result.txt", "w");

    int i=0 ;
    char message[10], Morse_table[72][10] ;

    // Record Morse code table from mos.txt
    for(i=0; i<72; i++) {
        fscanf(file_Morse_table, "%s", &Morse_table[i]);
    }

    // Start to convert Morse code into character or number
    while(fscanf(file_message, "%s", message) != EOF) {
        for(i=1; i<72; i+=2) {
            if(!strcmp(Morse_table[i], message)) {
                // CASE: Match with Morse code table
                printf("%s", Morse_table[i-1]);
                fprintf(file_Morse_decode_result, "%s", Morse_table[i-1]);
                break ;

            } else {
                if(!strcmp("|", message)) {
                    // CASE: Message is equal to "|"
                    printf(" ");
                    fprintf(file_Morse_decode_result, " ");
                    break ;

                } else if(!strcmp("!", message) || !strcmp(",", message)) {
                    // CASE: Message is equal to "!" or ","
                    printf("%s", message);
                    fprintf(file_Morse_decode_result, "%s", message);
                    break ;
                }
            }
        }
    }

    // Close opened file
    fclose(file_Morse_table);
    fclose(file_message);
    fclose(file_Morse_decode_result);
}

// Use Vigenere table to decode a message
void Vigenere_decode(char *keywords) {
    FILE *file_message = fopen("morse_result.txt", "r");
    FILE *file_Vigenere_decode_result = fopen("output_decode.txt", "w");

    int count=0, int_message=0, int_key=0, idx_key=0, idx_result=0;
    char character[26]={'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char message, Vigenere_decode_result[150];

    // Convert lowercase into uppercase (keywords)
    for(count=0; keywords[count]!='\0'; count++) {
        if(keywords[count] > 92) {
            keywords[count] = keywords[count] - 32;
        }
    }

    // Start to decode message with Vigenere table according to keywords
    for(idx_result=0; fscanf(file_message, "%c", &message)!=EOF; idx_result++) {
        if(message != ' ' && message != ',' && message != '!') {
            // Follow the rule of Vigenere table to decode the message
            int_message = (int)message - 65;
            int_key = (int)keywords[idx_key] - 65;
            Vigenere_decode_result[idx_result] = (int_message-int_key >= 0) ? character[int_message-int_key] : character[26-(int_key-int_message)];

            printf("%c", Vigenere_decode_result[idx_result]);
            fprintf(file_Vigenere_decode_result, "%c", Vigenere_decode_result[idx_result]);

            idx_key++ ;

        } else {
            printf("%c", message);
            fprintf(file_Vigenere_decode_result, "%c", message);
        }

        // Repeatedly using keywords
        if(idx_key == strlen(keywords)) {
            idx_key = 0;
        }
    }

    // Close opened file
    fclose(file_message);
    fclose(file_Vigenere_decode_result);
}

// Use Vigenere table to encode a message
void Vigenere_encode(char *keywords, char *Vigenere_encode_result) {
    FILE *file_message = fopen("encode.txt", "r");
    FILE *file_Vigenere_encode_result = fopen("vigenere_result.txt", "w");

    int count=0, int_message=0, int_key=0, idx_key=0, idx_result=0;
    char character[26]={'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char message;

    // Convert lowercase into uppercase (keywords)
    for(count=0; keywords[count]!='\0'; count++) {
        if(keywords[count] > 92) {
            keywords[count] = keywords[count] - 32;
        }
    }

    // Start to encode message with Vigenere table according to keywords
    for(idx_result=0; fscanf(file_message, "%c", &message)!=EOF; idx_result++) {
        printf("%c", message);

        // Convert lowercase into uppercase (message)
        if(message > 96 && message < 123) {
            message = message - 32 ;
        }

        if(message > 64 && message < 91) {
            // Follow the rule of Vigenere table to encode the message
            int_message = (int)message - 65;
            int_key = (int)keywords[idx_key] - 65;
            Vigenere_encode_result[idx_result] = (int_message+int_key > 25) ? character[int_message+int_key-26] : character[int_message+int_key];

            idx_key++ ;

        } else {
            Vigenere_encode_result[idx_result] = (message == '-') ? '|' : message;
        }

        // Repeatedly using keywords
        if(idx_key == strlen(keywords)) {
            idx_key = 0;
        }
    }

    // Show encoded results
    printf("\n\nResult : ");
    for(idx_result=0; Vigenere_encode_result[idx_result]!='\0'; idx_result++) {
        printf("%c", Vigenere_encode_result[idx_result]);
        fprintf(file_Vigenere_encode_result, "%c ", Vigenere_encode_result[idx_result]);
    }

    // Close opened file
    fclose(file_message);
    fclose(file_Vigenere_encode_result);
}

// Convert character or number into Morse code
void character_to_Morse(char *Vigenere_encode_result) {
    FILE *file_Morse_table = fopen("mos.txt", "r");
    FILE *file_message = fopen("vigenere_result.txt", "r");
    FILE *file_Morse_encode_result = fopen("output_encode.txt", "w");

    int idx_Morse=0, idx_result=0 ;
    char message[5], Morse_table[72][10] ;

    // Record Morse code table from mos.txt
    for(idx_Morse=0; idx_Morse<72; idx_Morse++) {
        fscanf(file_Morse_table, "%s", &Morse_table[idx_Morse]);
    }

    // Start to convert character or number into Morse code
    for(idx_result=0; fscanf(file_message, "%s", message)!=EOF; idx_result++) {
        for(idx_Morse=0; idx_Morse<72; idx_Morse+=2) {
            if(!strcmp(Morse_table[idx_Morse], message)) {
                // CASE: Match with Morse code table
                fprintf(file_Morse_encode_result, "%s ", Morse_table[idx_Morse+1]);
                break ;

            } else if((Vigenere_encode_result[idx_result] < 65 || Vigenere_encode_result[idx_result] > 90) && (Vigenere_encode_result[idx_result] < 48 || Vigenere_encode_result[idx_result] > 57)) {
                // CASE: Non-character or non-number
                fprintf(file_Morse_encode_result, "%c ", Vigenere_encode_result[idx_result]);
                break ;
            }
        }
    }

    // Close opened file
    fclose(file_Morse_table);
    fclose(file_message);
    fclose(file_Morse_encode_result);
}
