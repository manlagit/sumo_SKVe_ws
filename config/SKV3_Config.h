/*
 * SKV3 Combat Robot Configuration File
 * Professional Settings for Competition Use
 * 
 * This file contains all configurable parameters for expert-level
 * combat robot control systems based on competition standards.
 */

#ifndef SKV3_CONFIG_H
#define SKV3_CONFIG_H

// ===== HARDWARE CONFIGURATION =====

// Motor Driver Pin Assignments (SKV Shield Standard)
#define MOTOR_LEFT_PWM          9     // ENA - Left motor PWM control
#define MOTOR_LEFT_DIR1         8     // IN1 - Left motor direction A
#define MOTOR_LEFT_DIR2         7     // IN2 - Left motor direction B
#define MOTOR_RIGHT_PWM         10    // ENB - Right motor PWM control
#define MOTOR_RIGHT_DIR1        6     // IN3 - Right motor direction A
#define MOTOR_RIGHT_DIR2        5     // IN4 - Right motor direction B

// Weapon and Safety Systems
#define WEAPON_PIN              3     // Weapon motor control pin
#define EMERGENCY_STOP_PIN      2     // Hardware emergency stop (interrupt)
#define LED_STATUS_PIN          13    // Status LED indicator
#define BUZZER_PIN              4     // Audio alert (optional)

// Bluetooth Communication
#define BT_RX_PIN               4     // Bluetooth module RX pin
#define BT_TX_PIN               12    // Bluetooth module TX pin
#define BT_ENABLE_PIN           11    // HC-05 enable pin for AT commands

// ===== PERFORMANCE PARAMETERS =====

// Motor Control Constants (Competition Optimized)
#define WORM_MOTOR_DEADBAND     80    // Minimum PWM for worm motor movement
#define MAX_MOTOR_SPEED         255   // Maximum PWM value (0-255)
#define MOTOR_ACCELERATION_RATE 50    // PWM units per update cycle
#define PWM_FREQUENCY_HZ        3900  // Optimized PWM frequency

// Communication Settings (Expert Standards)
#define BLUETOOTH_BAUD_RATE     9600  // Standard HC-05 baud rate
#define SERIAL_DEBUG_BAUD       115200 // High-speed debug serial
#define COMMAND_BUFFER_SIZE     32    // Maximum command length
#define RESPONSE_TARGET_MS      50    // Target response time under 50ms

// Safety Protocol Constants (Competition Requirements)
#define SAFETY_TIMEOUT_MS       500   // Maximum time without signal
#define EMERGENCY_RESPONSE_US   1000  // Emergency stop response time (microseconds)
#define WATCHDOG_TIMEOUT_MS     1000  // Backup watchdog timer
#define LOW_VOLTAGE_CUTOFF_MV   9000  // 3.0V per cell for 3S LiPo

// ===== ROBOT BEHAVIOR SETTINGS =====

// Movement Speeds (Optimized for Combat)
#define SPEED_FORWARD           200   // Forward movement speed
#define SPEED_BACKWARD          180   // Reverse movement speed  
#define SPEED_TURN              150   // Turning speed
#define SPEED_ATTACK            255   // Maximum attack speed
#define SPEED_PRECISION         120   // Slow precision movement

// Weapon Control
#define WEAPON_SPINUP_TIME_MS   1000  // Time to reach full weapon speed
#define WEAPON_COOLDOWN_TIME_MS 2000  // Mandatory cooldown period
#define WEAPON_MAX_RUN_TIME_MS  30000 // Maximum continuous run time

// ===== ADVANCED CONFIGURATION =====

// Protocol Selection
#define ENABLE_SINGLE_CHAR_COMMANDS   true   // 'F', 'B', 'L', 'R', 'S', 'W'
#define ENABLE_SPEED_COMMANDS         true   // 'F180', 'B120', etc.
#define ENABLE_DIFFERENTIAL_COMMANDS  true   // 'M150200' format
#define ENABLE_PACKET_PROTOCOL        true   // Error-checked packets
#define ENABLE_BINARY_PROTOCOL        false  // High-performance binary

// Safety Features
#define ENABLE_HARDWARE_ESTOP         true   // Physical emergency stop
#define ENABLE_SOFTWARE_WATCHDOG      true   // Software watchdog timer
#define ENABLE_VOLTAGE_MONITORING     true   // Battery voltage protection
#define ENABLE_CURRENT_LIMITING       false  // Motor current protection
#define ENABLE_THERMAL_PROTECTION     false  // Temperature monitoring

// Competition Compliance
#define COMPETITION_MODE              true   // Enable all safety features
#define ALLOW_WEAPON_CONTROL          true   // Permit weapon operation
#define REQUIRE_FAILSAFE              true   // Mandatory failsafe systems
#define LOG_ALL_COMMANDS              false  // Command logging (debug only)

// ===== EXPERT TUNING PARAMETERS =====

// Motor Control Tuning
#define DIFFERENTIAL_GAIN             1.0    // Differential drive sensitivity
#define TURN_RATE_MULTIPLIER          0.8    // Turn speed adjustment
#define ACCELERATION_SMOOTHING        0.3    // Motor acceleration filter
#define DECELERATION_MULTIPLIER       1.5    // Faster deceleration

// Communication Optimization  
#define COMMAND_TIMEOUT_MS            100    // Individual command timeout
#define BLUETOOTH_RETRY_COUNT         3      // Command retry attempts
#define SIGNAL_STRENGTH_THRESHOLD     -80    // Minimum RSSI (dBm)
#define PACKET_LOSS_THRESHOLD         5      // Max consecutive lost packets

// Performance Monitoring
#define ENABLE_PERFORMANCE_METRICS    false  // Performance measurement
#define LOOP_TIME_TARGET_US           20000  // Target loop time (20ms)
#define COMMAND_LATENCY_WARNING_MS    75     // Latency warning threshold
#define CPU_USAGE_WARNING_PERCENT     85     // CPU usage warning

// ===== CALIBRATION VALUES =====

// Motor Calibration (Measured Values)
#define LEFT_MOTOR_OFFSET             0      // Left motor speed offset
#define RIGHT_MOTOR_OFFSET            5      // Right motor speed offset  
#define MOTOR_MIN_EFFECTIVE_PWM       75     // Minimum effective PWM
#define MOTOR_MAX_SAFE_PWM            240    // Maximum safe continuous PWM

// Sensor Calibration
#define VOLTAGE_DIVIDER_RATIO         3.3    // Battery voltage measurement
#define CURRENT_SENSOR_SENSITIVITY    100    // mV per Amp
#define TEMPERATURE_OFFSET_C          2.0    // Temperature sensor offset

#endif // SKV3_CONFIG_H