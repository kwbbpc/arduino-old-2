

#include "NanoPbEncoderFactory.h"
#include "TemperatureEncoder.h"

namespace encoders{ namespace nanopb{


	NanoPbEncoderFactory::NanoPbEncoderFactory(NewDataFn dataCallback):
	m_dataCallbackFn(dataCallback),
	m_encoderIndex(0)
	{}

	NanoPbEncoderFactory::~NanoPbEncoderFactory()
	{
		--m_encoderIndex;

		while(m_encoderIndex >= 0)
		{
			delete m_encoders[m_encoderIndex];
			--m_encoderIndex;
		}
	}

	NanoPbCodec* NanoPbEncoderFactory::makeEncoder()
	{
		NanoPb
		ISensorEncoder* encoder = new TemperatureEncoder(m_dataCallbackFn);
		//add the encoder to the array
		m_encoders[m_encoderIndex] = encoder;
		//increment the index
		++m_encoderIndex;

		return encoder;

	}

}}