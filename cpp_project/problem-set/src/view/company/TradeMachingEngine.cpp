#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
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
#include <algorithm>
#include <unordered_map>
using namespace std;

const int ORDER_ID_INDEX_IN_BUY = 4;
const int ORDER_TYPE_INDEX_IN_BUY = 1;
const int ORDER_PRICE_INDEX_IN_BUY = 2;
const int ORDER_QUANTITY_INDEX_IN_BUY = 3;

const int ORDER_ID_INDEX_IN_SELL = 4;
const int ORDER_TYPE_INDEX_IN_SELL = 1;
const int ORDER_PRICE_INDEX_IN_SELL = 2;
const int ORDER_QUANTITY_INDEX_IN_SELL = 3;

const int ORDER_ID_INDEX_IN_CANCEL = 1;

const int ORDER_ID_INDEX_IN_MODIFY = 1;
const int ORDER_TYPE_INDEX_IN_MODIFY = 2;
const int ORDER_PRICE_INDEX_IN_MODIFY = 3;
const int ORDER_QUANTITY_INDEX_IN_MODIFY = 4;

// template <class T> struct greater : binary_function <T, T, bool> {
//     bool operator() (const T& x, const T& y) const
//     {
//         return x > y;
//     }
// };

class MachingEngine
{
private:
    enum class Type { IOC, GFD, NONE};
    enum class Status { PENDING, EXECUTED, CANCELED, NONE };
    enum class Operation { BUY, SELL, CANCEL, MODIFY, PRINT, INVALID};
    enum class Direction { B, S, N };
    class Order {
    public:
        string orderId = "";
        Type type = Type::NONE;
        Direction dir = Direction::N;
        int price = 0 ;
        int quantity = 0;
        Order() {};
        bool operator== (const Order& order_) const
        {
            return (orderId == order_.orderId) &&
                (type == order_.type) &&
                (dir == order_.dir) &&
                (price == order_.price) &&
                (quantity == order_.quantity);
        }
        Order(string orderId_, Type type_, Direction dir_,int price_,int quantity_)
            :orderId(orderId_), type(type_), dir(dir_), price(price_), quantity(quantity_)
        {
        }
        void SetOrder(string orderId_, Type type_, Direction dir_, int price_, int quantity_)
        {
            orderId = orderId_;
            type = type_;
            dir = dir_;
            price = price_;
            quantity = quantity_;
        }
    };
    struct OperationReq
    {
        Operation oper;
        Order order;
    };
    struct ExecutedOrder {
        Order order1;
        Order order2;
    };
public:

    OperationReq ParseBuyOption(vector<string>& buyOperStrVect)
    {
        OperationReq req;
        if (buyOperStrVect.size() != 5 )
        {
            req.oper = Operation::INVALID;
            return req;
        }

        int price = 0;
        int quantity = 0;
        try
        {
            price = stoi(buyOperStrVect[ORDER_PRICE_INDEX_IN_BUY]);
            if (price <= 0)
            {
                req.oper = Operation::INVALID;
                return req;
            }
        }
        catch (...)
        {
            req.oper = Operation::INVALID;
            return req;
        }
        try
        {
            quantity = stoi(buyOperStrVect[ORDER_QUANTITY_INDEX_IN_BUY]);
            if (quantity <= 0)
            {
                req.oper = Operation::INVALID;
                return req;
            }
        }
        catch (...)
        {
            req.oper = Operation::INVALID;
            return req;
        }
        Type type;
        if (buyOperStrVect[ORDER_TYPE_INDEX_IN_BUY] == "IOC")
            type = Type::IOC;
        else if (buyOperStrVect[ORDER_TYPE_INDEX_IN_BUY] == "GFD")
            type = Type::GFD;
        else
        {
            req.oper = Operation::INVALID;
            return req;
        }
        req.order.SetOrder(buyOperStrVect[ORDER_ID_INDEX_IN_BUY], type, Direction::B, price, quantity);
        return req;
    }

    void ExecuteBuy(Order& order)
    {
        //ensure buy order is not exist in orderBuyPendingIndexMap
        if (orderBuyPendingIndexMap.find(order.price) != orderBuyPendingIndexMap.end())
        {
            for (auto& it : orderBuyPendingIndexMap[order.price])
            {
                if (it.orderId == order.orderId)
                {
                    return;
                }
            }
        }
        int price = order.price;
        int quantity = order.quantity;
        vector<Order> dealOrderInfo;
        //any sell available order will be executed
        for (auto& it : orderSellPendingIndexMap)
        {
            //sell price is greater than this order will not be executed
            if (it.first > price)
            {
                break;
            }
            if (quantity > 0)
            {
                for (auto& orderIt : it.second)
                {
                    //current order will be completely executed 
                    if (quantity >= orderIt.quantity)
                    {
                        quantity -= orderIt.quantity;
                        dealOrderInfo.push_back(orderIt);
                    }
                    //current order will be partially executed 
                    else
                    {
                        orderIt.quantity -= order.quantity;
                        quantity = 0;
                        dealOrderInfo.push_back(orderIt);
                        break;
                    }
                }
            }
            //current order is already executed 
            else
            {
                break;
            }
        }
        //dump deal info
        for (auto& itDeal : dealOrderInfo)
        {
            //store executed order into dealsVect
            executedVect.push_back({ itDeal ,order });
            //remove executed sell order from sell pending queue
            orderSellPendingIndexMap[itDeal.price].remove(itDeal);
            cout << "TRADE" << " " << itDeal.orderId << " " << itDeal.price \
                << " " << itDeal.quantity << " " << \
                order.orderId << " " << order.price << " " << itDeal.quantity << endl;
        }

        //GFD order that residual quantity is not zero should store into buy pending index map
        if (quantity > 0 && order.type == Type::GFD)
        {
            order.quantity = quantity;
            orderBuyPendingIndexMap[order.price].push_back(order);
        }

    }

    OperationReq ParseSellOption(vector<string>& sellOperVect)
    {
        OperationReq req;
        if (sellOperVect.size() != 5)
        {
            req.oper = Operation::INVALID;
            return req;
        }
        int price = 0;
        int quantity = 0;
        try
        {
            price = stoi(sellOperVect[ORDER_PRICE_INDEX_IN_SELL]);
            if (price <= 0)
            {
                req.oper = Operation::INVALID;
                return req;
            }
        }
        catch (...)
        {
            req.oper = Operation::INVALID;
            return req;
        }
        try
        {
            quantity = stoi(sellOperVect[ORDER_QUANTITY_INDEX_IN_SELL]);
            if (quantity <= 0)
            {
                req.oper = Operation::INVALID;
                return req;
            }
        }
        catch (...)
        {
            req.oper = Operation::INVALID;
            return req;
        }
        Type type;
        if (sellOperVect[ORDER_TYPE_INDEX_IN_SELL] == "IOC")
            type = Type::IOC;
        else if (sellOperVect[ORDER_TYPE_INDEX_IN_SELL] == "GFD")
            type = Type::GFD;
        else
        {
            req.oper = Operation::INVALID;
            return req;
        }
        req.order.SetOrder(sellOperVect[ORDER_ID_INDEX_IN_SELL], type, Direction::B, price, quantity);
        return req;
    }
    void ExecuteSell(Order& order)
    {
        //ensure sell order is not exist in orderSellPendingIndexMap
        if (orderSellPendingIndexMap.find(order.price) != orderSellPendingIndexMap.end())
        {
            for (auto& it : orderSellPendingIndexMap[order.price])
            {
                if (it.orderId == order.orderId)
                {
                    return;
                }
            }
        }
        int price = order.price;
        int quantity = order.quantity;
        vector<Order> dealOrderInfo;
        //any buy available order will be executed
        for (map<int, list<Order>>::reverse_iterator it = orderBuyPendingIndexMap.rbegin(); it != orderBuyPendingIndexMap.rend(); ++it)
        {
            if (it->first < price)
            {
                break;
            }
            if (quantity > 0)
            {
                for (auto& orderIt : it->second)
                {
                    //current order will be completely executed 
                    if (quantity >= orderIt.quantity)
                    {
                        quantity  -= orderIt.quantity;
                        dealOrderInfo.push_back(orderIt);
                    }
                    //current order will be partially executed 
                    else
                    {
                        orderIt.quantity -= quantity;
                        quantity = 0;
                        dealOrderInfo.push_back(orderIt);
                        break;
                    }
                }
            }
            else
            {
                break;
            }
        }

        //dump deal info
        for (auto& itDeal : dealOrderInfo)
        {
            //store executed order into dealsVect
            executedVect.push_back({ itDeal ,order });
            //remove executed buy order from sell pending queue
            orderBuyPendingIndexMap[itDeal.price].remove(itDeal);

            cout << "TRADE" << " " << itDeal.orderId << " " << itDeal.price \
                << " " << itDeal.quantity << " " << \
                order.orderId << " " << order.price << " " << itDeal.quantity << endl;
        }

        //GFD order that residual quantity is not zero should store into sell pending index map
        if (quantity > 0 && order.type == Type::GFD)
        {
            order.quantity = quantity;
            orderSellPendingIndexMap[order.price].push_back(order);
        }
    }

    OperationReq ParseCancleOption(vector<string>& cancelOperVect)
    {
        OperationReq req;
        if (cancelOperVect.size() != 2)
        {
            req.oper = Operation::INVALID;
            return req;
        }
        if (cancelOperVect[ORDER_ID_INDEX_IN_CANCEL].empty())
        {
            req.oper = Operation::INVALID;
            return req;
        }
        req.oper = Operation::CANCEL;
        req.order.orderId = cancelOperVect[ORDER_ID_INDEX_IN_CANCEL];
        return req;

    }
    void ExecuteCancel(string orderId_)
    {
        Order cancelOrder;
        bool orderExistSellFlag = false;
        //find order in orderSellPendingIndexMap to remove the order;
        for (auto& itOrders : orderSellPendingIndexMap)
        {
            for (auto& itOrder : itOrders.second)
            {
                if (itOrder.orderId == orderId_)
                {
                    orderExistSellFlag = true;
                    cancelOrder = itOrder;
                    break;
                }
            }
        }
        if (orderExistSellFlag)
        {
            orderSellPendingIndexMap[cancelOrder.price].remove(cancelOrder);
            canceledOrdersVect.push_back(cancelOrder);
        }

        bool orderExistBuyFlag = false;
        //find order in orderBuyPendingIndexMap to remove the order;
        for (auto& itOrders : orderBuyPendingIndexMap)
        {
            for (auto& itOrder : itOrders.second)
            {
                if (itOrder.orderId == orderId_)
                {
                    orderExistBuyFlag = true;
                    cancelOrder = itOrder;
                    break;
                }
            }
        }
        if (orderExistBuyFlag)
        {
            orderBuyPendingIndexMap[cancelOrder.price].remove(cancelOrder);
            canceledOrdersVect.push_back(cancelOrder);
        }
    }

    OperationReq ParseModifyOption(vector<string>& modifyOperVect)
    {
        OperationReq req;
        if (modifyOperVect.size() != 5)
        {
            req.oper = Operation::INVALID;
            return req;
        }
        int price = 0;
        int quantity = 0;
        try
        {
            price = stoi(modifyOperVect[ORDER_PRICE_INDEX_IN_MODIFY]);
            if (price <= 0)
            {
                req.oper = Operation::INVALID;
                return req;
            }
        }
        catch (...)
        {
            req.oper = Operation::INVALID;
            return req;
        }
        try
        {
            quantity = stoi(modifyOperVect[ORDER_QUANTITY_INDEX_IN_MODIFY]);
            if (quantity <= 0)
            {
                req.oper = Operation::INVALID;
                return req;
            }
        }
        catch (...)
        {
            req.oper = Operation::INVALID;
            return req;
        }

        Order oldOrder;
        //find oldOrder to get Type
        oldOrder.orderId = modifyOperVect[ORDER_ID_INDEX_IN_MODIFY];
        for (auto& itOrders : orderSellPendingIndexMap)
        {
            for (auto& itOrder : itOrders.second)
            {
                if (oldOrder.orderId == itOrder.orderId)
                {
                    oldOrder = itOrder;
                    break;
                }
            }
        }
        if (oldOrder.type != Type::GFD)
        {
            for (auto& itOrders : orderBuyPendingIndexMap)
            {
                for (auto& itOrder : itOrders.second)
                {
                    if (oldOrder.orderId == itOrder.orderId)
                    {
                        oldOrder = itOrder;
                        break;
                    }
                }
            }
        }
        if (oldOrder.type != Type::GFD)
        {
            req.oper = Operation::INVALID;
            return req;
        }
        //remove oldOrder from the pending index map
        ExecuteCancel(oldOrder.orderId);

        Direction dir = Direction::N;
        if (modifyOperVect[ORDER_TYPE_INDEX_IN_MODIFY] == "BUY")
        {
            dir = Direction::B;
            req.oper = Operation::BUY;
        }
        else if (modifyOperVect[ORDER_TYPE_INDEX_IN_MODIFY] == "SELL")
        {
            dir = Direction::S;
            req.oper = Operation::SELL;
        }
        else
        {
            req.oper = Operation::INVALID;
            return req;
        }
        req.order.SetOrder(oldOrder.orderId, oldOrder.type, dir, price, quantity);

        return req;

    }
    void ExecPrint()
    {
        cout << "SELL:" <<endl;
        for (map<int, list<Order>>::const_reverse_iterator itOrders = orderSellPendingIndexMap.rbegin(); itOrders != orderSellPendingIndexMap.rend(); ++itOrders)
        {
            for (auto& itOrder : itOrders->second)
            {
                cout << itOrder.price << " "<< itOrder.quantity << endl;
            }
        }
        cout << "BUY:" << endl;
        for (map<int, list<Order>>::const_reverse_iterator itOrders = orderBuyPendingIndexMap.rbegin(); itOrders != orderBuyPendingIndexMap.rend(); ++itOrders)
        {
            for (auto& itOrder : itOrders->second)
            {
                cout << itOrder.price <<" "<< itOrder.quantity << endl;
            }
        }
    }

    void ParseOption(string userInput)
    {
        string buf;
        stringstream ss(userInput);
        vector<string> inputVec;
        while (ss >> buf) {
            inputVec.push_back(buf);
        }
        OperationReq req;
        if (inputVec[0] == "BUY")
        {
            req = ParseBuyOption(inputVec);
            if (req.oper != Operation::INVALID)
            {
                ExecuteBuy(req.order);
            }
        }
        else if (inputVec[0] == "SELL")
        {
            req = ParseSellOption(inputVec);
            if (req.oper != Operation::INVALID)
            {
                ExecuteSell(req.order);
            }
        }
        else if (inputVec[0] == "CANCEL")
        {
            req = ParseCancleOption(inputVec);
            if (req.oper != Operation::INVALID)
            {
                ExecuteCancel(req.order.orderId);
            }
        }
        else if (inputVec[0] == "MODIFY")
        {
            req = ParseModifyOption(inputVec);
            if (req.oper == Operation::BUY)
            {
                ExecuteBuy(req.order);
            }
            else if (req.oper == Operation::SELL)
            {
                ExecuteSell(req.order);
            }
        }
        else if (inputVec[0] == "PRINT")
        {
            ExecPrint();
        }
            
    }

private:
    //executed order
    vector<ExecutedOrder> executedVect;
    //canceled order
    vector<Order> canceledOrdersVect;
    //map<key:price, list<Order>>
    //priority is decrease in according with the price decrease
    map<int, list<Order> > orderBuyPendingIndexMap;
    //map<key:price, list<Order>>
    //priority is decrease in according with the price increase
    map<int, list<Order> > orderSellPendingIndexMap;
};

int TestMachingEngine() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    string userInput;
    MachingEngine trademachingEngine;
    while (getline(cin, userInput)) {
        trademachingEngine.ParseOption(userInput);
    }
    return 0;
}