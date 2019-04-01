/*
  Modbus RS485 Soil Moisture Sensor with temp
   - read all the holding and register values for ID 1
   - read temp and moisture for ID 11
   - method to change ID 1 to a new ID
  Circuit:
   - MKR 1000 board
   - MKR 485 shield
   - Modbus RS485 soil moisture sensor
        by Catnip electronics
        https://www.tindie.com/products/miceuz/modbus-rs485-soil-moisture-sensor-2/ 
               
*/
// ArduinoModbus depends on the ArduinoRS485 library
#include <ArduinoRS485.h> 
#include <ArduinoModbus.h>

void setup() 
{
  Serial.begin(9600);
  Serial.println("Starting Modbus Client Moisture Sensor");
  // start the Modbus client, DEFAULT the moisture sensor runs at 19200 with a 500ms innterval
  if (!ModbusRTUClient.begin(19200)) 
  {
      Serial.println("Error, the modbus client did not start");
      while (1);
  }
}
// Main Program Loop
void loop() 
{
  //will change ID 1 to ID 11
  //writeHoldingRegisterValues();
  readHoldingRegisterValues();
  delay(500);
  readHoldingRegisterValues2();
  delay(500);
  readHoldingRegisterValues3();
  delay(500);
  readHoldingRegisterValues4();
  delay(500);
  readInputRegisterValues11();
  delay(500);
  readInputRegisterValues11t();
  delay(500);
  readInputRegisterValues();
  delay(500);
  readInputRegisterValues2();
  delay(5000);
  Serial.println();
}
    // call to change the ID of Sensor
void writeHoldingRegisterValues() 
{
     Serial.println("Write to Holding Register 1 to change ID ... ");
     //  the values are id number, holding register number 0(ID), and last is the new ID value
     ModbusRTUClient.holdingRegisterWrite(1, 0x00, 11);
     if (!ModbusRTUClient.endTransmission()) 
     {
       Serial.print("failed to connect ");
       // prints error of failure
       Serial.println(ModbusRTUClient.lastError());
     } 
     else 
        {
          Serial.println("changed to ID");
        }
}
//*********************************************************************
//  HOLDING REGISTER VALUES FOR THE MOISTURE SENSOR
// Register number  Size (bytes)  Valid values   Default value Description
//    0                 2             [1 - 247]     1         ID or Modbus address
//    1                 2             [0 - 7]       4         Baud rate
//    2                 2             [0 - 2]       0         Parity Note: most cheap ebay USB to RS485 dongles don't support parity properly!
//    3                 2             [1 - 65535]   500       Measurement interval in milliseconds
//    4                 2             [1 - 65535]   0         Time to sleep in seconds. Write to this register to put the sensor to sleep.
//*********************************************************************
// reads the ID of the moiture sensor
void readHoldingRegisterValues() {
  Serial.println("Reading ID value ... ");
  // read 1 Input Register value from (slave) ID 1, address 0x00
  if (!ModbusRTUClient.requestFrom(1, HOLDING_REGISTERS, 0x00, 1)) 
  {
    Serial.print("failed to connect ");
    Serial.println(ModbusRTUClient.lastError());
  }
  else 
      {
        Serial.println("the ID is ");
          while (ModbusRTUClient.available()) 
          {
          Serial.print(ModbusRTUClient.read());
          Serial.print(' ');
          }
        Serial.println();
      }
}
// reads the serial speed/baud rate to the sensor, default is 4 which is 19200
void readHoldingRegisterValues2()
{
     Serial.println("Reading Holding 2 Input Register values for Baud Rate ... ");
     delay(500);
     // read 1 Input Register value from (slave) id 42, address 0x00
  if (!ModbusRTUClient.requestFrom(1, HOLDING_REGISTERS, 0x01, 1))
  {
      Serial.print("failed to connect ");
      Serial.println(ModbusRTUClient.lastError());
  } 
  else 
     {
      Serial.println("the baud rate is ");
      while (ModbusRTUClient.available())  
      {
         Serial.print(ModbusRTUClient.read());
         Serial.print(' ');
      }
      Serial.println();
     }
}
// READ HOLDING REGISTER value for Parity
void readHoldingRegisterValues3() 
{
    Serial.println("Reading Holding 3 Input Register values for Parity ... ");
    delay(500);
    // read 1 Input Register value from (slave) id 42, address 0x00
  if (!ModbusRTUClient.requestFrom(1, HOLDING_REGISTERS, 0x02, 1)) 
  {
    Serial.print("failed to connect ");
    Serial.println(ModbusRTUClient.lastError());
  } 
  else 
     {
        Serial.println("the parity is ");
        while (ModbusRTUClient.available()) 
        {
          Serial.print(ModbusRTUClient.read());
          Serial.print(' ');
        }
        Serial.println();
     }
}
// READ HOLDING REGISTER value for Interval default is 500
void readHoldingRegisterValues4() 
{
   Serial.println("Reading Holding 4 Input Register values for Interval(500) ... ");
   delay(500);
   // read 1 Input Register value from (slave) id 1, address 0x03
  if (!ModbusRTUClient.requestFrom(1, HOLDING_REGISTERS, 0x03, 1))
  {
    Serial.print("failed to connect ");
    Serial.println(ModbusRTUClient.lastError());  
  } 
  else 
     {
        Serial.println("the interval delay is ");
        while (ModbusRTUClient.available()) 
        {
          Serial.print(ModbusRTUClient.read());
          Serial.print(' ');
        }
        Serial.println();
    }
}
// READ Moisture for ID 1
void readInputRegisterValues() {
  Serial.println("Reading ID 1, Register 0, MOISTURE value ... ");
  delay(300);
  // read 1 input value from (slave) ID 1 and register 0
  if (!ModbusRTUClient.requestFrom(1, INPUT_REGISTERS, 0x00,1)) {
    Serial.print("failed to connect ");
    Serial.println(ModbusRTUClient.lastError());
  } else {
    Serial.println("moisture for ID 1 is ");

    while (ModbusRTUClient.available()) {
      Serial.print(ModbusRTUClient.read());
      Serial.print(' ');
    }
    Serial.println();
  }
}
// READ Temp for ID 1
void readInputRegisterValues2() 
{
  Serial.println("Reading ID 1, Register 1, TEMP value ... ");
  // read 1 input value from (slave) ID 1, input register, register 1 and 1 value
  if (!ModbusRTUClient.requestFrom(1, INPUT_REGISTERS, 0x01,1)) 
  {
      Serial.print("failed to connect ");
      Serial.println(ModbusRTUClient.lastError());
  } 
  else 
     {
        Serial.println("temp for ID 1 is ");
        while (ModbusRTUClient.available()) 
        {
            Serial.print(ModbusRTUClient.read());
            Serial.print(' ');
        }
        Serial.println();
     }
}
// READ Moisture for ID 11
void readInputRegisterValues11() 
{
  Serial.print("Reading ID 11, Register 0, MOISTURE value... ");
  // read 1 input value from (slave) ID 11 for moisture
  if (!ModbusRTUClient.requestFrom(11, INPUT_REGISTERS, 0x00,1)) 
  {
      Serial.print("failed to connect ");
      Serial.println(ModbusRTUClient.lastError());
  } 
  else 
     {
        Serial.println("moisture for ID 11 is ");
    
        while (ModbusRTUClient.available()) 
        {
           Serial.print(ModbusRTUClient.read());
           Serial.print(' ');
        }
        Serial.println();
     }
}
// READ Temp for ID 11
void readInputRegisterValues11t() 
{
  Serial.print("Reading ID 11, Register 1, TEMP value... ");
  // read 1 input value from (slave) ID 11 for temp
  if (!ModbusRTUClient.requestFrom(11, INPUT_REGISTERS, 0x01,1)) 
  {
      Serial.print("failed to connect ");
      Serial.println(ModbusRTUClient.lastError());
  } 
  else 
     {
        Serial.println("temp for ID 11 is ");
        while (ModbusRTUClient.available()) 
        {
           Serial.print(ModbusRTUClient.read());
           Serial.print(' ');
        }
        Serial.println();
     }
}