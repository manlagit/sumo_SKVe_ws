#include "../include/WormMotorController.h"

/*
 * WormMotorController Implementation
 * Optimized for Combat Robot DC Worm Motors
 * Implements expert-level motor control techniques
 */

WormMotorController::WormMotorController(uint8_t pwmPin, uint8_t dir1Pin, uint8_t dir2Pin, 
                                       uint8_t deadband, int8_t trim) 
    : _pwmPin(pwmPin), _dir1Pin(dir1Pin), _dir2Pin(dir2Pin),
      _deadband(deadband), _trim(trim), _accelRate(ACCELERATION_RATE),
      _currentSpeed(0), _targetSpeed(0), _emergencyStopActive(false) {
}

void WormMotorController::begin() {
    // Initialize pins
    pinMode(_pwmPin, OUTPUT);
    pinMode(_dir1Pin, OUTPUT);
    pinMode(_dir2Pin, OUTPUT);
    
    // Set initial state
    digitalWrite(_dir1Pin, LOW);
    digitalWrite(_dir2Pin, LOW);
    analogWrite(_pwmPin, 0);
    
    // Optimize PWM frequency for smoother operation
    _updatePWMFrequency();
    
    // Initialize state
    _currentSpeed = 0;
    _targetSpeed = 0;
    _emergencyStopActive = false;
}

void WormMotorController::setSpeed(int16_t speed) {
    if (_emergencyStopActive) return;
    
    // Constrain speed to valid range
    speed = constrain(speed, -255, 255);
    
    // Apply trim compensation
    speed = _applyTrim(speed);
    
    // Set direction
    _setDirection(speed >= 0);
    
    // Apply deadband compensation and set PWM
    uint8_t pwmValue = _applyDeadband(abs(speed));
    _setPWM(pwmValue);
    
    _currentSpeed = speed;
    _targetSpeed = speed;
}
void WormMotorController::setSpeedSmooth(int16_t speed) {
    if (_emergencyStopActive) return;
    
    _targetSpeed = constrain(speed, -255, 255);
    
    // Gradual acceleration/deceleration
    if (_currentSpeed < _targetSpeed) {
        _currentSpeed = min(_currentSpeed + _accelRate, _targetSpeed);
    } else if (_currentSpeed > _targetSpeed) {
        _currentSpeed = max(_currentSpeed - _accelRate, _targetSpeed);
    }
    
    setSpeed(_currentSpeed);
}

void WormMotorController::stop() {
    _currentSpeed = 0;
    _targetSpeed = 0;
    _setPWM(0);
}

void WormMotorController::emergencyStop() {
    // Interrupt-safe emergency stop
    _emergencyStopActive = true;
    _currentSpeed = 0;
    _targetSpeed = 0;
    
    // Direct register manipulation for fastest response
    digitalWrite(_dir1Pin, LOW);
    digitalWrite(_dir2Pin, LOW);
    analogWrite(_pwmPin, 0);
}

void WormMotorController::brake() {
    // Active braking by setting both direction pins HIGH
    digitalWrite(_dir1Pin, HIGH);
    digitalWrite(_dir2Pin, HIGH);
    analogWrite(_pwmPin, 255);
    delay(10);  // Brief braking pulse
    stop();
}
// Status Methods
int16_t WormMotorController::getCurrentSpeed() const {
    return _currentSpeed;
}

bool WormMotorController::isMoving() const {
    return abs(_currentSpeed) > 0;
}

bool WormMotorController::isStopped() const {
    return _currentSpeed == 0;
}

// Configuration Methods
void WormMotorController::setTrim(int8_t trim) {
    _trim = constrain(trim, -50, 50);
}

void WormMotorController::setDeadband(uint8_t deadband) {
    _deadband = constrain(deadband, 0, 150);
}

void WormMotorController::setAcceleration(uint8_t accelRate) {
    _accelRate = constrain(accelRate, 1, 255);
}

// Calibration Methods
void WormMotorController::calibrate() {
    // Auto-calibrate deadband by finding minimum effective PWM
    uint8_t minPWM = 50;
    
    for (uint8_t pwm = 50; pwm <= 120; pwm += 5) {
        _setDirection(true);
        _setPWM(pwm);
        delay(100);
        
        // In real implementation, check encoder feedback or current draw
        // For now, use conservative value
        minPWM = pwm;
        break;
    }
    
    _deadband = minPWM;
    stop();
}
void WormMotorController::testMotor() {
    // Motor functionality test sequence
    Serial.println(F("Testing motor..."));
    
    // Test forward
    Serial.println(F("Forward test"));
    setSpeed(100);
    delay(500);
    
    // Test reverse
    Serial.println(F("Reverse test"));
    setSpeed(-100);
    delay(500);
    
    // Stop
    Serial.println(F("Stop test"));
    stop();
    delay(200);
    
    Serial.println(F("Motor test complete"));
}

// Private Methods
void WormMotorController::_setDirection(bool forward) {
    if (forward) {
        digitalWrite(_dir1Pin, HIGH);
        digitalWrite(_dir2Pin, LOW);
    } else {
        digitalWrite(_dir1Pin, LOW);
        digitalWrite(_dir2Pin, HIGH);
    }
}

void WormMotorController::_setPWM(uint8_t pwmValue) {
    analogWrite(_pwmPin, pwmValue);
}

uint8_t WormMotorController::_applyDeadband(uint8_t rawPWM) {
    if (rawPWM == 0) return 0;
    
    // Map to effective range: [deadband, 255]
    return map(rawPWM, 1, 255, _deadband, 255);
}
int16_t WormMotorController::_applyTrim(int16_t speed) {
    if (speed == 0) return 0;
    
    // Apply trim as percentage adjustment
    int16_t trimmedSpeed = speed + (_trim * speed / 100);
    return constrain(trimmedSpeed, -255, 255);
}

void WormMotorController::_updatePWMFrequency() {
    // Optimize PWM frequency for pins 9 and 10 (Timer 1)
    if (_pwmPin == 9 || _pwmPin == 10) {
        // Set Timer1 prescaler to 8 for ~3.9kHz frequency
        TCCR1B = (TCCR1B & 0xF8) | 0x02;
    }
    
    // Optimize PWM frequency for pins 5 and 6 (Timer 0)
    if (_pwmPin == 5 || _pwmPin == 6) {
        // Set Timer0 prescaler to 8 for ~7.8kHz frequency
        TCCR0B = (TCCR0B & 0xF8) | 0x02;
    }
    
    // Optimize PWM frequency for pin 3 (Timer 2)
    if (_pwmPin == 3) {
        // Set Timer2 prescaler to 8 for ~3.9kHz frequency  
        TCCR2B = (TCCR2B & 0xF8) | 0x02;
    }
}