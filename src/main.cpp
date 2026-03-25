
#include <iostream>
#include <vector>
#include <climits>
#include <cstdio>
#include <windows.h>
using namespace std;

vector<int> inputPrices()
{
    int n;
    cout << "Enter number of days: ";
    cin >> n;
    vector<int> price(n);
    cout << "Enter prices:\n";
    for (int i = 0; i < n; i++)
        cin >> price[i];
    return price;
}

vector<vector<int>> loadFromFile()
{
    vector<vector<int>> datasets;
    FILE *fp = fopen("prices.txt", "r");

    if (fp == NULL)
    {
        cout << "File not found\n";
        return datasets;
    }

    int n;
    while (fscanf(fp, "%d", &n) != EOF)
    {
        vector<int> temp(n);
        for (int i = 0; i < n; i++)
        {
            fscanf(fp, "%d", &temp[i]);
        }
        datasets.push_back(temp);
    }

    fclose(fp);
    return datasets;
}

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

int kTransactions(vector<int> &price, int k)
{
    int n = price.size();
    if (n == 0)
        return 0;

    vector<vector<int>> dp(k + 1, vector<int>(n, 0));

    for (int i = 1; i <= k; i++)
    {
        int maxDiff = -price[0];
        for (int j = 1; j < n; j++)
        {
            dp[i][j] = max(dp[i][j - 1], price[j] + maxDiff);
            maxDiff = max(maxDiff, dp[i - 1][j] - price[j]);
        }
    }
    return dp[k][n - 1];
}

int cooldown(vector<int> &price)
{
    int n = price.size();
    if (n <= 1)
        return 0;

    vector<int> buy(n), sell(n);
    buy[0] = -price[0];
    buy[1] = max(-price[0], -price[1]);
    sell[1] = max(0, price[1] - price[0]);

    for (int i = 2; i < n; i++)
    {
        buy[i] = max(buy[i - 1], sell[i - 2] - price[i]);
        sell[i] = max(sell[i - 1], buy[i - 1] + price[i]);
    }
    return sell[n - 1];
}

int transactionFee(vector<int> &price, int fee)
{
    int n = price.size();
    if (n == 0)
        return 0;

    int buy = -price[0], sell = 0;

    for (int i = 1; i < n; i++)
    {
        buy = max(buy, sell - price[i]);
        sell = max(sell, buy + price[i] - fee);
    }
    return sell;
}

void runSingle(vector<int> &price)
{
    if (price.size() == 0)
    {
        cout << "Enter prices first\n";
        return;
    }

    cout << "Single Transaction: " << singleTransaction(price) << endl;
    cout << "Multiple Transactions: " << multipleTransactions(price) << endl;
    cout << "Multi Buy Single Sell: " << multipleBuySingleSell(price) << endl;

    int k;
    cout << "Enter K: ";
    cin >> k;
    cout << "K Transactions: " << kTransactions(price, k) << endl;

    cout << "Cooldown: " << cooldown(price) << endl;

    int fee;
    cout << "Enter fee: ";
    cin >> fee;
    cout << "Transaction Fee: " << transactionFee(price, fee) << endl;
}

void runDatasets(vector<vector<int>> &datasets)
{
    if (datasets.size() == 0)
    {
        cout << "No datasets loaded\n";
        return;
    }

    for (int d = 0; d < datasets.size(); d++)
    {
        cout << "\n--- Dataset " << d + 1 << " ---\n";
        vector<int> price = datasets[d];

        cout << "Prices: ";
        for (int x : price)
            cout << x << " ";
        cout << endl;

        cout << "Single: " << singleTransaction(price) << endl;
        cout << "Multiple: " << multipleTransactions(price) << endl;
        cout << "Multi Buy Single Sell: " << multipleBuySingleSell(price) << endl;
        cout << "K=2: " << kTransactions(price, 2) << endl;
        cout << "Cooldown: " << cooldown(price) << endl;
        cout << "Fee=1: " << transactionFee(price, 1) << endl;
    }
}

void showMenu()
{
    cout << "\n1. Enter Prices\n";
    cout << "2. Load Datasets from File\n";
    cout << "3. Run All Modules (Single Input)\n";
    cout << "4. Run All Datasets\n";
    cout << "5. Exit\n";
    cout << "Enter choice: ";
}

void controller()
{
    vector<int> price;
    vector<vector<int>> datasets;
    int choice;

    do
    {
        showMenu();
        cin >> choice;

        if (choice == 1)
        {
            price = inputPrices();
        }
        else if (choice == 2)
        {
            datasets = loadFromFile();
            cout << "Datasets loaded: " << datasets.size() << endl;
        }
        else if (choice == 3)
        {
            runSingle(price);
        }
        else if (choice == 4)
        {
            runDatasets(datasets);
        }

    } while (choice != 5);
}

int main()
{
    controller();
    return 0;
}