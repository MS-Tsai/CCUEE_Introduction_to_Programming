/*********************************************
 * Author: Meng-Shiun, Tsai
 * Date: 2016/05/18
 * Program: Binary conversion program
*********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convert_decimal_to_binary(char *input); // Convert a decimal digit to binary format

int main() {
    int counter=0;
    char input[20];

    printf("%d, %d, %d\n\n", !1, !0, !3);

    printf("Welcome to the 16-bit\n  binary conversion program!\n\n");
    printf("*Type 'q' to exit the program");

    while(1) {
        printf("\nInput   : ");
        scanf("%s", input);

        // 'q' means that user wants to quit the program
        if(!strcmp("q", input)) {
            break;
        }

        for(counter=0; input[counter]!='\0'; counter++) {
            // Each character of the input must be 0~9 or '-' (first character)
            if((input[counter] <= 47 || input[counter] >= 58) && input[0] != 45) {
                break;
            }
        }

        if(counter == strlen(input)) {
            // CASE: All of the characters are integer, then convert this decimal digit to binary format
            if(atoi(input) < 32768 && atoi(input) > -32769) {
                printf("Result  :");
                convert_decimal_to_binary(input);

            } else if(atoi(input) <= -32769 || atoi(input) >= 32768) {
                printf("Input is out of range!!!\n");
                printf("Allowable range is -32768 to 32767");
            }
        } else {
            printf("Invalid input!");
        }
    }

    return 0;
}

// Convert a decimal digit to binary format
void convert_decimal_to_binary(char *input) {
    int binary_number[16]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} ; // Declare origin 16-bit value = 0
    int key=atoi(input), divisor=key, remainder, i=15 ;

    // Check if the input is smaller than 0 or not
    if(key < 0) {
        divisor = 0 - key - 1;
    }

    // Convert a decimal digit to binary format
    for(i=15; divisor!=0; i--) {
        remainder = divisor % 2 ;
        divisor = divisor / 2 ;

        binary_number[i] = remainder; // Remainder is the binary value
    }

    // Display converted result
    for(i=0; i<16; i++) {
        if(i % 4 == 0) {
            printf(" ");
        }
        printf("%d", binary_number[i] ^ (key < 0));
    }
}
