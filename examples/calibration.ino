/*
 * Robot Calibration Program
 * Calibrate motors and sensors for optimal performance
 */

#include "../config/robot_config.h"
#include "../include/WormMotorController.h"

WormMotorController leftMotor(MOTOR_LEFT_PWM, MOTOR_LEFT_DIR1, MOTOR_LEFT_DIR2);
WormMotorController rightMotor(MOTOR_RIGHT_PWM, MOTOR_RIGHT_DIR1, MOTOR_RIGHT_DIR2);

void setup() {
    Serial.begin(9600);
    Serial.println(F("SKVe Robot Calibration Program"));
    Serial.println(F("=============================="));
    
    // Initialize motors
    leftMotor.begin();
    rightMotor.begin();
    
    Serial.println(F("Starting calibration sequence..."));
    delay(2000);
    
    // Calibration sequence
    calibrateMotorDeadband();
    calibrateMotorTrim();
    testCalibratedMovement();
    
    Serial.println(F("Calibration complete!"));
    Serial.println(F(""));
    Serial.println(F("Interactive mode:"));
    Serial.println(F("  'd' - Test deadband"));
    Serial.println(F("  't' - Test trim"));
    Serial.println(F("  's' - Test straight movement"));
    Serial.println(F("  'r' - Reset to defaults"));
}

void loop() {
    if (Serial.available()) {
        char command = Serial.read();
        processCalibrationCommand(command);
    }
}

void calibrateMotorDeadband() {
    Serial.println(F("\n--- Motor Deadband Calibration ---"));
    
    Serial.println(F("Testing left motor deadband..."));
    uint8_t leftDeadband = findMinimumPWM(leftMotor, "Left");
    
    Serial.println(F("Testing right motor deadband..."));
    uint8_t rightDeadband = findMinimumPWM(rightMotor, "Right");
    
    Serial.print(F("Recommended deadband values:"));
    Serial.print(F("  Left: "));
    Serial.println(leftDeadband);
    Serial.print(F("  Right: "));
    Serial.println(rightDeadband);
    
    // Apply calibrated values
    leftMotor.setDeadband(leftDeadband);
    rightMotor.setDeadband(rightDeadband);
}
uint8_t findMinimumPWM(WormMotorController& motor, String motorName) {
    Serial.print(F("Finding minimum PWM for "));
    Serial.print(motorName);
    Serial.println(F(" motor..."));
    
    uint8_t minPWM = 255;  // Start high
    
    // Test PWM values from 50 to 120
    for (uint8_t pwm = 50; pwm <= 120; pwm += 5) {
        Serial.print(F("Testing PWM: "));
        Serial.println(pwm);
        
        // Set motor speed
        motor.setSpeed(pwm);
        delay(500);  // Let motor stabilize
        
        // In real implementation, check if motor is actually moving
        // For now, we'll use a conservative approach
        
        motor.stop();
        delay(200);
        
        // Prompt user for feedback
        Serial.println(F("Did the motor move? (y/n):"));
        while (!Serial.available()) { delay(10); }
        
        char response = Serial.read();
        Serial.flush();  // Clear buffer
        
        if (response == 'y' || response == 'Y') {
            minPWM = pwm;
            Serial.print(F("Motor moved at PWM: "));
            Serial.println(pwm);
            break;
        }
    }
    
    return minPWM + 10;  // Add safety margin
}

void calibrateMotorTrim() {
    Serial.println(F("\n--- Motor Trim Calibration ---"));
    Serial.println(F("This test checks if robot goes straight"));
    
    Serial.println(F("Running straight test..."));
    leftMotor.setSpeed(150);
    rightMotor.setSpeed(150);
    
    delay(3000);  // Run for 3 seconds
    
    leftMotor.stop();
    rightMotor.stop();
    
    Serial.println(F("Did robot go straight? (y/n):"));
    while (!Serial.available()) { delay(10); }
    
    char response = Serial.read();
    Serial.flush();
    
    if (response != 'y' && response != 'Y') {
        Serial.println(F("Which direction did it drift?"));
        Serial.println(F("  'l' - Drifted left"));
        Serial.println(F("  'r' - Drifted right"));
        
        while (!Serial.available()) { delay(10); }
        char direction = Serial.read();
        Serial.flush();
        
        int8_t trim = 0;
        if (direction == 'l' || direction == 'L') {
            trim = -5;  // Slow down left motor
            Serial.println(F("Applying left motor trim: -5"));
        } else if (direction == 'r' || direction == 'R') {
            trim = 5;   // Speed up left motor
            Serial.println(F("Applying left motor trim: +5"));
        }
        
        leftMotor.setTrim(trim);
    } else {
        Serial.println(F("Robot goes straight - no trim needed"));
    }
}