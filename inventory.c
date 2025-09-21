#include "vending_machine.h"

bool is_product_available(const Product *product, int quantity) {
    if (product == NULL) {
        return false;
    }
    return product->stock >= quantity;
}

void update_stock(Product *product, int quantity) {
    if (product != NULL && product->stock >= quantity) {
        product->stock -= quantity;
    }
}

void display_inventory_status(const VendingMachine *machine) {
    printf("\n=== INVENTORY STATUS ===\n");
    
    int total_items = 0;
    for (int i = 0; i < machine->total_products; i++) {
        total_items += machine->products[i].stock;
    }
    
    printf("Total items in stock: %d\n", total_items);
    printf("Machine cash balance: $%.2f\n", machine->cash_balance);
    
    printf("\nDetailed stock levels:\n");
    for (int i = 0; i < machine->total_products; i++) {
        printf("  %s: %d units\n", 
               machine->products[i].name, 
               machine->products[i].stock);
    }
    
    display_separator();
}