//Open close pronciple(OCP)
//a class should be open for extension but closed for modification
//we should be able to add new functionality without changing existing code

//using Abstraction, inheritance and polymorphism we can achieve OCP
#include<iostream>
#include<vector>

class Product{
    public:
        std::string name;
        double      price;

        //constructor using member initializer list
        Product(std::string n, double p): name(n), price(p) {}
};


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

        void saveToSQLDatabase(){
            //code to save cart details to database
            std::cout<< "Saving cart details to database..." <<std::endl;
        }

        void saveToMongoDB(){
            //code to save cart details to MongoDB
            std::cout<< "Saving cart details to MongoDB..." <<std::endl;
        }

        void saveToFile(){
            //code to save cart details to a file
            std::cout<< "Saving cart details to a file..." <<std::endl;
        }
};

/////////// OCP ///////////////////////
class Database{
    private:
        ShoppingCartSRP* cart;
    public:
        virtual void save(const ShoppingCartSRP* cart) = 0; //pure virtual function
        virtual ~Database() {} //virtual destructor
};

class SQLDatabase : public Database{
    public:
        void save(ShoppingCartSRP* cart) override {
            std::cout<< "Saving cart details to SQL Database..." <<std::endl;
        }
};

class MongoDB : public Database{
    public:
        void save(ShoppingCartSRP* cart) override {
            std::cout<< "Saving cart details to MongoDB..." <<std::endl;
        }
};

class FileDatabase : public Database{
    public:
        void save(ShoppingCartSRP* cart) override {
            std::cout<< "Saving cart details to a file..." <<std::endl;
        }
};


int main(){
    Database* cart = new Database();

    Product* p1 = new Product("Laptop", 999.99);
    Product* p2 = new Product("Mouse", 49.99);
    cart->addProduct(p1);
    cart->addProduct(p2);

    InvoicePrinter* printer = new InvoicePrinter(cart);
    printer->printInvoice();

    DatabaseSaver* dbSaver = new DatabaseSaver(cart);
    dbSaver->saveToSQLDatabase();

    ////////Using OCP
    Database* sqlDb = new SQLDatabase();
    sqlDb->save(cart);
    Database* mongoDb = new MongoDB();
    mongoDb->save(cart);
    Database* fileDb = new FileDatabase();
    fileDb->save(cart);



    //clean up
    delete p1;
    delete p2;
    delete cart;
    delete printer;
    delete dbSaver;
    delete sqlDb;
    delete mongoDb;
    delete fileDb;

    return 0;
}