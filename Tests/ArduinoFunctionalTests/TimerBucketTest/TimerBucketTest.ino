
#include <MsTimer2.h>
#include <ISensor.h>
#include <TimerBucket.h>
#include <SensorType.h>
#include "TestSensor.h"
#include <pb.h>


util::TimerBucket* bucket = util::TimerBucket::getInstance();

void setup()
{
	
	Serial.begin(115200);

	Serial.print("bucket instance is "); Serial.println((int)bucket);
	Serial.println("Grabbing a new instance... ");
	
	bucket = util::TimerBucket::getInstance();
	Serial.print("bucket instance is "); Serial.println((int)bucket);

	bucket->add(500, new sensor::test::TestSensor(1), true);
	bucket->add(500, new sensor::test::TestSensor(2), true);
	bucket->add(500, new sensor::test::TestSensor(3), true);
	
	bucket->add(1000, new sensor::test::TestSensor(4), true);
	bucket->add(1000, new sensor::test::TestSensor(5), true);

	bucket->add(2000, new sensor::test::TestSensor(6), true);
	bucket->add(2000, new sensor::test::TestSensor(7), true);

	bucket->add(4000, new sensor::test::TestSensor(8), true);
	bucket->add(4000, new sensor::test::TestSensor(9), true);
	
	Serial.println("Timers initialized, starting.");
	bucket->start();

}

int i = 0;

void loop()
{
	while(bucket->isDataAvailable())
	{

		//Serial.print("Messagebuffer count: "); Serial.println(bucket->m_messageBuffer->count);
		//Serial.print("MessageBuffer getindex: "); Serial.println(bucket->m_messageBuffer->m_getIndex);
		//Serial.print("MessageBuffer putindex: "); Serial.println(bucket->m_messageBuffer->m_putIndex);

		sensor::ISensor* sensorWithNewData = bucket->getAvailableData();
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

		if(!bucket->isDataAvailable())
		{
			Serial.println("End of retrival");
			Serial.println();Serial.println();
		}
	}
	
	
}
