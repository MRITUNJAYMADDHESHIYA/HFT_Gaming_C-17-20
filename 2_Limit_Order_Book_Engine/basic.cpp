//1.OrderType:-      limit order, market order, (IOC, FOK, Iceberg)
//2.Actions:-        New order, Cancel order, Modify order
//3.Matching Rules:- Price-Time Priority, Continuous matching, partial fills allowed
//

//C++17
//Linux/wsl(i am using wsl)
//single-instrument, single-threaded matching core


//upgrade the design slightly
//a.the best price level
//b.accessing its head order
//c.removing filled orders safely

