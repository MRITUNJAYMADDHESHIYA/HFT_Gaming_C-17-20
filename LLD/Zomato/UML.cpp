//UML diagram:-
//Bottom-up approch


// <<singleton>>                                              <<modal>>                                       <<model>>
//RestaurantManager(addRestaurant, searchByLocation)------>Restaurant(id, name, add, vector<menuItems>)------>MenuItem(code, name, price)
//                                                                  | |                                              |               |
//                                                                  | |                                              |               |
// User(id, name, addr, cart)-------------- -------------->Cart(restau|rant, vector<menuItem>, total, addToCart, clear)              |
//     |                                                              |                                                              |
//     |                                                              |--------------------------------------------------------------|
//     |                                                              |
// Order(id, Restaurant, vector<menuitems>, user, paymentStrategy, getType())--------->PaymentStrategy(pay())-------->NetBanking(pay) + UPI(pay) + CreditCard(pay)
//  |          |
//  |          |
//  |     DeliveryOrder(getType()) + pickupOrder(getType())__________________
//  |                                                   |                    |
//  | <<interface>>                                     |                    |
// o|rderFactory(createOrder())----------->NowOrderFactory(createOrder) + SchedualOrderFactory(createOrder)
//  |
//  | <<singleton>>
// o|rderManager(vector<order> order)
//  |
//  |
//NotificationService(notify(order))
//

