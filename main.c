#include "vending_machine.h"

int main(void) {
    VendingMachine machine;
    int choice, quantity;
    bool running = true;
    
    // Initialize the vending machine
    initialize_products(&machine);
    
    display_welcome_message();
    pause_for_user();
    
    while (running) {
        CLEAR_SCREEN();
        display_main_menu(&machine);
        
        choice = get_user_choice();
        
        switch (choice) {
            case 1:
            case 2:
            case 3:
            case 4: {
                // Product selection
                Product *selected_product = get_product_by_id(&machine, choice);
                
                if (selected_product == NULL) {
                    printf("Invalid product selection.\n");
                    break;
                }
                
                printf("\nYou selected: %s ($%.2f each)\n", 
                       selected_product->name, selected_product->price);
                printf("Available stock: %d\n", selected_product->stock);
                
                if (selected_product->stock == 0) {
                    printf("Sorry, this product is out of stock.\n");
                    break;
                }
                
                quantity = get_quantity_input();
                
                if (quantity > 0) {
                    complete_transaction(&machine, choice, quantity);
                } else {
                    printf("Invalid quantity entered.\n");
                }
                
                pause_for_user();
                break;
            }
            
            case 5:
                // Display inventory status
                CLEAR_SCREEN();
                display_inventory_status(&machine);
                pause_for_user();
                break;
                
            case 0:
                printf("\nThank you for using the Snack Machine!\n");
                printf("Have a great day!\n");
                running = false;
                break;
                
            default:
                printf("Invalid choice. Please select a valid option.\n");
                pause_for_user();
                break;
        }
    }
    
    return 0;
}