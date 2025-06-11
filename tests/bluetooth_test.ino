/*
 * Bluetooth Communication Test
 * Test HC-05 module and command processing
 */

#include "../config/robot_config.h"
#include "../include/BluetoothComm.h"

BluetoothComm bluetooth(BT_SOFT_RX, BT_SOFT_TX);

void setup() {
    Serial.begin(9600);
    Serial.println(F("SKVe Bluetooth Test Program"));
    Serial.println(F("==========================="));
    
    // Initialize Bluetooth
    bluetooth.begin(BLUETOOTH_BAUD);
    
    Serial.println(F("Bluetooth initialized"));
    Serial.println(F("Send commands via Bluetooth to test:"));
    Serial.println(F("  F, B, L, R, S - Basic commands"));
    Serial.println(F("  F180 - Speed commands"));
    Serial.println(F("  M150200 - Differential commands"));
    Serial.println(F(""));
    
    // Test connection
    if (bluetooth.testConnection()) {
        Serial.println(F("Bluetooth connection test: PASSED"));
    } else {
        Serial.println(F("Bluetooth connection test: FAILED"));
        Serial.println(F("Check HC-05 wiring and power"));
    }
}

void loop() {
    // Check for Bluetooth commands
    if (bluetooth.hasCommand()) {
        String command = bluetooth.readCommand();
        command.trim();
        
        Serial.print(F("Received: "));
        Serial.println(command);
        
        // Test command parsing
        testCommandParsing(command);
        
        // Echo response
        bluetooth.sendResponse("OK: " + command);
    }
    
    // Check for serial commands (for testing)
    if (Serial.available()) {
        String testCmd = Serial.readString();
        testCmd.trim();
        Serial.print(F("Testing command: "));
        Serial.println(testCmd);
        testCommandParsing(testCmd);
    }
}
void testCommandParsing(String command) {
    Serial.println(F("--- Command Analysis ---"));
    
    // Test single character commands
    if (command.length() == 1) {
        char cmd = command.charAt(0);
        Serial.print(F("Single char command: "));
        Serial.println(cmd);
        
        switch (cmd) {
            case 'F': Serial.println(F("  -> Forward")); break;
            case 'B': Serial.println(F("  -> Backward")); break;
            case 'L': Serial.println(F("  -> Left")); break;
            case 'R': Serial.println(F("  -> Right")); break;
            case 'S': Serial.println(F("  -> Stop")); break;
            case 'A': Serial.println(F("  -> Attack")); break;
            case 'E': Serial.println(F("  -> Emergency Stop")); break;
            case '?': Serial.println(F("  -> Status Request")); break;
            default: Serial.println(F("  -> Unknown command")); break;
        }
    }
    
    // Test speed commands
    else if (command.length() > 1 && (command.startsWith("F") || command.startsWith("B") || 
                                     command.startsWith("L") || command.startsWith("R"))) {
        char direction = command.charAt(0);
        int speed = command.substring(1).toInt();
        
        Serial.print(F("Speed command: "));
        Serial.print(direction);
        Serial.print(F(" at speed "));
        Serial.println(speed);
        
        if (speed >= 0 && speed <= 255) {
            Serial.println(F("  -> Valid speed range"));
        } else {
            Serial.println(F("  -> Invalid speed range (0-255)"));
        }
    }
    
    // Test differential commands
    else if (command.startsWith("M") && command.length() >= 7) {
        String leftStr = command.substring(1, 4);
        String rightStr = command.substring(4, 7);
        int leftSpeed = leftStr.toInt();
        int rightSpeed = rightStr.toInt();
        
        Serial.print(F("Differential command: Left="));
        Serial.print(leftSpeed);
        Serial.print(F(" Right="));
        Serial.println(rightSpeed);
    }
    
    // Test packet protocol
    else if (command.startsWith("!") && command.endsWith("#")) {
        Serial.println(F("Packet protocol detected"));
        
        if (bluetooth.validateChecksum(command)) {
            Serial.println(F("  -> Checksum valid"));
        } else {
            Serial.println(F("  -> Checksum invalid"));
        }
    }
    
    else {
        Serial.println(F("Unknown command format"));
    }
    
    Serial.println(F(""));
}