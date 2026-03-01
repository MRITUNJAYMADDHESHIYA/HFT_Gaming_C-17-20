//Problems:- Maintainability, Readability, Bugs
//SOLID:- Single Responsibility Principle(SRP)
//     :- Open/Closed Principle(OCP)
//     :- Liskov Substitution Principle(LSP)
//     :- Interface Segregation Principle(ISP)
//     :- Dependency Inversion Principle(DIP)

//SRP:-A class should have only one reason to change, meaning it should only have one job or responsibility.
#include<iostream>
#include<vector>

class Product{
    public:
        std::string name;
        double      price;

        //constructor using member initializer list
        Product(std::string n, double p): name(n), price(p) {}
        ////////////constructor using assignment in body(extra default constructor)
        // Product(std::string name, double price){
        //     this->name = name;
        //     this->price = price;
        // }
};

class ShoppingCart{
    private:
        std::vector<Product*> products;
    public:
        void addProduct(Product* p){
            products.push_back(p);
        }

        const std::vector<Product*>& getProducts() {
            return products;
        }


        //1.calculates total price in cart
        double calculateTotal(){
            double total = 0.0;
            for(auto p : products){
                total += p->price;
            }
            return total;
        }

        //2.prints invoice
        void printInvoice(){
            std::cout<< "Invoice: " <<std::endl;
            for(auto p : products){
                std::cout<< p->name << " - $" << p->price <<std::endl;
            }
            std::cout<< "Total: $" << calculateTotal() <<std::endl;
        }

        //3.save to DB
        void saveToDatabase(){
            //code to save cart details to database
            std::cout<< "Saving cart details to database..." <<std::endl;
        }
};


///////SRP
class ShoppingCartSRP{
    private:
        std::vector<Product*> products;
    public:
        void addProduct(Product* p){
            products.push_back(p);
        }

        const std::vector<Product*>& getProducts() const {
            return products;
        }

        double calculateTotal() const{
            double total = 0.0;
            for(auto p : products){
                total += p->price;
            }
            return total;
        }
};

class InvoicePrinter{
    private:
        const ShoppingCartSRP* cart;
    public:
        InvoicePrinter(const ShoppingCartSRP* c): cart(c) {}

        void printInvoice() const {
            std::cout<< "Invoice: " <<std::endl;
            for(auto p : cart->getProducts()){
                std::cout<< p->name << " - $" << p->price <<std::endl;
            }
            std::cout<< "Total: $" << cart->calculateTotal() <<std::endl;
        }
};

class DatabaseSaver{
    private:
        const ShoppingCartSRP* cart;
    public:
        DatabaseSaver(const ShoppingCartSRP* c): cart(c) {}

        void saveToDatabase(){
            //code to save cart details to database
            std::cout<< "Saving cart details to database..." <<std::endl;
        }
};


int main(){
    ShoppingCart* cart = new ShoppingCart();

    Product* p1 = new Product("Laptop", 999.99);
    Product* p2 = new Product("Mouse", 49.99);

    cart->addProduct(p1);
    cart->addProduct(p2);

    cart->printInvoice();
    cart->saveToDatabase();

    //clean up
    delete p1;
    delete p2;
    delete cart;

    return 0;
}