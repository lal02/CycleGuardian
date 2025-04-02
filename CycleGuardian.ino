#include <ArduinoBLE.h>
#include <Arduino_HS300x.h>

//UUIDs must not be changed! they are hardcoded in the android application
BLEService testService("5aee9db1-cdd5-47ac-9b9e-cdf97eb2b302");
//Change Characteristic type depending on data sent
BLEFIntCharacteristic characteristics("51d88c05-58a9-4e1c-8153-99ffd5d1c5c0",BLERead | BLENotify);
int nextvalue = 0;
void setup() {
  
  Serial.begin(9600);

  if(!BLE.begin()){
    Serial.println("BLE Failed to initialize");
  }

  if (!HS300x.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
    while (1);
  }

  // Setting BLE Name; must not be changed! hardcoded in the android application
  BLE.setLocalName("CycleGuardian_HW");
  
  // Setting BLE Service Advertisment
  BLE.setAdvertisedService(testService);
    
  // Adding characteristics to BLE Service Advertisment
  testService.addCharacteristic(characteristics);
  
  BLE.addService(testService);
  BLE.advertise();

  Serial.println("Bluetooth device is now active, waiting for connections...");
}

void loop() {
  // put your main code here, to run repeatedly:
    BLEDevice central = BLE.central();
    if (central)
    {
        Serial.print("Connected to central: ");
        Serial.println(central.address());
        
        while (central.connected())
        {
          //write value to android application
          //ML has to determin whether to write 0 (no crash) or 1 (crash)
          characteristics.writeValue(0);
          //delay(1000);
        }
        
    }
    else{
      Serial.println("central not functioning properly");
    }    
}


