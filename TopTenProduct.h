#pragma once
#include <iostream>
#include <map>
#include <unordered_map>
#include <string>

using namespace std;

class Product
{
private:
	int m_productid;
	string m_productname;
	unsigned int m_count;
public:
	Product() :m_productid(0), m_productname(""), m_count(0)
	{

	}
	Product(const int& pid, const string& name, const int &count)
	{
		m_productid = pid;
		m_productname = name;
		m_count = count;
	}
	Product(const Product& p) = default;
	Product(Product&& p) = default;
	Product& operator = (const Product&) = default;
	Product& operator = (Product&&) = default;

	string getName()
	{
		return m_productname;
	}

	int getcount() { return m_count; }

	int getProductid() { return m_productid; }

	void setcount(int count) { m_count = count; return; }
};

struct Node
{
public:
	Product* product;
	Node* next;
	Node(Product* p)
	{
		product = p;
		next = NULL;
	}
};

class PriorityQueue
{
private:
	Node* root;
	int m_maxcapacity;
	int m_size;
public:
	PriorityQueue(int maxcapacity);
	~PriorityQueue();
	void push(Product* p);
	Node* getRootNode();
	vector<Product> getTopTen();
};

class TopTenProductList
{
private:
	std::unordered_map<string, Product*> products;
	//PriorityQueue toptenproducts;
	//std::priority_queue<Product*> topten;
	bool IsLastOnehourProduct(int hour, int min);
public:
	TopTenProductList();
	~TopTenProductList();
	void PutProductInfo(const int& pid, const string& name, const int& count);	
	void GetTopProductInfo(PriorityQueue &toptenproducts);
};