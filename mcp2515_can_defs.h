#include <Arduino.h>
#include <inttypes.h>

#define MCP_DLC_MASK        0x0F          

#define MCP_STAT_RXIF_MASK   (0x03)

// Define MCP2515 register addresses

#define MCP_CANCTRL     0x0F

#define MCP_CNF3        0x28
#define MCP_CNF2        0x29
#define MCP_CNF1        0x2A
#define MCP_CANINTE     0x2B
#define MCP_CANINTF     0x2C

#define MCP_TXB0CTRL    0x30
#define MCP_TXB0SIDH    0x31
#define MCP_TXB1CTRL    0x40
#define MCP_TXB1SIDH    0x41
#define MCP_TXB2CTRL    0x50
#define MCP_TXB2SIDH    0x51
#define MCP_RXB0CTRL    0x60
#define MCP_RXB0SIDH    0x61
#define MCP_RXB1CTRL    0x70
#define MCP_RXB1SIDH    0x71

#define MCP_TX_MASK     0x54


// Define SPI Instruction Set

#define MCP_WRITE       0x02
#define MCP_READ        0x03
#define MCP_BITMOD      0x05
#define MCP_LOAD_TX0    0x40
#define MCP_LOAD_TX1    0x42
#define MCP_LOAD_TX2    0x44

#define MCP_RTS_TX0     0x81
#define MCP_RTS_TX1     0x82
#define MCP_RTS_TX2     0x84
#define MCP_RTS_ALL     0x87
#define MCP_READ_RX0    0x90
#define MCP_READ_RX1    0x94
#define MCP_READ_STATUS 0xA0
#define MCP_RX_STATUS   0xB0
#define MCP_RESET       0xC0


// CANCTRL Register Values

#define MODE_NORMAL     0x00
#define MODE_SLEEP      0x20
#define MODE_LOOPBACK   0x40
#define MODE_LISTENONLY 0x60
#define MODE_CONFIG     0x80
#define MODE_POWERUP    0xE0
#define MODE_MASK       0xE0
#define ABORT_TX        0x10
#define MODE_ONESHOT    0x08
#define CLKOUT_ENABLE   0x04
#define CLKOUT_DISABLE  0x00
#define CLKOUT_PS1      0x00
#define CLKOUT_PS2      0x01
#define CLKOUT_PS4      0x02
#define CLKOUT_PS8      0x03



// CANINTF Register Bits
#define MCP_RX0IF       0x01
#define MCP_RX1IF       0x02

// clock

#define MCP_16MHz	1
#define MCP_8MHz	2

// speed 16M

#define MCP_16MHz_1000kBPS_CFG1 (0x00)
#define MCP_16MHz_1000kBPS_CFG2 (0xD0)
#define MCP_16MHz_1000kBPS_CFG3 (0x82)

#define MCP_16MHz_500kBPS_CFG1 (0x00)
#define MCP_16MHz_500kBPS_CFG2 (0xF0)
#define MCP_16MHz_500kBPS_CFG3 (0x86)

#define MCP_16MHz_250kBPS_CFG1 (0x41)
#define MCP_16MHz_250kBPS_CFG2 (0xF1)
#define MCP_16MHz_250kBPS_CFG3 (0x85)

#define MCP_16MHz_200kBPS_CFG1 (0x01)
#define MCP_16MHz_200kBPS_CFG2 (0xFA)
#define MCP_16MHz_200kBPS_CFG3 (0x87)

#define MCP_16MHz_125kBPS_CFG1 (0x03)
#define MCP_16MHz_125kBPS_CFG2 (0xF0)
#define MCP_16MHz_125kBPS_CFG3 (0x86)

#define MCP_16MHz_100kBPS_CFG1 (0x03)
#define MCP_16MHz_100kBPS_CFG2 (0xFA)
#define MCP_16MHz_100kBPS_CFG3 (0x87)

#define MCP_16MHz_95kBPS_CFG1 (0x03)
#define MCP_16MHz_95kBPS_CFG2 (0xAD)
#define MCP_16MHz_95kBPS_CFG3 (0x07)

#define MCP_16MHz_83k3BPS_CFG1 (0x03)
#define MCP_16MHz_83k3BPS_CFG2 (0xBE)
#define MCP_16MHz_83k3BPS_CFG3 (0x07)

#define MCP_16MHz_80kBPS_CFG1 (0x03)
#define MCP_16MHz_80kBPS_CFG2 (0xFF)
#define MCP_16MHz_80kBPS_CFG3 (0x87)

#define MCP_16MHz_50kBPS_CFG1 (0x07)
#define MCP_16MHz_50kBPS_CFG2 (0xFA)
#define MCP_16MHz_50kBPS_CFG3 (0x87)

#define MCP_16MHz_40kBPS_CFG1 (0x07)
#define MCP_16MHz_40kBPS_CFG2 (0xFF)
#define MCP_16MHz_40kBPS_CFG3 (0x87)

#define MCP_16MHz_33kBPS_CFG1 (0x09)
#define MCP_16MHz_33kBPS_CFG2 (0xBE)
#define MCP_16MHz_33kBPS_CFG3 (0x07)

#define MCP_16MHz_31k25BPS_CFG1 (0x0F)
#define MCP_16MHz_31k25BPS_CFG2 (0xF1)
#define MCP_16MHz_31k25BPS_CFG3 (0x85)

#define MCP_16MHz_25kBPS_CFG1 (0X0F)
#define MCP_16MHz_25kBPS_CFG2 (0XBA)
#define MCP_16MHz_25kBPS_CFG3 (0X07)

#define MCP_16MHz_20kBPS_CFG1 (0x0F)
#define MCP_16MHz_20kBPS_CFG2 (0xFF)
#define MCP_16MHz_20kBPS_CFG3 (0x87)

#define MCP_16MHz_10kBPS_CFG1 (0x1F)
#define MCP_16MHz_10kBPS_CFG2 (0xFF)
#define MCP_16MHz_10kBPS_CFG3 (0x87)

#define MCP_16MHz_5kBPS_CFG1 (0x3F)
#define MCP_16MHz_5kBPS_CFG2 (0xFF)
#define MCP_16MHz_5kBPS_CFG3 (0x87)

#define MCP_16MHz_666kBPS_CFG1 (0x00)
#define MCP_16MHz_666kBPS_CFG2 (0xA0)
#define MCP_16MHz_666kBPS_CFG3 (0x04)


// speed 8M

#define MCP_8MHz_1000kBPS_CFG1 (0x00)
#define MCP_8MHz_1000kBPS_CFG2 (0x80)
#define MCP_8MHz_1000kBPS_CFG3 (0x00)

#define MCP_8MHz_500kBPS_CFG1 (0x00)
#define MCP_8MHz_500kBPS_CFG2 (0x90)
#define MCP_8MHz_500kBPS_CFG3 (0x02)

#define MCP_8MHz_250kBPS_CFG1 (0x00)
#define MCP_8MHz_250kBPS_CFG2 (0xb1)
#define MCP_8MHz_250kBPS_CFG3 (0x05)

#define MCP_8MHz_200kBPS_CFG1 (0x00)
#define MCP_8MHz_200kBPS_CFG2 (0xb4)
#define MCP_8MHz_200kBPS_CFG3 (0x06)

#define MCP_8MHz_125kBPS_CFG1 (0x01)
#define MCP_8MHz_125kBPS_CFG2 (0xb1)
#define MCP_8MHz_125kBPS_CFG3 (0x05)

#define MCP_8MHz_100kBPS_CFG1 (0x01)
#define MCP_8MHz_100kBPS_CFG2 (0xb4)
#define MCP_8MHz_100kBPS_CFG3 (0x06)

#define MCP_8MHz_80kBPS_CFG1 (0x01)
#define MCP_8MHz_80kBPS_CFG2 (0xbf)
#define MCP_8MHz_80kBPS_CFG3 (0x07)

#define MCP_8MHz_50kBPS_CFG1 (0x03)
#define MCP_8MHz_50kBPS_CFG2 (0xb4)
#define MCP_8MHz_50kBPS_CFG3 (0x06)

#define MCP_8MHz_40kBPS_CFG1 (0x03)
#define MCP_8MHz_40kBPS_CFG2 (0xbf)
#define MCP_8MHz_40kBPS_CFG3 (0x07)

#define MCP_8MHz_31k25BPS_CFG1 (0x07)
#define MCP_8MHz_31k25BPS_CFG2 (0xa4)
#define MCP_8MHz_31k25BPS_CFG3 (0x04)

#define MCP_8MHz_20kBPS_CFG1 (0x07)
#define MCP_8MHz_20kBPS_CFG2 (0xbf)
#define MCP_8MHz_20kBPS_CFG3 (0x07)

#define MCP_8MHz_10kBPS_CFG1 (0x0f)
#define MCP_8MHz_10kBPS_CFG2 (0xbf)
#define MCP_8MHz_10kBPS_CFG3 (0x07)

#define MCP_8MHz_5kBPS_CFG1 (0x1f)
#define MCP_8MHz_5kBPS_CFG2 (0xbf)
#define MCP_8MHz_5kBPS_CFG3 (0x07)

#define MCP2515_OK         (0)
#define MCP2515_FAIL       (1)
#define CAN_OK				0

// initial value of gCANAutoProcess

#define CAN_5KBPS           1
#define CAN_10KBPS          2
#define CAN_20KBPS          3
#define CAN_25KBPS          4
#define CAN_31K25BPS        5
#define CAN_33KBPS          6
#define CAN_40KBPS          7
#define CAN_50KBPS          8
#define CAN_80KBPS          9
#define CAN_83K3BPS         10
#define CAN_95KBPS          11
#define CAN_100KBPS         12
#define CAN_125KBPS         13
#define CAN_200KBPS         14
#define CAN_250KBPS         15
#define CAN_500KBPS         16
#define CAN_666KBPS         17
#define CAN_1000KBPS        18

#define CAN_MSGAVAIL        (0)
#define CAN_NOMSG           (1)
