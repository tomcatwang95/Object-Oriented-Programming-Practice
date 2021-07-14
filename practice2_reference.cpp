//Implement In-place quick sort
//You are only allowed to modify pointers of nodes, but not values of nodes
//Do not modify main function
//Do not introduce new functions

#include "pch.h"
#include <iostream>
using namespace std;

class node {
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
	void make_random_list(int m, int n); //create m nodes with value randomly in 0 ... n-1
	void print_forward();
	void print_backward();

	//inplement the following member functions:

	void sort(node * p1, node * p2);
	//Range of sort is from *p1 to *p2
	//Use in-place quick sort algorithm to sort the linked list in ascending order.
	//You are only allowed to modify the pointers of nodes, but not values of nodes

};

void doubly_linked_list::sort(node * p1, node * p2)
{
	node *pivot;
	node *finder, *res1, *res2;
	node *leftend = nullptr, *rightend = nullptr;
	pivot = p1;
	finder = pivot->next;
	while (finder != p2)
	{
		res1 = finder;
		res2 = finder;
		finder = finder->next;
		if (res1->value < pivot->value)
		{
			if (p1 == head)
			{
				res1->next = head;
				head = res1;
			}
			else
			{
				res1->previous = pivot->previous;
				pivot->previous->next = res1;//separate piviot
			}
			if (leftend == nullptr)
			{
				leftend = res1;
			}
			else
			{
				leftend->next = res1;
				res1->previous = leftend;
				leftend = res1;
			}
			delete res1;
		}
		if (res2->value >= pivot->value)
		{
			if (p2 == tail)
			{
				if (rightend == nullptr)
				{
					tail = res2;
					res2->next = tail;
					rightend = res2;
				}
				else
				{
					rightend->previous = res2;
					res2->next = rightend;
					rightend = res2;
				}
			}
			else
			{
				if (rightend == nullptr)
				{
					p2->next->previous = res2;
					res2->next = p2->next;
					rightend = res2;
				}
				else
				{
					rightend->previous = res2;
					res2->next = rightend;
					rightend = res2;
				}
			}
			delete res2;
		}
		leftend->next = pivot;
		pivot->previous = leftend;
		rightend->previous = pivot;
		pivot->next = rightend;
	} 
	
	
	if (p1->value != pivot->value || p2->value != pivot->value)
	{
		sort(p1, pivot);
		sort(pivot->next, p2);
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

	d1.sort(d1.head, d1.tail);
	d1.print_forward();
	d1.print_backward();


	getchar();
	getchar();
	return 0;
}
