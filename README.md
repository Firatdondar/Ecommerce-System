# E-Commerce Object-Oriented Programming Project

This project is a C++ Object-Oriented Programming (OOP) console application that simulates an e-commerce platform. It features user authentication, a product catalog across various categories, shopping cart management, and a checkout system with discount/shipping logic based on customer tiers.

## Features
- **Polymorphism & Inheritance:** Demonstrates OOP concepts with base `Product` and `Customer` classes branching into specialized sub-classes.
- **File I/O:** Loads customer accounts dynamically from a text file (`customers.txt`).
- **Cart Management:** Add to cart, remove items, calculate subtotals, and simulate stock deduction.
- **Checkout Calculations:** Calculates final price using shipping costs and customer-specific discount rates (Standard, Premium, Corporate).

## How to Run
1. Ensure `customers.txt` is in the same directory as the executable.
2. Build the project using CMake or your preferred C++ compiler (requires C++17).
3. Run the executable and log in using the credentials from `customers.txt` (e.g., Username: `aliveli`, Password: `12345`).