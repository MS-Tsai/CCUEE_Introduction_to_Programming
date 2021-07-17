#include <stdio.h>

void PrintCalendar(int input_year, int input_month, int input_day, int first_day, int feb_days); // Print out a monthly calendar

int main() {
    int input_year=-1, input_month=-1, input_day=-1, first_day, feb_days, total_days, day_of_week, counter;
    char name_month[13][10]={"nothing", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    char name_week[7][10]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

    // User interface
    printf("1. If you enter Year    0     0  , the program will show calendar.\n");
    printf("2. If you enter Year  Month   0  , the program will show monthly calendar.\n");
    printf("3. If you enter Year  Month  Day , the program will show the day of week.\n");
    printf("4. If you enter   0     0     0  , the program will be ended.\n\n");

    // Check if the input is "0 0 0" or not
    while(input_year != 0 || input_month != 0 || input_day != 0) {
        printf("Please enter Year Month Day (separated by space): ");
        scanf("%d %d %d", &input_year, &input_month, &input_day);
        printf("\n");

        first_day = ((input_year-1)+((input_year-1)/4)-((input_year-1)/100)+((input_year-1)/400)+1)%7; // Calculate the day of week as 1/1 of the chosen year, formula: (((year-1)+((year-1)/4)-((year-1)/100)+((year-1)/400)+1)%7)
        feb_days = ((input_year%4 == 0 && input_year%100 != 0) || input_year%400 == 0) ? 29 : 28; // Check if chosen year is leap year, then set the days of February to 29/28 (yes/no)

        // Check the input is suitable or not
        if((input_year >= 1753) && (input_month < 13 && input_month >= 0) && (input_day < 32 && input_day >= 0)) {
            if(input_year != 0 && input_month != 0 && input_day == 0) {
                // Check if the input format is "year month 0", then show the calendar of chosen year/month
                printf(" %s", name_month[input_month]);
                PrintCalendar(input_year, input_month, input_day, first_day, feb_days);

            } else if(input_year != 0 && input_month == 0 && input_day == 0) {
                // Check if the input format is "year 0 0", then show the calendar of each month with chosen year
                for(input_month=1; input_month<13; input_month++){
                    printf(" %s",name_month[input_month]);
                    PrintCalendar(input_year, input_month, input_day, first_day, feb_days);
                }

            } else {
                // Check if the input format is "year month day", then show the day of week with chosen year/month/day
                int days[13]={0, 31, feb_days, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31} ;

                // Calculate the total number of days from 1/1 (not including chosen month)
                for(counter=1, total_days=0; counter<input_month; counter++) {
                    total_days = total_days + days[counter];
                }

                day_of_week = ((total_days-1 + input_day%7) + first_day) % 7; // Calculate the day of week with chosen year/month/day

                printf("%s\n\n", name_week[day_of_week]);
            }
        } else if((input_year < 1753) && (input_month >= 13 && input_month < 0) && (input_day >= 32 && input_day < 0)) {
            printf("Warning , the value is wrong . Please enter again\n\n");
        }
    }

    printf("The program is end\n\n");

    system("pause");

    return 0;
}

// Print out a monthly calendar
void PrintCalendar(int input_year, int input_month, int input_day, int first_day, int feb_days) {
    int i, dash, num, space=first_day ;
    int days[13]={0, 31, feb_days, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31} ;

    // Calculate the number of space before the first day of each month
    for(i=1; i<input_month; i++) {
        space = (space + days[i]) % 7;
    }

    printf("\n||Sun\tMon\tTues\tWed\tThurs\tFri\tSat\t||\n||");
    printf("--------------------------------------------------    ||\n||");

    for(dash=1; dash<=space; dash++) {
        printf("  - \t"); // Print out "-" before the first day of each month
    }

    // Print out the monthly calendar
    for(num=1; num<=days[input_month]; num++) {
        printf("%3d\t", num);

        if(num%7 == (7 - space)%7) {
            printf((num >= 28 && (days[input_month] + space)%7 == 0) ? "||\n" : "||\n||");
        }
    }

    // Use "-" to complement the rest of space
    if((space + days[input_month])%7 != 0) {
        for(dash=1; dash<=7-(space + days[i])%7; dash++) {
            printf("  - \t");
        }
        printf("||");
    }

    printf("\n\n");
}
