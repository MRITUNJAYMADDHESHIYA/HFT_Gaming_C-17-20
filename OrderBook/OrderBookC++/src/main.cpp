#include<iostream>
#include "../include/Order.hpp"
#include "../include/Helper.hpp"

using std::cout;
using std::cin;

int main(){

    Orderbook ob(true);

    while(true){
        int action;
        cout<< "Options\n-----------\n|1. Print OrderBook|\n|2. Submit Order |\n--------------------\nChoice: ";
        cin>>action;
        cout<<"\n";

        if(action == 1){
            ob.print();
        }else if(action == 2){
            //inputs
            int order_type_input;
            int quantity;
            int side_input;
            double price;

            cout<<"Enter order type:\n0. Market order\n1. Limit order\nSelection:";
            cin>>order_type_input;
            OrderType order_type = static_cast<OrderType>(order_type_input);

            
        }
    }
}