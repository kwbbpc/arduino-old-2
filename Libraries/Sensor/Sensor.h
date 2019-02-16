 
#ifndef SENSOR_H
#define SENSOR_H

struct Sensor
{
  public: 
  virtual char* GetStatusMessage() = 0;
    
};

#endif