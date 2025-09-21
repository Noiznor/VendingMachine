# Vending Machine Simulator

A modular C application that simulates a snack vending machine with complete inventory management and transaction processing.

## Features

### Core Functionality
- **Product Catalog**: 4 different products (Candy, Chips, Cookies, Soda)
- **Inventory Management**: Track stock levels starting with 100 units per item
- **Transaction Processing**: Handle quantity selection, payment, and change
- **Stock Validation**: Verify availability before completing purchases
- **Dynamic Display**: Real-time updates of prices, stock, and machine balance

### Architecture
- **Modular Design**: Separated into logical modules for maintainability
- **Clean Interface**: Console-based UI with screen clearing between operations
- **Error Handling**: Robust input validation and error messages
- **Memory Management**: Efficient use of structures and arrays

## Project Structure

```
├── vending_machine.h    # Main header with structures and function prototypes
├── main.c              # Main program loop and user interface
├── product.c           # Product catalog and product management
├── inventory.c         # Stock tracking and inventory operations
├── transaction.c       # Payment processing and transaction handling
├── display.c           # UI functions and screen formatting
├── input.c             # User input handling and validation
├── Makefile           # Build configuration
└── README.md          # This documentation
```

## Building and Running

### Prerequisites
- GCC compiler
- Make utility
- Terminal/console environment

### Build Commands

```bash
# Build the application
make

# Clean build artifacts
make clean

# Rebuild everything
make rebuild

# Build and run
make run

# Build with debug symbols
make debug
```

### Manual Compilation
```bash
gcc -Wall -Wextra -std=c99 -pedantic main.c product.c inventory.c transaction.c display.c input.c -o vending_machine
```

## Usage

1. **Start the program**: `./vending_machine`
2. **Select products**: Choose from options 1-4
3. **Enter quantity**: Specify how many items you want
4. **Make payment**: Insert money to complete the transaction
5. **View inventory**: Option 5 shows current stock levels
6. **Exit**: Option 0 to quit

### Menu Options
- `1` - Candy ($1.25)
- `2` - Chips ($2.50)
- `3` - Cookies ($3.75)
- `4` - Soda ($2.00)
- `5` - View Inventory Status
- `0` - Exit

## Technical Details

### Data Structures
```c
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
```

### Key Functions
- `initialize_products()` - Set up product catalog
- `complete_transaction()` - Handle entire purchase process
- `process_payment()` - Manage payment and change calculation
- `update_stock()` - Modify inventory levels
- `display_main_menu()` - Show current machine state

## Design Principles

- **Separation of Concerns**: Each module handles specific functionality
- **Data Encapsulation**: Structures group related data
- **Error Handling**: Validate inputs and handle edge cases
- **User Experience**: Clear prompts and informative messages
- **Maintainability**: Modular code structure for easy updates

## Future Enhancements

- Add more product types
- Implement restocking functionality
- Add sales reporting
- Support for different payment methods
- Configuration file for prices and initial stock
