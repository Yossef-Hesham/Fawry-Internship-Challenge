#include <bits/stdc++.h>
using namespace std;
const double SHIPPING_RATE = 0.05;


class Customer {
private:
    string name;
    double balance;


public:    
    Customer(string name,  double balance) : name(name) , balance(balance) {}   

    double getBalance() const {
        return balance; 
    }

    void withdraw(double cost) {
        this->balance -= cost;
    }

    string getName() const {
        return name; 
    }

};



class Product{

protected:

    string name;
    double price;
    int quantity;
    bool Is_expired;
    double shipping_fees;
    double weight;

public:

    Product(string name, double price, int quantity, bool Is_expired) : name(name), price(price), quantity(quantity), Is_expired(Is_expired) {
        if (price < 0 || quantity <= 0) {
            throw invalid_argument("Price must be non-negative and quantity must be positive");
        }
    }


    virtual string getName() const = 0; 
    virtual double getPrice() const = 0; 
    virtual int getQuantity() const = 0;
    virtual bool getItexpired() const  = 0; 
    virtual double getWeight() const = 0;


    virtual double getShippingFees() const = 0; 
    
    virtual double total_cost() const = 0;
    virtual double total_shipping_fees() const = 0;

};





class Shippable_Product : public Product {
public:
    Shippable_Product(string name, double price, int quantity, bool Is_expired, double weight)
        : Product(name, price, quantity, Is_expired) {
        this->weight = weight;
        this->shipping_fees = shipping_fees;
    }


    double getShippingFees() const override {
        return price * SHIPPING_RATE;
    }

    double getWeight() const override {
        return weight;
    }

    string getName() const override {
        return name;
    }

    double getPrice() const override {
        return price;
    }

    bool getItexpired() const override {
        return Is_expired;
    }

    int getQuantity() const override {
        return quantity;
    }

    double total_cost() const override {
        return price * quantity;
    }

    double total_shipping_fees() const override {
        return total_cost() * SHIPPING_RATE;
    }

};



class NonShippable_Product : public Product {
public:
    NonShippable_Product(string name, double price, int quantity, bool Is_expired)
        : Product(name, price, quantity, Is_expired) {}

   
    double getShippingFees() const override {
        return 0;
    }

    double getWeight() const override {
        return 0.0;
    }

    string getName() const override {
        return name;
    }

    double getPrice() const override {
        return price;
    }

    bool getItexpired() const override {
        return Is_expired;
    }

    int getQuantity() const override {
        return quantity;
    }

    double total_cost() const override {
        return price * quantity;
    }

    double total_shipping_fees() const override {
        return 0.0;
    }
};







class Cart {
private:
    vector<Product*> products;  
    Customer* customer;
    vector<Product*> product_to_ship;

public:

    

    Cart(Customer* c) : customer(c) {}


    void add(Product* product) {

        try 
        {
            if (product->getItexpired() == true) 
                throw invalid_argument(product->getName() + " is expired and cannot be added to the cart");
            
            if (product->getQuantity() <= 0)
                throw invalid_argument("Product quantity must be greater than zero");

            if(customer->getBalance() < product->total_cost() + product->total_shipping_fees()) {
                throw invalid_argument("Insufficient balance to add " + product->getName() + " to the cart");
            }
        }
        catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << endl;
            return;
        }


        products.push_back(product);
        if (product->getWeight() > 0)
            product_to_ship.push_back(product);

        
        // customer->withdraw();
        customer->withdraw(product->total_cost());
        customer->withdraw(product->total_shipping_fees());
    }


    double TotalCost() const {
        double totalCost = 0.0;
        for (const auto& product : products) {
            totalCost += product->total_cost(); 
        }
        return totalCost;
    }


    double shippint_cost() const {
        double shippint_cost = 0.0;
        for (const auto& product : products) {
                shippint_cost += product->total_shipping_fees();
        }
        return shippint_cost;
    }




    void Checkout_receipt() const {

        if (products.empty()) {
            cout << "Cart is empty." << endl;
            return;
        }


        cout << "** Checkout_receipt **" << endl;
        for (const auto& product : products) {
            cout << product->getQuantity() << "x " << product->getName()  << "    " << product->getPrice() << endl;
        }

        double Cost = TotalCost();
        double shippintCost = shippint_cost();
        

        cout << "--------------------------------------\n";
        cout << "Subtotal    " << Cost  << endl;
        cout << "shipping     " <<  shippintCost << endl;
        cout << "Amount     " << shippintCost + Cost<< endl;
        
        


        cout << "balance  " <<  customer->getBalance() << endl;
    }


    vector<Product*> get_shippables() const {
        return product_to_ship;
    }

    ~Cart() {
        for (auto& product : products) {
            delete product; // Free dynamically allocated memory
        }
        products.clear(); // Clear the vector
    }
};

class shipping_service {


public:

    void shippingService (vector<Product*> product) {
        double total_package_weight = 0;
        for(auto &item : product) {
            total_package_weight += item->getWeight();
            cout << item->getQuantity() << "x " <<  item->getName() << "    " << item->getWeight() << endl;
        }

        cout << "Total package weight " << total_package_weight << '\n';
    }

};






int main() {
    Customer* c = new Customer("Youssef", 800);
    Cart cart(c);


    // (string name, double price, int quantity, bool Is_expired, double weight)

    Product* book = new Shippable_Product("Book", 100.3, 2, false, 1.5);

    Product* iphone = new Shippable_Product("iphone", 300.0, 2, false, 1.5);

    // this product is expired
    Product* cheese = new Shippable_Product("cheese", 15, 2, true, 3.0);



    //(string name, double price, int quantity, bool Is_expired)
    Product* ticket = new NonShippable_Product("Event Ticket", 200.0, 1, false);

    
    

    cart.add(book);
    cart.add(iphone);
    cart.add(ticket);
    cart.add(cheese); // This will throw an error because cheese is expired);



    
    shipping_service service;
    service.shippingService(cart.get_shippables());


    cout << '\n' << '\n';

  

    cart.Checkout_receipt();

    

    delete c;
    return 0;
}

