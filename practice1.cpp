#include "pch.h"
#include <iostream>
using namespace std;

class node
{
public:
	int value;
	node * next;
	node * previous;
	node(int i) { value = i; next = previous = nullptr; }
	node() { next = previous = nullptr; }
};

class doubly_linked_list {
public:
	node * head;
	node * tail;
	doubly_linked_list() { head = tail = nullptr; }
	void make_random_list(int m, int n);
	void print_forward();
	void print_backward();
	void sort();
	void insert(int k);
	void remove(int k, int n);
};

void doubly_linked_list::insert(int k)
{
	node *p1 = head;
	node *p2;
	node *pstar = nullptr;
	node *pand = nullptr;
	p2 = new node(k);

	if (p1 == nullptr)
	{
		head = tail = p2;
		return;
	}
	if (p1->next == nullptr)
	{
		p1->next = p2;
		p2->previous = p1;
		tail = p2;
		return;
	}
	int count = 0;
	while (p1 != nullptr)
	{
		if (p1->value == p2->value)
		{
			count++;
			if (count == 1)
			{
				pstar = p1;
			}
			pand = p1;
		}
		if (count >= 1 && p1->value != p2->value)
		{
			break;
		}
		p1 = p1->next;
	}
	if (count == 0 || pstar == nullptr || pand == nullptr)
	{
		tail->next = p2;
		p2->previous = tail;
		tail = p2;
		return;
	}
	node *pfind = pstar;
	if (pstar->previous == nullptr)
	{
		pand->next = p2;
		p2->previous = pand;
		if (pand->next == nullptr)
		{
			p2 = tail;
		}
		else
		{
			p2->next = pand->next;
			p2->next->previous = p2;
		}
		return;
	}
	
	while (pfind != nullptr && pfind->previous != nullptr)
	{
		if (pfind->value == pfind->previous->value)
		{
			for (int m = 0; m < count; m++)
			{
				pfind = pfind->next;
			}
			if (pfind->value == pstar->value)
			{
				p2->next = pand->next;
				pand->next->previous = p2;
				pand->next = p2;
				p2->previous = pand;
				return;
			}
			else 
			{
				if (pand->next == nullptr)
				{
					tail=pstar->previous;
					tail->next = nullptr;
				}
				else
				{
					pstar->previous->next = pand->next;
					pand->next->previous = pstar->previous;
				}
					pand->next = p2;
					p2->previous = pand;
					pfind->previous->next = pstar;
					pstar->previous = pfind->previous;
					p2->next = pfind;
					pfind->previous = p2;
			}
			return;
		}
		for (int i = count; i > 0; i--)
		{
			if (pfind != nullptr)
			{
				pfind = pfind->previous;
			}
			else break;
		}
	}
	
	if (pand->next == nullptr)
	{
		tail = pstar->previous;
		tail->next = nullptr;
	}
	else
	{
		pstar->previous->next = pand->next;
		pand->next->previous = pstar->previous;
	}
	pand->next = p2;
	p2->previous = pand;
	p2->next = head;
	head->previous = p2;
	head = pstar;
	pstar->previous = nullptr;
}
void doubly_linked_list::remove(int k, int n)
{
	node *p1 = head,*p2=nullptr;
	int co=0;
	while (p1 != nullptr)
	{
		if (p1->value == k)
		{
			co++;
			if (co == 1)
			{
				p2 = p1;
			}
		}
		p1 = p1->next;
	}
	cout << endl;
	node *p3;
	p3 = p2;
	for (int i = 0; i < co; i++)
	{
		p3 = p3->next;
	}
	p3->next->previous = p2->previous;
	p2->previous->next = p3->next;
	if (co > n)
	{
		for (int j = 0; j < co-n; j++)
		{
			insert(k);
		}
	}
	else
	{
		return;
	}
}

void doubly_linked_list::sort()
{
	node *p1 = head;
	head = nullptr;
	tail = nullptr;
	int tem;
	while (p1 != nullptr)
	{
		tem = p1->value;
		insert(tem);
		p1 = p1->next;
	}
}
void doubly_linked_list::make_random_list(int m, int n) {

	for (int i = 0; i < m; i++) {
		node * p1 = new node(rand() % n);
		p1->previous = tail;
		if (tail != nullptr) tail->next = p1;
		tail = p1;
		if (head == nullptr) head = p1;
	}
}

void doubly_linked_list::print_forward() {
	cout << endl;
	node * p1 = head;
	while (p1 != nullptr) {
		cout << p1->value << " ";
		p1 = p1->next;
	}
}

void doubly_linked_list::print_backward() {
	cout << endl;
	node * p1 = tail;
	while (p1 != nullptr) {
		cout << p1->value << " ";
		p1 = p1->previous;
	}
}
int main() {
	doubly_linked_list d1;
	d1.make_random_list(50, 20);
	d1.print_forward();
	d1.print_backward();

	d1.sort();
	d1.print_forward();
	d1.print_backward();

	d1.insert(16);
	d1.print_forward();
	d1.print_backward();

	d1.insert(16);
	d1.print_forward();
	d1.print_backward();

	d1.insert(16);
	d1.print_forward();
	d1.print_backward();

	d1.insert(16);
	d1.print_forward();
	d1.print_backward();
	
	d1.remove(4, 3);
	d1.print_forward();
	d1.print_backward();
	
	getchar();
	getchar();
	return 0;
}
