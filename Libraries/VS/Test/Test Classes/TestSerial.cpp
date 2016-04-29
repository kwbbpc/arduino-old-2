
#include "TestSerial.h"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

namespace serial{ namespace test{


	void TestSerial::write(const uint8_t* buffer, uint16_t bufferSize)
	{
		writtenMessages.push_back(Message(buffer,bufferSize));
	}

	int TestSerial::read(uint8_t* buffer, uint16_t bufferSize)
	{
		readMessages.push_back(Message(buffer,bufferSize));
		return bufferSize;
	}


}}