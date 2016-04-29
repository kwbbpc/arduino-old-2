
#include "MessageBuilder.h"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

namespace util{

		MessageBuilder::MessageBuilder(int messageSize)
		{
			internalMessage = new uint8_t[messageSize];

			for(int i = 0; i< messageSize; ++i)
			{
				internalMessage[i] = 0;
			}

			internalIndex = 0;
		}

		MessageBuilder::MessageBuilder()
		{
			internalMessage = 0;
			internalIndex = 0;
		}

		void MessageBuilder::init(int messageSize)
		{
			delete[] internalMessage;
			internalMessage = new uint8_t[messageSize];
			for(int i = 0; i< messageSize; ++i)
			{
				internalMessage[i] = 0;
			}
			internalIndex = 0;

		}

		MessageBuilder::~MessageBuilder()
		{
			delete[] internalMessage;
		}

		bool MessageBuilder::deepCopy(uint8_t** destination)
		{
			*destination = new uint8_t[internalIndex];

			for(int i=0; i<internalIndex; ++i)
			{
				(*destination)[i] = internalMessage[i];
			}

			return true;
		}

		uint8_t* MessageBuilder::get()
		{
			return internalMessage;
		}

		int MessageBuilder::sizeOf()
		{
			return internalIndex;
		}

		void MessageBuilder::append(const uint8_t* origin, int indexBegin, int indexEnd)
		{
			for(int i = indexBegin; i < indexEnd; ++i, ++internalIndex)
			{
				internalMessage[internalIndex] = origin[i];
			}
		}

}