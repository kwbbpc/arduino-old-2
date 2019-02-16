#ifndef NANOPBENCODERFACTORY_H
#define NANOPBENCODERFACTORY_H

#include "IEncoderFactory.h"
#include "ISensorEncoder.h"
#include <stdint.h>



namespace encoders { namespace nanopb {

	//New data function callback for nanopb encoding
	typedef void (*NewDataFn)(uint8_t*, size_t);


	class NanoPbEncoderFactory : public IEncoderFactory
	{

	public:
		
		//Construction and destruction
		NanoPbEncoderFactory(const char* boardGuid, NewDataFn dataCallback);
		~NanoPbEncoderFactory();

		//Creates a temperature encoder and returns the interface
		virtual ISensorEncoder* makeTemperatureEncoder();

	private:
		NewDataFn m_dataCallbackFn;
		ISensorEncoder* m_encoders[16];
		int m_encoderIndex;

	};

}}

#endif