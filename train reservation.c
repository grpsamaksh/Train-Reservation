#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Passenger {
    int id;
    char name[50];
    int age;
    char train[100];
};

void bookTicket() {
    struct Passenger p;
    FILE *fp;

    fp = fopen("reservation.txt", "ab");

    if (fp == NULL) {
        printf("File opening error!\n");
        return;
    }

    printf("\nEnter Passenger ID: ");
    scanf("%d", &p.id);

    printf("Enter Passenger Name: ");
    scanf(" %[^\n]", p.name);

    printf("Enter Passenger Age: ");
    scanf("%d", &p.age);

    printf("Enter Train Name: ");
    scanf(" %[^\n]", p.train);

    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);

    printf("\nTicket Booked Successfully!\n");
}

void searchTicket() {
    struct Passenger p;
    FILE *fp;
    int id, found = 0;

    printf("\nEnter Passenger ID: ");
    scanf("%d", &id);

    fp = fopen("reservation.txt", "rb");

    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id == id) {
            printf("\nRecord Found!");
            printf("\nID: %d", p.id);
            printf("\nName: %s", p.name);
            printf("\nAge: %d", p.age);
            printf("\nTrain: %s\n", p.train);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nRecord not found!");

    fclose(fp);
}

void cancelTicket() {
    struct Passenger p;
    FILE *fp, *temp;
    int id, found = 0;

    printf("\nEnter Passenger ID: ");
    scanf("%d", &id);

    fp = fopen("reservation.txt", "rb");
    temp = fopen("temp.txt", "wb");

    if (fp == NULL || temp == NULL) {
        printf("File error!\n");
        return;
    }

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id != id) {
            fwrite(&p, sizeof(p), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("reservation.txt");
    rename("temp.txt", "reservation.txt");

    if (found)
        printf("\nTicket Cancelled Successfully!\n");
    else
        printf("\nRecord not found!\n");
}

void checkAvailability() {
    printf("\n=====Available Trains=====\n");
    printf("1. Vande Bharat Express\n");
    printf("2. Kumbha Express\n");
    printf("3. Himachal Express\n");
    printf("4. Garib Rath\n");
    printf("5. Janmabhoomi Express\n");
    printf("6. Himgiri Superfast Express\n");
    printf("7. Ujjaini Express\n");
    printf("8. Shatabdi Express\n");
    printf("9. Uttranchal Express\n");
    printf("10. Duronto Express\n");
    printf("11. Tejas Express\n");
    printf("12. Rajdhani Express\n");
}

int main() {
    int c;

    while (1) {
        printf("\n\n========  Train Reservation  ========\n");
        printf("1. Check Train Availability\n");
        printf("2. Book Ticket\n");
        printf("3. Search Ticket\n");
        printf("4. Cancel Ticket\n");
        printf("5. Exit\n");

        printf("Enter your choice by given number:");
        scanf("%d", &c);

        switch (c) {
            case 1: checkAvailability(); break;
            case 2: bookTicket(); break;
            case 3: searchTicket(); break;
            case 4: cancelTicket(); break;
            case 5:
                printf("Thank you for using our system!\n");
                exit(0);
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}