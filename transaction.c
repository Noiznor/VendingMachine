#include "vending_machine.h"

double calculate_total_cost(const Product *product, int quantity) {
    if (product == NULL || quantity <= 0) {
        return 0.0;
    }
    return product->price * quantity;
}

bool process_payment(VendingMachine *machine, double amount_due) {
    double total_paid = 0.0;
    double payment;
    
    printf("\nTotal amount due: $%.2f\n", amount_due);
    
    while (total_paid < amount_due) {
        display_payment_prompt(amount_due - total_paid);
        payment = get_payment_input();
        
        if (payment < 0) {
            printf("Invalid payment amount. Please enter a positive value.\n");
            continue;
        }
        
        total_paid += payment;
        printf("Payment received: $%.2f\n", payment);
        printf("Total paid: $%.2f\n", total_paid);
        
        if (total_paid < amount_due) {
            printf("Remaining balance: $%.2f\n", amount_due - total_paid);
        }
    }
    
    // Calculate and display change
    double change = total_paid - amount_due;
    if (change > 0) {
        printf("Change dispensed: $%.2f\n", change);
    }
    
    // Add the net amount to machine's cash balance
    machine->cash_balance += amount_due;
    
    return true;
}

bool complete_transaction(VendingMachine *machine, int product_id, int quantity) {
    Product *product = get_product_by_id(machine, product_id);
    
    if (product == NULL) {
        printf("Error: Product not found.\n");
        return false;
    }
    
    // Check stock availability
    if (!is_product_available(product, quantity)) {
        display_insufficient_stock_message(product, quantity, product->stock);
        return false;
    }
    
    // Calculate total cost
    double total_cost = calculate_total_cost(product, quantity);
    
    // Display transaction summary
    display_transaction_summary(product, quantity, total_cost);
    
    // Process payment
    if (!process_payment(machine, total_cost)) {
        printf("Payment processing failed.\n");
        return false;
    }
    
    // Update inventory
    update_stock(product, quantity);
    
    printf("\nTransaction completed successfully!\n");
    printf("Dispensing %d x %s\n", quantity, product->name);
    printf("Thank you for your purchase!\n");
    
    return true;
}