#ifndef CART_H
#define CART_H

#include <iostream>
#include <vector>
#include "Product.h"
#include "Customer.h"

using namespace std;

// Struct to hold cart items.
struct CartItem {
    Product* product;
    int quantity;
};

// Class handling shopping cart operations and stock management.
class Cart {
private:
    vector<CartItem> items;

public:
    Cart() {}
    
    // Destructor: if the cart is destroyed without purchase, restore stocks.
    ~Cart() { clear(); }

    // Adds a product to the cart. Prevents adding if stock is insufficient.
    void addItem(Product* newProduct, int quantity) {
        if (quantity <= 0) return;
        if (newProduct->getStock() < quantity) {
            cout << "ERROR: Insufficient Stock! Available: " << newProduct->getStock() << endl;
            return;
        }
        
        // If product is already in the cart, increase quantity instead of adding a new row.
        bool found = false;
        for (size_t i = 0; i < items.size(); i++) {
            if (items[i].product->getId() == newProduct->getId()) {
                items[i].quantity += quantity;
                found = true;
                break;
            }
        }
        if (!found) {
            CartItem newItem;
            newItem.product = newProduct;
            newItem.quantity = quantity;
            items.push_back(newItem);
        }
        
        // Deduct added item from stock.
        newProduct->decreaseStock(quantity);
        cout << quantity << " pcs " << newProduct->getName() << " added to cart." << endl;
    }

    // Removes an item from the cart and restores its stock.
    void removeItem(int productId) {
        for (size_t i = 0; i < items.size(); i++) {
            if (items[i].product->getId() == productId) {
                items[i].product->increaseStock(items[i].quantity);
                cout << items[i].product->getName() << " removed from cart." << endl;
                items.erase(items.begin() + i);
                return;
            }
        }
        cout << "Product not found in cart." << endl;
    }

    // Empties the cart entirely and restores stocks.
    void clear() {
        for (size_t i = 0; i < items.size(); i++) {
            items[i].product->increaseStock(items[i].quantity);
        }
        items.clear();
    }

    // Lists the cart contents and subtotals.
    void listItems() const {
        if (items.empty()) {
            cout << "Your cart is empty." << endl;
            return;
        }
        cout << "\n--- SHOPPING CART ---" << endl;
        cout << left << setw(5) << "ID" << setw(20) << "Product" << setw(10) << "Unit P." << setw(8) << "Qty" << setw(10) << "Total" << endl;
        cout << "--------------------------------------------------------" << endl;
        for (size_t i = 0; i < items.size(); i++) {
            double total = items[i].product->getPrice() * items[i].quantity;
            cout << left << setw(5) << items[i].product->getId()
                 << setw(20) << items[i].product->getName()
                 << setw(10) << items[i].product->getPrice()
                 << setw(8) << items[i].quantity
                 << setw(10) << total << endl;
        }
        cout << "--------------------------------------------------------" << endl;
    }

    // Calculates the cart's subtotal.
    double getSubtotal() const {
        double total = 0;
        for (size_t i = 0; i < items.size(); i++) {
            total += (items[i].product->getPrice() * items[i].quantity);
        }
        return total;
    }

    bool isEmpty() const { return items.empty(); }
    
    // Clears the cart upon purchase completion without restoring stocks (since they are sold).
    void completePurchase() { items.clear(); }
};

#endif