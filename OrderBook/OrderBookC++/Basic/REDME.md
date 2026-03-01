We try to match orders by order type rather than just by what comes first in time. Second, market orders we set to have a price of 0. There is no "market price" in our example so just setting it at 0 lets us know we want to just execute this order. one could say it is better to use an unordered map instead of a vector. I would agree with them but vectors are easier for this example.

