# Real-Time Pipe Flow and Leak Monitoring System (IoT)

This project implements an IoT-based real-time pipe flow and leak monitoring prototype using **NodeMCU ESP8266**, **water flow sensors**, **LED indicators**, and an **active buzzer**. It detects anomalies such as leaks, no-flow conditions, and transient states while providing a **live web dashboard** for monitoring.

---

## 📌 Table of Contents
- [Introduction](#introduction)
- [Problem Statement](#problem-statement)
- [Project Objectives](#project-objectives)
- [Project Scope](#project-scope)
- [System Features](#system-features)
- [Hardware Components](#hardware-components)
- [Schematic Diagram](#schematic-diagram)
- [Code Overview](#code-overview)
- [Implementation Steps](#implementation-steps)
- [Testing & Results](#testing--results)
- [How to Run](#how-to-run)

---

## 🧾 Introduction

The **Real-Time Pipe Flow and Leak Monitoring System** is designed to detect abnormal flow patterns in pipelines using IoT-enabled components. It continuously measures water flow at two points to identify leaks, no-flow conditions, and transient flow states. Data is transmitted wirelessly and displayed through an HTML/JavaScript-based dashboard hosted on the ESP8266.

This system is beneficial for **water distribution**, **industrial fluid transport**, and **environmental management**, making pipeline monitoring more efficient and sustainable.

---

## 🚨 Problem Statement

Water wastage due to hidden leaks, inefficient monitoring systems, and illegal pipe tampering is a major issue—especially in Sabah, where illegal tapping causes up to **60% revenue loss**. Manual monitoring methods often fail to detect leaks early.

This project provides a **real-time automated monitoring system** to:
- Detect leaks immediately  
- Reduce water wastage  
- Improve operational efficiency  
- Support environmental sustainability  

---

## 🎯 Project Objectives

1. **Design and Implement a Real-Time Monitoring System**  
   Using ESP8266 and dual flow sensors for continuous flow tracking.

2. **Achieve Accurate Anomaly Detection**  
   Identify leaks, no-flow conditions, and transient disturbances.

3. **Develop a Web-Based Dashboard**  
   Display real-time sensor data, alerts, and system status.

4. **Validate the Prototype Under Different Conditions**  
   Normal flow, no flow, and leak simulations.

---

## 📘 Project Scope

The system uses IoT sensors, wireless communication, and a web interface to detect pipeline anomalies. Key components include:
- ESP8266 NodeMCU (microcontroller + Wi-Fi)
- Water flow sensors
- LED + buzzer indicators
- Web dashboard for real-time visualization

The system focuses on early leak detection, remote monitoring, and accurate flow analysis.

---

## ✨ System Features

- 🔵 **Real-time flow monitoring**
- 🔔 **Leak detection with LED blinking + buzzer alarm**
- 🟡 **Transient flow stabilization logic**
- 🌐 **Live dashboard via ESP8266 web server**
- 📡 **Wireless communication**
- 🧪 **Tested under normal, leak, and no-flow scenarios**

---

## 🔧 Hardware Components

- NodeMCU ESP8266  
- 2× Water Flow Sensors (YF-S201)  
- Active Buzzer  
- Yellow LED (2-pin)  
- 1kΩ Resistor  
- Breadboard  
- Jumper Wires  

---

## 🔌 Schematic Diagram
*schematic_diagram.png*

---

## 🧠 Code Overview

The Arduino code handles:
- Pulse counting via hardware interrupts  
- Flow rate calculation  
- Leak detection logic  
- Transient delay filtering  
- Web server hosting  
- JSON API for real-time data  
- LED/Buzzer hardware signaling  

Key functions:
- `updateOutputs()`
- `handleSensorData()`
- `handleRoot()`
- `countPulseA()` / `countPulseB()`

---

## 🛠 Implementation Steps

### **1. Prepare Pipes**
- Create normal and leak-simulated pipes  
- Attach sensors securely using sealant  

### **2. Assemble Circuit**
- Connect sensors to D6 and D7  
- Buzzer to D8  
- LED + 1kΩ resistor to D5  

### **3. Upload Code**
- Set Wi-Fi SSID & password  
- Upload using Arduino IDE  
- Open Serial Monitor to get IP address  

### **4. Test Prototype**
Test 3 conditions:
- **Normal flow** → LED ON (no buzzer)  
- **Leak detected** → LED BLINK + buzzer ON  
- **No flow** → LED OFF + buzzer OFF  

---

## 🧪 Testing & Results

### ✔ Normal Flow  
- LED ON  
- No alarm  
- Stable flow difference ≤ 5 mL/sec  

### ✔ Leak Detected  
- Difference > 5 mL/sec  
- LED blinking  
- Buzzer activated  
- "ALERT: Leak detected!" shown on dashboard  

### ✔ No Flow  
- Both sensors < threshold  
- LED OFF  
- Dashboard displays "No flow detected"  

---

## ▶ How to Run

1. Install **Arduino IDE**  
2. Install ESP8266 board package  
3. Upload code to NodeMCU  
4. Connect to same Wi-Fi network  
5. Open Serial Monitor → copy ESP8266 IP  
6. Paste IP into browser  
7. View real-time dashboard  

---
