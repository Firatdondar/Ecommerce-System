#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Abstract base class holding customer information.
class Customer {
protected:
    int id;
    string firstName;
    string lastName;
    string username;
    string password;
    string customerType;

public:
    // Constructor to assign customer details.
    Customer(int _id, string _fName, string _lName, string _uName, string _pass, string _type) {
        id = _id;
        firstName = _fName;
        lastName = _lName;
        username = _uName;
        password = _pass;
        customerType = _type;
    }
    
    virtual ~Customer() {}

    // Getter methods.
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getFullName() const { return firstName + " " + lastName; }
    string getType() const { return customerType; }

    // Pure virtual functions for discount and shipping calculations.
    // These will be overridden in derived classes.
    virtual double getDiscountRate() const = 0; 
    virtual double getShippingCost(double cartTotal) const = 0;

    virtual void print() const {
        cout << left << setw(5) << id 
             << setw(20) << (firstName + " " + lastName)
             << setw(15) << customerType;
    }
};

// Intermediate class for individual customers.
class Individual : public Customer {
public:
    Individual(int _id, string _fName, string _lName, string _uName, string _pass, string _type)
        : Customer(_id, _fName, _lName, _uName, _pass, _type) {}
};

// Standard customers: No discount, paid shipping.
class Standard : public Individual {
public:
    Standard(int _id, string _fName, string _lName, string _uName, string _pass)
        : Individual(_id, _fName, _lName, _uName, _pass, "Standard") {}

    double getDiscountRate() const override { return 0.0; }
    double getShippingCost(double cartTotal) const override { return 30.0; }
};

// Premium customers: 10% discount and free shipping for orders over 500.
class Premium : public Individual {
public:
    Premium(int _id, string _fName, string _lName, string _uName, string _pass)
        : Individual(_id, _fName, _lName, _uName, _pass, "Premium") {}

    double getDiscountRate() const override { return 0.10; }
    double getShippingCost(double cartTotal) const override {
        if (cartTotal >= 500.0) return 0.0;
        return 30.0; 
    }
};

// Corporate customers: Added company name and tax number fields.
// 15% discount and always free shipping.
class Corporate : public Customer {
private:
    string companyName;
    string taxNumber;
public:
    Corporate(int _id, string _fName, string _lName, string _uName, string _pass, string _company, string _tax)
        : Customer(_id, _fName, _lName, _uName, _pass, "Corporate") {
        companyName = _company;
        taxNumber = _tax;
    }

    double getDiscountRate() const override { return 0.15; }
    double getShippingCost(double cartTotal) const override { return 0.0; }

    void print() const override {
        Customer::print();
        cout << " | Company: " << companyName << " TaxNo: " << taxNumber;
    }
};

#endif