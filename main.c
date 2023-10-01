#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 50
#define M 30

struct node {
    char date[M];
    double amount;
    char category[N];
    struct node* next;
};

struct record {
    double x, y;
};

void create(char x[], double y, char z[], struct node** temp);
void display(int a3, struct node* income, struct node* expense);
struct node* readnext(struct node* ptr, FILE* fpointer);
void writeincome(struct node* ptr);
void writeexpense(struct node* ptr);
void deleterecord(struct node* ptr);
struct node* readincome(struct node* ptr);
struct node* readexpense(struct node* ptr);
void write(struct record* point);
struct record* readrecord();

int main() {
    int option;

    double b;
    char c[N], a[M];
    char s1[15], s2[15], s3[15];
    FILE* fpointer;
    struct node* income = NULL;
    struct node* expense = NULL;
    struct record* point = NULL;
    double currentincome = 0;
    double currentexpense = 0;

    if ((fpointer = fopen("Record.txt", "r")) != NULL)
    {
        point = readrecord();
        currentincome = point->x;
        currentexpense = point->y;
        fclose(fpointer);
    }

    if ((fpointer = fopen("myincome.txt", "r")) != NULL)
    {
        income = readincome(income);
        fclose(fpointer);
    }

    if ((fpointer = fopen("myexpense.txt", "r")) != NULL) {
        expense = readexpense(expense);
        fclose(fpointer);
    }

    do {

        printf("                                           "
               "_______________________________________________\n  ");
        printf("                                         |     YOUR INCOME   = "
               "    "
               " %.2lf HUF      \n ",
               currentincome);
        printf("                                          |     YOUR EXPENSE  "
               "=    "
               "  %.2lf HUF     \n ",
               currentexpense);
        printf("                                          |     YOUR BALANCE  "
               "=    "
               "  %.2lf HUF     \n ",
               currentincome - currentexpense);
        printf("                                          "
               "|_______________________________________________\n");
        printf("ENTER THE OPTION FROM THE BELOW \n\n");
        printf("1.INSERT INCOME \n");
        printf("2.INSERT EXPENSE \n");
        printf("3.VIEW INCOME RECORD \n");
        printf("4.VIEW EXPENSE RECORD \n");
        printf("5.EXIT\n");
        scanf("%d", &option);
        printf("\n\n\n");

        switch (option) {
        case 1:
            printf("**************   ADD INCOME   *****************\n\n");
            printf("Enter The Date(e.g day month year)\n");
            scanf("%s %s %s", s1, s2, s3);
            strcpy(a, "");
            strcat(a, s1);
            strcat(a, " ");
            strcat(a, s2);
            strcat(a, " ");
            strcat(a, s3);
            printf("Enter The Amount\n");
            scanf("%lf", &b);
            printf("Enter the Category\n");
            scanf("%s", c);

            currentincome = currentincome + b;
            create(a, b, c, &income);
            writeincome(income);

            break;
        case 2:
            printf("**************    ADD EXPENSE   *****************\n\n");
            printf("Enter The Date(e.g day month year)\n");

            scanf("%s %s %s", s1, s2, s3);
            strcpy(a, "");
            strcat(a, s1);
            strcat(a, " ");
            strcat(a, s2);
            strcat(a, " ");
            strcat(a, s3);

            printf("Enter The Amount\n");
            scanf("%lf", &b);
            printf("Enter The Category\n");
            scanf("%s", c);

            currentexpense = currentexpense + b;
            create(a, b, c, &expense);
            writeexpense(expense);

            break;
        case 3:
            printf("*********   YOUR INCOME RECORD IS   *******\n\n");
            display(3, income, expense);
            break;
        case 4:
            printf("*********   YOUR EXPENSE RECORD IS   *******\n\n");
            display(4, income, expense);
            break;
        case 5:
            if (!point) {
                point = (struct record*)malloc(sizeof(struct record));
            }
            point->x = currentincome;
            point->y = currentexpense;
            write(point);
            break;
        default:
            printf("WRONG OPTION SELECTED -Enter Valid Option");
            break;
        }
    } while (option != 5);

    deleterecord(expense);
    deleterecord(income);
    free(point);
    return 0;
}

void create(char x[], double y, char z[], struct node** temp)
{
    struct node *newnode, *ptr;
    newnode = (struct node*)malloc(sizeof(struct node));
    if (*temp == NULL) {
        strcpy(newnode->date, x);
        newnode->amount = y;
        strcpy(newnode->category, z);
        newnode->next = NULL;
        *temp = newnode;
    } else {
        ptr = *temp;
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        strcpy(newnode->date, x);
        newnode->amount = y;
        strcpy(newnode->category, z);
        newnode->next = NULL;
        ptr->next = newnode;
    }
}

void deleterecord(struct node* ptr) {
    struct node* freeme = ptr;
    struct node* holdme = NULL;
    while (freeme != NULL) {
        holdme = freeme->next;
        free(freeme);
        freeme = holdme;
    }
}

struct node* readnext(struct node* ptr, FILE* fpointer) {
    if (ptr == NULL) {
        ptr = (struct node*)malloc(sizeof(struct node));
        if (fscanf(fpointer, "%30[^;];%lf;%s\n", ptr->date, &ptr->amount,
                   ptr->category) != 3) {
            free(ptr);
            ptr = NULL;
        } else {
            ptr->next = NULL;
        }
    } else {
        struct node* ptr1 = ptr;
        struct node* ptr2 = (struct node*)malloc(sizeof(struct node));
        while (ptr1->next != NULL) {
            ptr1 = ptr1->next;
        }
        if (fscanf(fpointer, "%30[^;];%lf;%s\n", ptr2->date, &ptr2->amount,
                   ptr2->category) != 3) {
            free(ptr2);
        } else {
            ptr1->next = ptr2;
            ptr2->next = NULL;
        }
    }
    return ptr;
}

struct node* readincome(struct node* ptr) {
    FILE* fpointer;
    fpointer = fopen("myincome.txt", "r");
    if (fpointer != NULL) {
        while (!feof(fpointer)) {
            ptr = readnext(ptr, fpointer);
        }
        fclose(fpointer);
    } else {
        printf("ERROR IN OPENINNG FILE\n");
    }
    return ptr;
}
void display(int a3, struct node* income, struct node* expense) {
    FILE* fpointer = NULL;
    if (a3 == 3) // if case 3 is executed,we have to print income record
    {

        if ((fpointer = fopen("myincome.txt", "r")) ==
            NULL) /*if user try to view record when there is no any record,i.e
                    when user runs program first time and wants to view record
                    i.e there
                    is no any file created yet as myincome.txt,then it will
                    =NULL */

        {
            printf("NO RECORDS AVAILABLE\n\n");
            printf("___________________________________________________________"
                   "______"
                   "_______________________________________________\n\n");

        } else {
            // income=readincome(income);
            struct node* ptr2 = income;
            while (ptr2 != NULL) {
                printf("Date: %s\nAmount: %.2lf HUF\nCategory: %s\n\n",
                       ptr2->date, ptr2->amount, ptr2->category);
                ptr2 = ptr2->next;
            }
            printf("___________________________________________________________"
                   "______"
                   "_______________________________________________\n\n");
            fclose(fpointer);
        }
    } else if (a3 ==
               4) // if case 4 is executed then we have to print expenese record
    {

        if ((fpointer = fopen("myexpense.txt", "r")) ==
            NULL) /*if user try to view record when there is no any record,i.e
                   when user runs program first time and wants to view record
                   i.e there
                   is no any file created yet as myexpense.txt,then it will
                   =NULL */

        {
            printf("NO RECORDS AVAILABLE\n\n");
            printf("___________________________________________________________"
                   "______"
                   "_______________________________________________\n\n");
        } else {

            //   expense=readexpense(expense);
            struct node* ptr2 = expense;
            while (ptr2 != NULL) {
                printf("Date: %s\nAmount: %.2lf HUF\nCategory: %s\n\n",
                       ptr2->date, ptr2->amount, ptr2->category);
                ptr2 = ptr2->next;
            }
            printf("___________________________________________________________"
                   "______"
                   "_______________________________________________\n\n");
            fclose(fpointer);
        }
    }
}
void writeincome(struct node* ptr) {
    FILE* fpointer;
    fpointer = fopen("myincome.txt", "w");
    if (fpointer != NULL) {
        struct node* ptr1 = ptr;
        struct node* holdnext = NULL;
        while (ptr1 != NULL) {
            holdnext = ptr1->next;
            ptr1->next = NULL;
            fprintf(fpointer, "%s;%lf;%s\n", ptr1->date, ptr1->amount,
                    ptr1->category);
            /*every time we write into file,it will overwrite
                          the data...... whole data will be deleted and
                          new data will be written into file*/
            ptr1->next = holdnext;
            holdnext = NULL;
            ptr1 = ptr1->next;
        }
        fclose(fpointer);
        fpointer = NULL;
        printf("\nINCOME SAVED SUCCESSFULLY\n\n");
        printf("_______________________________________________________________"
               "____"
               "_____________________________________________\n\n");

    } else {
        printf("\nCANNOT SAVE INCOME..TRY AGAIN\n");
        printf("_______________________________________________________________"
               "____"
               "_____________________________________________\n\n");
    }
}

void writeexpense(struct node* ptr) {
    FILE* fpointer;
    fpointer = fopen("myexpense.txt", "w");
    if (fpointer != NULL) {
        struct node* ptr1 = ptr;
        struct node* holdnext = NULL;
        while (ptr1 != NULL) {
            holdnext = ptr1->next;
            ptr1->next = NULL;
            fprintf(fpointer, "%s;%lf;%s\n", ptr1->date, ptr1->amount,
                    ptr1->category);
            /*every time we write into file,it will overwrite
                                 the data..... whole data will be deleted and
                                 new data will be written into file*/
            ptr1->next = holdnext;
            holdnext = NULL;
            ptr1 = ptr1->next;
        }
        fclose(fpointer);
        fpointer = NULL;
        printf("\nEXPENSE SAVED SUCCESSFULLY\n\n");
        printf("_______________________________________________________________"
               "____"
               "_____________________________________________\n\n");

    } else {
        printf("\nCANNOT SAVE EXPENSE..TRY AGAIN\n\n");
        printf("_______________________________________________________________"
               "____"
               "_____________________________________________\n\n");
    }
}

struct node* readexpense(struct node* ptr) {
    FILE* fpointer;
    fpointer = fopen("myexpense.txt", "r");
    if (fpointer != NULL) {
        while (!feof(fpointer)) {
            ptr = readnext(ptr, fpointer);
        }
    } else {
        printf("cannonot open file\n");
    }
    fclose(fpointer);
    return ptr;
}
void write(struct record* point1) {
    FILE* fpointer;
    fpointer = fopen("Record.txt", "w");
    if (fpointer != NULL) {
        fprintf(fpointer, "%lf;%lf\n", point1->x, point1->y);
        /*every time we write into file,it will overwrite the
                      data..... whole data will be deleted and new data
                      will be written into file*/
        fclose(fpointer);
    } else {
        printf("FILEOPEN ERROR\n");
    }
}
struct record* readrecord() {
    FILE* fpointer;
    fpointer = fopen("Record.txt", "r");
    struct record* ptr = NULL;

    if (fpointer != NULL) {
        fseek(fpointer, 0, SEEK_SET);

        ptr = (struct record*)malloc(sizeof(struct record));
        fscanf(fpointer, "%lf;%lf", &ptr->x, &ptr->y);
        fclose(fpointer);
    } else {
        printf("CANNOT OPEN FILE\n");
    }

    return ptr;
}
