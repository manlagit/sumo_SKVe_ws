/*
 * Motor Test Program
 * Quick test for motor functionality and calibration
 */

#include "../config/robot_config.h"
#include "../include/WormMotorController.h"

// Create motor controllers
WormMotorController leftMotor(MOTOR_LEFT_PWM, MOTOR_LEFT_DIR1, MOTOR_LEFT_DIR2);
WormMotorController rightMotor(MOTOR_RIGHT_PWM, MOTOR_RIGHT_DIR1, MOTOR_RIGHT_DIR2);

void setup() {
    Serial.begin(9600);
    Serial.println(F("SKVe Motor Test Program"));
    Serial.println(F("======================"));
    
    // Initialize motors
    leftMotor.begin();
    rightMotor.begin();
    
    Serial.println(F("Motors initialized. Starting test sequence..."));
    delay(2000);
    
    // Test sequence
    testBasicMovement();
    testSpeedRange();
    testDifferentialControl();
    
    Serial.println(F("Motor test complete!"));
}

void loop() {
    // Interactive test mode
    if (Serial.available()) {
        char command = Serial.read();
        processTestCommand(command);
    }
}

void testBasicMovement() {
    Serial.println(F("\n--- Basic Movement Test ---"));
    
    Serial.println(F("Forward test..."));
    leftMotor.setSpeed(150);
    rightMotor.setSpeed(150);
    delay(1000);
    
    Serial.println(F("Stop test..."));
    leftMotor.stop();
    rightMotor.stop();
    delay(500);
    
    Serial.println(F("Backward test..."));
    leftMotor.setSpeed(-150);
    rightMotor.setSpeed(-150);
    delay(1000);
    
    Serial.println(F("Stop test..."));
    leftMotor.stop();
    rightMotor.stop();
    delay(500);
}