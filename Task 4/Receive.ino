#include <SPI.h> // Include SPI library
#include "nRF24L01.h" // Include nRF24L01 library
#include "RF24.h" // Include RF24 library

RF24 radio(9, 10); // Create the RF24 object on pins 9 and 10
byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; // Possible addresses

// Define a structure to hold the data received
struct DataPacket {
  byte counter; // For example, an integer counter
  byte counter2;
  char message[32]; // String message (max 31 characters + null terminator)
};

void setup() {
  Serial.begin(9600); // Open serial port for communication
  radio.begin(); // Activate the module
  radio.setAutoAck(1); // Enable acknowledgment mode
  radio.setRetries(0, 15); // Set retry settings
  radio.setPayloadSize(sizeof(DataPacket)); // Set payload size to the size of DataPacket

  radio.openReadingPipe(1, address[0]); // We want to listen on pipe 1
  radio.setChannel(0x60); // Set the channel
  radio.setPALevel(RF24_PA_MAX); // Set power level
  radio.setDataRate(RF24_250KBPS); // Set data rate

  radio.powerUp(); // Start working
  radio.startListening(); // Start listening for signals
}

void loop(void) {
  if (radio.available()) { // Check if data is available
    DataPacket dataReceived; // Create a variable to hold the received data
    radio.read(&dataReceived, sizeof(dataReceived)); // Read the data

    // Print the received data to the serial monitor
    Serial.print("Received Count: "); 
    Serial.print(dataReceived.counter); 
    Serial.print(" - ");
    Serial.print(dataReceived.counter2);
    Serial.print(" - Message: "); 
    Serial.println(dataReceived.message);
  }
}
