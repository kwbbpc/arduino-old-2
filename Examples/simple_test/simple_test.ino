

#include <pb_encode.h>
#include <pb_decode.h>

#include <examples\simple\simple.pb.h>

//MUST include the .c file, this has the definition of the _fields variable.
#include <examples\simple\simple.pb.c>

void setup(void)
{

  //initialize the serial port (USB)
  Serial.begin(115200);


}


uint8_t buffer[128];
size_t message_length;
bool status;

void loop(void)
{


  
    //make a simple message
    SimpleMessage message = SimpleMessage_init_zero;

    //create the stream
    pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

    //populate
    message.lucky_number = 444;


    //encode
    status = pb_encode(&stream, SimpleMessage_fields, &message);
    message_length = stream.bytes_written;

    //send it if it was successful
    if(!status)
      Serial.println("Failed to encode message");
    else

      Serial.write(buffer, message_length);
      Serial.println();


    delay(2000);


}



