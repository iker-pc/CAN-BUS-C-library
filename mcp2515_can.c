#include <Arduino.h>
#include "stdint.h" 
#include "stdio.h"
#include "inttypes.h"
#include "string.h"

#include "spi.h"
#include "mcp2515_can.h"

/* The default value for the sender identifier is the highest allowed. 
As the identifier of a standard frame has 11 bits, the maximum value, 
in decimal format, is the 2047*/ 
struct tCANconfig sentCANFrame = { .id = 2047 };

struct tCANconfig receivedCANFrame;



/*****************************************************
*       MCP2515 Registers Manipulation functions     *
*                                                    *
******************************************************/

/*********************************************************************************************************
** Function name:           - mcp2515_readRegister
** Description:             - This function is used to read the value of the MCP2515 registers. 
** Input arguments:         - A byte variable with the register's memory address that wants to be read.
** Output values:           - The value read from the MCP2515 register
*********************************************************************************************************/
byte mcp2515_readRegister(const byte address){
	beginTransaction();
	byte ret;
	spi_send(MCP_READ);
	spi_send(address);
	ret = spi_send(0x00);
	endTransaction();
	return ret;
}


/*********************************************************************************************************
** Function name:           - mcp2515_setRegister
** Description:             - This function is used to overwrite the values of the MCP2515 registers.
** Input arguments:         - A byte variable with the register's memory address that wants to be overwritten
**                          and the new value that wants to be written.
** Output values:           
*********************************************************************************************************/
void mcp2515_setRegister(const byte address, const byte value){
	beginTransaction();
	spi_send(MCP_WRITE);
  spi_send(address);
  spi_send(value);
  endTransaction();
}


/*********************************************************************************************************
** Function name:           - mcp2515_modifyRegister
** Description:             - This function is used to modify single bits of the controller's registers. 
**                          Unlike the previous function which overwrittes the whole value of a register,
**                          this function can modify single bits of the given register.
**                          and the new value that wants to be written.
** Input arguments          - The register's memory address to be modified, a mask that indicates which 
**                          register's bits will be modified, and the new bits values to be written
**                          in that register. 
**                
** Output values:           
*********************************************************************************************************/
void mcp2515_modifyRegister(const byte address, const byte mask, const byte data){
	beginTransaction();	
	spi_send(MCP_BITMOD);
  spi_send(address);
  spi_send(mask);
  spi_send(data);
  endTransaction();
}

/*****************************************************
******************************************************/




/*****************************************************
*             Configuration functions                *
*                                                    *
******************************************************/

/*********************************************************************************************************
** Function name:           - mcp2515_setRate
** Description:             - This function is used to define the bitrate that wants to be used during the
**                          CAN frames exchanging process (see mcp2515_can_defs.h). 
** Input arguments:         - Two byte variables which indicates the rate to be used and the microcontroller's
**                          frequency.
** Output values:         
*********************************************************************************************************/
void mcp2515_setRate(byte canSpeed, byte clock){

  byte cfg1, cfg2, cfg3;

  switch (clock) {

    case (MCP_16MHz) :
      switch (canSpeed){

        case (CAN_5KBPS):
          cfg1 = MCP_16MHz_5kBPS_CFG1;
          cfg2 = MCP_16MHz_5kBPS_CFG2;
          cfg3 = MCP_16MHz_5kBPS_CFG3;
          break;

        case (CAN_10KBPS):
          cfg1 = MCP_16MHz_10kBPS_CFG1;
          cfg2 = MCP_16MHz_10kBPS_CFG2;
          cfg3 = MCP_16MHz_10kBPS_CFG3;
          break;

        case (CAN_20KBPS):
          cfg1 = MCP_16MHz_20kBPS_CFG1;
          cfg2 = MCP_16MHz_20kBPS_CFG2;
          cfg3 = MCP_16MHz_20kBPS_CFG3;
          break;

        case (CAN_25KBPS):
          cfg1 = MCP_16MHz_25kBPS_CFG1;
          cfg2 = MCP_16MHz_25kBPS_CFG2;
          cfg3 = MCP_16MHz_25kBPS_CFG3;
          break;

        case (CAN_31K25BPS):
          cfg1 = MCP_16MHz_31k25BPS_CFG1;
          cfg2 = MCP_16MHz_31k25BPS_CFG2;
          cfg3 = MCP_16MHz_31k25BPS_CFG3;
          break;

        case (CAN_33KBPS):
          cfg1 = MCP_16MHz_33kBPS_CFG1;
          cfg2 = MCP_16MHz_33kBPS_CFG2;
          cfg3 = MCP_16MHz_33kBPS_CFG3;
          break;

        case (CAN_40KBPS):
          cfg1 = MCP_16MHz_40kBPS_CFG1;
          cfg2 = MCP_16MHz_40kBPS_CFG2;
          cfg3 = MCP_16MHz_40kBPS_CFG3;
          break;

        case (CAN_50KBPS):
          cfg1 = MCP_16MHz_50kBPS_CFG1;
          cfg2 = MCP_16MHz_50kBPS_CFG2;
          cfg3 = MCP_16MHz_50kBPS_CFG3;
          break;

        case (CAN_80KBPS):
          cfg1 = MCP_16MHz_80kBPS_CFG1;
          cfg2 = MCP_16MHz_80kBPS_CFG2;
          cfg3 = MCP_16MHz_80kBPS_CFG3;
          break;

        case (CAN_83K3BPS):
          cfg1 = MCP_16MHz_83k3BPS_CFG1;
          cfg2 = MCP_16MHz_83k3BPS_CFG2;
          cfg3 = MCP_16MHz_83k3BPS_CFG3;
          break;

        case (CAN_95KBPS):
          cfg1 = MCP_16MHz_95kBPS_CFG1;
          cfg2 = MCP_16MHz_95kBPS_CFG2;
          cfg3 = MCP_16MHz_95kBPS_CFG3;
          break;

        case (CAN_100KBPS):
          cfg1 = MCP_16MHz_100kBPS_CFG1;
          cfg2 = MCP_16MHz_100kBPS_CFG2;
          cfg3 = MCP_16MHz_100kBPS_CFG3;
          break;

        case (CAN_125KBPS):
          cfg1 = MCP_16MHz_125kBPS_CFG1;
          cfg2 = MCP_16MHz_125kBPS_CFG2;
          cfg3 = MCP_16MHz_125kBPS_CFG3;
          break;

        case (CAN_200KBPS):
          cfg1 = MCP_16MHz_200kBPS_CFG1;
          cfg2 = MCP_16MHz_200kBPS_CFG2;
          cfg3 = MCP_16MHz_200kBPS_CFG3;
          break;

        case (CAN_250KBPS):
          cfg1 = MCP_16MHz_250kBPS_CFG1;
          cfg2 = MCP_16MHz_250kBPS_CFG2;
          cfg3 = MCP_16MHz_250kBPS_CFG3;
          break;

        case (CAN_500KBPS):
          cfg1 = MCP_16MHz_500kBPS_CFG1;
          cfg2 = MCP_16MHz_500kBPS_CFG2;
          cfg3 = MCP_16MHz_500kBPS_CFG3;
          break;

        case (CAN_666KBPS):
          cfg1 = MCP_16MHz_666kBPS_CFG1;
          cfg2 = MCP_16MHz_666kBPS_CFG2;
          cfg3 = MCP_16MHz_666kBPS_CFG3;
          break;

        case (CAN_1000KBPS):
          cfg1 = MCP_16MHz_1000kBPS_CFG1;
          cfg2 = MCP_16MHz_1000kBPS_CFG2;
          cfg3 = MCP_16MHz_1000kBPS_CFG3;
          break;

        default:
          break;
      }
      break;

    case (MCP_8MHz) :
      switch (canSpeed){

        case (CAN_5KBPS) :
          cfg1 = MCP_8MHz_5kBPS_CFG1;
          cfg2 = MCP_8MHz_5kBPS_CFG2;
          cfg3 = MCP_8MHz_5kBPS_CFG3;
          break;

        case (CAN_10KBPS) :
          cfg1 = MCP_8MHz_10kBPS_CFG1;
          cfg2 = MCP_8MHz_10kBPS_CFG2;
          cfg3 = MCP_8MHz_10kBPS_CFG3;
          break;

        case (CAN_20KBPS) :
          cfg1 = MCP_8MHz_20kBPS_CFG1;
          cfg2 = MCP_8MHz_20kBPS_CFG2;
          cfg3 = MCP_8MHz_20kBPS_CFG3;
          break;

        case (CAN_31K25BPS) :
          cfg1 = MCP_8MHz_31k25BPS_CFG1;
          cfg2 = MCP_8MHz_31k25BPS_CFG2;
          cfg3 = MCP_8MHz_31k25BPS_CFG3;
          break;

        case (CAN_40KBPS) :
          cfg1 = MCP_8MHz_40kBPS_CFG1;
          cfg2 = MCP_8MHz_40kBPS_CFG2;
          cfg3 = MCP_8MHz_40kBPS_CFG3;
          break;

        case (CAN_50KBPS) :
          cfg1 = MCP_8MHz_50kBPS_CFG1;
          cfg2 = MCP_8MHz_50kBPS_CFG2;
          cfg3 = MCP_8MHz_50kBPS_CFG3;
          break;

        case (CAN_80KBPS) :
          cfg1 = MCP_8MHz_80kBPS_CFG1;
          cfg2 = MCP_8MHz_80kBPS_CFG2;
          cfg3 = MCP_8MHz_80kBPS_CFG3;
          break;

        case (CAN_100KBPS) :
          cfg1 = MCP_8MHz_100kBPS_CFG1;
          cfg2 = MCP_8MHz_100kBPS_CFG2;
          cfg3 = MCP_8MHz_100kBPS_CFG3;
          break;

        case (CAN_125KBPS) :
          cfg1 = MCP_8MHz_125kBPS_CFG1;
          cfg2 = MCP_8MHz_125kBPS_CFG2;
          cfg3 = MCP_8MHz_125kBPS_CFG3;
          break;

        case (CAN_200KBPS) :
          cfg1 = MCP_8MHz_200kBPS_CFG1;
          cfg2 = MCP_8MHz_200kBPS_CFG2;
          cfg3 = MCP_8MHz_200kBPS_CFG3;
          break;

        case (CAN_250KBPS) :
          cfg1 = MCP_8MHz_250kBPS_CFG1;
          cfg2 = MCP_8MHz_250kBPS_CFG2;
          cfg3 = MCP_8MHz_250kBPS_CFG3;
          break;

        case (CAN_500KBPS) :
          cfg1 = MCP_8MHz_500kBPS_CFG1;
          cfg2 = MCP_8MHz_500kBPS_CFG2;
          cfg3 = MCP_8MHz_500kBPS_CFG3;
          break;

        case (CAN_1000KBPS) :
          cfg1 = MCP_8MHz_1000kBPS_CFG1;
          cfg2 = MCP_8MHz_1000kBPS_CFG2;
          cfg3 = MCP_8MHz_1000kBPS_CFG3;
          break;

        default:
          break;
      }
      break;

    default:
      break;
  }

  mcp2515_setRegister(MCP_CNF1, cfg1);
  mcp2515_setRegister(MCP_CNF2, cfg2);
  mcp2515_setRegister(MCP_CNF3, cfg3);
}


/*********************************************************************************************************
** Function name:           - mcp2515_setCANCTRL_Mode
** Description:             - This function is used to modify the operation mode of the CAN controller.
**                          Modes are specified in the mcp2515_can_defs.h file. Some of the controller
**                          register's can only be modified when the controller is in "Configuration Mode".
** Input arguments:         - A byte variable with the value that represents each of the possible operation
**                           mode (see mcp2515_can_defs.h file). 
** Output values:           - The function returns a byte type variable. Its value is '0' if the mode is changed
**                          properly and '1' if there is a problem when changing operation mode.
*********************************************************************************************************/
byte mcp2515_setCANCTRL_Mode(const byte newmode){
  
  byte i;

  mcp2515_modifyRegister(MCP_CANCTRL, MODE_MASK, newmode);

  i = mcp2515_readRegister(MCP_CANCTRL);
  i &= MODE_MASK;

  if ( i == newmode )
  {
    return MCP2515_OK;
  }

  return MCP2515_FAIL;
}


/*********************************************************************************************************
** Function name:           - mcp2515_initCANBuffers
** Description:             - This function clears the value of the registers associated with the transmit
**                          and receive buffers.
** Input arguments:         
** Output values:           
*********************************************************************************************************/
void mcp2515_initCANBuffers(){
	
  mcp2515_setRegister(MCP_TXB0CTRL, 0x00);
  mcp2515_setRegister(MCP_TXB0SIDH, 0x00);
  mcp2515_setRegister(MCP_TXB1CTRL, 0x00);
  mcp2515_setRegister(MCP_TXB1SIDH, 0x00);
  mcp2515_setRegister(MCP_TXB2CTRL, 0x00);
  mcp2515_setRegister(MCP_TXB2SIDH, 0x00);
  mcp2515_setRegister(MCP_LOAD_TX1, 0x00);
  mcp2515_setRegister(MCP_LOAD_TX2, 0x00);
  mcp2515_setRegister(MCP_TX_MASK, 0X00);
  mcp2515_setRegister(MCP_RXB0CTRL, 0x00);
  mcp2515_setRegister(MCP_RXB1CTRL, 0x00);

}


/*********************************************************************************************************
** Function name:           - mcp2515_reset
** Description:             - This function clears the CAN Controller registers values. 
** Input arguments:         
** Output values:           
*********************************************************************************************************/
void mcp2515_reset(){
  beginTransaction(); 
  spi_send(MCP_RESET);
  endTransaction();
}


/*********************************************************************************************************
** Function name:           - mcp2515_init
** Description:             - This function needs to be used to configure the MCP2515 CAN Controller before
**                          start sending and receiving frames. It calls all the configuration functions shown
**                          above in order to clear the Controller registers' and set the CAN bitrate.
** Input arguments:         - Two byte variables which indicates the rate to be used and the microcontroller's
**                          frequency.
** Output values:           - It returns a byte type variable which value is '0' if the initial configuration
**                          goes well or '1' if it fails.
*********************************************************************************************************/
byte mcp2515_init(byte canSpeed, byte clock){

  byte res;

	mcp2515_reset();

	res = mcp2515_setCANCTRL_Mode(MODE_CONFIG);

  mcp2515_setRate(canSpeed, clock);

  if(res == MCP2515_OK){

    mcp2515_initCANBuffers();

    mcp2515_setRegister(MCP_CANINTE, MCP_RX0IF | MCP_RX1IF);

    mcp2515_setCANCTRL_Mode(MODE_NORMAL);

  }

  return res;
	
}

/*****************************************************
******************************************************/


/*****************************************************
*        Sending CAN Frames functions                *
*                                                    *
******************************************************/

/*********************************************************************************************************
** Function name:           - set_CAN_node_id
** Description:             - This function is used to set the identifier of the Data frames sent by a node.
** Input arguments:         - The value of the identifier to set.     
** Output values:       
*********************************************************************************************************/
void set_CAN_node_id(uint16_t id){
  sentCANFrame.id = id;
}


/*********************************************************************************************************
** Function name:           - get_CAN_node_id
** Description:             - This function is used to get the identifier of the Data frames sent by a node.
** Input arguments:              
** Output values:           - The value of the id.
*********************************************************************************************************/
uint16_t get_CAN_node_id(){
  return sentCANFrame.id;
}

/*********************************************************************************************************
** Function name:           - set_sent_message_payload
** Description:             - This function establishes the payload of the Data frames sent by a node and
**                          the length of this payload (in bytes).
** Input arguments:         - A pointer to the memory address where the payload's data is stored and an
**                          integer value with the length of this payload.   
** Output values:       
*********************************************************************************************************/
void set_sent_message_payload(uint8_t *payload, int len){
  memcpy(&sentCANFrame.payload, payload, len);
  sentCANFrame.payloadLength = len;
}


/*********************************************************************************************************
** Function name:           - get_sent_message_payload
** Description:             - This function is used to get a determined byte of the payload. The payload
**                          is stored in an array which maximum length is 8 bytes. The input argument
**                          is used to tell the function what position of this array return.
** Input arguments:         - An integer that indicates what position of the array where the payload is
**                          stored will be returned 
** Output values:           - The value of that payload's fragment.
*********************************************************************************************************/
uint8_t get_sent_message_payload(int index){
  return sentCANFrame.payload[index];
}


/*********************************************************************************************************
** Function name:           - get_sent_message_payloadLength
** Description:             - This function returns the payload's length of the Data frame sent.
** Input arguments:         
** Output values:           - The payload's length of the sent Data frames.
*********************************************************************************************************/
int get_sent_message_payloadLength(){
  return sentCANFrame.payloadLength;
}


/*********************************************************************************************************
** Function name:           - mcp2515_write_data_frame
** Description:             - This function is used to write an appropiate value in the CAN Controller's 
**                          registers in order to write a CAN Data frame with the identifier and the payload
**                          established by the previous functions.
** Input arguments:         
** Output values:          
*********************************************************************************************************/
void mcp2515_write_data_frame(){

  int i;

  beginTransaction(); 
  
  // Starting to load data in transmission buffer 0.
  spi_send(MCP_LOAD_TX0);

  // Configuration and arbitration registers.
  byte SIDH = (byte) ( sentCANFrame.id >> 3 );              //TXB0SIDH
  byte SIDL = (byte) (( sentCANFrame.id & 0x07 ) << 5);     //TXB0SIDL
  byte EID8 = 0x00;                                         //TXB0DLC
  byte EID0 = 0x00;                                         //TXB0EID8
  byte DLC = (byte) sentCANFrame.payloadLength;             //TXB0EID8

  /* Loading values of configuration registers */
  spi_send(SIDH);
  spi_send(SIDL);
  spi_send(EID8);
  spi_send(EID0);
  spi_send(DLC);
  /**********************************************/

  /* Loading payload in TXB0Dm registers */
  for (i = 0; i < sentCANFrame.payloadLength; i++){
    spi_send(sentCANFrame.payload[i]);
  }
  /***************************************/

  endTransaction();

}


/*********************************************************************************************************
** Function name:           - mcp2515_write_remote_frame
** Description:             - This function is used to write an appropiate value in the CAN Controller's 
**                          registers in order to write a CAN Remote frame
** Input arguments:         - The identifier of the remote node from which we want to receive data
** Output values:          
*********************************************************************************************************/
void mcp2515_write_remote_frame(uint16_t remoteId){

  beginTransaction(); 
  
  // Starting to load data in transmission buffer 0
  spi_send(MCP_LOAD_TX0);

  // Configuration and arbitration registers.
  byte SIDH = (byte) ( remoteId >> 3 );                     //TXB0SIDH
  byte SIDL = (byte) (( remoteId & 0x07 ) << 5);            //TXB0SIDL
  byte EID8 = 0x00;                                         //TXB0EID8
  byte EID0 = 0x00;                                         //TXB0EID0
  byte DLC = 0x40;                                          //TXB0DLC

  /* Loading values of configuration registers */
  spi_send(SIDH);
  spi_send(SIDL);
  spi_send(EID8);
  spi_send(EID0);
  spi_send(DLC);
  /**********************************************/

  endTransaction();

}


/*********************************************************************************************************
** Function name:           - mcp2515_start_transmit
** Description:             - This function is used to start transmitting the frame written by the function
**                          "mcp2515_write_remote_frame" or the function "mcp2515_write_data_frame".
** Input arguments:         
** Output values:          
*********************************************************************************************************/
void mcp2515_start_transmit(){
  beginTransaction(); 
  spi_send(MCP_RTS_TX0);
  endTransaction();
}


/*********************************************************************************************************
** Function name:           - send_CAN_data_frame
** Description:             - This function writes a Data frame in the CAN Controller's registers and then 
**                          transmit it over the bus
** Input arguments:         
** Output values:          
*********************************************************************************************************/
void send_CAN_data_frame()
{
  mcp2515_write_data_frame();
  mcp2515_start_transmit();
}


/*********************************************************************************************************
** Function name:           - send_CAN_remote_frame
** Description:             - This function writes a Remote frame in the CAN Controller's registers and then 
**                          transmit it over the bus
** Input arguments:         - The identifier of the remote node from which we want to receive data
** Output values:          
*********************************************************************************************************/
void send_CAN_remote_frame(uint16_t remoteId){
  mcp2515_write_remote_frame(remoteId);
  mcp2515_start_transmit();
}

/*****************************************************
******************************************************/




/*****************************************************
*        Receiving CAN Frames functions              *
*                                                    *
******************************************************/

/*********************************************************************************************************
** Function name:           - mcp2515_readStatus
** Description:             - This function is used to know whether the controller has an incoming package
**                          in the receive buffer 0. 
** Input arguments:         
** Output values:           - It returns the value of the constant "CAN_MSGAVAIL" if an incoming message is
**                          detected and the value of the constant "CAN_NOMSG" if is not detected.
*********************************************************************************************************/
byte mcp2515_readStatus(){
  byte res;
  beginTransaction();
  spi_send(MCP_READ_STATUS);
  res = spi_send(0x00);
  endTransaction();
  return ((res & MCP_STAT_RXIF_MASK) ? CAN_MSGAVAIL : CAN_NOMSG);
}


/*********************************************************************************************************
** Function name:           - mcp2515_read_canMsg
** Description:             - This function reads the message stored in the receive buffer 0 and stores it
**                          in a C struct used to store the received message information. 
** Input arguments:         
** Output values:           
*********************************************************************************************************/
void mcp2515_read_canMsg(){
  
  int i;
  int len;

  beginTransaction();

  spi_send(MCP_READ_RX0);

  // Configuration and arbitration registers.
  byte SIDH = spi_send(0x00);                               //TXB0SIDH
  byte SIDL = spi_send(0x00);                               //TXB0SIDL
  byte EID8 = spi_send(0x00);                               //TXB0EID8
  byte EID0 = spi_send(0x00);                               //TXB0EID0
  byte DLC = spi_send(0x00);                                //TXB0DLC

  receivedCANFrame.rtrBit=(SIDL & 0x10 ? 1 : 0 );
  receivedCANFrame.id = (SIDH << 3) + (SIDL >> 5);

  len = (int) ( DLC & MCP_DLC_MASK );

  receivedCANFrame.payloadLength = len;

  for (i = 0; i < len; i++) {
    receivedCANFrame.payload[i] = spi_send(0x00);
  }

  endTransaction();

}


/*********************************************************************************************************
** Function name:           - get_received_message_id
** Description:             - This function is used to get the identifier of the received frame. 
** Input arguments:         
** Output values:           - The identifier of the received frame
*********************************************************************************************************/
uint16_t get_received_message_id(){
  return receivedCANFrame.id;
}


/*********************************************************************************************************
** Function name:           - is_data_frame
** Description:             - This function checks whether the received frame is a Data frame or a Remote frame
** Input arguments:         
** Output values:           - A byte type variable which is '0' when the received frame is a Data frame
**                          and '1' when the received frame is a remote frame.
*********************************************************************************************************/
byte is_data_frame(){
  return receivedCANFrame.rtrBit;
}


/*********************************************************************************************************
** Function name:           - get_received_message_payloadLength
** Description:             - This function is used to get the payload's length of the received frame
** Input arguments:         
** Output values:           - A integer variable which value is the payload's length of the received frame
*********************************************************************************************************/
int get_received_message_payloadLength(){
  return receivedCANFrame.payloadLength;
}


/*********************************************************************************************************
** Function name:           - get_received_message_payload
** Description:             - This function is used to get a determined byte of the payload. The payload
**                          of the received frame is stored in an array which maximum length is 8 bytes. 
**                          The input argument is used to tell the function what position of this array return.
** Input arguments:         - An integer that indicates what position of the array where the payload is
**                          stored will be returned 
** Output values:           - The value of that payload's fragment.
*********************************************************************************************************/
uint8_t get_received_message_payload(int index){
  return receivedCANFrame.payload[index];
}

/*****************************************************
******************************************************/


