#ifndef VENDING_MACHINE_H
#define VENDING_MACHINE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PRODUCTS 4
#define MAX_NAME_LENGTH 20
#define INITIAL_STOCK 100
#define CLEAR_SCREEN() system("clear || cls")

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    double price;
    int stock;
} Product;

typedef struct {
    Product products[MAX_PRODUCTS];
    double cash_balance;
    int total_products;
} VendingMachine;

// Product management functions
void initialize_products(VendingMachine *machine);
Product* get_product_by_id(VendingMachine *machine, int id);
void display_product_info(const Product *product);

// Inventory management functions
bool is_product_available(const Product *product, int quantity);
void update_stock(Product *product, int quantity);
void display_inventory_status(const VendingMachine *machine);

// Transaction functions
double calculate_total_cost(const Product *product, int quantity);
bool process_payment(VendingMachine *machine, double amount_due);
bool complete_transaction(VendingMachine *machine, int product_id, int quantity);

// Display functions
void display_welcome_message(void);
void display_main_menu(const VendingMachine *machine);
void display_transaction_summary(const Product *product, int quantity, double total_cost);
void display_insufficient_stock_message(const Product *product, int requested, int available);
void display_payment_prompt(double amount_due);

// Input functions
int get_user_choice(void);
int get_quantity_input(void);
double get_payment_input(void);

// Utility functions
void pause_for_user(void);
void display_separator(void);

#endif