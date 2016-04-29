

//REQUIRED LIBRARY
#include <EEPROM.h>
//////////////////

#include <SensorType.h>
#include <MessageId.h>
#include <Sensor.h>
#include <Control.h>
#include <MsTimer2.h>
#include <Parser.h>


#include <Wire.h>
#include <Servo.h>

#include <string.h>


/*******************************************************************PIN DEFINITIONS*****************************************************************************/
const int webcamServoPin = 5;
const int lightPin = 8;



struct WebcamServo : public Sensor, public Control
{
private:
  
  Servo servo;
  int degreesRotation;
  char* webcamSensorType;
  SensorType::Enum type;

public:  
  WebcamServo()
  {
    type = SensorType::Webcam;
    webcamSensorType = "49";
  }
  
  SensorType::Enum GetType() const
  {
    return type;
  }
  
  void attach(int pin)
  {
    servo.attach(pin);
  }

  
  char* GetStatusMessage()
  {
    char* header = MessageId::GetHasMessageHeader(MessageId::Status);
    char message [500];
    int degreesRotation = servo.read();
    sprintf(message, "%s,%d,%d", header, webcamSensorType, degreesRotation);
    
    return message;
  }
  
  void ExecuteAction(char* action)
  {    
    
    Serial.println("Executing action.");
    
    int degreeSet = atoi(action);
    
    //input safetey checks
    if(degreeSet > 155)
      degreeSet = 155;

    if(degreeSet < 10)
      degreeSet = 10;

    int current = servo.read();
    
    Serial.print("Current servo value is [");
    Serial.print(current);
    Serial.println("].");

    Serial.print("Writing [");
    Serial.print(degreeSet);
    Serial.println("] to the servo.");
      
    //write the PWM signal to the servo  
    servo.write(degreeSet);
    
    //delay for 20ms, because the servo can't be 
    //refreshed any faster than 20ms at a time.
    delay(20);
  } 
  


};



struct LightSwitch : public Sensor, public Control
{
private:
  
  int state;
  char* lightSwitchSensorType;
  int pinNumber;
  SensorType::Enum type;

public:  
  LightSwitch(int pin)
  {
    type = SensorType::LightSwitch;
    pinNumber = pin;
    state = 0;
    lightSwitchSensorType = "32";
  }
  
  SensorType::Enum GetType() const
  {
    return type;
  }

  
  char* GetStatusMessage()
  {
    state = digitalRead(pinNumber);
    if(state > 0)
      state = 1;
      
    char* header = MessageId::GetHasMessageHeader(MessageId::Status);
    char message [500];
    sprintf(message, "%s,%d,%d", header, lightSwitchSensorType, state);
    
    return message;
  }
  
  void ExecuteAction(char* action)
  {    
    
    Serial.println("Executing action.");
    
    int state = atoi(action);
    
    //input safetey checks
    if(state != 1)
      state = 0;
      
    int current = digitalRead(pinNumber);
    
    Serial.print("Current pin value is [");
    Serial.print(current);
    Serial.println("].");

    Serial.print("Writing [");
    Serial.print(state);
    Serial.println("] to the switch.");
      
    //write the state to the pin.
    if(state == 1)
      digitalWrite(pinNumber, HIGH);
    else
      digitalWrite(pinNumber, LOW);

    delay(20);
  } 

};


WebcamServo webcamServo;
LightSwitch lightSwitch(lightPin);
Parser parser;

void printStatusMessages()
{  
  cli();
  Serial.println(webcamServo.GetStatusMessage());
  sei();
  delay(1000);
  cli();
  Serial.println(lightSwitch.GetStatusMessage());
  sei();
}



void setup()
{

  webcamServo.attach(webcamServoPin);
  
  MsTimer2::stop();
  MsTimer2::set(10000,printStatusMessages);
  MsTimer2::start();
  
  /* I2C - Shit be broke.
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);   // set the LED on  
  
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(ReceiveEvent); // register event
  Wire.onRequest(RequestEvent); // register event
  
  */
  
  
  
  Serial.begin(9600);           // start serial for output
}

int doOnce = 1;

void loop()
{
  
  if(doOnce)
  {
    webcamServo.ExecuteAction("20");
      
    parser.RegisterControl(webcamServo);
    parser.RegisterControl(lightSwitch);
    doOnce = 0;
  }
  

  
}






void serialEvent()
{
  
  char message[500];
  int index = 0;
  
  while( Serial.available() > 0 )
  {
    char incomingByte = Serial.read();
    message[index] = incomingByte;
    ++ index;
    message[index] = '\0';
    
    //MUST delay here to give enough time for the next char to arrive over serial
    delay(10);
  }
  
  if(message[0] != '\0')
  {
    Serial.print("Message received: ");
    Serial.println(message);
    
    //MUST delay here to let the println finish before disabling interrupts.
    delay(1000);
    
    
    //hand off to the parser
    parser.ParseMessage(message);
    
    //clear teh message
    message[0] = '\0';
    index = 0;
  }
}

