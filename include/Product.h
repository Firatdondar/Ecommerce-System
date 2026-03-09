#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Abstract base class to hold basic product properties.
class Product {
protected:
    int id;
    string productName;
    string category;
    double price;
    int stock;

public:
    // Constructor to initialize base variables.
    Product(int _id, string _name, string _cat, double _price, int _stock) {
        id = _id;
        productName = _name;
        category = _cat;
        price = _price;
        stock = _stock;
    }

    // Virtual destructor for memory management.
    virtual ~Product() {}

    // Encapsulation getters.
    int getId() const { return id; }
    string getName() const { return productName; }
    string getCategory() const { return category; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }

    // Stock management methods.
    void decreaseStock(int amount) { if (stock >= amount) stock -= amount; }
    void increaseStock(int amount) { stock += amount; }

    // Virtual method to print product details.
    virtual void print() const {
        cout << left 
             << setw(6) << id 
             << setw(25) << productName 
             << setw(14) << category 
             << setw(8) << price << " TL    "
             << setw(5) << stock << " Pcs";
    }
};

// Electronics category class.
class Electronics : public Product {
private:
    string brand;
    string model; 
    int warrantyYears;
public:
    Electronics(int _id, string _name, double _price, int _stock, string _brand, string _model, int _warranty)
        : Product(_id, _name, "Electronics", _price, _stock) {
        brand = _brand;
        model = _model;
        warrantyYears = _warranty;
    }
    
    // Call base class print and append specific properties.
    void print() const override {
        Product::print();
        cout << " | " << brand << " " << model << ", " << warrantyYears << " Yrs Wrnty." << endl;
    }
};

// Furniture category class.
class Furniture : public Product {
private:
    string material;
    string color;
    bool requiresAssembly;
public:
    Furniture(int _id, string _name, double _price, int _stock, string _material, string _color, bool _assembly)
        : Product(_id, _name, "Furniture", _price, _stock) {
        material = _material;
        color = _color;
        requiresAssembly = _assembly;
    }

    void print() const override {
        Product::print();
        cout << " | " << material << ", " << color << ", Assembly: " << (requiresAssembly ? "Yes" : "No") << endl;
    }
};

// Clothing category class.
class Clothing : public Product {
private:
    string size;
    string fabric;
    string gender;
public:
    Clothing(int _id, string _name, double _price, int _stock, string _size, string _fabric, string _gender)
        : Product(_id, _name, "Clothing", _price, _stock) {
        size = _size;
        fabric = _fabric;
        gender = _gender;
    }

    void print() const override {
        Product::print();
        cout << " | " << size << ", " << fabric << " (" << gender << ")" << endl;
    }
};

// Cosmetics category class.
class Cosmetics : public Product {
private:
    string brand;
    string skinType;
    int volume;
public:
    Cosmetics(int _id, string _name, double _price, int _stock, string _brand, string _skin, int _volume)
        : Product(_id, _name, "Cosmetics", _price, _stock) {
        brand = _brand;
        skinType = _skin;
        volume = _volume;
    }

    void print() const override {
        Product::print();
        cout << " | " << brand << ", " << skinType << ", " << volume << "ml" << endl;
    }
};

// Kitchenware category class.
class Kitchenware : public Product {
private:
    string material;
    int pieceCount;
    string brand;
public:
    Kitchenware(int _id, string _name, double _price, int _stock, string _material, int _piece, string _brand)
        : Product(_id, _name, "Kitchenware", _price, _stock) {
        material = _material;
        pieceCount = _piece;
        brand = _brand;
    }

    void print() const override {
        Product::print();
        cout << " | " << brand << ", " << material << ", " << pieceCount << " Pcs" << endl;
    }
};

#endif