#include <MsTimer2.h>
#include <Wire.h>
#include <Servo.h>

#include <string.h>




int debug = 1;

/*******************************************************************PIN DEFINITIONS*****************************************************************************/
const int webcamServoPin = 5;







/*******************************************************************DEVICE DEFINITIONS*****************************************************************************/
const char* ardyId = "ardy";


struct SensorType
{
  
  enum Enum
  {
    Temperature = 0x00,
    Thermostat = 0x01,
    LightSensor = 0x10,
    LightSwitch = 0x20,
    Blinds = 0x30,
    Webcam = 0x31,
    CarbonMonoxide = 0x40,
    Humidity = 0x50,
    
    
    Invalid = 0xFF
  };
  
    static char* translator(Enum type)
    {
      char retVal[10];
      sprintf(retVal,"%d",type);
      return retVal;
    }
          
    static const Enum& translator(char* type)
    {
      
      if(strcmp(type,translator(Temperature)) == 0)
        return Temperature;
      if(strcmp(type,translator(Thermostat)) == 0)
        return Thermostat;
      if(strcmp(type,translator(LightSensor)) == 0)
        return LightSensor;
      if(strcmp(type,translator(LightSwitch)) == 0)
        return LightSwitch;
      if(strcmp(type,translator(Blinds)) == 0)
        return Blinds;
      if(strcmp(type,translator(Webcam)) == 0)
        return Webcam;
      if(strcmp(type,translator(CarbonMonoxide)) == 0)
        return CarbonMonoxide;
      if(strcmp(type,translator(Humidity)) == 0)
        return Humidity;
        
      return Invalid;
    } 
  
};  
    


struct MessageId
{
    enum Enum
    {
      StatusMessageQuery = 0x02,
      StatusMessage = 0x03,
      ActionMessage = 0x04
    };
    
    static char* translator(Enum id)
    {
      char retVal[10];
      sprintf(retVal, "%d", id);
      
    }    
};
      





struct Sensor
{
  public:
  virtual void PrintStatusMessage() = 0;
  
  protected:
 
  void PrintHasStatusMessageHeader
  ()
  {
    Serial.print("HASMESSAGE,");
    Serial.print(MessageId::StatusMessage);
    Serial.print(",");
    Serial.print(ardyId);
    Serial.print(",");
  }
  
};



struct Control
{
  
  SensorType::Enum type;
  
 public:
  virtual void ExecuteAction(char* action) = 0;
  
  Control(SensorType::Enum t)
  {
    type = t;
  }
  
  SensorType::Enum GetType() const { return type; };
 
};



//TODO implement add
struct Parser
{
  
  private:
  

  
      struct ControlNode
      {
            ControlNode *next;
            ControlNode *prev;
            Control *control_;
            
      };
  
  struct ControlList
  {        
    
    public:
    
    
    ControlNode *nodes;
    int count;
    
    ControlList()
    {
      count = 0;
      nodes = (ControlNode*)malloc(sizeof(ControlNode));
      nodes->control_ = NULL;
      nodes->next = NULL;
      nodes->prev = NULL;
    }
    
    int getSize()
    {
      return count;
    }
    
    ControlNode * _begin()
    {
      while(nodes->prev != NULL)
          nodes = nodes->prev;    
          
      return nodes;
    }
    
    ControlNode * _end()
    {
      while(nodes->next != NULL)
          nodes = nodes->next;
          
      return nodes;
    }
    
    
    
    void add(Control& control)
    {
      
      
        while(nodes->next != NULL)
            nodes = nodes->next;
          
        nodes->next = new ControlNode;//(ControlNode *)malloc(sizeof(ControlNode));  //create the new node
        nodes->next->control_ = &control;  //set the node
        nodes->next->next = NULL;  //set the end
        nodes->next->prev = nodes;
     
    }
    
  };
      
      
  ControlList controls;
  
  
  
  public:
  
  //TODO implement add
  void RegisterControl(Control& control)
  {
    controls.add(control);    
  }
  
  Control* FindControl(SensorType::Enum type)
  {
    //start at the beginning of the control list
    ControlNode* control = controls._begin();
    
    while(control != NULL)
    {
      //check the type
       SensorType::Enum controlType = control->control_->GetType();
       
       //if the type matches
       if(controlType == type)
         return control->control_;  //return just the control
       else
         control = control->next;  //get the next control
    }

  }
  
  
  
  void ParseMessage(char* message)
  {   

     //tokenize the string.
     char* signature = strtok_r(message,",",&message);
     
     if(signature == NULL)
     {
       return;
       
     }       
     
     if(strcmp(signature,"HASMESSAGE") != 0)
     {
       //drop the message
       return;
     }
     
     //grab the message id
     char * messageId = strtok_r(message,",",&message);
     if(messageId == NULL)
     {
       return;       
     } 

     //grab the board id
     char * boardId = strtok_r(message,",",&message);
     if(boardId == NULL)
     {
       return;
     }
     
        
       
     if(strcmp(boardId,ardyId))
     {
       return;
     }
     
     //grab the control type
     char * type = strtok_r(message,",",&message);
     
     //grab the control type
     char * action = strtok_r(message,",",&message);

     
     //TODO - lookup the control in the controls list and execute action.
     SensorType::Enum typeEnum = SensorType::translator(type);
     Control* control = FindControl(typeEnum);
     
     if(control != NULL)
     {
     
     //executing action
     control->ExecuteAction(action);
     
     
     }
     
     //update the status
     delay(100);
     printStatusMessages();
  

  }

};





struct WebcamServo : public Sensor, public Control
{
private:
  
  Servo servo;
  int degreesRotation;
  char* webcamSensorType;

public:  
  WebcamServo() : Control(SensorType::Webcam)
  {
    webcamSensorType = "49";
  }
  
  void attach(int pin)
  {
    servo.attach(pin);
  }

  
  void PrintStatusMessage()
  {
    PrintHasStatusMessageHeader();
    Serial.print(webcamSensorType);
    Serial.print(",");
    degreesRotation = servo.read();
    Serial.println(degreesRotation);
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
  
  void ExecuteAction(int action)
  {    
    
    Serial.println("Executing action.");
    
    //input safetey checks
    if(action > 155)
      action = 155;

    if(action < 10)
      action = 10;

    int current = servo.read();
    
    Serial.print("Current servo value is [");
    Serial.print(current);
    Serial.println("].");

    Serial.print("Writing [");
    Serial.print(action);
    Serial.println("] to the servo.");
      
    //write the PWM signal to the servo  
    servo.write(action);
    
    //delay for 20ms, because the servo can't be 
    //refreshed any faster than 20ms at a time.
    delay(20);
  } 

};


WebcamServo webcamServo;
Parser parser;

void printStatusMessages()
{  
  cli();
  webcamServo.PrintStatusMessage();
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
    webcamServo.ExecuteAction(20);
      
    parser.RegisterControl(webcamServo);
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

