/*
 * SKVe Sumo Robot - Main Program
 * Competition-Grade Combat Robot Control System
 * Based on Expert Combat Robotics Standards
 * 
 * Features:
 * - Professional motor control with deadband compensation
 * - Multi-protocol Bluetooth communication
 * - Competition-grade safety systems
 * - Performance optimization for <50ms response times
 * - Expert-level code architecture
 */

#include "config/robot_config.h"
#include "include/WormMotorController.h"
#include "include/BluetoothComm.h"
#include "include/SafetySystem.h"

// ============================================================================
// GLOBAL OBJECTS
// ============================================================================

// Motor Controllers
WormMotorController leftMotor(MOTOR_LEFT_PWM, MOTOR_LEFT_DIR1, MOTOR_LEFT_DIR2, 
                             MOTOR_DEADBAND_LEFT, LEFT_MOTOR_TRIM);
WormMotorController rightMotor(MOTOR_RIGHT_PWM, MOTOR_RIGHT_DIR1, MOTOR_RIGHT_DIR2, 
                              MOTOR_DEADBAND_RIGHT, RIGHT_MOTOR_TRIM);

// Communication System
BluetoothComm bluetooth(BT_SOFT_RX, BT_SOFT_TX);

// Safety System
SafetySystem safety;

// ============================================================================
// GLOBAL VARIABLES
// ============================================================================

// Robot state
volatile bool emergencyStopTriggered = false;
unsigned long lastCommandTime = 0;
bool robotInitialized = false;

// Performance monitoring
unsigned long loopStartTime = 0;
unsigned long maxLoopTime = 0;
// ============================================================================
// SETUP FUNCTION
// ============================================================================

void setup() {
    // Initialize serial communication for debugging
    Serial.begin(9600);
    Serial.println(F(""));
    Serial.println(F("================================="));
    Serial.println(F("SKVe Sumo Robot - Competition Grade"));
    Serial.println(F("Expert Combat Robotics System"));
    Serial.println(F("================================="));
    
    // Initialize status LED
    pinMode(STATUS_LED_PIN, OUTPUT);
    digitalWrite(STATUS_LED_PIN, HIGH);  // LED on during initialization
    
    Serial.println(F("Initializing systems..."));
    
    // Initialize safety system first (highest priority)
    Serial.print(F("Safety System... "));
    safety.begin();
    safety.attachEmergencyStop(emergencyStopHandler);
    Serial.println(F("OK"));
    
    // Initialize motor controllers
    Serial.print(F("Motor Controllers... "));
    leftMotor.begin();
    rightMotor.begin();
    Serial.println(F("OK"));
    
    // Initialize Bluetooth communication
    Serial.print(F("Bluetooth Communication... "));
    bluetooth.begin(BLUETOOTH_BAUD);
    
    #if BLUETOOTH_BAUD_FAST == 115200
    bluetooth.configureModule();
    #endif
    
    Serial.println(F("OK"));
    
    // Run motor test if enabled
    #if ENABLE_MOTOR_TEST
    Serial.println(F("Running motor test sequence..."));
    runMotorTest();
    #endif    
    // Final initialization
    digitalWrite(STATUS_LED_PIN, LOW);   // LED off when ready
    robotInitialized = true;
    
    Serial.println(F(""));
    Serial.println(F("Robot initialization complete!"));
    Serial.println(F("Ready for competition."));
    Serial.println(F(""));
    Serial.println(F("Command Format:"));
    Serial.println(F("  F/B/L/R/S - Basic movement"));
    Serial.println(F("  F180 - Forward at speed 180"));
    Serial.println(F("  M150200 - Left=150, Right=200"));
    Serial.println(F("  !05M15020099# - Packet protocol"));
    Serial.println(F("================================="));
    
    // Reset timing
    lastCommandTime = millis();
}

// ============================================================================
// MAIN LOOP
// ============================================================================

void loop() {
    loopStartTime = micros();
    
    // Safety system update (highest priority)
    safety.update();
    
    // Check if robot is safe to operate
    if (!safety.isSafeToOperate()) {
        stopAllMotors();
        handleSafetyViolation();
        return;
    }
    
    // Process Bluetooth commands
    processBluetoothCommands();
    
    // Update motor control (smooth acceleration)
    updateMotorControl();
    
    // Performance monitoring
    #if ENABLE_PERFORMANCE_MONITOR
    updatePerformanceMetrics();
    #endif
    
    // Main loop delay for consistent timing
    delay(LOOP_DELAY_MS);
}
// ============================================================================
// BLUETOOTH COMMAND PROCESSING
// ============================================================================

void processBluetoothCommands() {
    if (!bluetooth.hasCommand()) return;
    
    String command = bluetooth.readCommand();
    command.trim();
    
    if (command.length() == 0) return;
    
    // Reset communication timeout
    safety.resetCommunicationTimeout();
    lastCommandTime = millis();
    
    // Process command based on enabled protocols
    bool commandProcessed = false;
    
    #if SUPPORT_PACKET_PROTOCOL
    if (command.startsWith("!") && command.endsWith("#")) {
        commandProcessed = processPacketCommand(command);
    }
    #endif
    
    #if SUPPORT_DIFFERENTIAL
    if (!commandProcessed && command.startsWith("M")) {
        commandProcessed = processDifferentialCommand(command);
    }
    #endif
    
    #if SUPPORT_SPEED_COMMANDS
    if (!commandProcessed && (command.startsWith("F") || command.startsWith("B") || 
                             command.startsWith("L") || command.startsWith("R"))) {
        commandProcessed = processSpeedCommand(command);
    }
    #endif
    
    #if SUPPORT_SINGLE_CHAR
    if (!commandProcessed && command.length() == 1) {
        commandProcessed = processSingleCharCommand(command);
    }
    #endif
    
    if (!commandProcessed) {
        bluetooth.sendError("Invalid command: " + command);
        Serial.println("Invalid command: " + command);
    }
}
// ============================================================================
// COMMAND PROCESSING FUNCTIONS
// ============================================================================

bool processSingleCharCommand(String command) {
    char cmd = command.charAt(0);
    
    switch (cmd) {
        case 'F':
            moveForward(SPEED_FORWARD);
            break;
        case 'B':
            moveBackward(SPEED_FORWARD);
            break;
        case 'L':
            turnLeft(SPEED_TURN);
            break;
        case 'R':
            turnRight(SPEED_TURN);
            break;
        case 'S':
            stopAllMotors();
            break;
        case 'A':  // Attack mode
            moveForward(SPEED_ATTACK);
            break;
        case 'E':  // Emergency stop
            safety.triggerEmergencyStop();
            break;
        case '?':  // Status request
            bluetooth.sendStatus(safety.getStatusString());
            break;
        default:
            return false;
    }
    
    #if DEBUG_MODE
    Serial.print("Single char command: ");
    Serial.println(cmd);
    #endif
    
    return true;
}
bool processSpeedCommand(String command) {
    char direction = command.charAt(0);
    int speed = command.substring(1).toInt();
    
    // Validate speed range
    speed = constrain(speed, 0, 255);
    
    switch (direction) {
        case 'F':
            moveForward(speed);
            break;
        case 'B':
            moveBackward(speed);
            break;
        case 'L':
            turnLeft(speed);
            break;
        case 'R':
            turnRight(speed);
            break;
        default:
            return false;
    }
    
    #if DEBUG_MODE
    Serial.print("Speed command: ");
    Serial.print(direction);
    Serial.print(" at speed ");
    Serial.println(speed);
    #endif
    
    return true;
}

bool processDifferentialCommand(String command) {
    // Format: M<leftSpeed><rightSpeed>
    if (command.length() < 7) return false;  // Minimum: M000000
    
    String leftStr = command.substring(1, 4);
    String rightStr = command.substring(4, 7);
    
    int leftSpeed = leftStr.toInt();
    int rightSpeed = rightStr.toInt();
    
    // Handle negative speeds (would need different format in real implementation)
    leftSpeed = constrain(leftSpeed, -255, 255);
    rightSpeed = constrain(rightSpeed, -255, 255);
    
    setMotorSpeeds(leftSpeed, rightSpeed);
    
    #if DEBUG_MODE
    Serial.print("Differential: L=");
    Serial.print(leftSpeed);
    Serial.print(" R=");
    Serial.println(rightSpeed);
    #endif
    
    return true;
}
bool processPacketCommand(String command) {
    // Format: !<length><command><data><checksum>#
    if (command.length() < 6) return false;
    
    // Validate checksum first
    if (!bluetooth.validateChecksum(command)) {
        bluetooth.sendError("Checksum mismatch");
        return false;
    }
    
    // Extract command data
    char cmdType = command.charAt(3);
    String data = command.substring(4, command.length() - 3);
    
    switch (cmdType) {
        case 'M':  // Motor command
            if (data.length() >= 6) {
                int leftSpeed = data.substring(0, 3).toInt();
                int rightSpeed = data.substring(3, 6).toInt();
                setMotorSpeeds(leftSpeed, rightSpeed);
                return true;
            }
            break;
        case 'S':  // Stop command
            stopAllMotors();
            return true;
        case 'E':  // Emergency stop
            safety.triggerEmergencyStop();
            return true;
    }
    
    return false;
}

// ============================================================================
// MOVEMENT FUNCTIONS
// ============================================================================

void moveForward(int speed) {
    leftMotor.setSpeed(speed);
    rightMotor.setSpeed(speed);
    
    #if DEBUG_MODE
    Serial.print("Moving forward at speed: ");
    Serial.println(speed);
    #endif
}

void moveBackward(int speed) {
    leftMotor.setSpeed(-speed);
    rightMotor.setSpeed(-speed);
    
    #if DEBUG_MODE
    Serial.print("Moving backward at speed: ");
    Serial.println(speed);
    #endif
}
void turnLeft(int speed) {
    leftMotor.setSpeed(-speed);
    rightMotor.setSpeed(speed);
    
    #if DEBUG_MODE
    Serial.print("Turning left at speed: ");
    Serial.println(speed);
    #endif
}

void turnRight(int speed) {
    leftMotor.setSpeed(speed);
    rightMotor.setSpeed(-speed);
    
    #if DEBUG_MODE
    Serial.print("Turning right at speed: ");
    Serial.println(speed);
    #endif
}

void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    leftMotor.setSpeed(leftSpeed);
    rightMotor.setSpeed(rightSpeed);
    
    #if DEBUG_MODE
    Serial.print("Motor speeds - Left: ");
    Serial.print(leftSpeed);
    Serial.print(" Right: ");
    Serial.println(rightSpeed);
    #endif
}

void stopAllMotors() {
    leftMotor.stop();
    rightMotor.stop();
    
    #if DEBUG_MODE
    Serial.println("All motors stopped");
    #endif
}
// ============================================================================
// UTILITY AND SAFETY FUNCTIONS
// ============================================================================

void emergencyStopHandler() {
    // Interrupt service routine for emergency stop
    emergencyStopTriggered = true;
    leftMotor.emergencyStop();
    rightMotor.emergencyStop();
    
    // Flash LED to indicate emergency stop
    digitalWrite(STATUS_LED_PIN, HIGH);
}

void handleSafetyViolation() {
    // Handle safety system violations
    stopAllMotors();
    
    // Flash status LED
    static unsigned long lastFlash = 0;
    if (millis() - lastFlash > 250) {
        digitalWrite(STATUS_LED_PIN, !digitalRead(STATUS_LED_PIN));
        lastFlash = millis();
    }
    
    // Send safety status if Bluetooth is available
    static unsigned long lastStatusSend = 0;
    if (millis() - lastStatusSend > 1000) {
        bluetooth.sendStatus("SAFETY VIOLATION: " + safety.getStatusString());
        lastStatusSend = millis();
    }
}

void updateMotorControl() {
    // Update smooth motor control if enabled
    // This function can be used for acceleration ramping in future
    // Currently motors handle their own smooth control
}

void runMotorTest() {
    Serial.println(F("Testing left motor..."));
    leftMotor.testMotor();
    
    Serial.println(F("Testing right motor..."));
    rightMotor.testMotor();
    
    Serial.println(F("Motor test sequence complete"));
}
#if ENABLE_PERFORMANCE_MONITOR
void updatePerformanceMetrics() {
    unsigned long loopTime = micros() - loopStartTime;
    
    if (loopTime > maxLoopTime) {
        maxLoopTime = loopTime;
    }
    
    // Print performance stats every 5 seconds
    static unsigned long lastPerfPrint = 0;
    if (millis() - lastPerfPrint > 5000) {
        Serial.print(F("Max loop time: "));
        Serial.print(maxLoopTime);
        Serial.println(F(" microseconds"));
        
        safety.printStatus();
        
        lastPerfPrint = millis();
        maxLoopTime = 0;  // Reset for next measurement period
    }
}
#endif

// ============================================================================
// EXPERT COMBAT ROBOTICS FEATURES
// ============================================================================

void performCompetitionStartup() {
    // Competition-specific startup sequence
    Serial.println(F("Competition startup sequence initiated"));
    
    // Brief LED flash to signal ready state
    for (int i = 0; i < 3; i++) {
        digitalWrite(STATUS_LED_PIN, HIGH);
        delay(200);
        digitalWrite(STATUS_LED_PIN, LOW);
        delay(200);
    }
    
    Serial.println(F("Robot ready for competition"));
}

// ============================================================================
// END OF PROGRAM
// ============================================================================