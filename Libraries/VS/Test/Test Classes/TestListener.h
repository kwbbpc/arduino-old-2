#ifndef  TESTLISTENER
#define TESTLISTENER

#include "Messaging/Temperature/ITemperatureListener.h"
#include <vector>

namespace testclasses {

class TestListener : public messaging::temperature::ITemperatureListener
{

public:
	TestListener();

	virtual void onTemperature(Temperature message);

	std::vector<Temperature> receivedTemperatureMessages;


};


}
#endif // ! TESTLISTENER

