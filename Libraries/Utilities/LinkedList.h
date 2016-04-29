#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

template<class T>
struct LinkedList
{

private:
	//Node is an element in the linked list that holds the element reference and the next/previous elements.
	template<class U>
	struct Node
	{
		Node()
			:
			previous(0),
			next(0)
		{}

		Node(U i, Node* p, Node* n)
			: storedItem(i),
			previous(p),
			next(n)
		{}

		~Node()
		{
			previous = 0;
			next = 0;
		}

		U storedItem;
		Node<U>* previous;
		Node<U>* next;

	};


public:


	class Iterator {

	public:
		Iterator(Node<T>* node):
		thisNode(node)
		{

		}

		Iterator next()
		{
			return Iterator(thisNode->next);
		}

		Iterator prev()
		{
			return Iterator(thisNode->previous);
		}

		bool operator!=(Iterator rhs)
		{

			if (thisNode == NULL)
				return rhs.thisNode != NULL;

			if (rhs.thisNode == NULL)
				return thisNode != NULL;
			
			return thisNode->storedItem != rhs.thisNode->storedItem;
		}

		bool operator==(Iterator rhs)
		{
			if (thisNode == NULL)
				return rhs.thisNode == NULL;

			if (rhs.thisNode == NULL)
				return thisNode == NULL;

			return thisNode->storedItem == rhs.thisNode->storedItem;
		}

		T operator*()
		{
			return thisNode->storedItem;
		}

		T operator->()
		{
			return thisNode->storedItem;
		}
		
		void operator++()
		{
			thisNode = thisNode->next;
		}

		void operator--()
		{
			thisNode = thisNode->previous;
		}




	private:

		Node<T>* thisNode;

	};



	//Constructor
	LinkedList()
	: head(0), m_size(0)
	{
	};

	//Desctructor.
	~LinkedList()
	{
		Node<T>* n = head;
		while(n)
		{
			Node<T>* next = n->next;
			delete n;
			n = next;
		}

	}

	//returns the size of the array
	int size()
	{
		return m_size;
	}

	//adds a reference of the item to the array
	bool add(T item)
	{
		//go to the end of the list
		Node<T>* iter = head;

		if(!head)
		{
			head = new Node<T>(item,0,0);
			++m_size;
			return true;
		}

		while(iter->next)
		{
			iter = iter->next;
		}

		iter->next = new Node<T>(item, iter, 0);
		++m_size;
		return true;

	}

	//removes a reference to an item from the array
	bool remove(T item)
	{
		Node<T>* iter = head;

		//while there is a next item, and the current item isn't what we're looking for
		while(iter->next && iter->storedItem != item)
		{
			iter = iter->next;
		}

		if(iter->storedItem == item)
		{
			Node<T>* toRemove = iter;
			if(iter == head)
			{
				//replace the head node
				head = toRemove->next;
				head->previous = 0;
			}
			else
			{
				toRemove->previous->next = toRemove->next;
				if(toRemove->next)
				{
					toRemove->next->previous = toRemove->previous;
				}
			}
			delete toRemove;
			--m_size;
			return true;
		}

		return false;
		
	}

	Iterator begin()
	{
		return Iterator(head);
	}

	Iterator end()
	{
		Node<T>* iter = head;
		while (iter->next)
			iter = iter->next;

		return Iterator(iter->next);
	}

	Iterator last()
	{
		Node<T>* iter = head;
		while (iter->next)
			iter = iter->next;

		return Iterator(iter);
	}


	//accesses an element within the array
	T operator[](int index)
	{
		Node<T>* iter = head;
		Node<T>* prev = head;

		int count = 0;
		while(count != index)
		{
			prev = iter;
			iter = iter->next;
			++count;
			if(!iter)
			{
				//if searching for last element
				if(index == -1)
				{
					return prev->storedItem;
				}
				//element not found
				return 0;
			}

		}
		return iter->storedItem;
	}





private:

	Node<T>* head;
	int m_size;

};

#endif