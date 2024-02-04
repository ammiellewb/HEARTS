#include <Wire.h>
#include "MAX30105.h"




MAX30105 particleSensor;




void setup() {
    Wire.begin();




    // Start the serial communication.
    Serial.begin(9600);
    while (!Serial); // Leonardo: wait for serial monitor
    Serial.println("\nI2C Scanner");




    // Scanning for I2C devices.
    byte error, address;
    int nDevices;




    Serial.println("Scanning...");




    nDevices = 0;
    for (address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();




        if (error == 0) {
            Serial.print("I2C device found at address 0x");
            if (address < 16)
                Serial.print("0");
            Serial.print(address, HEX);
            Serial.println("  !");




            nDevices++;
        } else if (error == 4) {
            Serial.print("Unknown error at address 0x");
            if (address < 16)
                Serial.print("0");
            Serial.println(address, HEX);
        }
    }
    if (nDevices == 0)
        Serial.println("No I2C devices found\n");
    else
        Serial.println("done\n");




    // MAX30105 initialization.
    Serial.println("MAX30105 Basic Readings Example");




    if (particleSensor.begin() == false) {
        Serial.println("MAX30105 was not found. Please check wiring/power.");
        while (1); // Halt execution if sensor not found
    }




    particleSensor.setup(); // Configure sensor. Use 6.4mA for LED drive
}




void loop() {
    // Read sensor values
    uint32_t redValue = particleSensor.getRed();
    uint32_t irValue = particleSensor.getIR();
    uint32_t greenValue = particleSensor.getGreen();
    //int oxygenLevel = -200 * (redValue - irValue) + 3;




    // Print values in comma-separated format for Serial Plotter
    Serial.print(redValue);
    Serial.print(",");
    Serial.print(irValue);
    Serial.print(",");
    Serial.println(greenValue);  // 'println' to end the line here
    //Serial.println(oxygenLevel);




    // Delay to make the data readable - adjust as needed
    delay(100);
}
