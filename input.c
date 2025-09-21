#include "vending_machine.h"

int get_user_choice(void) {
    int choice;
    if (scanf("%d", &choice) != 1) {
        // Clear invalid input
        while (getchar() != '\n');
        return -1;
    }
    return choice;
}

int get_quantity_input(void) {
    int quantity;
    printf("Enter quantity: ");
    
    if (scanf("%d", &quantity) != 1 || quantity <= 0) {
        while (getchar() != '\n');
        printf("Invalid quantity. Please enter a positive number.\n");
        return -1;
    }
    
    return quantity;
}

double get_payment_input(void) {
    double payment;
    
    if (scanf("%lf", &payment) != 1) {
        while (getchar() != '\n');
        return -1.0;
    }
    
    return payment;
}