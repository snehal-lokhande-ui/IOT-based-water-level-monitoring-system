# 💧 IoT-Based Water Level Monitoring System

An intelligent water level detection and motor control system designed using ultrasonic sensors and ESP32. It enables **real-time monitoring**, **automatic pump control**, and **alert notifications**, making it ideal for residential, agricultural, and industrial water tanks.

---

## 📌 Project Overview

This project uses an **ultrasonic sensor** to detect the water level inside a tank. Based on predefined thresholds, it automatically turns the motor ON/OFF and alerts users via an LCD and buzzer. The data is also sent to a cloud platform (like ThingSpeak) for IoT-based monitoring.

---

## ⚙️ Features

- 🚰 Automatic tank filling control (ON/OFF pump)
- 📶 Real-time level monitoring with IoT (ThingSpeak)
- ⚠️ Alerts for overflow, dry run, and low levels
- 📟 LCD Display for local feedback
- 🔔 Buzzer indication
- 💡 LED indicators for water level stages

---

## 🧠 Hardware Components

- **ESP32 / NodeMCU**
- **Ultrasonic Sensor (HC-SR04)**
- **Relay Module (for motor control)**
- **16x2 LCD Display (I2C or Parallel)**
- **Buzzer**
- **LEDs**
- **Power Supply (5V/12V depending on relay & motor)**

---

## 🔌 Circuit Connections
| Component       | ESP32 Pin |
|-----------------|-----------|
| Ultrasonic TRIG | D23       |
| Ultrasonic ECHO | D22       |
| Relay           | D21       |
| LCD (I2C) SDA   | D21       |
| LCD (I2C) SCL   | D22       |
| Buzzer          | D19       |
| LED Indicators  | D18, D5, D4 (level LEDs) |

*Note: Pin numbers can be adjusted based on hardware setup.*

---

## 🌐 IoT Integration

**Platform:** ThingSpeak  
**Fields Sent:**
- Distance / Water Level (%)
- Pump Status (ON/OFF)

**Connectivity:** ESP32 connects to Wi-Fi and uploads data every few seconds to ThingSpeak using API key.

---

## 🧾 Working Logic

1. Ultrasonic sensor measures water level in cm.
2. If level < threshold → Motor ON
3. If level > max limit → Motor OFF
4. Data uploaded to ThingSpeak
5. Buzzer & LEDs indicate critical conditions (overflow / dry)

---

## 📁 File Structure

📦 water-level-monitoring
┣ 📜 water_monitoring.ino # Arduino code
┣ 📜 README.md # Project info
┗ 📸 images/ # Circuit diagrams, tank photos, etc.

---

## 📸 Project Images

> Add your prototype or circuit photos here:
> ![Prototype](images/prototype.jpg)

---

## 🔧 Future Enhancements

- Mobile app for level alerts
- Water usage analytics dashboard
- Multi-tank support
- GSM-based SMS alert integration

---

## 👩‍💻 Author

**Snehal Navanath Lokhande**  
Electronics & Telecommunication, COEP Technological University  
[LinkedIn](https://www.linkedin.com/in/snehal-lokhande-376b27357)

---

## 📄 License

This project is licensed under the [MIT License](https://choosealicense.com/licenses/mit/).

