#include <Arduino.h>
#include "stdint.h" 
#include "stdio.h"
#include "inttypes.h"
#include "string.h"

#include "spi.h"

uint8_t spi_send( uint8_t data )
{
	// put byte in send-buffer
	SPDR = data;
	
	// wait until byte was send
	while( !( SPSR & (1<<SPIF) ) );

	return SPDR;

}

void disable_spi()
{
  SPCR = 0;
}

void setup_spi(uint8_t mode, int dord, int interrupt, uint8_t clock)
{
  // specify pin directions for SPI pins on port B
  if (clock == SPI_SLAVE) { // if slave SS and SCK is input
    DDRB &= ~(1<<SPI_MOSI_PIN); // input
    DDRB |= (1<<SPI_MISO_PIN); // output
    DDRB &= ~(1<<SPI_SS_PIN); // input
    DDRB &= ~(1<<SPI_SCK_PIN);// input
  } else {
    DDRB |= (1<<SPI_MOSI_PIN); // output
    DDRB &= ~(1<<SPI_MISO_PIN); // input
    DDRB |= (1<<SPI_SCK_PIN);// output
    DDRB |= (1<<SPI_SS_PIN);// output
  }
  SPCR = ((interrupt ? 1 : 0)<<SPIE) // interrupt enabled
    | (1<<SPE) // enable SPI
    | (dord<<DORD) // LSB or MSB
    | (((clock != SPI_SLAVE) ? 1 : 0) <<MSTR) // Slave or Master
    | (((mode & 0x02) == 2) << CPOL) // clock timing mode CPOL
    | (((mode & 0x01)) << CPHA) // clock timing mode CPHA
    | (((clock & 0x02) == 2) << SPR1) // cpu clock divisor SPR1
    | ((clock & 0x01) << SPR0); // cpu clock divisor SPR0
  SPSR = (((clock & 0x04) == 4) << SPI2X); // clock divisor SPI2X
}

void beginTransaction(){
	setup_spi(SPI_MODE_0, SPI_MSB, SPI_NO_INTERRUPT, SPI_MSTR_CLK128);
	digitalWrite(10, LOW);
}

void endTransaction(){
	digitalWrite(10, HIGH);
	disable_spi();
}
