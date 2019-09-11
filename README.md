# CAN-BUS-C-library

<p>Controller Area Network (CAN bus) is a well-known communications protocol based on a bus topology,
used for the transmission of messages in distributed systems. This repository contains a Software that
allows the communication between 2 Arduino boards by using this protocol.</p>

<p>In short, a CAN Network is made up by a variable amount of certain nodes and the bus, to which all of them are connected.
Every CAN node needs to have a CAN controller, and a CAN transceiver. The host controller of the node (ECU), which is 
responsible for the functioning of the respective node, uses the CAN controller to encapsulate the message that they want
to send in accordance with the CAN protocol, and then the CAN transceiver is responsible of inserting the message into the 
physical channel.</p> 

<p>This Software has been developed specifically to be used with the MCP2515 CAN controller, from Microchip vendor. This 
microcontroller is integrated within the Arduino CAN Bus Shield. The host controller that has been used is an Arduino Mega
Board. Both of them communicate each other by using the SPI Interface. The way to perform the different CAN operations is 
by written the different CAN Controller registers. Each register has its own mission: To write the different CAN message fields
, to send it to the BUS or to read an incoming one.</p>

<p>The software of this project has been divided into different folders according the functionalities that its containing code
performs. The "spi_module" folder contains a set of funcions to allow the communication via the SPI interface between the host 
Controller and the CAN Controller. The "mcp_2515" folder contains the software that is used to perform the CAN
communication. The code contained within this folder uses the spi module functions to write, or read, the proper MCP2515 CAN 
controller register. Here we can find the main functions of the library. Finally, the .ino files placed in the root folder are the ones used by the Arduino Boards to exchange CAN
messages. These files are only two examples that show how to exploit the previously mentioned functions.</p>



