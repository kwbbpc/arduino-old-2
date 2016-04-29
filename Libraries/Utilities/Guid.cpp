
#include "Guid.h"
#include <stdlib.h>

namespace util{ namespace guid{

	int Hash(const char* guid)
	{
		int hash = 0;
		//add the chars of the guid
		for(int i = 0; guid[i] != '\0'; ++i)
		{
			hash += guid[i];
		}


		hash = (hash) % (HashedSensorTableSize - 1);
		return hash;


	}

}}