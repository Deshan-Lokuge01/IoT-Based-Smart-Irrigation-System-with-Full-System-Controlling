<div align="center">
  <table>
  <tr>
    <td width="60%" valign="top">

## 🌿 Smart Irrigation System 🌱  
**IoT-Enabled Precision Agriculture Solution**

- Real-time soil moisture monitoring
- Automated water control
- Dual dashboard interfaces (local + cloud)
- Crop-specific irrigation algorithms
- Energy efficient design

    </td>
    <td width="40%" align="center">
      <img src="https://media.licdn.com/dms/image/v2/D4D12AQEM2SmEYNXoxQ/article-cover_image-shrink_720_1280/article-cover_image-shrink_720_1280/0/1736334584453?e=2147483647&v=beta&t=I2-OJwx4zs17o1JM7l_rCYGvs2AJkmpUEXVSpM3xGUs" width="400"/>
    </td>
  </tr>
</table>
</div>

<div align="center">
  <strong>A cutting-edge IoT solution revolutionizing agriculture 🌍</strong><br>
  
  #
  
  Monitor, optimize, and grow with precision for sustainable farming. Designed for crops like cabbage, this system ensures water efficiency and thriving harvests using real-time data and automation.
</div>

# 

<div align="center">
    <img src="https://img.shields.io/badge/Platform-ThingsBoard-blue">
  <img src="https://img.shields.io/badge/Microcontroller-ESP32-green">
  <img src="https://img.shields.io/badge/Sensor%20Network-LoRa%20WAN-yellow">
  <img src="https://img.shields.io/badge/Water%20Savings-30%25-brightgreen">
</div>

---


## 🚀 Quick Start

The **Smart Irrigation System** is an IoT-powered marvel under the Smart Agriculture umbrella. It transforms farming by enabling real-time monitoring and optimization of irrigation, ensuring crops flourish with minimal waste. Built for farmers and enterprises, this platform blends innovation with sustainability to maximize yields and revenue.

---

## ✨ Features

- **🌧️ Remote Monitoring**: Keep tabs on soil moisture and water conditions from anywhere.
- **🧠 AI-Powered Insights**: Leverage predictions, crop analytics, and harvest management for smarter decisions.

---

## 🌟 Why This Project?

### 📜 The Story
Water is life, but traditional irrigation often squanders it. Surface irrigation, while ancient and simple, risks over- or under-watering without real-time data. Our IoT system uses sensors and automation to perfect water delivery, making every drop count.

### 🎯 Our Mission
Precision is key for water-hungry crops like cabbage, which suffer from root diseases if mismanaged. This system:
- Delivers **just-right** water doses using live sensor data.
- Integrates with **ThingsBoard Cloud** for seamless monitoring, alerts, and control via a sleek dashboard.
- Boosts crop quality and saves water through automation with human oversight.

---

## 🥬 Crop Focus: Cabbage

Cabbage, a Sri Lankan favorite, thrives in the cool highlands of Nuwara-Eliya, Badulla, and Kandy.

### ☁️ Climate Needs
- **Sweet Spot**: 15°C–20°C.
- **Watch Out**: Above 25°C harms quality.
- **Pro Tip**: Plant in cooler months for lush, high-quality heads.

### 🌱 Soil Needs
- **Type**: Fertile, well-drained loamy soils.
- **pH**: 6.0–6.8.
- **Prep**: Boost with compost or manure; plow and harrow for seedlings.

### 💧 Water Needs
- **Weekly**: 25–30 mm.
- **Best Method**: Drip or sprinklers for even flow.
- **Careful**: Overwatering invites root diseases.

---

## 🔧 Tools & Tech

### 🚿 Irrigation Setup
- **Canals & Channels**: Concrete or lined for smooth water flow.
- **Gates & Valves**: Fine-tune water distribution.
- **Field Design**: Raised beds or furrows tailored for cabbage.

### 📡 Sensors & Monitoring
- **Soil Moisture Sensors**: Guide irrigation timing.
- **Flow Meters**: Track water usage.
- **Weather Sensors**: Adapt to changing conditions.

### 🔌 Integration & Automation
- **Hardware**:
  - Lay out canals, gates, valves, and pumps.
  - Wire up power supply and sensors (moisture, flow, weather).
- **Control System**:
  - Pick a microcontroller (ESP32, Arduino, Raspberry Pi).
  - Code algorithms for sensor-driven irrigation.
  - Add Wi-Fi, GSM, or LoRa for remote access.

### 💻 Software Stack
- **Microcontroller Code**:
  - Read sensor data (soil, weather).
  - Control valves based on thresholds.
  - Sync with ThingsBoard.
- **App Development**:
  - Set up ThingsBoard on cloud or local server.
  - Push sensor data via MQTT/HTTP.
  - Build dashboards for real-time insights.

**Core Tech**: ESP32, soil moisture sensors, flow sensors, ThingsBoard Cloud.

---

## 🏗️ System Blueprint

### 🎮 Control System
Relays and flow meters orchestrate water flow, responding to ThingsBoard dashboard commands. Relays toggle valves at set soil moisture levels, while flow meters display live water rates for precise control.

**Parts List**:
- ESP32 (38-pin)
- 4-Relay Module
- Solenoids (x4)
- Flow Sensor
- LM2596 Adjustable Buck Converter (x2)
- AMS1117 12V-to-5V Converter
- Logic Level Converter
- Power Modules (x3)

**Schematic**:
<p align="center">
  <img src="https://github.com/Deshan-Lokuge01/IoT-Based-Smart-Irrigation-System-with-Full-System-Controlling/blob/main/Schemetic_View_of_Control_System.jpg" alt="Control System Schematic" />
</p>

**Circuit Build**:
<p align="center">
  <img src="https://github.com/Deshan-Lokuge01/IoT-Based-Smart-Irrigation-System-with-Full-System-Controlling/blob/main/Control_System_on_Dot_Board.jpg" alt="Control Circuit" width="650"/>
</p>

### 🌍 Soil Sensor Circuit
Soil sensors capture real-time moisture data, relaying it to ThingsBoard at regular intervals. High or low moisture triggers relays to adjust irrigation, ensuring crops stay perfectly hydrated.

**Parts List**:
- ESP32 (38-pin)
- MAX485 TTL Module
- Soil Sensor
- LM2596 Adjustable Buck Converter
- AMS1117 12V-to-5V Converter
- Power Modules (x2)

**Schematic**:
<p align="center">
  <img src="https://github.com/Deshan-Lokuge01/IoT-Based-Smart-Irrigation-System-with-Full-System-Controlling/blob/main/Schemetic_View_of_Soil_Sensor_Circuit.jpg" alt="Soil Sensor Schematic" />
</p>

**Circuit Build**:
<p align="center">
  <img src="https://github.com/Deshan-Lokuge01/IoT-Based-Smart-Irrigation-System-with-Full-System-Controlling/blob/main/Soil_Sensor_Circuit_on_Dot_Board.jpg" alt="Soil Sensor Circuit" width="500"/>
</p>

---

## 💾 Code & Dashboards

### 🛠️ Software Overview
Powered by **Arduino IDE** for hardware and **ThingsBoard Cloud** for the interface, this system:
- Tracks soil moisture and water flow in real time.
- Automates irrigation with sensor-driven logic.
- Visualizes data on dynamic dashboards to optimize water use and crop health.

### 📊 ThingsBoard Dashboard
The "Smart Irrigation System" dashboard brings data to life with these widgets:
1. Soil moisture percentage.
2. Real-time flow rate.
3. Soil moisture trends (graph).
4. Flow sensor trends (graph).
5. Daily water usage (liters).
6. Device status (online/offline).
7. Solenoid controls (on/off).
8. Daily water consumption log.
9. Soil moisture threshold alerts.
10. Critical alarms:
    - Water usage > 100L.
    - Soil moisture outside `SoilMin` or `SoilMax`.

**Dashboard Snapshot**:
<p align="center">
  <img src="https://github.com/Deshan-Lokuge01/IoT-Based-Smart-Irrigation-System-with-Full-System-Controlling/blob/main/ThingsBoard_DashBoard_View.jpg" alt="ThingsBoard Dashboard" width="700"/>
</p>

---

## ⚖️ Calibration

### 🌱 Soil Sensor Tuning
**Steps**:
1. Dry soil to 0% moisture.
2. Divide 0–100% into intervals; estimate water needs.
3. Weigh a soil sample.
4. Add calculated water, mix, and reweigh.
5. Note sensor readings from ThingsBoard.
6. Calculate actual moisture and log in Excel.
7. Repeat across intervals.
8. Graph sensor vs. actual values to derive a calibration equation.

**Note**: Started with dry soil (not wet-then-dried) due to limited drying tools.

### 💧 Flow Sensor Tuning
**Steps**:
1. Fill tank to 3/4.
2. Run water through pipes.
3. Open all solenoids; measure 0.2L with a stopwatch.
4. Record dashboard’s calculated liters.
5. Log sensor vs. actual values in Excel.
6. Repeat for 3, 2, and 1 solenoid(s), taking multiple readings.
7. Graph results to derive a calibration equation.

---

## 🏆 Final Prototype

<p align="center">
  <img src="https://github.com/Deshan-Lokuge01/IoT-Based-Smart-Irrigation-System-with-Full-System-Controlling/blob/main/ProtoType_2.jpg" alt="Final Prototype" width="600"/>
</p>

---

## 🌏 Future Vision

Cabbage farming in Sri Lanka’s highlands shines with fertile soils and smart irrigation. This system saves water, boosts yields, and empowers small farmers. Paired with organic soil care, it delivers top-tier crops sustainably.

### 🚀 What’s Next?
- **Mobile App**: Guide farmers on water, soil, and crop management in real time.
- **More Sensors**: Monitor broader environmental factors.
- **Scalability**: Adapt for diverse crops and regions.

---

<p align="center">
  <strong>Built with 💦 and 🌿 for a thriving planet.</strong>
</p>

---
---
