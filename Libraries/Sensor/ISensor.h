#ifndef ISENSOR_H
#define ISENSOR_H





namespace sensor{


	struct SensorType
	{
		enum Enum
		{
			Temperature,

			Max,
			Invalid = -1
		};
	};

	
	class ISensor
	{
	  public: 

		  //performs initialization of the sensor
		  virtual bool initialize() = 0;
		  		  
		  //get the sensors unique id
		  virtual const char* getUniqueId() const = 0;
		  
		  //gets the sensor type
		  virtual SensorType::Enum getType() const = 0;

		  //gets the hardware name of the device
		  virtual const char* getDeviceName() const = 0;
	};

}

#endif