
#ifndef IENCODER
#define IENCODER


namespace messaging {

	class IEncoder
	{

	public:

		template<class MSGTYPE>
		virtual bool decodeMessage(const uint8_t* buffer, uint16_t length, const pb_field_t fields[], MSGTYPE& decodedMessage) = 0;

		template<class MSGTYPE>
		virtual int encodeMessage(const MSGTYPE* message, uint8_t** encodedMessage) = 0;

	};

}


#endif // !IENCODER
