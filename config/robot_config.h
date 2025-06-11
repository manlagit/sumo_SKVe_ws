#ifndef ROBOT_CONFIG_H
#define ROBOT_CONFIG_H

/*
 * SKVe Sumo Robot Configuration
 * Optimized for Combat Robot Competition Standards
 * Based on Expert Combat Robotics Guidelines
 */

// ============================================================================
// HARDWARE PIN ASSIGNMENTS (SKV Shield Compatible)
// ============================================================================

// Motor Control Pins (L298N/L293D Compatible)
#define MOTOR_LEFT_PWM      9    // ENA pin for left motor speed control
#define MOTOR_LEFT_DIR1     8    // IN1 pin for left motor direction
#define MOTOR_LEFT_DIR2     7    // IN2 pin for left motor direction

#define MOTOR_RIGHT_PWM     10   // ENB pin for right motor speed control  
#define MOTOR_RIGHT_DIR1    6    // IN3 pin for right motor direction
#define MOTOR_RIGHT_DIR2    5    // IN4 pin for right motor direction

// Weapon Control (Optional for advanced sumo designs)
#define WEAPON_PWM          3    // Weapon motor PWM control
#define WEAPON_DIR1         4    // Weapon direction pin 1
#define WEAPON_DIR2         12   // Weapon direction pin 2

// Safety and Status
#define EMERGENCY_STOP_PIN  2    // Hardware interrupt pin (INT0)
#define STATUS_LED_PIN      13   // Built-in LED for status indication
#define POWER_LED_PIN       A0   // External power indicator LED

// Communication
#define BLUETOOTH_RX        0    // Hardware serial RX (USB conflicts during programming)
#define BLUETOOTH_TX        1    // Hardware serial TX (USB conflicts during programming)
// Alternative SoftwareSerial pins if needed:
#define BT_SOFT_RX          11   // SoftwareSerial RX for HC-05
#define BT_SOFT_TX          12   // SoftwareSerial TX for HC-05

// Sensor Pins (Future expansion)
#define VOLTAGE_SENSE_PIN   A1   // Battery voltage monitoring
#define CURRENT_SENSE_PIN   A2   // Motor current monitoring

// ============================================================================
// PERFORMANCE PARAMETERS (Competition Optimized)
// ============================================================================

// Motor Control Constants
#define MOTOR_DEADBAND      80   // Minimum PWM to overcome static friction
#define MOTOR_MAX_SPEED     255  // Maximum PWM value
#define ACCELERATION_RATE   50   // PWM units per cycle for smooth ramping
#define MOTOR_RIGHT_OFFSET  5    // Calibration offset for motor matching

// Speed Presets for Different Maneuvers
#define SPEED_FORWARD       200  // Standard forward movement
#define SPEED_TURN          150  // Turning speed for maneuverability  
#define SPEED_ATTACK        255  // Maximum attack speed
#define SPEED_RETREAT       180  // Retreat/defensive speed

// PWM Frequency Optimization (3.9kHz for smoother operation)
#define PWM_FREQ_PRESCALER  2    // Timer prescaler for optimal frequency

// ============================================================================
// COMMUNICATION SETTINGS
// ============================================================================

#define BLUETOOTH_BAUD      9600    // Standard HC-05 baud rate
#define BLUETOOTH_BAUD_FAST 115200  // High-performance baud rate
#define COMMAND_BUFFER_SIZE 32      // Buffer size for incoming commands
#define COMMAND_TIMEOUT     50      // Command parsing timeout (ms)

// ============================================================================
// SAFETY PROTOCOL CONSTANTS (Competition Requirements)
// ============================================================================

// Timeout Settings
#define RADIO_TIMEOUT       500     // Radio signal timeout (ms)
#define WATCHDOG_TIMEOUT    1000    // Backup watchdog timeout (ms)
#define EMERGENCY_RESPONSE  1       // Emergency stop response time (ms)

// Battery Safety (3S LiPo = 11.1V nominal)
#define LOW_VOLTAGE_CUTOFF  9000    // 3.0V per cell (mV)
#define LOW_VOLTAGE_WARNING 9900    // 3.3V per cell (mV)
#define VOLTAGE_DIVIDER_RATIO 3.0   // For voltage sensing circuit

// Weapon Safety Timers
#define WEAPON_SPINUP_TIME    1000  // Weapon spin-up delay (ms)
#define WEAPON_COOLDOWN_TIME  2000  // Weapon cooldown period (ms)
#define WEAPON_MAX_RUN_TIME   30000 // Maximum continuous run time (ms)

// ============================================================================
// ROBOT BEHAVIOR SETTINGS
// ============================================================================

// Movement Characteristics
#define DIFFERENTIAL_GAIN   1.0     // Differential drive sensitivity
#define TURN_RATE_MULTIPLIER 0.8    // Turn rate scaling factor
#define MIN_EFFECTIVE_PWM   75      // Minimum PWM for reliable movement

// Competition Modes
#define SUMO_MODE_DEFENSIVE false   // Defensive vs aggressive behavior
#define AUTO_ATTACK_ENABLED false   // Automatic attack on object detection
#define RETREAT_ON_EDGE     true    // Retreat behavior at ring edge

// ============================================================================
// ADVANCED CONFIGURATION OPTIONS
// ============================================================================

// Feature Enables
#define ENABLE_PACKET_PROTOCOL  true    // Enable packet-based communication
#define ENABLE_CHECKSUM         true    // Enable command checksums
#define ENABLE_PERFORMANCE_MONITOR false // Disable by default for competition
#define ENABLE_SENSOR_FUSION    false   // Future sensor integration
#define ENABLE_TELEMETRY        false   // Disable telemetry for competition

// Debug and Testing
#define DEBUG_MODE              false   // Disable debug output for performance
#define ENABLE_MOTOR_TEST       true    // Enable startup motor test
#define ENABLE_COMMUNICATION_TEST true  // Enable Bluetooth connectivity test

// Protocol Support
#define SUPPORT_SINGLE_CHAR     true    // 'F', 'B', 'L', 'R', 'S'
#define SUPPORT_SPEED_COMMANDS  true    // 'F180', 'B120'
#define SUPPORT_DIFFERENTIAL    true    // 'M150200'
#define SUPPORT_PACKET_PROTOCOL true    // '!05M15020099#'

// ============================================================================
// CALIBRATION VALUES
// ============================================================================

// Motor Calibration
#define LEFT_MOTOR_TRIM     0       // Trim value for left motor (-50 to +50)
#define RIGHT_MOTOR_TRIM    0       // Trim value for right motor (-50 to +50)
#define MOTOR_DEADBAND_LEFT 80      // Individual deadband for left motor
#define MOTOR_DEADBAND_RIGHT 85     // Individual deadband for right motor

// Sensor Calibration  
#define VOLTAGE_CALIBRATION 1.0     // Voltage sensor calibration factor
#define CURRENT_CALIBRATION 1.0     // Current sensor calibration factor

// Timing Calibration
#define LOOP_DELAY_MS       10      // Main loop delay for consistent timing
#define SENSOR_UPDATE_RATE  100     // Sensor update frequency (ms)

#endif // ROBOT_CONFIG_H