#ifndef ISENSORENCODER_H
#define ISENSORENCODER_H

#include <ISensor.h>

#include <pb.h>
#include <pb_encode.h>
#include <pb_decode.h>


#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

namespace messaging{ namespace nanopb{
	
	const uint32_t Version = 1;

	//Does a C string copy
	inline bool copyString(const char* source, char* destination)
	{
		int sourceSize = strlen(source);
		int destSize = strlen(destination);
		if (destSize < sourceSize)
			return false;

		//Grab one extra char for the null terminator
		for (int i = 0; i < sourceSize + 1; ++i)
		{
			destination[i] = source[i];
		}

		return true;
	}


	//! Decodes a message payload
	//! buffer - the buffer the entire message (includes header and headersize)
	//! length - the message length in the buffer
	//! fieldsType[out] - a reference to the fields type corresponding to the payload message
	//! decodededMessage[out] - a reference to the container to store the decoded payload message in
	//!
	//! returns bool - successfully decoded
	template<class MSGTYPE>
	bool decodeMessage(uint8_t* buffer, const uint16_t length, const pb_field_t fields[], MSGTYPE& decodedMessage)
	{

		//make a stream to read from the buffer
		pb_istream_t istream = pb_istream_from_buffer(buffer, length);

		//pull out the header and check if this is the destination board
		bool success = pb_decode(&istream, fields, &decodedMessage);

		return success;
	};

	//! Encodes a message payload.  returns the number of bytes that were written to the buffer.  If 
	//! encoding failed, then 0 bytes are returned as written.  Make sure the buffer passed in is cleaned up!
	//! message - the message to be encoded
	//! encodedMessage (out) - the serialized message
	template<class MSGTYPE>
	int encodeMessage(const MSGTYPE* message, const pb_field_t fields[], uint8_t** encodedMessage)
	{


		//encode the message
		static const int BufferMaxSize = 512;
		*encodedMessage = new uint8_t[BufferMaxSize];

		//create the stream that will write to the buffer
		pb_ostream_t stream = pb_ostream_from_buffer(*encodedMessage, BufferMaxSize);


		//encode the message
		if (!pb_encode(&stream, fields, message))
			return 0;	//encoding failed, no bytes written
		else
			return stream.bytes_written;




	};
		
}}

#endif