# SKVe Robot Wiring Guide

## Pin Connections untuk SKV Shield

### Motor Connections (L298N/L293D Compatible)

#### Left Motor (Motor A)
```
Arduino Pin  | SKV Shield | Function
-------------|------------|------------------
Pin 9        | ENA        | Left Motor Speed (PWM)
Pin 8        | IN1        | Left Motor Direction 1
Pin 7        | IN2        | Left Motor Direction 2
```

#### Right Motor (Motor B)  
```
Arduino Pin  | SKV Shield | Function
-------------|------------|------------------
Pin 10       | ENB        | Right Motor Speed (PWM)
Pin 6        | IN3        | Right Motor Direction 1
Pin 5        | IN4        | Right Motor Direction 2
```

### HC-05 Bluetooth Module

#### Standard Connection (SoftwareSerial)
```
HC-05 Pin    | Arduino Pin | Function
-------------|-------------|------------------
VCC          | 5V          | Power (5V)
GND          | GND         | Ground
TXD          | Pin 11      | Bluetooth TX → Arduino RX
RXD          | Pin 12      | Bluetooth RX ← Arduino TX
```

#### Alternative (Hardware Serial) - Untuk prestasi maksimum
```
HC-05 Pin    | Arduino Pin | Function
-------------|-------------|------------------
VCC          | 5V          | Power (5V)
GND          | GND         | Ground
TXD          | Pin 0 (RX)  | Hardware Serial RX
RXD          | Pin 1 (TX)  | Hardware Serial TX
```
**Note:** Hardware serial konfliks dengan USB programming. Disconnect semasa upload code.

### Safety dan Status

#### Emergency Stop Button
```
Component    | Arduino Pin | Function
-------------|-------------|------------------
Push Button  | Pin 2       | Emergency Stop (Interrupt)
Pull-up Res.| Pin 2       | 10kΩ to 5V
```

#### Status LEDs
```
Component    | Arduino Pin | Function
-------------|-------------|------------------
Status LED   | Pin 13      | Robot Status (Built-in LED)
Power LED    | Pin A0      | Power Indicator
```

### Sensor Connections (Optional)

#### Battery Monitoring
```
Component     | Arduino Pin | Function
--------------|-------------|------------------
Voltage Div.  | Pin A1      | Battery Voltage Monitor
Current Sens. | Pin A2      | Motor Current Monitor
```

### Power Connections

#### LiPo Battery (11.1V 3S)
```
Battery Wire  | Connection  | Function
--------------|-------------|------------------
Red (+)       | SKV Shield  | Main Power Input
Black (-)     | SKV Shield  | Ground
Balance Conn. | Charger     | Balance Charging
```

#### Power Distribution
```
Component     | Power Source | Voltage
--------------|-------------|------------------
Arduino Uno   | SKV Shield  | 5V (Regulated)
HC-05 Module  | Arduino 5V  | 5V
Motors        | SKV Shield  | 11.1V (Direct)
Servos        | Arduino 5V  | 5V
```

## Wiring Diagram ASCII

```
                    Arduino Uno
                 ┌─────────────────┐
    Emergency -> │2              13│ -> Status LED
                 │3              12│ -> HC-05 TXD
                 │4              11│ <- HC-05 RXD  
      Motor R1 <-│5              10│ -> Motor R PWM
      Motor R2 <-│6               9│ -> Motor L PWM
      Motor L2 <-│7               8│ -> Motor L1
                 │               A0│ -> Power LED
                 │               A1│ <- Battery Voltage
                 │               A2│ <- Current Sensor
                 │                 │
                 │   5V  GND   VIN │
                 └─────┬───┬───┬───┘
                       │   │   │
                 ┌─────┴───┴───┴─────┐
                 │    SKV Shield     │
                 │                   │
                 │  M1+  M1-  M2+  M2-│
                 └────┬───┬───┬───┬───┘
                      │   │   │   │
               Left Motor │   │ Right Motor
                      │   │   │   │
                    Red Blk Red Blk
```

## Expert Wiring Tips

### 1. Noise Reduction
- **Capacitors 100nF** across motor terminals untuk reduce EMI
- **Twisted pair wires** untuk motor connections
- **Separate analog/digital grounds** jika possible

### 2. Power Management
- **Thick wires (18-20 AWG)** untuk motor power
- **Fuse protection** pada main power line
- **Low ESR capacitors** near switching circuits

### 3. Combat Robot Standards
- **Secure connections** - use solder + heat shrink
- **Strain relief** pada all cable connections
- **Redundant emergency stop** wiring
- **Battery disconnect** accessible dari luar

### 4. Performance Optimization
- **Short signal paths** untuk high-frequency PWM
- **Ground plane** untuk noise immunity
- **Filter capacitors** near IC power pins

## Troubleshooting

### Motor Issues
- **Check polarity** - swap motor wires jika berputar salah arah
- **Voltage drop** - gunakan thicker wires
- **PWM noise** - add motor capacitors

### Bluetooth Issues  
- **Baud rate mismatch** - ensure Arduino dan app sama baud rate
- **Range problems** - check antenna orientation
- **Pairing issues** - reset HC-05 dengan AT commands

### Power Issues
- **Brown-out resets** - check battery voltage under load
- **Noise coupling** - separate motor dan logic grounds
- **Overcurrent** - check motor stall conditions

## Safety Checklist

- [ ] Emergency stop button accessible
- [ ] Battery disconnect functional  
- [ ] No exposed high-voltage connections
- [ ] Secure motor mounting
- [ ] Strain relief pada all cables
- [ ] Fuse/breaker protection
- [ ] Low voltage cutoff configured
- [ ] All connections soldered dan insulated

**Remember: Safety first dalam combat robotics!** 🛡️