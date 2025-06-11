#ifndef WORM_MOTOR_CONTROLLER_H
#define WORM_MOTOR_CONTROLLER_H

#include "Arduino.h"
#include "../config/robot_config.h"

/*
 * WormMotorController Class
 * Specialized for DC Worm Motors in Combat Robotics
 * Features: Deadband compensation, acceleration ramping, emergency stop
 */

class WormMotorController {
public:
    // Constructor
    WormMotorController(uint8_t pwmPin, uint8_t dir1Pin, uint8_t dir2Pin, 
                       uint8_t deadband = MOTOR_DEADBAND, int8_t trim = 0);
    
    // Initialization
    void begin();
    
    // Motor Control Methods
    void setSpeed(int16_t speed);           // Set motor speed (-255 to +255)
    void setSpeedSmooth(int16_t speed);     // Set speed with acceleration ramping
    void stop();                            // Immediate stop
    void emergencyStop();                   // Emergency stop (interrupt safe)
    void brake();                           // Active braking
    
    // Status Methods
    int16_t getCurrentSpeed() const;        // Get current motor speed
    bool isMoving() const;                  // Check if motor is moving
    bool isStopped() const;                 // Check if motor is stopped
    
    // Configuration Methods
    void setTrim(int8_t trim);              // Set motor trim (-50 to +50)
    void setDeadband(uint8_t deadband);     // Set minimum PWM threshold
    void setAcceleration(uint8_t accelRate); // Set acceleration rate
    
    // Calibration Methods
    void calibrate();                       // Auto-calibrate deadband
    void testMotor();                       // Motor functionality test

private:
    // Pin assignments
    uint8_t _pwmPin;
    uint8_t _dir1Pin;
    uint8_t _dir2Pin;
    
    // Motor parameters
    uint8_t _deadband;
    int8_t _trim;
    uint8_t _accelRate;
    
    // Current state
    int16_t _currentSpeed;
    int16_t _targetSpeed;
    bool _emergencyStopActive;
    
    // Internal methods
    void _setDirection(bool forward);
    void _setPWM(uint8_t pwmValue);
    uint8_t _applyDeadband(uint8_t rawPWM);
    int16_t _applyTrim(int16_t speed);
    void _updatePWMFrequency();
};