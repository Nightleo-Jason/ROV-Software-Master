#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(9, 10); // Create the RF24 object on pins 9 and 10
byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; // Possible addresses

// Define a structure to hold the data to be sent
struct DataPacket {
  byte counter; // For example, an integer counter
  byte counter2;
  char message[32]; // String message (max 31 characters + null terminator)
};

DataPacket dataPacket; // Create an instance of the data packet

void setup() {
  Serial.begin(9600); // Open serial port for communication

  radio.begin(); // Activate the module
  radio.setAutoAck(1); // Enable acknowledgment mode
  radio.setRetries(0, 15); // Set retry settings
  radio.setPayloadSize(sizeof(dataPacket)); // Set payload size to the size of DataPacket

  radio.openWritingPipe(address[0]); // We are pipe 0, open the channel for sending
  radio.setChannel(0x60); // Set the channel

  radio.setPALevel(RF24_PA_MAX); // Set power level
  radio.setDataRate(RF24_250KBPS); // Set data rate

  radio.powerUp(); // Start working
  radio.stopListening(); // We are the transmitter

}

void loop(void) {
  // Prepare the data to send
  dataPacket.counter++; // Increment the counter
  dataPacket.counter2+=2;
  if (dataPacket.counter > 255) {
    dataPacket.counter = 0; // Reset if it exceeds 255
    dataPacket.counter2 = 0;
  }

  // Specify the message to send
  snprintf(dataPacket.message, sizeof(dataPacket.message), "hello sekai");

  Serial.print("Sending: "); 
  Serial.print(dataPacket.counter); 
  Serial.print(" - "); 
  Serial.print(dataPacket.counter2); 
  Serial.print(" - "); 
  Serial.println(dataPacket.message);

  radio.write(&dataPacket, sizeof(dataPacket)); // Send the data packet

  delay(1000); // Wait for a second before sending again
}
