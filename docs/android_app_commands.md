# SKVe Sumo Robot - Android App Commands

## Arahan Standard untuk Expert Combat Robot

Berdasarkan kajian mendalam tentang Combat Robot Bluetooth Control Systems, berikut adalah format arahan yang expert gunakan:

### 1. SINGLE CHARACTER COMMANDS (Paling mudah)
```
F = Maju (Forward)
B = Undur (Backward) 
L = Belok kiri (Left)
R = Belok kanan (Right)
S = Berhenti (Stop)
A = Serangan (Attack mode - kelajuan maksimum)
E = Emergency Stop
? = Status robot
```

### 2. SPEED COMMANDS (Dengan kawalan kelajuan)
```
F180 = Maju pada kelajuan 180 (0-255)
B120 = Undur pada kelajuan 120
L100 = Belok kiri pada kelajuan 100
R150 = Belok kanan pada kelajuan 150
```

### 3. DIFFERENTIAL DRIVE (Kawalan motor berasingan)
```
M150200 = Motor kiri 150, motor kanan 200
M255000 = Motor kiri penuh, motor kanan stop (putar kiri)
M000255 = Motor kiri stop, motor kanan penuh (putar kanan)
```

### 4. PACKET PROTOCOL (Expert level dengan checksum)
```
!05M15020099# = Packet dengan checksum untuk kebolehpercayaan
Format: !<length><command><data><checksum>#
```

## Aplikasi Android Yang Disyorkan:

### 1. **Dabble by STEMpedia** (TERBAIK untuk pemula)
- Interface gamepad yang mudah
- Sokongan semua format arahan
- Monitoring sambungan built-in
- Download: Play Store "Dabble"

### 2. **Bluetooth RC Car Controller**
- Dioptimumkan untuk robot beroda
- Interface differential drive
- Kawalan kelajuan sliding
- Download: Play Store "Bluetooth RC Car"

### 3. **Bluetooth Terminal** (Untuk expert)
- Hantar arahan manual
- Tengok response real-time
- Custom command macros
- Download: Play Store "Bluetooth Terminal"

## Setup Bluetooth Module HC-05:

### Optimisasi Prestasi Expert:
```
AT+UART=115200,0,0  (Upgrade dari 9600 ke 115200 baud - 12x lebih laju)
AT+NAME=SKVe_SUMO    (Nama robot)
AT+PSWD=9876         (Password keselamatan)
AT+CMODE=0           (Slave mode)
```

## Strategy Pertempuran untuk Robot Lawan:

### 1. **Aggressive Mode:**
```
A  = Serangan terus (kelajuan 255)
```

### 2. **Tactical Movements:**
```
F200  = Maju sederhana untuk positioning
L150  = Turn cepat untuk dodge
R150  = Counter-attack turn
```

### 3. **Emergency Maneuvers:**
```
B255  = Retreat pantas
S     = Stop segera untuk regrouping
```

### 4. **Advanced Tactics:**
```
M255100  = Ramming attack (kiri pantas, kanan sederhana)
M100255  = Flanking maneuver (kanan pantas, kiri sederhana)
M255255  = Full forward assault
M000000  = Complete stop untuk strategy
```

## Keselamatan Competition:

- **Timeout:** Robot akan stop automatik selepas 500ms tanpa signal
- **Emergency Stop:** Tekan 'E' atau butang hardware untuk stop segera
- **Battery Monitor:** Robot akan warning bila battery lemah
- **Failsafe:** Semua motor akan stop jika kehilangan signal

## Tips Expert untuk Competition:

1. **Gunakan 'A' untuk serangan awal** - kelajuan maksimum untuk push power
2. **'?' untuk check status** sebelum match
3. **Latih muscle memory untuk 'E'** - emergency stop mesti cepat
4. **Gunakan differential drive M commands** untuk precision movement
5. **Test latency dengan packet protocol** untuk timing critical

Robot ini dibangunkan menggunakan standard expert combat robotics dengan response time <50ms untuk competitive advantage!