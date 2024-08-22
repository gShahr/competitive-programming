#include <cstdint>
#include <exception>
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <stdexcept>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <optional>
#include <algorithm>
#include <unordered_map>

using namespace std;

class OrderState
{
public:
    int numberOfStores;
    int numberOfOrders;
    int numberOfDifferrentBeverages;
    int numberOfBeverages;
    int mxStores;
    int mxPerBeverageTotal;
    
    map<int, pair<string, int>> orders;

    OrderState()
    {
    }

    void UpdateLimit(const int numberOfStores, const int perBeverageTotal)
    {
        mxStores = numberOfStores;
        mxPerBeverageTotal = perBeverageTotal;
    }

    void ProcessOrder(const int uniqueId, const int storeId, const std::string& beverageName, const int quantity)
    {
        bool ok = true;
        if (orders.find(storeId) != orders.end()) {
            if (orders[storeId].second + quantity > mxPerBeverageTotal)
        }
        if (ok) orders[storeId] = {beverageName, quantity};
    }

    void CloseStore(const int storeId)
    {
    }

    void PrintState()
    {
        cout << "number_of_stores: " << numberOfStores << "," << endl;
        cout << "number_of_orders: " << numberOfOrders << "," << endl;
        cout << "number_of_different_beverages: " << numberOfDifferrentBeverages << "," << endl;
        cout << "number_of_beverages: " << numberOfBeverages << "," << endl;
    }
};


int main()
{
    OrderState OrderState{};

    std::string operation;
    int numberOfStores;
    int perBeverageTotal;
    int uniqueId;
    int storeId;
    std::string beverage;
    int quantity;
    
    while(!std::cin.eof())
    {
        std::cin >> operation;
        if (operation == "UPDATE_LIMIT")
        {
            std::cin >> numberOfStores >> perBeverageTotal;
            OrderState.UpdateLimit(numberOfStores, perBeverageTotal);
        }
        else if (operation == "ORDER_UPDATE")
        {
            std::cin >> uniqueId >> storeId >> beverage >> quantity;
            OrderState.ProcessOrder(uniqueId, storeId, beverage, quantity);
        }
        else if (operation == "CLOSE_STORE")
        {
            std::cin >> storeId;
            OrderState.CloseStore(storeId);
        }
        else if (operation == "PRINT_STATE")
        {
            OrderState.PrintState();
        }
        else
        {
            std::cerr << "Malformed input!\n" << operation << std::endl;
            return -1;
        }
        if (std::cin.eof()) break;
    }
    return 0;
}