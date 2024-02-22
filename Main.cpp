
#include <iostream>
#include <vector>
#include <initializer_list>
#include <memory>
#include <tuple>
#include <Windows.h>
#include <map>
#include "TopTenProduct.h"
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
    TopTenProductList topten;
    srand((int)time(0));
    for (int i = 0; i < 1000; i++)
    {
        topten.PutProductInfo((rand() % 100) + 1, "miphone", (rand() % 10));
    }

    Node* root = NULL;
    PriorityQueue pqueue(10);
    topten.GetTopProductInfo(pqueue);
    root = pqueue.getRootNode();

    vector<Product> products = pqueue.getTopTen();
    for (auto p : products)
    {
        cout << "Product id " << p.getProductid();
        cout << "Product name" << p.getName();
        cout << "Product count" << p.getcount() << endl;
    }
}