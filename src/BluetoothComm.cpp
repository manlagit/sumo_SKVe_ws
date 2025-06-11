#include "../include/BluetoothComm.h"

/*
 * BluetoothComm Implementation
 * Competition-grade Bluetooth communication system
 */

BluetoothComm::BluetoothComm(uint8_t rxPin, uint8_t txPin) {
    if (rxPin == 0 && txPin == 1) {
        _useHardwareSerial = true;
        _bluetooth = nullptr;
    } else {
        _useHardwareSerial = false;
        _bluetooth = new SoftwareSerial(rxPin, txPin);
    }
    _lastCommandTime = 0;
}

void BluetoothComm::begin(long baudRate) {
    if (_useHardwareSerial) {
        Serial.begin(baudRate);
        Serial.println(F("Bluetooth: Hardware Serial initialized"));
    } else {
        _bluetooth->begin(baudRate);
        Serial.println(F("Bluetooth: Software Serial initialized"));
    }
    
    delay(1000);  // Allow module to initialize
    clearBuffer();
    
    #if ENABLE_COMMUNICATION_TEST
    if (testConnection()) {
        Serial.println(F("Bluetooth: Connection test passed"));
    } else {
        Serial.println(F("Bluetooth: Connection test failed"));
    }
    #endif
}

bool BluetoothComm::testConnection() {
    // Send test command and wait for response
    if (_useHardwareSerial) {
        Serial.print(F("AT"));
        delay(100);
        return Serial.available() > 0;
    } else {
        _bluetooth->print(F("AT"));
        delay(100);
        return _bluetooth->available() > 0;
    }
}
void BluetoothComm::configureModule() {
    // Configure HC-05 for optimal performance
    Serial.println(F("Configuring Bluetooth module..."));
    
    delay(1000);
    
    // Set baud rate to high speed if enabled
    #if BLUETOOTH_BAUD_FAST == 115200
    if (_useHardwareSerial) {
        Serial.print(F("AT+UART=115200,0,0"));
    } else {
        _bluetooth->print(F("AT+UART=115200,0,0"));
    }
    delay(500);
    #endif
    
    // Set device name
    if (_useHardwareSerial) {
        Serial.print(F("AT+NAME=SKVe_SUMO"));
    } else {
        _bluetooth->print(F("AT+NAME=SKVe_SUMO"));
    }
    delay(500);
    
    // Set slave mode
    if (_useHardwareSerial) {
        Serial.print(F("AT+CMODE=0"));
    } else {
        _bluetooth->print(F("AT+CMODE=0"));
    }
    delay(500);
    
    Serial.println(F("Bluetooth configuration complete"));
}

bool BluetoothComm::hasCommand() {
    bool dataAvailable = false;
    
    if (_useHardwareSerial) {
        dataAvailable = Serial.available() > 0;
        if (dataAvailable) {
            _commandBuffer += Serial.readString();
        }
    } else {
        dataAvailable = _bluetooth->available() > 0;
        if (dataAvailable) {
            _commandBuffer += _bluetooth->readString();
        }
    }
    
    // Check for complete command
    return _commandBuffer.length() > 0 && 
           (_commandBuffer.indexOf('\n') >= 0 || _isPacketComplete(_commandBuffer));
}