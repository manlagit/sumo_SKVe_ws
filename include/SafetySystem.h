#ifndef SAFETY_SYSTEM_H
#define SAFETY_SYSTEM_H

#include "Arduino.h"
#include "../config/robot_config.h"

/*
 * SafetySystem Class
 * Competition-grade safety protocols for combat robots
 * Multi-layer safety architecture with redundant protection
 */

class SafetySystem {
public:
    // Constructor
    SafetySystem();
    
    // Initialization
    void begin();
    void attachEmergencyStop(void (*callback)());
    
    // Safety Monitoring
    void update();                          // Call in main loop
    bool isSafeToOperate();                // Overall safety status
    void checkTimeouts();                  // Check communication timeouts
    void checkBatteryVoltage();           // Monitor battery levels
    void checkEmergencyStop();            // Check emergency stop state
    
    // Timeout Management
    void resetCommunicationTimeout();     // Reset radio timeout
    bool isCommunicationTimeout();        // Check if communication lost
    void setRadioTimeout(unsigned long timeout);
    
    // Battery Management
    void updateBatteryVoltage(float voltage);
    float getBatteryVoltage();
    bool isLowVoltage();
    bool isCriticalVoltage();
    
    // Emergency Procedures
    void triggerEmergencyStop();          // Software emergency stop
    void clearEmergencyStop();           // Clear emergency state
    bool isEmergencyActive();            // Check emergency status
    
    // Status and Diagnostics
    void printStatus();                  // Print safety status
    String getStatusString();            // Get status as string
    
    // Weapon Safety (for advanced designs)
    bool isWeaponSafe();
    void startWeaponSpinup();
    void stopWeapon();
    bool isWeaponSpunUp();

private:
    // Timeout tracking
    unsigned long _lastCommandTime;
    unsigned long _radioTimeout;
    unsigned long _watchdogTimeout;
    
    // Battery monitoring
    float _batteryVoltage;
    bool _lowVoltageWarning;
    bool _criticalVoltage;
    
    // Emergency stop state
    volatile bool _emergencyStopActive;
    volatile bool _hardwareEmergencyStop;
    
    // Weapon safety
    unsigned long _weaponStartTime;
    bool _weaponSpinupComplete;
    bool _weaponRunning;
    
    // Internal methods
    void _initializeInterrupts();
    float _readBatteryVoltage();
    void _updateStatusLED();
    
    // Static interrupt handler
    static void _emergencyStopISR();
    static SafetySystem* _instance;
};

// Safety status codes
enum SafetyStatus {
    SAFETY_OK = 0,
    SAFETY_LOW_VOLTAGE = 1,
    SAFETY_CRITICAL_VOLTAGE = 2,
    SAFETY_COMMUNICATION_TIMEOUT = 4,
    SAFETY_EMERGENCY_STOP = 8,
    SAFETY_WEAPON_UNSAFE = 16
};

#endif // SAFETY_SYSTEM_H