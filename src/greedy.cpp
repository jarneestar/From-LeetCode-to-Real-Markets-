int singleTransaction(vector<int> &price)
{
    int minPrice = INT_MAX, profit = 0;
    for (int i = 0; i < price.size(); i++)
    {
        minPrice = min(minPrice, price[i]);
        profit = max(profit, price[i] - minPrice);
    }
    return profit;
}

int multipleTransactions(vector<int> &price)
{
    int profit = 0;
    for (int i = 1; i < price.size(); i++)
    {
        if (price[i] > price[i - 1])
            profit += price[i] - price[i - 1];
    }
    return profit;
}

int multipleBuySingleSell(vector<int> &price)
{
    int n = price.size();
    if (n == 0)
        return 0;
    int maxFuture = price[n - 1];
    int profit = 0;
    for (int i = n - 2; i >= 0; i--)
    {
        if (price[i] < maxFuture)
            profit += maxFuture - price[i];
        else
            maxFuture = price[i];
    }
    return profit;
}
