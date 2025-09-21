const readline = require('readline');

// Constants
const MAX_PRODUCTS = 4;
const INITIAL_STOCK = 100;

// Product structure
class Product {
    constructor(id, name, price, stock = INITIAL_STOCK) {
        this.id = id;
        this.name = name;
        this.price = price;
        this.stock = stock;
    }
}

// Vending Machine class
class VendingMachine {
    constructor() {
        this.products = [];
        this.cashBalance = 0.0;
        this.totalProducts = 0;
        this.rl = readline.createInterface({
            input: process.stdin,
            output: process.stdout
        });
    }

    // Initialize products
    initializeProducts() {
        this.products = [
            new Product(1, "Candy", 1.25),
            new Product(2, "Chips", 2.50),
            new Product(3, "Cookies", 3.75),
            new Product(4, "Soda", 2.00)
        ];
        this.totalProducts = MAX_PRODUCTS;
        console.log(`Vending machine initialized with ${this.totalProducts} products.`);
    }

    // Get product by ID
    getProductById(id) {
        return this.products.find(product => product.id === id) || null;
    }

    // Display product info
    displayProductInfo(product) {
        if (!product) {
            console.log("Product not found.");
            return;
        }
        console.log(`${product.id.toString().padEnd(2)}. ${product.name.padEnd(12)} $${product.price.toFixed(2)} (Stock: ${product.stock})`);
    }

    // Check if product is available
    isProductAvailable(product, quantity) {
        return product && product.stock >= quantity;
    }

    // Update stock
    updateStock(product, quantity) {
        if (product && product.stock >= quantity) {
            product.stock -= quantity;
        }
    }

    // Calculate total cost
    calculateTotalCost(product, quantity) {
        if (!product || quantity <= 0) {
            return 0.0;
        }
        return product.price * quantity;
    }

    // Display functions
    clearScreen() {
        console.clear();
    }

    displayWelcomeMessage() {
        this.clearScreen();
        console.log("╔══════════════════════════════════════╗");
        console.log("║        WELCOME TO SNACK MACHINE     ║");
        console.log("║         Your favorite snacks         ║");
        console.log("╚══════════════════════════════════════╝");
        console.log("");
    }

    displayMainMenu() {
        console.log("=== AVAILABLE PRODUCTS ===");
        
        this.products.forEach(product => {
            this.displayProductInfo(product);
        });
        
        console.log("\nMachine Status:");
        console.log(`Cash Balance: $${this.cashBalance.toFixed(2)}`);
        
        this.displaySeparator();
        console.log("5. View Inventory Status");
        console.log("0. Exit");
        this.displaySeparator();
    }

    displayInventoryStatus() {
        console.log("\n=== INVENTORY STATUS ===");
        
        const totalItems = this.products.reduce((sum, product) => sum + product.stock, 0);
        
        console.log(`Total items in stock: ${totalItems}`);
        console.log(`Machine cash balance: $${this.cashBalance.toFixed(2)}`);
        
        console.log("\nDetailed stock levels:");
        this.products.forEach(product => {
            console.log(`  ${product.name}: ${product.stock} units`);
        });
        
        this.displaySeparator();
    }

    displayTransactionSummary(product, quantity, totalCost) {
        console.log("\n=== TRANSACTION SUMMARY ===");
        console.log(`Product: ${product.name}`);
        console.log(`Unit Price: $${product.price.toFixed(2)}`);
        console.log(`Quantity: ${quantity}`);
        console.log(`Total Cost: $${totalCost.toFixed(2)}`);
        this.displaySeparator();
    }

    displayInsufficientStockMessage(product, requested, available) {
        console.log("\n⚠️  INSUFFICIENT STOCK ⚠️");
        console.log(`Product: ${product.name}`);
        console.log(`Requested quantity: ${requested}`);
        console.log(`Available stock: ${available}`);
        console.log("Please select a smaller quantity or choose a different product.");
    }

    displaySeparator() {
        console.log("----------------------------------------");
    }

    // Input functions
    async getUserChoice() {
        return new Promise((resolve) => {
            this.rl.question("Enter your choice: ", (answer) => {
                const choice = parseInt(answer);
                resolve(isNaN(choice) ? -1 : choice);
            });
        });
    }

    async getQuantityInput() {
        return new Promise((resolve) => {
            this.rl.question("Enter quantity: ", (answer) => {
                const quantity = parseInt(answer);
                if (isNaN(quantity) || quantity <= 0) {
                    console.log("Invalid quantity. Please enter a positive number.");
                    resolve(-1);
                } else {
                    resolve(quantity);
                }
            });
        });
    }

    async getPaymentInput(amountDue) {
        return new Promise((resolve) => {
            this.rl.question(`Please insert $${amountDue.toFixed(2)}: $`, (answer) => {
                const payment = parseFloat(answer);
                resolve(isNaN(payment) ? -1.0 : payment);
            });
        });
    }

    async pauseForUser() {
        return new Promise((resolve) => {
            this.rl.question("\nPress Enter to continue...", () => {
                resolve();
            });
        });
    }

    // Process payment
    async processPayment(amountDue) {
        let totalPaid = 0.0;
        
        console.log(`\nTotal amount due: $${amountDue.toFixed(2)}`);
        
        while (totalPaid < amountDue) {
            const payment = await this.getPaymentInput(amountDue - totalPaid);
            
            if (payment < 0) {
                console.log("Invalid payment amount. Please enter a positive value.");
                continue;
            }
            
            totalPaid += payment;
            console.log(`Payment received: $${payment.toFixed(2)}`);
            console.log(`Total paid: $${totalPaid.toFixed(2)}`);
            
            if (totalPaid < amountDue) {
                console.log(`Remaining balance: $${(amountDue - totalPaid).toFixed(2)}`);
            }
        }
        
        // Calculate and display change
        const change = totalPaid - amountDue;
        if (change > 0) {
            console.log(`Change dispensed: $${change.toFixed(2)}`);
        }
        
        // Add the net amount to machine's cash balance
        this.cashBalance += amountDue;
        
        return true;
    }

    // Complete transaction
    async completeTransaction(productId, quantity) {
        const product = this.getProductById(productId);
        
        if (!product) {
            console.log("Error: Product not found.");
            return false;
        }
        
        // Check stock availability
        if (!this.isProductAvailable(product, quantity)) {
            this.displayInsufficientStockMessage(product, quantity, product.stock);
            return false;
        }
        
        // Calculate total cost
        const totalCost = this.calculateTotalCost(product, quantity);
        
        // Display transaction summary
        this.displayTransactionSummary(product, quantity, totalCost);
        
        // Process payment
        if (!(await this.processPayment(totalCost))) {
            console.log("Payment processing failed.");
            return false;
        }
        
        // Update inventory
        this.updateStock(product, quantity);
        
        console.log("\nTransaction completed successfully!");
        console.log(`Dispensing ${quantity} x ${product.name}`);
        console.log("Thank you for your purchase!");
        
        return true;
    }

    // Main program loop
    async run() {
        this.initializeProducts();
        this.displayWelcomeMessage();
        await this.pauseForUser();
        
        let running = true;
        
        while (running) {
            this.clearScreen();
            this.displayMainMenu();
            
            const choice = await this.getUserChoice();
            
            switch (choice) {
                case 1:
                case 2:
                case 3:
                case 4: {
                    // Product selection
                    const selectedProduct = this.getProductById(choice);
                    
                    if (!selectedProduct) {
                        console.log("Invalid product selection.");
                        break;
                    }
                    
                    console.log(`\nYou selected: ${selectedProduct.name} ($${selectedProduct.price.toFixed(2)} each)`);
                    console.log(`Available stock: ${selectedProduct.stock}`);
                    
                    if (selectedProduct.stock === 0) {
                        console.log("Sorry, this product is out of stock.");
                        break;
                    }
                    
                    const quantity = await this.getQuantityInput();
                    
                    if (quantity > 0) {
                        await this.completeTransaction(choice, quantity);
                    } else {
                        console.log("Invalid quantity entered.");
                    }
                    
                    await this.pauseForUser();
                    break;
                }
                
                case 5:
                    // Display inventory status
                    this.clearScreen();
                    this.displayInventoryStatus();
                    await this.pauseForUser();
                    break;
                    
                case 0:
                    console.log("\nThank you for using the Snack Machine!");
                    console.log("Have a great day!");
                    running = false;
                    break;
                    
                default:
                    console.log("Invalid choice. Please select a valid option.");
                    await this.pauseForUser();
                    break;
            }
        }
        
        this.rl.close();
    }
}

// Create and run the vending machine
const vendingMachine = new VendingMachine();
vendingMachine.run().catch(console.error);