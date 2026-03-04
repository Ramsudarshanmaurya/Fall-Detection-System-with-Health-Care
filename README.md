# 🏥 Fall Detection System with Healthcare Monitoring
### Arduino | MPU6050 | MAX30100 | GSM SIM900A | GPS Neo-6M | IoT

<div align="center">

![Project](https://img.shields.io/badge/Project-Fall%20Detection%20System-red?style=for-the-badge&logo=arduino)
![Arduino](https://img.shields.io/badge/MCU-Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![IoT](https://img.shields.io/badge/Domain-IoT%20%7C%20Healthcare-blue?style=for-the-badge)
![Published](https://img.shields.io/badge/Research-Published%20IJRPR-green?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-96%25-brightgreen?style=for-the-badge)

</div>

---

## 📄 Research Publication

> **Published in International Journal of Research Publication and Reviews (IJRPR)**
> Vol 6, Issue 4, April 2025
> 📄 Research Paper: `Research-Paper/IJRPR43113.pdf`

---

## 📌 Project Overview

An **IoT-based wearable device** for real-time fall detection with **96% accuracy**, specifically designed for **elderly safety monitoring**. The system automatically sends emergency alerts with GPS location to caregivers via GSM when a fall is detected.

- 🎯 96% fall detection accuracy
- 💓 Real-time Heart Rate & SpO2 monitoring
- 📍 GPS location-based SMS emergency alerts
- 👴 Designed for elderly safety
- 📡 I2C communication for multiple sensors

---

## 📁 Project Structure

```
Fall-Detection-System-with-Health-Care/
├── 📂 Code/
│   └── fall_detection_system_with_heal...  ← Arduino source code
├── 📂 Circuit-Diagram/
│   └── Screenshot 2026-03-03...            ← Circuit diagram
├── 📂 Project Report/
│   └── fall detection system.pdf           ← Full project report
├── 📂 Research-Paper/
│   └── IJRPR43113.pdf                      ← Published research paper
└── 📄 README.md
```

---

## 🛠️ Hardware Required

| Component | Specification | Function |
|-----------|--------------|----------|
| Arduino Uno/Nano | ATmega328P, 5V | Main microcontroller |
| MPU6050 | 3-axis Accel + Gyro, I2C | Fall detection |
| MAX30100 | Heart Rate + SpO2, I2C | Health monitoring |
| GSM SIM900A | Quad-band, AT commands | Emergency SMS |
| GPS Neo-6M | NMEA output, UART | Location tracking |
| Li-Po Battery | 3.7V, 2000mAh | Power supply |
| Jumper Wires | Male-Female | Connections |

---

## 🔌 Pin Connections

```
Arduino              MPU6050 (I2C)
──────────────────────────────────
A4  (SDA)   ──►     SDA
A5  (SCL)   ──►     SCL
5V          ──►     VCC
GND         ──►     GND
D2          ──►     INT (Interrupt)

Arduino              MAX30100 (I2C)
──────────────────────────────────
A4  (SDA)   ──►     SDA   (shared bus)
A5  (SCL)   ──►     SCL   (shared bus)
3.3V        ──►     VCC
GND         ──►     GND

Arduino              GSM SIM900A
──────────────────────────────────
D10 (TX)    ──►     RX
D11 (RX)    ──►     TX
GND         ──►     GND
12V         ──►     Power

Arduino              GPS Neo-6M
──────────────────────────────────
D3  (TX)    ──►     RX
D4  (RX)    ──►     TX
5V          ──►     VCC
GND         ──►     GND
```

> ⚠️ **MPU6050 aur MAX30100 dono I2C bus pe hain — Common SDA/SCL use hoti hai!**

---

## ⚙️ Circuit Diagram

![Circuit Diagram](Circuit-Diagram/Screenshot%202026-03-03%20025402....png)

---

## 🧠 Working Principle

### Fall Detection Algorithm
```
1. MPU6050 se 3-axis acceleration data
   400Hz sampling rate pe read karo

2. Resultant acceleration calculate karo:
   a = √(ax² + ay² + az²)

3. Threshold check:
   IF a > 2.5g (sudden impact)
   AND post-fall a < 0.3g (lying still)
   THEN → FALL DETECTED! 🚨

4. Accuracy: 96% (tested on 50+ fall simulations)
```

### Health Monitoring
```
MAX30100 continuously monitor karta hai:
→ Heart Rate (BPM)
→ SpO2 (Blood Oxygen %)
→ Data Serial Monitor pe display hota hai
```

### Emergency Alert System
```
Fall detect hone pe:
1. GPS Neo-6M se coordinates lo
   (Latitude, Longitude)

2. GSM SIM900A se SMS bhejo:
   "FALL DETECTED!
    Location: lat, long
    Heart Rate: XX BPM
    SpO2: XX%
    Google Maps: maps.google.com/..."

3. Caregiver ke phone pe
   instantly SMS pahunch jaata hai!
```

---

## 💻 Software Setup

### Step 1 — Arduino IDE Install Karo
[arduino.cc/en/software](https://www.arduino.cc/en/software)

### Step 2 — Libraries Install Karo
```
Sketch → Include Library → Manage Libraries

Install karo:
✅ MPU6050 by Electronic Cats
✅ MAX30100lib by OXullo Intersecans
✅ TinyGPS++ by Mikal Hart
✅ SoftwareSerial (built-in)
```

### Step 3 — Caregiver Number Set Karo
`fall_detection_system.ino` mein:
```c
String caregiverNumber = "+91XXXXXXXXXX"; // Number yahan likho
```

### Step 4 — Upload & Test!
```
1. Arduino pe Upload karo
2. Serial Monitor kholo (9600 baud)
3. Sensor data dekho
4. Device hath mein pakad ke
   suddenly neeche karo → Test!
```

---

## 📊 Results & Testing

| Test | Result |
|------|--------|
| Fall Detection Accuracy | **96%** |
| False Positive Rate | 4% |
| SMS Alert Delay | < 5 seconds |
| Heart Rate Accuracy | ±2 BPM |
| SpO2 Accuracy | ±1% |
| Battery Life | ~8 hours continuous |
| Fall Simulations Tested | 50+ |

---

## 🔬 Tech Stack

```
Hardware:  Arduino | MPU6050 | MAX30100 | SIM900A | Neo-6M
Software:  C++ | Arduino IDE
Protocol:  I2C | UART | AT Commands | NMEA
Domain:    IoT | Healthcare | Embedded Systems | Wearables
```

---

## 📰 Research Publication

| Field | Details |
|-------|---------|
| **Journal** | International Journal of Research Publication and Reviews |
| **ISSN** | 2582-7421 |
| **Volume** | 6, Issue 4 |
| **Month** | April 2025 |
| **Paper ID** | IJRPR43113 |
| **Topic** | Fall Detection System with Healthcare Monitoring |

📄 Full paper: `Research-Paper/IJRPR43113.pdf`

---

## 🔮 Future Enhancements

- [ ] ESP32 + WiFi — Cloud data upload (ThingSpeak/Firebase)
- [ ] OLED Display — Real-time vitals display on device
- [ ] Android App — Live monitoring dashboard
- [ ] ML Model — Better fall detection with Edge Impulse
- [ ] Temperature sensor — Body temperature monitoring
- [ ] BLE — Wireless data to smartphone

---

## 👨‍💻 Developer

**Ramsudarshan Maurya**
📍 Buddha Institute of Technology, Gorakhpur
🎓 B.Tech ECE — AKTU Lucknow (2025)
🏢 Intern — UniConverge Technologies, Noida
📄 Published Researcher — IJRPR Journal

---

## 📄 License

MIT License — freely use, modify and distribute with attribution.

---

<div align="center">

**⭐ Agar helpful laga toh Star zaroor do! ⭐**

Made with ❤️ by Ramsudarshan Maurya

</div>
