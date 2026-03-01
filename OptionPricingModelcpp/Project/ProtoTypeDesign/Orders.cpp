//Creating differnt type of orders using prototype design pattern
#include<iostream>

enum OrderType{
    LimitOrder  = 0,
    MarketOrder = 1
};

std::string OrderTypeToString(OrderType order_type){
    switch(order_type){
        case OrderType::LimitOrder:
            return "LimitOrder";
        case OrderType::MarketOrder:
            return "MarketOrder";
        default:
            return "Error: InvalidOrderType";
    }
}

class Order{
    public:
        Order() = delete; //there must be no order in the system with default params
        Order(int order_qty, int order_price, OrderType order_type): //constructor
            order_qty(order_qty),
            order_price(order_price),
            order_type(order_type)
        {};


        //create deep copy instead of shallow copy becouse of containing dynamically allocated resources
        Order* clone(){
            Order* obj = new Order(this->order_qty, this->order_price, this->order_type);
            return obj;
        }


        //if update any-thing
        void UpdateQty(const int order_qty){
            this->order_qty = order_qty;
        }
        void UpdatePrice(const int order_price){
            this->order_price = order_price;
        }
        void UpdateOrderType(const OrderType order_type){
            this->order_type = order_type;
        }

        void DisplayOrderFields() const{
            std::cout<<"OrderQty:\t"<<this->order_qty
                    <<"\nOrderPrice:\t"<<this->order_price
                    <<"\nOrderType:\t"<<OrderTypeToString(this->order_type) <<std::endl;
        }

        ~Order(){std::cout<<"Cleaning up the price data" <<std::endl;} //destructor
    
    private:
        int order_qty;
        double order_price;
        OrderType order_type;
};


int main(){

    Order* order = new Order(10, 100, OrderType::LimitOrder);
    order->DisplayOrderFields();

    Order* cloned_order = order->clone();
    cloned_order->UpdateOrderType(OrderType::MarketOrder);
    cloned_order->DisplayOrderFields();

    delete order;
    delete cloned_order;
    return 0;
}