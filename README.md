---

# Real-Time Pipe Flow and Leak Monitoring System (IoT)

This project implements an IoT-based real-time pipe flow and leak monitoring prototype using **NodeMCU ESP8266**, **water flow sensors**, **LED indicators**, and an **active buzzer**. It detects anomalies such as leaks, no-flow conditions, and transient states while providing a **live web dashboard** for monitoring.

---

## 📌 Table of Contents

* [Introduction](#introduction)
* [Problem Statement](#problem-statement)
* [Project Objectives](#project-objectives)
* [Project Scope](#project-scope)
* [System Features](#system-features)
* [Hardware Components](#hardware-components)
* [Schematic Diagram](#schematic-diagram)
* [Code Overview](#code-overview)
* [Implementation Steps](#implementation-steps)
* [Testing & Results](#testing--results)
* [How to Run](#how-to-run)

---

## Introduction

🧾 The **Real-Time Pipe Flow and Leak Monitoring System** is designed to detect abnormal flow patterns in pipelines using IoT-enabled components. It continuously measures water flow at two points to identify leaks, no-flow conditions, and transient flow states. Data is transmitted wirelessly and displayed through an HTML/JavaScript-based dashboard hosted on the ESP8266.

This system is beneficial for **water distribution**, **industrial fluid transport**, and **environmental management**, making pipeline monitoring more efficient and sustainable.

---

## Problem Statement

🚨 Water wastage due to hidden leaks, inefficient monitoring systems, and illegal pipe tampering is a major issue—especially in Sabah, where illegal tapping causes up to **60% revenue loss**. Manual monitoring often fails to detect leaks early.

This project provides a **real-time automated monitoring system** to:

* Detect leaks immediately
* Reduce water wastage
* Improve operational efficiency
* Support environmental sustainability

---

## Project Objectives

🎯

1. **Design and Implement a Real-Time Monitoring System**
2. **Achieve Accurate Anomaly Detection**
3. **Develop a Web-Based Dashboard**
4. **Validate the Prototype Under Different Conditions**

---

## Project Scope

📘
The system uses IoT sensors, wireless communication, and a web interface to detect pipeline anomalies. Components include:

* ESP8266 NodeMCU
* Water flow sensors
* LED + buzzer
* Web dashboard

---

## System Features

✨

* Real-time flow monitoring
* Leak detection with LED + buzzer
* Transient flow stabilization logic
* Web-based dashboard
* Wi-Fi enabled ESP8266 communication
* Tested across multiple flow conditions

---

## Hardware Components

🔧

* NodeMCU ESP8266
* 2× Water Flow Sensors
* Active Buzzer
* Yellow LED
* 1kΩ Resistor
* Breadboard
* Jumper Wires

---

## Schematic Diagram

<img width="990" height="503" alt="Image" src="https://github.com/user-attachments/assets/76b5bbfa-7086-4837-a7eb-1303507b012c" />

---

## Code Overview

🧠 The Arduino code includes:

* Pulse counting via interrupts
* Flow calculation
* Leak detection logic
* A transient delay system
* Web server + JSON API
* LED & buzzer signaling

---

## Implementation Steps

🛠

### 1. Prepare Pipes

* Normal pipe + drilled leak-simulated pipe
* Attach sensors with sealant

### 2. Assemble Circuit

* Sensors → D6 & D7
* Buzzer → D8
* LED (with resistor) → D5

### 3. Upload Code

* Update Wi-Fi settings
* Upload via Arduino IDE
* Get IP from Serial Monitor

### 4. Test Prototype

* Normal → LED ON
* Leak → LED blink + buzzer ON
* No flow → LED OFF

---

## Testing & Results

🧪

### ✔ Normal Flow

Stable flow → LED ON

### ✔ Leak Detected

Flow difference > 5 mL/sec
→ LED BLINK + buzzer

### ✔ No Flow

Flow < threshold
→ LED OFF

---

## How to Run

▶

1. Install Arduino IDE
2. Install ESP8266 Board Manager
3. Upload code
4. Connect to Wi-Fi
5. Get ESP8266 IP
6. Open IP in browser
7. View real-time dashboard

---
