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
	void make_random_list(int m, int n); 
	void print_forward();
	void print_backward();
	void sort(node * p1, node * p2);
};

void doubly_linked_list::sort(node * p1, node * p2)
{
	node *pivot;
	node *finder, *res1;
	node *phead=p1 , *ptail=p2;
	int count=0;
	if (p1 == nullptr||p2 == nullptr||p1 == p2)
	{
		return;
	}
	pivot = p1;
	finder = p1->next;
	while (finder != nullptr&&finder != p2->next)
	{
		res1 = finder;
		ptail = finder;
		finder = finder->next;
		if (res1->value < pivot->value)
		{
			if (tail != p2)
			{
				ptail = ptail->previous;
			}
			count++;
			if (count == 1)
			{
				phead = res1;
			}
			if (res1 == tail)
			{
				tail = res1->previous;
				res1->previous->next = nullptr;
			}
			else
			{
				res1->previous->next = res1->next;
				res1->next->previous = res1->previous;
			}
			if (pivot == head)
			{
				head = res1;
				res1->previous = nullptr;
			}
			else
			{
				res1->previous = pivot->previous;
				pivot->previous->next = res1;
			}
			res1->next = pivot;
			pivot->previous = res1;
		}
		else if (res1->value == pivot->value)
		{
			ptail = ptail->previous;
			if (res1 == tail)
			{
				tail = res1->previous;
				res1->previous->next = nullptr;
			}
			else
			{
				res1->previous->next = res1->next;
				res1->next->previous = res1->previous;
			}
			res1->next = pivot->next;
			pivot->next->previous = res1;
			res1->previous = pivot;
			pivot->next = res1;
		}
	} 
	if (phead!=ptail->previous&&phead != pivot->previous&&phead!=pivot)
	{
		sort(phead, pivot->previous);
	}
	while (pivot->next!=nullptr&&pivot->next->value == pivot->value)
	{
		pivot = pivot->next;
	}
	if (ptail != phead->next&&pivot->next != ptail&&phead!=pivot)
	{
		sort(pivot->next, ptail);
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
