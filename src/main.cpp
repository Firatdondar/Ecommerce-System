#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <iomanip>

#include "Product.h"
#include "Customer.h"
#include "Cart.h"

using namespace std;

// Global lists and variables.
vector<Product*> products;
vector<Customer*> customers;
Cart cart;
Customer* activeCustomer = NULL;

// Manually loading products into memory.
void loadProducts() {
    // Electronics
    products.push_back(new Electronics(101, "Smartphone", 35000, 20, "Apple", "iPhone 14", 2));
    products.push_back(new Electronics(102, "Laptop", 28000, 10, "Lenovo", "ThinkPad X1", 2));
    products.push_back(new Electronics(103, "Bluetooth Headphones", 1500, 50, "JBL", "Tune 510BT", 2));
    products.push_back(new Electronics(104, "Smartwatch", 4000, 30, "Samsung", "Galaxy Watch 6", 2));
    products.push_back(new Electronics(105, "Powerbank", 800, 100, "Philips", "DLP100", 2));

    // Furniture
    products.push_back(new Furniture(201, "Study Desk", 2500, 15, "Wood", "Walnut", true));
    products.push_back(new Furniture(202, "Bookshelf", 1800, 20, "MDF", "White", true));
    products.push_back(new Furniture(203, "Chair", 900, 40, "Plastic/Metal", "Black", false));
    products.push_back(new Furniture(204, "TV Stand", 3200, 10, "Wood", "Oak", true));
    products.push_back(new Furniture(205, "Bean Bag Chair", 750, 30, "Fabric", "Red", false));

    // Clothing
    products.push_back(new Clothing(301, "Jeans", 800, 50, "32/32", "Denim", "Men"));
    products.push_back(new Clothing(302, "Sweatshirt", 600, 60, "L", "Cotton", "Unisex"));
    products.push_back(new Clothing(303, "Winter Coat", 2500, 20, "XL", "Polyester", "Women"));
    products.push_back(new Clothing(304, "Sneakers", 1800, 30, "42", "Leather/Synthetic", "Men"));
    products.push_back(new Clothing(305, "Beanie", 200, 100, "Std", "Wool", "Unisex"));

    // Cosmetics
    products.push_back(new Cosmetics(401, "Face Cream", 450, 40, "Nivea", "Dry Skin", 50));
    products.push_back(new Cosmetics(402, "Perfume", 1200, 25, "Avon", "All Skin Types", 100));
    products.push_back(new Cosmetics(403, "Shampoo", 120, 80, "Pantene", "Oily Hair", 400));
    products.push_back(new Cosmetics(404, "Sunscreen", 350, 50, "Sebamed", "Sensitive", 150));
    products.push_back(new Cosmetics(405, "Face Cleanser", 180, 60, "Garnier", "Combination", 200));

    // Kitchenware
    products.push_back(new Kitchenware(501, "Pot Set", 4500, 10, "Steel", 7, "Korkmaz"));
    products.push_back(new Kitchenware(502, "Pan", 600, 30, "Granite", 1, "Tefal"));
    products.push_back(new Kitchenware(503, "Dinner Set", 2000, 15, "Porcelain", 24, "Kutahya"));
    products.push_back(new Kitchenware(504, "Knife Set", 900, 25, "Stainless Steel", 6, "Solingen"));
    products.push_back(new Kitchenware(505, "Water Glass", 150, 100, "Glass", 6, "Pasabahce"));
}

// Parsing customers.txt and creating respective objects.
void loadCustomers() {
    ifstream file("data/customers.txt");
    if (!file.is_open()) {
        file.open("customers.txt");
    }
    if (!file.is_open()) {
        cout << "ERROR: customers.txt file could not be opened!" << endl;
        return;
    }
    string line;
    getline(file, line); // Skip the header row.

    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        vector<string> data;
        while (getline(ss, cell, ',')) data.push_back(cell);

        if (data.size() < 6) continue;
        int id = stoi(data[0]);
        string type = data[5];
        // Clean up carriage returns if on Windows
        if (!type.empty() && type[type.length()-1] == '\r') type.erase(type.length()-1);

        if (type == "Standard") customers.push_back(new Standard(id, data[1], data[2], data[3], data[4]));
        else if (type == "Premium") customers.push_back(new Premium(id, data[1], data[2], data[3], data[4]));
        else if (type == "Corporate") {
            string company = (data.size() > 6) ? data[6] : "";
            string taxNo = (data.size() > 7) ? data[7] : "";
            if (!taxNo.empty() && taxNo[taxNo.length()-1] == '\r') taxNo.erase(taxNo.length()-1);
            customers.push_back(new Corporate(id, data[1], data[2], data[3], data[4], company, taxNo));
        }
    }
    file.close();
}

// Handling user login and validation.
bool login() {
    string uName, pass;
    cout << "\n=== GENERAL E-COMMERCE STORE ===" << endl;
    cout << "Username (Enter '0' to exit): "; cin >> uName;
    
    if (uName == "0") {
        cout << "Shutting down program..." << endl;
        exit(0);
    }
    
    cout << "Password: "; cin >> pass;

    bool userFound = false;
    for (size_t i = 0; i < customers.size(); i++) {
        if (customers[i]->getUsername() == uName) {
            userFound = true;
            if (customers[i]->getPassword() == pass) {
                activeCustomer = customers[i];
                cout << "\nWelcome, " << activeCustomer->getFullName() << endl;
                return true;
            } else {
                cout << "ERROR: Incorrect password!" << endl;
                return false;
            }
        }
    }

    if (!userFound) {
        cout << "ERROR: No account found with this username!" << endl;
    }
    return false;
}

// Function to print products in a tabular format based on category.
void listCategory(string selectedCategory) {
    cout << "\n--- " << selectedCategory << " DEPARTMENT ---" << endl;
    cout << left << setw(6) << "ID" 
         << setw(25) << "Product Name" 
         << setw(14) << "Category" 
         << setw(14) << "Price" 
         << setw(12) << "Stock" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    for (size_t i = 0; i < products.size(); i++) {
        if (products[i]->getCategory() == selectedCategory) products[i]->print();
    }
    cout << "--------------------------------------------------------------------------------" << endl;
}

// Manages payments, discounts, shipping, and prints the order receipt.
void processPayment() {
    if (cart.isEmpty()) { cout << "Cart is empty." << endl; return; }

    double subtotal = cart.getSubtotal();
    double discount = subtotal * activeCustomer->getDiscountRate();
    double shipping = activeCustomer->getShippingCost(subtotal - discount);
    
    int choice;
    cout << "\n1. Credit Card (+2%)\n2. Wire Transfer (-3%)\n3. Cash on Delivery (+30TL)\nChoice: "; cin >> choice;
    
    double diff = 0;
    string method = "Cash on Delivery";
    if (choice == 1) { diff = (subtotal - discount) * 0.02; method = "Credit Card"; }
    else if (choice == 2) { diff = -(subtotal - discount) * 0.03; method = "Wire Transfer"; }
    else { diff = 30; }

    cout << "\n--- ORDER RECEIPT ---" << endl;
    cart.listItems();
    cout << "Subtotal: " << subtotal << " TL" << endl;
    cout << "Discount: -" << discount << " TL" << endl;
    cout << "Shipping: " << shipping << " TL" << endl;
    cout << "Payment Diff (" << method << "): " << diff << " TL" << endl;
    cout << "GRAND TOTAL: " << (subtotal - discount + shipping + diff) << " TL" << endl;
    
    cart.completePurchase();
}

// Menu for cart operations (View, Delete, Checkout).
void cartMenu() {
    int choice;
    while(true) {
        cart.listItems();
        cout << "\n[1] Remove Item [2] Checkout [0] Back to Main Menu\nChoice: "; cin >> choice;
        if (choice == 0) break;
        if (choice == 1) { int id; cout << "Product ID: "; cin >> id; cart.removeItem(id); }
        else if (choice == 2) { processPayment(); if(cart.isEmpty()) break; }
    }
}

// Main application menu for navigating categories.
void mainMenu() {
    int choice;
    while(true) {
        cout << "\n=== DEPARTMENTS ===" << endl;
        cout << "1. Electronics\n2. Furniture\n3. Clothing\n4. Cosmetics\n5. Kitchenware" << endl;
        cout << "[6] Go to Cart" << endl;
        cout << "[9] Logout (Switch User)" << endl;
        cout << "[0] Exit Program" << endl;
        cout << "Choice: "; cin >> choice;

        if (choice == 0) {
            cout << "Shutting down program. Have a nice day!" << endl;
            exit(0);
        }
        if (choice == 9) {
            cout << "Logging out..." << endl;
            break;
        }
        if (choice == 6) { cartMenu(); continue; }

        string cat = "";
        if (choice == 1) cat = "Electronics";
        else if (choice == 2) cat = "Furniture";
        else if (choice == 3) cat = "Clothing";
        else if (choice == 4) cat = "Cosmetics";
        else if (choice == 5) cat = "Kitchenware";
        else continue;

        listCategory(cat);
        
        int id, qty;
        cout << "\nEnter Product ID to add to cart (0 to cancel): "; 
        cin >> id;
        
        if (id != 0) {
            cout << "How many pieces?: ";
            cin >> qty;
            
            bool found = false;
            for (size_t i = 0; i < products.size(); i++) {
                if (products[i]->getId() == id) { 
                    cart.addItem(products[i], qty); 
                    found = true; 
                    break; 
                }
            }
            if (!found) cout << "Invalid Product ID!" << endl;
        }
    }
}

int main() {
    loadProducts();
    loadCustomers();
    
    while (true) {
        if (login()) {
            mainMenu(); 
            activeCustomer = NULL; 
            cart.clear();     
        } 
    }
    return 0;
}
