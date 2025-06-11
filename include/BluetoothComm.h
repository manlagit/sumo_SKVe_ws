#ifndef BLUETOOTH_COMM_H
#define BLUETOOTH_COMM_H

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "../config/robot_config.h"

/*
 * BluetoothComm Class
 * Expert-level Bluetooth communication for combat robots
 * Supports multiple command protocols with checksums
 */

class BluetoothComm {
public:
    // Constructor
    BluetoothComm(uint8_t rxPin = BT_SOFT_RX, uint8_t txPin = BT_SOFT_TX);
    
    // Initialization
    void begin(long baudRate = BLUETOOTH_BAUD);
    bool testConnection();
    void configureModule();
    
    // Communication Methods
    bool hasCommand();                      // Check if command available
    String readCommand();                   // Read raw command string
    bool parseCommand(String cmd, char &type, int &param1, int &param2);
    bool validateChecksum(String packet);   // Validate packet checksum
    
    // Protocol Support Methods
    bool parseSingleChar(String cmd, char &command);
    bool parseSpeedCommand(String cmd, char &direction, int &speed);
    bool parseDifferential(String cmd, int &leftSpeed, int &rightSpeed);
    bool parsePacketProtocol(String cmd, char &type, int &param1, int &param2);
    
    // Response Methods
    void sendResponse(String response);
    void sendStatus(String status);
    void sendError(String error);
    
    // Utility Methods
    void clearBuffer();
    uint8_t calculateChecksum(String data);
    bool isValidCommand(char cmd);

private:
    SoftwareSerial* _bluetooth;
    String _commandBuffer;
    unsigned long _lastCommandTime;
    bool _useHardwareSerial;
    
    // Internal methods
    void _flushInput();
    bool _isPacketComplete(String buffer);
    String _extractPacketData(String packet);
};

// Command Types Enumeration
enum CommandType {
    CMD_FORWARD = 'F',
    CMD_BACKWARD = 'B', 
    CMD_LEFT = 'L',
    CMD_RIGHT = 'R',
    CMD_STOP = 'S',
    CMD_WEAPON = 'W',
    CMD_MOTOR = 'M',
    CMD_EMERGENCY = 'E',
    CMD_STATUS = '?',
    CMD_INVALID = 0
};

#endif // BLUETOOTH_COMM_H