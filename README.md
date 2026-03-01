Creating many low-level projects in this repo...
Focus on:- High Performance coding fundamentals in C++17/20/23

1.Low-latency system design in C++
2.Multithreading & concurrency(Time and Memory Managment)
3.OPP'S, LLD, SOLID principles and clean architecture in C++
4.Implement some Stochastic methods




//////////////////This folder only for python ////////////////////////////
1.Task folder(and apply pair trading strategy for MFT in nifty and banknifty)
//1. base.ipynb
// ########### Pair Trading Strategy Class(some modification in zscore strategy then better perform) ##########
// ########### 1.Modified exit logic to exit at mid-point of bands (midpoint should be dynamic, in this case (Upper+Lower)/2 But if I want for Better exit then I can do = spread mean, or Z=0. )
// ########### 2.Added stop-loss based on implied volatility levels


//2.myModel.ipynb
//// I am using some model and try to optimize the above strategy based on regimes in the spread behavior
// ## using RegimeDetectorGMM
// # [1,2]---> 287.5, Sharpe Ratio: 6.04325228140793 (without model or)    -8025 trades
// # 1    ---> 203,   Sharpe Ratio: 9.29770921355591 (high quality trades) -2056 trades-------->this is perfect for this
// # 2    ---> 110,   Sharpe Ratio: 12.17756044604162                      -7141 trades

// ## using RegimeDetectorARHMM
// # [1] ---->193, Sharpe Ratio: 6.702584412675305                      -3656 trades
// # [2] ---->99   Sharpe Ratio: 6.190348145217359                      -4439 trades
