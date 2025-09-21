#include "vending_machine.h"

void initialize_products(VendingMachine *machine) {
    // Initialize product catalog
    machine->products[0] = (Product){1, "Candy", 1.25, INITIAL_STOCK};
    machine->products[1] = (Product){2, "Chips", 2.50, INITIAL_STOCK};
    machine->products[2] = (Product){3, "Cookies", 3.75, INITIAL_STOCK};
    machine->products[3] = (Product){4, "Soda", 2.00, INITIAL_STOCK};
    
    machine->total_products = MAX_PRODUCTS;
    machine->cash_balance = 0.0;
    
    printf("Vending machine initialized with %d products.\n", machine->total_products);
}

Product* get_product_by_id(VendingMachine *machine, int id) {
    for (int i = 0; i < machine->total_products; i++) {
        if (machine->products[i].id == id) {
            return &machine->products[i];
        }
    }
    return NULL;
}

void display_product_info(const Product *product) {
    if (product == NULL) {
        printf("Product not found.\n");
        return;
    }
    
    printf("%-2d. %-12s $%.2f (Stock: %d)\n", 
           product->id, 
           product->name, 
           product->price, 
           product->stock);
}