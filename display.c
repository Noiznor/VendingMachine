#include "vending_machine.h"

void display_welcome_message(void) {
    CLEAR_SCREEN();
    printf("╔══════════════════════════════════════╗\n");
    printf("║        WELCOME TO SNACK MACHINE     ║\n");
    printf("║         Your favorite snacks         ║\n");
    printf("╚══════════════════════════════════════╝\n");
    printf("\n");
}

void display_main_menu(const VendingMachine *machine) {
    printf("=== AVAILABLE PRODUCTS ===\n");
    
    for (int i = 0; i < machine->total_products; i++) {
        display_product_info(&machine->products[i]);
    }
    
    printf("\nMachine Status:\n");
    printf("Cash Balance: $%.2f\n", machine->cash_balance);
    
    display_separator();
    printf("5. View Inventory Status\n");
    printf("0. Exit\n");
    display_separator();
    printf("Enter your choice: ");
}

void display_transaction_summary(const Product *product, int quantity, double total_cost) {
    printf("\n=== TRANSACTION SUMMARY ===\n");
    printf("Product: %s\n", product->name);
    printf("Unit Price: $%.2f\n", product->price);
    printf("Quantity: %d\n", quantity);
    printf("Total Cost: $%.2f\n", total_cost);
    display_separator();
}

void display_insufficient_stock_message(const Product *product, int requested, int available) {
    printf("\n⚠️  INSUFFICIENT STOCK ⚠️\n");
    printf("Product: %s\n", product->name);
    printf("Requested quantity: %d\n", requested);
    printf("Available stock: %d\n", available);
    printf("Please select a smaller quantity or choose a different product.\n");
}

void display_payment_prompt(double amount_due) {
    printf("Please insert $%.2f: $", amount_due);
}

void display_separator(void) {
    printf("----------------------------------------\n");
}

void pause_for_user(void) {
    printf("\nPress Enter to continue...");
    getchar();
    getchar(); // Handle the newline from previous input
}