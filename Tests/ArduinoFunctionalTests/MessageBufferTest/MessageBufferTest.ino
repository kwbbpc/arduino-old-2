#include <MessageBuffer.h>
#include <ISensor.h>
#include "TestSensor.h"
#include <pb.h>



	util::MessageBuffer<sensor::ISensor> Buffer(10);

	sensor::test::TestSensor* pS1 = new sensor::test::TestSensor(1);
	sensor::test::TestSensor* pS2 = new sensor::test::TestSensor(2);
	sensor::test::TestSensor* pS3 = new sensor::test::TestSensor(3);
	sensor::test::TestSensor* pS4 = new sensor::test::TestSensor(4);

void setup()
{
	Serial.begin(115200);
	
	//Test adding a bunch of sensors to the buffer
	Serial.println("Adding sensors");
	Buffer.add(pS1);
	Buffer.add(pS2);
	Buffer.add(pS3);
	Buffer.add(pS4);
	Serial.println("Initialization done.");
}



int sensorId = 0;
void loop()
{



	//Get them out
	if(Buffer.hasData())
	{
		sensor::ISensor* next = Buffer.getNext();
		Serial.print("Got sensor "); Serial.println(((sensor::test::TestSensor*)(next))->m_id);
		//delete next;
		if(!Buffer.hasData())
		{
			Serial.println("No more data.");
		}

	}

	//add another
	//Buffer.add(pS1);
	//Buffer.add(pS2);
	//Buffer.add(pS3);
	//Buffer.add(pS4);

}