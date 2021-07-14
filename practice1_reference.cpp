//Do not modify main funaiton.
//Do not introduce new functions

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

	//inplement the following member functions:

	void sort();//sort all values based on frequency.
						  //In case of ties, the values occur earlier will appear earlier
						  //Example:  for list with values  7 6 12 4 33 12 6 6 7
						  //sorted results: 6 6 6 7 7 12 12 4 33

	doubly_linked_list operator+(const doubly_linked_list &L);//L is read-only
															  //return a frequency_sorted list by combining the current frequency_sorted list with another
															  //frequency_sorted list L
															  //If your algorithm is inefficient, you might lose points.
															  //The values in the current list occur before that of L.
															  //You will not modify L.

	void insert(int k);
	//after insert(12) to the above,
	//we have 6 6 6 12 12 12 7 7 4 33
	//Insert value k to a frequency_sorted list
	//After insert, the list remains frequency_sorted





	void remove(int k, int n); //remove value k n times from a frequency_sorted list.
							   //if there are fewer than n occurances of k, then remove all occurnces of k
							   //The final result will remain a frequency_sorted list.
							   //For example, if the list is 7 7 7 2 2 4 4 5 5 44 3
							   //After remove(2,5), the list will become 7 7 7 4 4 5 5 44 3
};

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
