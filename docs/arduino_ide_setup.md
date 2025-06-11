# Arduino IDE Setup Instructions

## Menyediakan Arduino IDE untuk SKVe Sumo Robot

### 1. Download dan Install Arduino IDE

1. Download Arduino IDE dari: https://www.arduino.cc/en/software
2. Install Arduino IDE (versi 1.8.19 atau 2.0+)
3. Jalankan Arduino IDE

### 2. Board Manager Setup

1. Buka **Tools** → **Board** → **Boards Manager**
2. Cari "Arduino AVR Boards"
3. Install jika belum ada
4. Pilih **Tools** → **Board** → **Arduino Uno**

### 3. Port Configuration

1. Sambung Arduino Uno ke komputer via USB
2. Pilih **Tools** → **Port** → pilih port yang betul (biasanya COM3, COM4, dll)
3. Pastikan **Tools** → **Programmer** → **AVRISP mkII**

### 4. Library Dependencies

Robot ini menggunakan built-in libraries sahaja:
- `Arduino.h` - Standard Arduino functions
- `SoftwareSerial.h` - For HC-05 communication (built-in)

**Tiada external libraries diperlukan!** 

### 5. Project Setup dalam Arduino IDE

#### Method 1: Manual Setup
1. Buat folder baru: `C:\Users\[User]\Documents\Arduino\SKVe_Robot\`
2. Copy semua files dari `sumo_SKVe_ws\src\` ke folder tersebut
3. Copy folder `config\` dan `include\` ke dalam folder yang sama
4. Buka `sumo_robot_main.ino`

#### Method 2: Direct Open
1. Buka Arduino IDE
2. File → Open → Browse ke `sumo_SKVe_ws\src\sumo_robot_main.ino`
3. Arduino IDE akan prompt untuk create sketch folder - click Yes
4. Copy `config\` dan `include\` folders ke sketch folder

### 6. File Structure dalam Arduino IDE

```
SKVe_Robot/
├── sumo_robot_main.ino         # Main sketch file
├── config/
│   └── robot_config.h          # Configuration file
├── include/
│   ├── WormMotorController.h   # Motor control header
│   ├── BluetoothComm.h         # Bluetooth header
│   └── SafetySystem.h          # Safety system header
└── src/
    ├── WormMotorController.cpp # Motor implementation
    └── BluetoothComm.cpp       # Bluetooth implementation
```

**Note:** Arduino IDE akan recognize files dalam tabs automatically.

### 7. Compilation Settings

#### Optimize for Performance:
1. **Tools** → **Optimize** → **Fastest (-O3)**  *(Arduino IDE 2.0)*
2. **Tools** → **CPU Speed** → **16MHz** (default)

#### Memory Usage:
- **Program Memory Usage:** ~15-20KB (48-60% of 32KB)
- **Dynamic Memory:** ~800-1200 bytes (40-60% of 2KB)

### 8. Upload Process

#### Standard Upload:
1. **Disconnect HC-05** jika menggunakan Hardware Serial (pins 0,1)
2. Click **Upload** button atau Ctrl+U
3. Wait for "Done uploading"
4. **Reconnect HC-05** selepas upload

#### If Upload Fails:
1. Check correct board selection (Arduino Uno)
2. Check correct port selection
3. Disconnect semua external devices kecuali USB
4. Press reset button pada Arduino, then upload immediately

### 9. Serial Monitor Setup

1. **Tools** → **Serial Monitor** atau Ctrl+Shift+M
2. Set baud rate to **9600** (bottom right)
3. Set line ending to **Newline** atau **Both NL & CR**

### 10. Testing Setup

#### Quick Test Sequence:
1. Upload code ke Arduino
2. Open Serial Monitor
3. Check for initialization messages:
   ```
   =================================
   SKVe Sumo Robot - Competition Grade
   Expert Combat Robotics System
   =================================
   Initializing systems...
   Safety System... OK
   Motor Controllers... OK
   Bluetooth Communication... OK
   Robot initialization complete!
   ```

#### If Problems:
- **No Serial Output:** Check baud rate (9600)
- **Compilation Errors:** Check all files are dalam sketch folder
- **Upload Errors:** Check board dan port settings

### 11. Bluetooth Testing

#### HC-05 AT Command Mode:
1. Disconnect dari Arduino
2. Connect HC-05 pin EN/KEY to 3.3V
3. Power on HC-05
4. Use Serial Monitor dengan baud rate 38400
5. Test dengan command: `AT` (should reply `OK`)

#### Bluetooth App Testing:
1. Upload code dengan Bluetooth connected
2. Pair phone dengan HC-05 (default PIN: 1234)
3. Open Bluetooth terminal app
4. Send test command: `F` (should move forward)

### 12. Performance Verification

#### Check Loop Performance:
Enable `ENABLE_PERFORMANCE_MONITOR true` dalam config untuk check:
- Loop execution time (should be <1ms)
- Memory usage
- Command response time

#### Expected Performance:
- **Command Response:** <50ms
- **Loop Time:** <1000µs
- **Emergency Stop:** <1µs

### 13. Competition Mode Setup

Before competition:
1. Set `DEBUG_MODE false` untuk performance
2. Set `ENABLE_PERFORMANCE_MONITOR false`
3. Test all safety systems
4. Verify battery voltage monitoring
5. Test emergency stop functionality

### 14. Common Issues dan Solutions

| Issue | Solution |
|-------|----------|
| Code won't compile | Check all files dalam sketch folder |
| Motors don't move | Check pin connections dan power |
| Bluetooth not connecting | Verify HC-05 wiring dan pairing |
| Robot doesn't respond | Check emergency stop not triggered |
| Erratic movement | Check battery voltage dan motor connections |

### 15. Expert Tips

1. **Use tabs efficiently** - Arduino IDE shows all project files dalam tabs
2. **Backup your config** - Save custom robot_config.h separately  
3. **Version control** - Use Git untuk track changes
4. **Test incrementally** - Upload dan test each feature separately
5. **Monitor memory** - Check memory usage dalam compilation output

---

**Setup complete! Ready for competition programming!** 🏆

**Next Steps:**
1. Test basic movement commands
2. Calibrate motors using calibration.ino
3. Test Bluetooth communication
4. Practice dengan Android app
5. Ready untuk competition! 🤖