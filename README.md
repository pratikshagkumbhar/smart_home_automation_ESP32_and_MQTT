# 🏠 Smart Home Automation using ESP32 & MQTT

Real-time IoT system for controlling **LED** and **Fan**, and monitoring **Temperature**, **Humidity**, and **Motion** using **ESP32**, **MQTT**, and a **Web Dashboard**.

---

## 🚀 Live Demo

🔗 **Dashboard:** [https://pratikshagkumbhar.github.io/iot/](https://pratikshagkumbhar.github.io/iot/)
🎥 **YouTube Demo:** ([https://youtu.be/DopDysZniz8?si=nKiSGLQ-L_4HXQbt](https://youtu.be/DopDysZniz8?si=grXDSIO-GqjuxkQG))

---

## ✨ Features

* 🌡 Temperature & Humidity Monitoring
* 👀 Motion Detection
* 💡 LED ON/OFF (Manual + Auto)
* 🌀 Fan ON/OFF (Manual + Auto based on temperature)
* 🖥 Real-time MQTT Dashboard
* 🎤 Voice Commands (LED/Fan control)
* 📟 OLED Display Status

---

## 🛠 Components

* ESP32
* DHT11 Sensor
* PIR Sensor
* Relay Module (5V)
* 12V DC Fan
* LED
* OLED SH1106 (I2C)
* Jumper Wires, Breadboard

---

## 📡 MQTT Topics

### **Publish**

* `home/room1/temperature`
* `home/room1/humidity`
* `home/room1/motion`
* `home/room1/leds/status`
* `home/room1/fan/status`

### **Subscribe**

* `home/room1/leds/control`
* `home/room1/fan/control`

---

## 🧩 ESP32 Code

Your complete ESP32 code is available inside the project folder.
(Place it in `/code/esp32.ino` or similar)

---

## 🌐 Dashboard Code

Dashboard HTML file is included in your repository.
(Place it in `/dashboard/index.html`)

---

## ⚙️ How It Works

1. ESP32 reads **DHT11 + PIR** sensors
2. Sends data to MQTT broker (`broker.hivemq.com`)
3. Dashboard receives live data via WebSocket
4. User controls devices via buttons or voice commands
5. ESP32 switches LED/Fan using GPIO + Relay

---
