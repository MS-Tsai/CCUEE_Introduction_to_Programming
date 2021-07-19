/*****************************************************
 * Author: Meng-Shiun, Tsai
 * Date: 2016/05/27
 * Program: Salary sheet (implemented by linked list)
*****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int salary;
    char department_stuID[15], department[5], stuID[10];
    struct node *next;
}NODE;

typedef struct salary_sheet {
    struct node *head;
}SALARY_SHEET;

void user_interface(int counter); // Create an user interface
int check_index_of_department(char *department_stuID); // Check new data is EE or COMM
SALARY_SHEET *create_salary_sheet(); // Create a new salary sheet (linked list)
NODE *create_node(char *department_stuID, char *department, char *stuID, int salary); // Create a node with given data
void insert_node(SALARY_SHEET *salary_sheet, NODE *node); // Insert a node into existed salary sheet
void search_node(NODE *current, char *search_condition, int *search_counter); // Search desired data from existed salary sheet
void delete_node(SALARY_SHEET *salary_sheet, NODE *current, NODE *previous, char *delete_condition, int *delete_counter); // Delete desired data from existed salary sheet
void show_salary_sheet(NODE *current); // Show all data in existed salary sheet

int main() {
    int counter=0, idx_department=-1;
    char mark='"';
    char choice[20], department_stuID[15], department_stuID_copy[15], salary[20], delete_condition[15], search_condition[15];
    char *department, *stuID;

    SALARY_SHEET *salary_sheet = create_salary_sheet();
    NODE *node = NULL;

    while(1) {
        int search_counter=0, delete_counter=0;

        // User interface
        user_interface(counter) ;
        printf("Input : ");
        scanf("%s", choice);

        if(!strcmp(choice, "5")) {
            // CASE_5: User wants to exit this program
            break;

        } else if(!strcmp(choice, "1")) {
            // CASE_1: User wants to add new data into the salary sheet
            printf("\n============= ADD ==============\n");
            printf("Please enter Uppercase letters\n");
            printf("input %cQUIT%c to exit !\n", mark, mark);
            printf("===============================\n");

            // Start to add new data
            while(1) {
                // Let user input his department and student_ID
                for(idx_department=-1; idx_department==-1; ) {
                    printf("Department/ID : ");
                    scanf("%s", department_stuID);

                    // Check if user's department is EE or COMM, idx_department=[0 ... QUIT; 1 ... EE; 2 ... COMM]
                    idx_department = check_index_of_department(department_stuID);

                    if(idx_department == -1) {
                        printf("Invalid input !!\n");
                        printf("-------------------------------\n");
                    }
                }

                if(!strcmp(department_stuID, "QUIT")) {
                    printf("=========== END ADD ===========\n\n");
                    break ;
                } else {
                    // Let user input his salary
                    while(1) {
                        printf("EARING : ");
                        scanf("%s", salary);

                        // Check if user's salary is larger than 0
                        if(atoi(salary) > 0) {
                            break;
                        } else {
                            printf("Invalid input !!  ");
                        }
                    }
                    printf("-------------------------------\n");

                    // Copy department_stuID for using strtok
                    strcpy(department_stuID_copy, department_stuID);
                    department = strtok(department_stuID_copy, "/"); // Make string user enters be separated by "/"
                    stuID = strtok(NULL, "\0");//"NULL" is in order to continue the former

                    // Add new data into salary sheet
                    node = create_node(department_stuID, department, stuID, atoi(salary));
                    insert_node(salary_sheet, node);
                    counter++;
                }
            }
        } else if(!strcmp(choice, "2")) {
            // CASE_2: User wants to search from the salary sheet
            printf("\n===========SEARCH==============\n");

            // Start to search
            if(counter == 0) {
                printf("EMPTY LIST !!\n");
            } else {
                // Let user input the search condition
                printf("Index : ");
                scanf("%s", search_condition);
                printf("----------- RESULT ------------\n");

                // Search from the salary sheet according to search condition
                search_node(salary_sheet->head, search_condition, &search_counter);
                if(search_counter == 0) {
                    printf("NO SEARCH RESULT !!\n");
                }
            }

            printf("=========== END SEARCH ==========\n\n");

        } else if(!strcmp(choice, "3")) {
            // CASE_3: User wants to show all data
            printf("\n============ SHOW ==============\n");

            // Show all data in the salary sheet
            if(counter == 0) {
                printf("NOTHING TO SHOW !!\n");
            } else {
                show_salary_sheet(salary_sheet->head);
            }

            printf("========== END SHOW ============\n\n");

        } else if(!strcmp(choice, "4")) {
            // CASE_4: User wants to delete data from the salary sheet
            printf("\n=========== DELETE =============\n");

            // Start to delete data from the salary sheet
            if(counter == 0) {
                printf("EMPTY LIST !!\n");
            } else {
                // Let user input the delete condition
                printf("Index : ");
                scanf("%s", delete_condition);
                printf("------- DELETED RESULT --------\n");

                // Delete data from the salary sheet according to delete condition
                delete_node(salary_sheet, salary_sheet->head, NULL, delete_condition, &delete_counter);
                if(delete_counter == 0) {
                    printf("  NO MATCHING DATA !!\n");
                }
                counter -= delete_counter;
            }

            printf("========= END DELETE ==========\n\n");

        } else {
            printf("\nError !!  Please enter again ~ ~ \n");
        }
    }

    printf("\n========= SEE U AROUND =========");

    return 0;
}

// Create an user interface
void user_interface(int counter) {
    printf("\nEARING BOOK !! %d data !!\n", counter);
    printf("==============================\n");
    printf("  1) ADD\n");
    printf("  2) SEARCH\n");
    printf("  3) SHOW ALL\n");
    printf("  4) DELETE\n");
    printf("  5) EXIT\n");
    printf("===============================\n");
}

// Check new data is EE or COMM
int check_index_of_department(char *department_stuID) {
    if(!strcmp(department_stuID, "QUIT")) {
        return 0;
    } else if(department_stuID[0] == 'E' && department_stuID[1] == 'E' && department_stuID[2] == '/') {
        return 1;
    } else if(department_stuID[0] == 'C' && department_stuID[1] == 'O' && department_stuID[2] == 'M' && department_stuID[3] == 'M' && department_stuID[4] == '/') {
        return 2;
    } else {
        return -1;
    }
}

// Create a new salary sheet (linked list)
SALARY_SHEET *create_salary_sheet() {
    SALARY_SHEET *salary_sheet = (SALARY_SHEET*)malloc(sizeof(SALARY_SHEET));
    salary_sheet->head = NULL;
    return salary_sheet;
}

// Create a node with given data
NODE *create_node(char *department_stuID, char *department, char *stuID, int salary) {
    NODE* node = (NODE*)malloc(sizeof(NODE));
    strcpy(node->department_stuID, department_stuID);
    strcpy(node->department, department);
    strcpy(node->stuID, stuID);
    node->salary = salary;
    node->next = NULL;

    return node;
}

// Insert a node into existed salary sheet
void insert_node(SALARY_SHEET *salary_sheet, NODE *node) {
    if(salary_sheet->head == NULL) {
        // CASE: First data
        salary_sheet->head = node;
    } else {
        // CASE: There are more than one data in existed salary sheet
        NODE *current=salary_sheet->head, *previous=NULL;
        while(current != NULL) {
            // Use strcmp to achieve sorted linked list (sorted by the order of department_stuID)
            if(strcmp(node->department_stuID, current->department_stuID) > 0) {
                previous = current;
                current = current->next;
            } else {
                if(previous == NULL) {
                    // CASE: Insert a node as the head of linked list
                    node->next = current;
                    salary_sheet->head = node;
                } else {
                    // CASE: Insert a node into any position except for the head and tail
                    previous->next = node;
                    node->next = current;
                }
                return;
            }
        }
        // CASE: Insert a node as the tail of linked list
        previous->next = node;
        return;
    }
}

// Search desired data from existed salary sheet
void search_node(NODE *current, char *search_condition, int *search_counter) {
    if(current != NULL) {
        if(strstr(current->department_stuID, search_condition) != NULL) {
            printf("  %s : %d\n", current->department_stuID, current->salary);
            (*search_counter) += 1 ;
        }
        search_node(current->next, search_condition, search_counter);
    }
}

// Delete desired data from existed salary sheet
void delete_node(SALARY_SHEET *salary_sheet, NODE *current, NODE *previous, char *delete_condition, int *delete_counter) {
    if(current != NULL) {
        if(!strcmp(current->department_stuID, delete_condition)) {
            printf("  %s : %d\n", current->department_stuID, current->salary);
            (*delete_counter) += 1;

            if(previous == NULL) {
                // CASE: Delete the head of linked list
                salary_sheet->head = current->next;
                free(current);
                current = salary_sheet->head;
                delete_node(salary_sheet, salary_sheet->head, previous, delete_condition, delete_counter);
            } else {
                // CASE: Delete a node in any position except for the head
                previous->next = current->next;
                free(current);
                delete_node(salary_sheet, previous->next, previous, delete_condition, delete_counter);
            }
        } else {
            // CASE: Non-matched node (recursion keeps going)
            delete_node(salary_sheet, current->next, current, delete_condition, delete_counter);
        }
    }
}

// Show all data in existed salary sheet
void show_salary_sheet(NODE *current) {
    if(current != NULL) {
        printf("%s : %d\n", current->department_stuID, current->salary);
        show_salary_sheet(current->next);
    }
}
