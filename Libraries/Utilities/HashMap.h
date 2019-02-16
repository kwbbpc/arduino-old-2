#ifndef HASHMAP
#define HASHMAP




#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include "LinkedList.h"



template <class Type>
class HashMap
{

public:


	HashMap()
	{
		initialize(5);
	}


	HashMap(int size)
	{
		initialize(size);	
	}

	bool containsKey(Type key)
	{

	}


private:

	void initialize(int arraySize)
	{

	}

	LinkedList<Type> linkedList;

	

};


#endif
