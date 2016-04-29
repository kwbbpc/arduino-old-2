
#include <ISensor.h>
#include <TestSensor.h>
#include <TimerBucket.h>
#include <MsTimer2.h>
#include <pb.h>

util::TimerBucket* taskQueue;
void setup()
{
	Serial.begin(115200);

	taskQueue = util::TimerBucket::getInstance();
	taskQueue->add(1000, new sensor::test::TestSensor(1), false);
	taskQueue->add(1000, new sensor::test::TestSensor(2), false);
	taskQueue->add(3000, new sensor::test::TestSensor(3), false);
	taskQueue->add(3000, new sensor::test::TestSensor(4), false);
	taskQueue->add(5000, new sensor::test::TestSensor(5), false);

	//one periodic, to make sure it didn't crash.
	taskQueue->add(7000, new sensor::test::TestSensor(6), true);

	taskQueue->start();
	
	Serial.println("Initialized.");

}

int count = 0;
void loop()
{
	++count;
	if(count > 20000)
	{
		Serial.println("Ping");
		count = 0;
	}

	while(taskQueue->isDataAvailable())
	{

		sensor::ISensor* sensorWithNewData = taskQueue->getAvailableData();
		if(sensorWithNewData)
		{
			Serial.print("New data from sensor:");
			Serial.println((int)sensorWithNewData);
			sensorWithNewData->sendUpdate();
		}
		else
		{
			Serial.println("Retrieved a bad sensor!");
		}

		if(!taskQueue->isDataAvailable())
		{
			Serial.println("End of retrival");
			Serial.println();Serial.println();
		}
	}
	
}
