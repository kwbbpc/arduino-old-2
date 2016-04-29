

#include "NanoPbCodec.h"

#include "Header.pb.h"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif


namespace encoders{ namespace nanopb{

	uint16_t GetHeaderSize(const uint8_t* buffer)
	{
		//first two bytes are the header size
		uint8_t headerSize[2];
		headerSize[0] = buffer[0];
		headerSize[1] = buffer[1];
		uint16_t* sizeOfHeader = reinterpret_cast<uint16_t*>(headerSize);
		return *sizeOfHeader;

	}

	bool decodeHeader(const uint8_t* buffer, uint16_t bytesRead, HeaderMessage& header)
	{
		if(bytesRead < 2)
		{
			return false;
		}

		int bufferIndex = 0;
		
		//get the header length
		HeaderSizeField headerSize = GetHeaderSize(buffer);

		bufferIndex += SizeOfHeaderSizeField;

		//get the header
		util::MessageBuilder headerBuffer(headerSize);
		//the header is contained after the header size, up to the number of bytes indicated by the size
		headerBuffer.append(buffer,bufferIndex,bufferIndex+headerSize);
				

		//make a stream to read from the buffer
		pb_istream_t istream = pb_istream_from_buffer(headerBuffer.get(), headerBuffer.sizeOf());

		//pull out the header and check if this is the destination board
		bool success = pb_decode(&istream, HeaderMessage_fields, &header);
				
		return success;

	}
	
}}