#include "stdint.h" 
#include "inttypes.h"

#include "mcp2515_can_defs.h"

struct tCANconfig	
{
	uint16_t id;
	byte   	rtrBit;                             
	uint8_t payload[8];
	int     payloadLength;
};


/*****************************************************
*       MCP2515 Registers Manipulation functions     *
*                                                    *
******************************************************/

byte mcp2515_readRegister(const byte address);

void mcp2515_setRegister(const byte address, const byte value);

void mcp2515_modifyRegister(const byte address, const byte mask, const byte data);

/*****************************************************
******************************************************/



/*****************************************************
*             Configuration functions                *
*                                                    *
******************************************************/

void mcp2515_setRate(byte canSpeed, byte clock);

byte mcp2515_setCANCTRL_Mode(byte newmode);

void mcp2515_initCANBuffers();

void mcp2515_reset();

byte mcp2515_init(byte canSpeed, byte clock);

/*****************************************************
******************************************************/



/*****************************************************
*        Sending CAN Frames functions                *
*                                                    *
******************************************************/

void set_CAN_node_id(uint16_t id);

uint16_t get_CAN_node_id();

void set_sent_message_payload(uint8_t *payload, int len);

void mcp2515_start_transmit();

void send_CAN_data_frame();

void mcp2515_write_data_frame();

void send_CAN_remote_frame(uint16_t remoteId);

void mcp2515_write_remote_frame();

uint8_t get_sent_message_payload(int index);

int get_sent_message_payloadLength();

/*****************************************************
******************************************************/



/*****************************************************
*        Receiving CAN Frames functions              *
*                                                    *
******************************************************/

byte mcp2515_readStatus();

void mcp2515_read_canMsg();

uint16_t get_received_message_id();

uint8_t get_received_message_payload(int index);

int get_received_message_payloadLength();

byte is_data_frame();

/*****************************************************
******************************************************/
