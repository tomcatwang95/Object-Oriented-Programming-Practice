#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

template <class T> class ThreeD {
public:
	T ht;
	T wid;
	T dep;
	ThreeD() { ht = wid = dep = 0; }
	ThreeD(T i) { ht = wid = dep = i; }
	ThreeD(T a, T b, T c) { ht = a; wid = b; dep = c; }
	bool operator!=(ThreeD<T> &t)
	{
		return (ht * wid * dep != t.ht * t.wid * t.dep);
	}
	bool operator==(ThreeD<T> &t)
	{
		return (ht*wid*dep == t.ht*t.wid*t.dep);
	}
	template <class T>friend ostream&operator<<(ostream &output, const ThreeD<T>&O);
	void operator=(const ThreeD &O);
};

template <class T>ostream&operator<<(ostream &output, const ThreeD<T>&O)
{
	output << "( " << O.ht << ", " << O.wid << ", " << O.dep << " )";
	return output;
}

template <class T>void ThreeD<T>::operator=(const ThreeD &O)
{
	ht = O.ht;
	wid = O.wid;
	dep = O.dep;
}

template <class T> class node {
public:
	T value;
	node<T> * next;
	node<T> * previous;
	node<T>() { next = nullptr; previous = nullptr; }
	node<T>(T v) { value = v; next = nullptr; previous = nullptr; }
};

template <class T> class linked_list {
public:
	node<T> * first; 
	node<T> * last; 
	linked_list() { first = last = nullptr; }
	linked_list(const initializer_list<T> &L);
	linked_list(const linked_list<T> &L);
	~linked_list();
	bool operator==(linked_list<T> &L);
	bool operator!=(linked_list<T> &L);
	void operator=(const linked_list &L);
	template <class T> friend ostream & operator<<(ostream &output, const linked_list<T>&O);
	void push_front(T t);
	void push_back(T t);
};

template <class T> linked_list<T>::linked_list(const initializer_list<T> &L) : linked_list()
{
	auto it1 = L.begin();
	node<T> *A = new node<T>(*it1);
	first = last = A;
	it1++;
	while (it1 != L.end())
	{
		node<T>*B = new node<T>(*it1);
		last->next = B;
		B->previous = last;
		last = B;
		it1++;
	}
}

template <class T> linked_list<T>::linked_list(const linked_list<T> &L) : linked_list()
{
	node<T> *NP = L.first;
	for (; NP != nullptr; NP = NP->next)
	{
		push_back(NP->value);
	}
}

template <class T> linked_list<T>::~linked_list()
{
	node<T> *D;
	while (first != nullptr)
	{
		D = first->next;
		delete first;
		first = D;
	}
}

template <class T>ostream&operator<<(ostream &output, const linked_list<T>&O)
{
	node<T> * p = O.first;
	do
	{
		output << p->value << " ";
		p = p->next;
	} while (p != nullptr);
	return output;
}

template <class T> void linked_list<T>::operator=(const linked_list<T> &L)
{
	node<T> * D;
	while (first != nullptr)
	{
		D = first->next;
		delete first;
		first = D;
	}
	D = L.first;
	while (D != nullptr)
	{
		push_back(D->value);
		D = D->next;
	}
}

template <class T> bool linked_list<T>::operator==(linked_list<T> &L)
{
	node<T> * p1 = first, *p2 = L.first;
	while (p1 != nullptr) 
	{
		if (p2==nullptr || p1->value != p2->value) 
		{ 
			return false; 
		}
		p1 = p1->next;
		p2 = p2->next;
	}
	if (p2!= nullptr)
	{
		return false;
	}
	else
	{
		return true;
	}
}

template <class T> bool linked_list<T>::operator!=(linked_list<T> &L)
{
	node<T> * p1 = first, *p2 = L.first;
	while (p1 != nullptr)
	{
		if (p2 == nullptr || p1->value != p2->value)
		{
			return true;
		}
		p1 = p1->next;
		p2 = p2->next;
	}
	if (p2 != nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <class T> void linked_list<T>::push_front(T t)
{
	node<T> *R = new node<T>(t);
	if (first == nullptr)
	{
		first = last = R;
	}
	else 
	{
		R->next = first;
		first->previous = R;
		R->previous = nullptr;
		first = R;
	}
}

template <class T> void linked_list<T>::push_back(T t)
{
	node<T> *R = new node<T>(t);
	if (first == nullptr)
	{
		first = last = R;
	}
	else
	{
		R->previous = last;
		last->next = R;
		last = R;
		R->next = nullptr;
	}
}

template <class X>
class item {
public:
	X data;
	item<X> *next;
	item<X> *previous;
	item<X>(X d) { data = d; next = nullptr; previous = nullptr; }
	bool operator==(item<X> I) { return data == I.data; }
	template <class X> friend ostream&operator<<(ostream &output, const item<X>&O);
	void operator=(const item<X> & I);
};
template <class X>void item<X>::operator=(const item<X> & I)
{
	data = I.data;
}

template <class X>ostream&operator<<(ostream &output, const item<X>&O)
{
	output << O.data;
	return output;
}

template <class X>
class bag {
public:
	item<X> *head; 
	item<X> *tail; 
	bag() { head = nullptr; tail = nullptr; num_items = 0; }
	bag(const initializer_list<X>&L);
	bag(const bag<X>&B);
	~bag();
	template <class X> friend ostream & operator<<(ostream &output, const bag<X>&O);
	void operator=(const bag<X> & B);
	int num_items;
	int size() { return num_items; }
	void push_back(X d); 
	void push_front(X d); 
	void pop_back(); 
	void pop_front(); 
	X &operator[](int i); 
	X front() 
	{  
		return head->data;
	}
	X back() 
	{ 
		return head->data;
	}
	void clear(); 
	item<linked_list<ThreeD<double>>> * find(linked_list<ThreeD<double>> &d);
	item<vector<linked_list<ThreeD<int>>>> *find(vector<linked_list<ThreeD<int>>>&L);
	void erase(int index);
	void erase(item<X> * p);
	item<X> * insert(item<X> *p, X d); 
};

template<class X> bag<X>::bag(const initializer_list<X>&L)
{
	auto it1 = L.begin();
	item<X> *A = new item<X>(*it1);
	head = tail = A;
	it1++;
	num_items = 1;
	while (it1 != L.end())
	{
		item<X>*B = new item<X>(*it1);
		tail->next = B;
		B->previous = tail;
		tail = B;
		it1++;
		num_items++;
	}
}

template<class X>bag<X>::bag(const bag<X>&B) :bag()
{
	item<X> * CO = B.head;
	while (CO != nullptr) 
	{
		push_back(CO->data);
		CO = CO->next;
	}
}

template<class X>bag<X>::~bag()
{
	item<X>*I = head, *D;
	while (I != nullptr)
	{
		D = I->next;
		delete I;
		I = D;
	}
}

template<class X>void bag<X>::operator=(const bag<X> & B)
{
	num_items = 0;
	head = tail = nullptr;
	item<X>*I = head, *D;
	while (I != nullptr)
	{
		D = I->next;
		delete I;
		I = D;
	}
	item<X> * CO = B.head;
	while (CO != nullptr)
	{
		push_back((*CO).data);
		CO = CO->next;
	}
}

template <class T> ostream & operator<<(ostream &output, const bag<T>&O)
{
	item<T> *B = O.head;
	while (B != nullptr)
	{
		output << B->data << " ";
		B = B->next;
	}
	return output;
}

template<class X>item<linked_list<ThreeD<double>>> *bag<X>::find(linked_list<ThreeD<double>> &d)
{
	item<linked_list<ThreeD<double>>>*Look;
	if (num_items == 0)
	{
		return nullptr;
	}
	for (Look = head; Look != nullptr; Look = Look->next)
	{
		if (Look->data == d)
		{
			return Look;
		}
	}
	return nullptr;
}

template<class X>item<vector<linked_list<ThreeD<int>>>> *bag<X>::find(vector<linked_list<ThreeD<int>>>&L)
{
	item<vector<linked_list<ThreeD<int>>>>*Look = head;
	while (Look != tail)
	{
		if (Look->data.size()==L.size())
		{
			int c = 0;
			for (unsigned i = 0; i < Look->data.size(); i++)
			{
				if (Look->data[i]!=L[i])
				{
					c++;
					break;
				}
			}
			if (c == 0)
			{ return Look;}
		}
		Look = Look->next;
	}
	return nullptr;
}


template <class X> X &bag<X>::operator[](int i)
{
	item<X> *Look = head;
	while (i > 0) 
	{
		Look = Look->next;
		i--;
	}
	return Look->data;
}

template <class X> item<X>*bag<X>:: insert(item<X> *p, X d)
{
	item<X>*I = new item<X>(d);
	if (p->previous == nullptr)
	{
		I->next = head;
		I->previous = nullptr;
		head = I;
	}
	else
	{
		p->previous->next = I;
		I->previous = p->previous;
		I->next = p;
		p->previous = I;
	}
	return I;
	num_items++;
}

template<class X> void bag<X>::erase(int index)
{
	item<X> * Look = head;
	if (num_items <= index) 
	{
		return;
	}
	if (num_items == 1) 
	{
		delete Look;
		head = nullptr;
		tail = nullptr;
		num_items=0;
		return;
	}
	for (int i = 0; i < index; i++) 
	{
		Look = Look->next;
	}
	if (index == 0) 
	{
		Look->next->previous = nullptr;
		head = Look->next;
		delete Look;
		num_items--;
		return;	
	}
	if (Look->next != nullptr)
	{
		Look->next->previous = Look->previous;
		Look->previous->next = Look->next;
		delete Look;
		num_items--;
	}
	else 
	{
		tail = Look->previous;
		Look->previous->next = nullptr;
		delete Look;
		num_items--;
	}
}

template<class X> void bag<X>::erase(item<X> * p)
{
	if (p == nullptr)
	{
		return;
	}
	if (*head == *p) 
	{ 
		head = p->next;
		head->previous = nullptr;
	}
	else if (*tail == *p) 
	{ 
		tail = p->previous; 
		tail->next = nullptr;
	}
	else
	{
		p->previous->next = p->next;
		p->next->previous = p->previous;
	}
	delete p;
	num_items--;
}

template<class X> void bag<X>::clear()
{
	item<X> *c1=head , *c2;
	while(c1!=nullptr)
	{
		c2 = c1->next;
		delete c1;
		c1 = c2;
	}
	head = tail = nullptr;
	num_items = 0;
}

template<class X> void bag<X>::push_front(X v) 
{
	item<X> *pf;
	pf = new item<X>(v);
	if (num_items == 0)
	{
		head = tail = pf;
	}
	else 
	{
		head->previous = pf;
		pf->next = head;
		head = pf;
	}
	num_items++;
}

template<class X> void bag<X>::push_back(X v)
{
	item<X> *pb;
	pb = new item<X>(v);
	if (num_items == 0)
	{
		head = tail = pb;
	}
	else
	{
		pb->previous = tail;
		tail->next = pb;
		tail = pb;
	}
	num_items++;
}

template<class X> void bag<X>::pop_front()
{
	if (num_items == 0)
	{
		return;
	}
	if (num_items == 1)
	{
		delete head;
		head = tail = nullptr;
		num_items = 0;
		return;
	}
	item<X>*POF;
	POF = head->next;
	head->previous = nullptr;
	delete head;
	head = POF;
	num_items--;
}

template<class X> void bag<X>::pop_back()
{
	if (num_items == 0)
	{
		return;
	}
	if (num_items == 1)
	{
		delete tail;
		head = tail = nullptr;
		num_items = 0;
		return;
	}
	item<X>*POB;
	POB = tail->previous;
	delete tail;
	tail = POB;
	num_items--;
	tail->next = nullptr;
}

template <class X>ostream&operator<<(ostream &output, const vector<X>&O)
{
	output << "[";
	for (size_t i = 0; i < O.size()-1; i++) 
	{
		output << O[i] << ", ";
	}
	output << O[O.size() - 1] << "]";
	return output;	
}

int main() {

	bag<double> bag_d;
	bag_d.push_back(5.5);
	bag_d.push_back(6.6);
	bag_d.push_front(4.4);
	bag_d.push_front(3.3);
	bag_d.pop_front();
	bag_d.pop_back();
	cout << bag_d << endl;;
	bag<int> bag_i;
	bag_i.push_back(5);
	bag_i.push_back(6);
	bag_i.push_front(4);
	bag_i.push_front(3);
	bag_i.pop_front();
	bag_i.pop_back();
	cout << bag_i << endl;

	ThreeD<int> td3(3), td4(4), td5(5), td6(6), td7(100, 200, 300);
	bag<ThreeD<int>> bag_3D;
	bag_3D.push_back(td5);
	bag_3D.push_back(td6);
	bag_3D.push_front(td4);
	bag_3D.push_front(td3);
	bag_3D.pop_front();
	bag_3D.pop_back();
	cout << bag_3D << endl;;
	cout << bag_3D.front() << bag_3D.back();
	cout << bag_3D[0] << " " << bag_3D[1] << endl;
	bag_3D[1] = td7;
	cout << bag_3D[0] << " " << bag_3D[1] << endl;
	bag_3D.clear();
	cout << bag_3D << endl;;
	cout << bag_3D.size() << endl;
	linked_list<string>ls_1;
	ls_1.push_front("David");
	ls_1.push_front("John");
	ls_1.push_front("Pat");
	ls_1.push_front("Ben");
	ls_1.push_front("Jeff");
	cout << ls_1 << endl;

	linked_list<string>ls_2;
	ls_2.push_front("Wendy");
	ls_2.push_front("Mary");
	ls_2.push_front("Nancy");
	ls_2.push_front("Jennifer");
	cout << ls_2 << endl;

	bag<linked_list<string>> bag_string;

	bag_string.push_back(ls_1);

	bag_string.push_back(ls_2);

	cout << bag_string << endl;
	cout << bag_string[1] << endl;

	ThreeD<double> t10(3.2, 7.4, 8.9), t11(5.6, 7.7, 2.987), t12(4.6, 7.5, 3.1416), t13(55.6, 66.8, 333.45);
	linked_list<ThreeD<double>> LTD1;
	LTD1.push_front(t10);

	LTD1.push_front(t11);
	linked_list<ThreeD<double>> LTD2;
	LTD2.push_front(t13);
	LTD2.push_front(t12);
	LTD2.push_front(t10);
	LTD2.push_front(t11);

	bag<linked_list<ThreeD<double> > > BLTD;
	BLTD.push_back(LTD1);
	BLTD.push_back(LTD2);
	cout << BLTD << endl;

	item<linked_list<ThreeD<double>>> * p2;

	p2 = BLTD.find(LTD1);
	BLTD.erase(p2);
	cout << BLTD << endl;
	BLTD.push_back(LTD1);
	cout << BLTD << endl;
	BLTD.erase(0);
	cout << BLTD << endl;

	vector<ThreeD<int>> V1 = { { 1,2,3 },{ 4,5,6 },{ 7,8,9 } };
	cout << V1 << endl;
	vector<bag<ThreeD<int>>> V2 = { { { 1,2,3 },{ 4,5,6 },{ 7,8,9 } },{ { 20,30,40 },{ 11,22, 33 } } };
	cout << V2 << endl;

	vector<bag<linked_list<int>>> V3 = { { { 1, 2, 3 },{ 4, 5 } },{ { 6,7 },{ 8, 9, 10 } } };
	cout << V3 << endl;

	bag<int> B10 = { 1,2,3,4,5 };
	bag<int> B11 = B10, B12;
	B12 = B10;
	cout << B10 << endl;
	B10.head->data = 1000;
	cout << B10 << endl;
	cout << B11 << endl;
	cout << B12 << endl;

	bag<vector<linked_list<ThreeD<int>>>> B13 = { { { { 1,2,3 },{ 4,5,6 } },{ { 7,8,9 },{ 10,11,12 },{ 13,14,15 } } },{ { { 16,17,18 },{ 19,20,21 },{ 22,23,24 } },{ { 25,26,27 },{ 28,29,30 } },{ { 31,32,33 },{ 34,35,36 },{ 37,38,39 },{ 40,41,42 } } } };
	cout << B13 << endl;

	bag<bag<bag<ThreeD<int>>>> B14 = { { { { 1,2,3 },{ 4,5,6 } },{ { 7,8,9 },{ 10,11,12 },{ 13,14,15 } } },{ { { 16,17,18 },{ 19,20,21 },{ 22,23,24 } },{ { 25,26,27 },{ 28,29,30 } },{ { 31,32,33 },{ 34,35,36 },{ 37,38,39 },{ 40,41,42 } } } };
	cout << B14 << endl;

	bag<linked_list<int>> * p10 = new bag<linked_list<int>>({ { 1,2,3,4 },{ 5,6,7 } });
	cout << *p10 << endl;
	delete p10;
	bag<vector<linked_list<ThreeD<int>>>> B15 = { { { { 1,2,3 },{ 4,5,6 } },{ { 7,8,9 },{ 10,11,12 },{ 13,14,15 } } },{ { { 16,17,18 },{ 19,20,21 },{ 22,23,24 } },{ { 25,26,27 },{ 28,29,30 } },{ { 31,32,33 },{ 34,35,36 },{ 37,38,39 },{ 40,41,42 } } } };
	cout << B15 << endl;
	B15.erase(1);
	cout << B15 << endl;
	bag<vector<linked_list<ThreeD<int>>>> B16 = { { { { 1,2,3 },{ 4,5,6 } },{ { 7,8,9 },{ 10,11,12 },{ 13,14,15 } } },{ { { 16,17,18 },{ 19,20,21 },{ 22,23,24 } },{ { 25,26,27 },{ 28,29,30 } },{ { 31,32,33 },{ 34,35,36 },{ 37,38,39 },{ 40,41,42 } } } };
	vector<linked_list<ThreeD<int>>> V4 = { { { 6,1,1 },{ 2,5,12 } },{ { 9,8,7 },{ 11,10,12 },{ 26,7,15 } } };
	vector<linked_list<ThreeD<int>>> V5 = { { { 6,1,1 },{ 2,5,12 } },{ { 9,8,7 },{ 11,10,12 },{ 26,7,5 } },{ { 6,1,1 },{ 2,5,12 } } };
	B16.insert(B16.head, V5);
	cout << B16.front().size() << endl;
	item<vector<linked_list<ThreeD<int>>> > * p20 = B16.find(V4);
	if (p20 != nullptr) cout << (p20->data).size() << endl;
	getchar();
	getchar();
	return 0;
}
