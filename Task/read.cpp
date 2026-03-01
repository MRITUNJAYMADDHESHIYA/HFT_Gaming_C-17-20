//given:- (Every Minute) Implied volatilities(IVs) BankNifty and Nifty
//     :- TTE(time to expiry) in years
//     :- 690512 rows and 3 columns
//     :- 9:15 to 15:30


//Focus :- Missing values present
//      :- p_l values depend on spread and IV values

//Formula used:-  Spread = IV_BankNifty - IV_Nifty
//            :-  p_l = Spread*(TTE)^0.7


///1. Build a z-score based trading system. It would use the z-scores of the spread to identify when volatility has diverged away from the historical mean and act accordingly. The calculation of the P/L here constitutes the base model.
///2. Build a better model than the z-score trading system
///3. Compare and optimize the absolute P/L, sharpe ratio and Drawdown


/////////// Summary /////////////////
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




////////////////////Some more thing I have to do it.
//1. I have to work on data-analysis, for accuracy
//2. Try some more models to identify regimes
//3. data is large so try to optimize code for fast execution