#include <iostream>
#include <string>
#include <unordered_map>
#include <ctime>
#include <time.h>
#include <map>
#include "TopTenProduct.h"

using namespace std;

PriorityQueue::PriorityQueue(int maxcapacity)
{
	m_maxcapacity = maxcapacity;
	root = NULL;
	m_size = 0;
}

PriorityQueue::~PriorityQueue()
{
	Node* pre = NULL;
	Node* temp = root;
	while (temp != NULL)
	{
		pre = temp;
		temp = temp->next;
		delete pre;
	}
	root = NULL;
}

void PriorityQueue::push(Product* p)
{
	if (root == NULL)
	{
		m_size = m_size + 1;
		root = new Node(p);
		return;
	}
	
	Node* temp = root;
	Node* pre = NULL;

	if (p->getcount() >= root->product->getcount())
	{
		Node* newNode = new Node(p);
		newNode->next = root;
		root = newNode;
		m_size = m_size + 1;
	}
	else
	{
		int inc = 0;
		while (temp != NULL && inc < m_maxcapacity)
		{
			if (temp != NULL && temp->product->getcount() >= p->getcount())
			{
				pre = temp;
				temp = temp->next;
			}
			else
			{
				break;
			}
			inc++;
		}
		if (inc < m_maxcapacity)
		{
			m_size = m_size + 1;
			Node* newNode = new Node(p);
			pre->next = newNode;
			newNode->next = temp;
		}
	}				

	if (m_size > m_maxcapacity)
	{
		int inc = 0;
		Node* temp = root;
		while (temp != NULL)
		{
			//before max capacity continue to iterate
			if (inc < m_maxcapacity)
			{
				pre = temp;
				temp = temp->next;
			}
			else if (inc == m_maxcapacity) //after reaches the max capacity make it to NULL
			{
				pre->next = NULL;
			}
			else //after max capacity delete all nodes not needed
			{
				m_size--;
				pre = temp;
				temp = temp->next;
				delete pre;
			}				

			inc++;
		}
	}
}

Node* PriorityQueue::getRootNode()
{
	return root;
}

vector<Product> PriorityQueue::getTopTen()
{
	vector<Product> vec;
	Node* temp = root;
	while (temp != NULL)
	{
		vec.push_back(*(temp->product));
		temp = temp->next;
	}
	return vec;
}


TopTenProductList::TopTenProductList()
{
		
}
TopTenProductList::~TopTenProductList()
{
	for (auto& p : products)
		delete p.second;
}
void TopTenProductList::PutProductInfo(const int& pid, const string& name, const int &count)
{
	time_t t = time(NULL);
	tm tm1{};
	localtime_s(&tm1, &t);
		
	char buff[256];
	sprintf_s(buff, "%d_%d_%d", tm1.tm_hour, tm1.tm_min, pid);
	string key = buff;
	if (products.find(key) == products.end())
	{
		products[key] = new Product(pid, name, count);
	}
	else
	{
		Product* p = products[key];
		int count = p->getcount() + 1;
		p->setcount(count);
	}
	cout << key << endl;	
}

bool TopTenProductList::IsLastOnehourProduct(int hour, int min)
{
	time_t t = time(NULL);
	tm tm1;
	localtime_s(&tm1, &t);
	int currhour = tm1.tm_hour;
	int currmin = tm1.tm_min;

	if ((currhour == hour && min <= currmin) || (currhour - 1 == hour) && min >= currmin)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void TopTenProductList::GetTopProductInfo(PriorityQueue & toptenproducts)
{
	//list of last one hour products
	std::map<int, Product*> tempproduct;		
	//iterate through the map to find the last one hour product counts
	for (auto &p : products)
	{
		string key = p.first;
		Product* product = p.second;
		int hour = 0;
		int min = 0;
		int productid = 0;

		int index1 = 0;
		index1 = (int)key.find("_");
		if (index1 != string::npos)
		{
			hour = atoi(key.substr(0, index1).c_str());
		}
		int index2 = (int)key.find("_", index1+1);
		if (index2 != string::npos)
		{
			min = atoi(key.substr(index1+1, index2-index1-1).c_str());
		}
		productid = atoi(key.substr(index2 + 1).c_str());

		//compact the unique products
			
		if (IsLastOnehourProduct(hour, min))
		{
			if (tempproduct.find(productid) == tempproduct.end())
			{
				tempproduct[productid] = new Product(productid, product->getName(), product->getcount());
			}
			else
			{ 
				Product* p = tempproduct[productid];
				int count = p->getcount() + product->getcount();
				p->setcount(count);
			}
		}
		else
		{
			//save storage because we always need to get only last one hour top ten products
			products.erase(key);
		}		

	}		

	//Iterate the last one hour products list and put it into priority queue
	//put it in priority queue
	for (auto &p : tempproduct)
	{
		Product* p1 = new Product(p.second->getProductid(), p.second->getName(), p.second->getcount());
		//p1->setcount();
		toptenproducts.push(p1);
	}

	//clear tempproduct
	for (auto &p : tempproduct)
	{
		delete p.second;
	}

	return;
}
