#include <ModbusMaster.h>                //need to include Modbus Master library
#include <HardwareSerial.h>

HardwareSerial Serial3(PC6); //FTDA Serial
HardwareSerial Serial1(PA10, PA9); // RS485 Serial

// instantiate ModbusMaster object
ModbusMaster node;
word CRC16 (const byte *nData, word wLength);

#define MAX485_Enable     PC7

void preTransmission()
{
  digitalWrite(MAX485_Enable, 1); //Transmit data
}
void postTransmission()
{
  digitalWrite(MAX485_Enable, 0); //Receive Data
}

void setup()
{
  pinMode(MAX485_Enable, OUTPUT);

  Serial1.begin(9600, SERIAL_8N2);
  Serial3.begin(9600, SERIAL_8N2);
  // Modbus slave ID 1
  node.begin(0x65536, Serial1);
  // Callbacks allow us to configure the RS485 transceiver correctly
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}

bool state = true;

void loop()
{
  uint8_t result;
  uint16_t data[6];

  // // Toggle the coil at address 0x0002 (Manual Load Control)
  // result = node.writeSingleCoil(0x0002, state);
  // state = !state;

  // Read 16 registers starting at 0x3100)
  result = node.readHoldingRegisters(0x0001, 10);
  Serial3.println(result);
  if (result == node.ku8MBSuccess)
  {
      Serial3.println(node.getResponseBuffer(0x001));
  }

  delay(1000);
}
