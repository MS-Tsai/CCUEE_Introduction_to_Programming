/**********************************
 * Author: Meng-Shiun, Tsai
 * Date: 2016/03/25
 * Program: Resistor Calculator
**********************************/

#include <stdio.h>
#include <string.h>

int main() {
    char percent='%', mark='"', enter[10], buffer[20];
    char *enter_1, *enter_2, *enter_3, *enter_4;
    char color[12][3]={"b", "br", "r", "o", "y", "g", "bl", "v", "gr", "w", "go", "s"};
    int en_1, en_2, en_3, en_4, ten, i, compare=1, count=0, choice;
    double total;

    FILE *history;

    printf(" Welcome to the \n   Resistor Color Code Program\n\n");

    while(1) {
        printf("============= Menu =============\n");
        printf("1. Color Code -> Resistor Value\n");
        printf("2. History\n");
        printf("3. Clear History\n");
        printf("4. Exit\n");
        printf("================================\n");
        printf("Input choice: ");
        scanf("%d", &choice);

        if(choice == 1) {
            // The condition when user chooses 1
            printf("\n**************INSTRUCTION**************\n");
            printf("Color Code:\n ");
            printf("Black  [b]  = 0\tGreen  [g]  = 5\n ");
            printf("Brown  [br] = 1\tBlue   [bl] = 6\n ");
            printf("Red    [r]  = 2\tViolet [v]  = 7\n ");
            printf("Orange [o]  = 3\tGray   [gr] = 8\n ");
            printf("Yellow [y]  = 4\twhite  [w]  = 9\n");
            printf("Tolerance Code:\n ");
            printf("Gold   [go] = 5%c\tSliver [s]  = 10%c\n\n", percent, percent);

            while(1) {
                history = fopen("History.txt", "a");

                printf("Input the color code, separated with '-'\n");
                printf("*Type in %creturn%c to back to main menu\n", mark, mark);
                printf("Color Code -> ");
                scanf("%s", enter);

                compare = strcmp(enter, "return"); // Compare whether string user enters is equal to "return"

                if(compare == 0) {
                    // If string user enters and "return" are the same, then back to menu
                    break ;
                }

                fprintf(history, "%12s", enter); // Print string to txt (%12s is in order to typesetting)

                // Make string user enters be separated by "-"
                enter_1 = strtok(enter,"-");
                enter_2 = strtok(NULL,"-"); // "NULL" is in order to continue the former
                enter_3 = strtok(NULL,"-");
                enter_4 = strtok(NULL,"\0"); // "\0" means the end of string

                // Analyze the four parts of string
                for(en_1=0, compare=1; compare!=0; en_1++)  compare = strcmp(enter_1, color[en_1]);
                for(en_2=0, compare=1; compare!=0; en_2++)  compare = strcmp(enter_2, color[en_2]);
                for(en_3=0, compare=1; compare!=0; en_3++)  compare = strcmp(enter_3, color[en_3]);
                for(en_4=0, compare=1; compare!=0; en_4++)  compare = strcmp(enter_4, color[en_4]);
                for(i=1, ten=1; i<en_3; i++)                ten = ten * 10; // The third string means how many times you should multiplier 10

                total = (double)((en_1 - 1) * 10 + en_2 - 1) * ten; // The value of ohms is ((en_1-1)*10+en_2-1)*ten

                if(total < 1000) {
                    printf("The color code translates to %.1f ohms with %d%c Tolerance\n\n", total, (en_4-10)*5, percent);
                } else if(total < 1000000 && total >= 1000) {
                    printf("The color code translates to %.1f Kohms with %d%c Tolerance\n\n", total/1000, (en_4-10)*5, percent);
                } else if(total < 1000000000 && total >= 1000000) {
                    printf("The color code translates to %.1f Mohms with %d%c Tolerance\n\n", total/1000000, (en_4-10)*5, percent);
                } else {
                    printf("The color code translates to %.1f Gohms with %d%c Tolerance\n\n", total/1000000000, (en_4-10)*5, percent);
                }

                fprintf(history, "%15.0f%15d\n", total, (en_4-10)*5); // Write the result to file
                fclose(history); // Close the file
            }

            printf("\n");

        } else if(choice == 2) {
            // The condition when user chooses 2
            history = fopen("History.txt", "r"); // Read the data from file

            printf("\n       Color     Resistance      Tolerance\n");
            printf("        code        in ohms         in '%c'\n", percent);
            printf("   =======================================");

            // Read the data until the end of data
            for(count=0; fscanf(history, "%s", buffer)!=EOF; count++) {
                if(count % 3 == 0) {
                    printf("\n%12s", buffer); // %12s is in order to typesetting
                } else if(count % 3 == 1 || count % 3 == 2) {
                    printf("%15s", buffer); // %15s is in order to typesetting
                }
            }

            printf("\n\n");
            fclose(history); // Close the file

        } else if(choice == 3) {
            // The condition when user chooses 3
            printf("Done deleting history file!\n\n");

            history = fopen("History.txt", "w"); // Use "w" to clear the file
            fprintf(history, "");
            fclose(history); // Close the file

        } else if(choice == 4) {
            //The condition when user chooses 4 (quit the program)
            break;
        }
    }

    return 0;
}
