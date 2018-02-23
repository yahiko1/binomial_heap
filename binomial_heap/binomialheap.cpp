// binomialheap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;


struct node
{
	int key;
	int degree;
	node* parent;
	node* child;
	node* sibling;
};


node* Binomial_Heap_Minimum(node* H);
node* Binomial_Heap_Merge(node* H1, node* H2);
void Binomial_Heap_Link(node*& y, node*& z);
node* Binomial_Heap_Union(node* H1, node* H2);
node* Binomial_Heap_Insert(node*& H, int x);
node* Binomial_Heap_Extract_Min(node* H);
void Binomial_Heap_Invert_List(node* x, node*& H1); 
void Binomial_Heap_Decrease_Key(node* H, node* x, int k);
void Binomial_Heap_Delete(node* H, node* x);
void Binomial_Heap_Display(node* H);
node* Binomial_Heap_Search(node* H, int k);


int main()
{
	int m, l, i;
	
	node* p;
	node* H = nullptr;
	while (1)
	{
		cout << "----------------------------" << endl;
		cout << "Operations on Binomial heap" << endl;
		cout << "----------------------------" << endl;
		cout << "1)Insert Element in the heap" << endl;
		cout << "2)Extract Minimum key node" << endl;
		cout << "3)Decrease key of a node" << endl;
		cout << "4)Delete a node" << endl;
		cout << "5)Display Heap" << endl;
		cout << "6)Exit" << endl;
		cout << "Enter Your Choice: ";
		cin >> i;
		switch (i)
		{
		case 1:
			cout << "Enter the element to be inserted: ";
			cin >> m;
			H = Binomial_Heap_Insert(H, m); 
			break;
		case 2:
			p = Binomial_Heap_Extract_Min(H);
			if (p != nullptr)
				cout << "The node with minimum key: " << p->key << endl;
			else
				cout << "Heap is empty" << endl;
			break;
		case 3:
			cout << "Enter the key to be decreased: ";
			cin >> m;
			cout << "Enter new key value: ";
			cin >> l;
			p = Binomial_Heap_Search(H, m);
			Binomial_Heap_Decrease_Key(H, p, l);
			break;
		case 4:
			cout << "Enter the key to be deleted: ";
			cin >> m;
			p = Binomial_Heap_Search(H, m);
			Binomial_Heap_Delete(H, p);
			break;
		case 5:
			Binomial_Heap_Display(H);
			break;
		case 6:
			exit(1);
		default:
			cout << "Wrong Choice";
		}
	}


	system("pause");
    return 0;
}


node* Binomial_Heap_Minimum(node* H)
{
	node* y = nullptr;
	node* x = H;
	int min = INT_MAX;
	while (x != nullptr)
	{
		if (x->key < min)
		{
			min = x->key;
			y = x;
		}
		x = x->sibling;
	}
	return y;
}


node* Binomial_Heap_Merge(node* H1, node* H2)
{
	node* H = nullptr;
	node* y;
	node* z;
	node* a;
	node* b;
	y = H1;
	z = H2;
	if (y != nullptr)
	{
		if (z != nullptr)
		{
			if (y->degree <= z->degree)
				H = y;
			else if (y->degree > z->degree)
				H = z;
	    }
	    else
			H = y;
	}
	else
		H = z;
	while (y != nullptr && z != nullptr)
	{
		if (y->degree < z->degree)
			y = y->sibling;
		else if (y->degree == z->degree)
		{
			a = y->sibling;
			y->sibling = z;
			y = a;
		}
		else
		{
			b = z->sibling;
			z->sibling = y;
			z = b;
		}
	}
	return H;
}


void Binomial_Heap_Link(node*& y, node*& z)
{
	y->parent = z;
	y->sibling = z->child;
	z->child = y;
	z->degree += 1;
}


node* Binomial_Heap_Union(node* H1, node* H2)
{
	node* x;
	node* prev_x;
	node* next_x;
	node* H = nullptr;
	H = Binomial_Heap_Merge(H1, H2);
	if (H == nullptr)
		return H;
	prev_x = nullptr;
	x = H;
	next_x = x->sibling;
	while (next_x != nullptr)
	{
		if ((x->degree != next_x->degree) || ((next_x->sibling != nullptr) && (next_x->sibling->degree == x->degree)))
		{
			prev_x = x;
			x = next_x;
		}
		else
		{
			if (x->key <= next_x->key)
			{
				x->sibling = next_x->sibling;
				Binomial_Heap_Link(next_x, x);
			}
			else
			{
				if (prev_x == nullptr)
					H = next_x;
				else
					prev_x->sibling = next_x;
				Binomial_Heap_Link(x, next_x);
				x = next_x;
			}
		}
		next_x = x->sibling;
	}
	return H;
}


node* Binomial_Heap_Insert(node*& H, int x)
{
	node* H1 = new node;
	H1->child = nullptr;
	H1->degree = 0;
	H1->key = x;
	H1->parent = nullptr;
	H1->sibling = nullptr;
	H = Binomial_Heap_Union(H, H1);
	return H;
}


node* Binomial_Heap_Extract_Min(node* H)
{
	int m = INT_MAX;
	node* a = H;
	node* temp = nullptr;
	temp = Binomial_Heap_Minimum(H);
	if (temp == H && temp->sibling == nullptr)  //до последнего елсе случай, когда самый первый корень миримальный
		H = nullptr;
	else if (temp == H)
		H = temp->sibling;
	else
	{
		while (a->sibling != temp)
			a = a->sibling;
		a->sibling = temp->sibling;
	}

	node* H1 = new node;
	if (temp->child != nullptr)
	{
		Binomial_Heap_Invert_List(temp->child, H1);
		temp->child->sibling = nullptr;
	}
	H = Binomial_Heap_Union(H1, H);
	return temp;
}


void Binomial_Heap_Invert_List(node* x, node*& H1)
{
	if (x->sibling != nullptr)
	{
		Binomial_Heap_Invert_List(x->sibling, H1);
		x->sibling->sibling = x;
	}
	else
		H1 = x;
}


void Binomial_Heap_Decrease_Key(node* H, node* x, int k)
{
	if (k > x->key)
	{
		cout << "\nNew key is larger thet previos\n ";
		return;
	}
	x->key = k;
	node* y = x;
	node* z = y->parent;
	while (z != nullptr && y->key < z->key)
	{
		swap(z->key, y->key);
		y = z;
		z = y->parent;
	}
}


void Binomial_Heap_Delete(node* H, node* x)
{
	int m = INT_MIN;
	Binomial_Heap_Decrease_Key(H, x, m);
	Binomial_Heap_Extract_Min(H);
}


void Binomial_Heap_Display(node* H)
{
	if (H == nullptr)
	{
		cout << "The Heap is empty" << endl;
		return;
	}
	cout << "The root nodes are: " << endl;
	node* p;
	p = H;
	while (p != nullptr)
	{
		cout << p->key;
		if (p->sibling != nullptr)
			cout << "-->";
		p = p->sibling;
	}
	cout << endl;
}


node* Binomial_Heap_Search(node* H, int k)
{
	node* x = H;
	node* p = nullptr;
	if (x->key == k)
	{
		p = x;
		return p;
	}
	if (x->child != nullptr && p == nullptr)
		p = Binomial_Heap_Search(x->child, k);
	if (x->sibling != nullptr && p == nullptr)
		p = Binomial_Heap_Search(x->sibling, k);
	return p;
}