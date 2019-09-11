#include <SPI.h>
extern "C"{
  #include "src/mcp2515_can.h"
};

const int SPI_CS_PIN = 10;
unsigned char sentMessagePayload [8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
int sentPayloadLength = sizeof(sentMessagePayload);
int receivedPayloadLength = 0;
bool transmitting = false;

void setup()
{
    Serial.begin(115200);

    pinMode(SPI_CS_PIN, OUTPUT);

    Serial.println();
    Serial.println("-----------------------------");
    Serial.println("Initializating CAN BUS Shield...");
      
    while (CAN_OK != mcp2515_init(CAN_500KBPS, MCP_16MHz))          
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println(" Init CAN BUS Shield again");
        delay(100);
    }
    
    Serial.println("CAN BUS Shield init ok!");
    Serial.println("-----------------------------");
    Serial.println();
    
    set_CAN_node_id(1);
    set_sent_message_payload(sentMessagePayload, sentPayloadLength);

    delay(5000);
}


void loop()
{   

    if(transmitting){
        send_CAN_data_frame();
    }

    if(CAN_MSGAVAIL == mcp2515_readStatus())            
    { 
        Serial.println("-----------------------------");
        Serial.println("CAN frame received with the following info:");
        
        mcp2515_read_canMsg();
        
        Serial.print("- ID: ");
        Serial.println(get_received_message_id(), DEC);
        
        Serial.print("- Frame type: ");
        if( ((int)is_data_frame()) == 0){
           Serial.println("Standard Data Frame");
        }else{
           Serial.println("Standard Remote Frame");
        }

        receivedPayloadLength = get_received_message_payloadLength();
        Serial.print("- Payload length: ");
        Serial.println(receivedPayloadLength);
  
        Serial.print("- Payload content: ");
        for(int i = 0; i < receivedPayloadLength; i++)    
        {
            Serial.print(get_received_message_payload(i), HEX);
            Serial.print("\t");
        }

        if( ((int)is_data_frame()) != 0){
            if(get_received_message_id() == get_CAN_node_id()){
                 Serial.println();
                 Serial.println("-----------------------------");
                 Serial.println("The identifier of the remote frame received is the same as this node's identifier"); 
                 Serial.println("Let's proceed sending CAN Data frames to the bus"); 
                 Serial.println("-----------------------------");
                 transmitting = true;
            }else{
                 Serial.println();
                 Serial.println("-----------------------------");
                 Serial.println("The identifier of the remote frame received is different from this node's identifier"); 
                 Serial.println("No action needed"); 
                 Serial.println("-----------------------------");
            }
        }
 
        Serial.println();
        Serial.println();
    }else{
      
      send_CAN_remote_frame(2047);
      
    }
    
    delay(500);
}
