
#include "TestListener.h"

namespace testclasses {


	TestListener::TestListener()
	{

	}

	void TestListener::onTemperature(Temperature message)
	{
		receivedTemperatureMessages.push_back(message);
	}

}