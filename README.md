# Smart Warehouse Security & Monitoring System using IoT and Firebase

## Project Overview
This project implements a smart IoT-based warehouse access control and environmental monitoring system designed for agricultural warehouses.

The system uses:
- ESP32 microcontroller
- RFID access control
- DHT11 temperature and humidity monitoring
- Servo motor door automation
- Firebase Realtime Database
- Android monitoring application

The system improves warehouse security and protects crops from environmental damage.

---

## Key Features

RFID-based role access control  
Real-time temperature and humidity monitoring  
Cloud data storage using Firebase  
Android app for remote monitoring  
Unauthorized access detection  
Cyber attack detection using honeypot system  
Real-time alert system with buzzer

---

## Hardware Components

ESP32 Microcontroller  
MFRC522 RFID Readers (2)  
DHT11 Sensors (2)  
Servo Motors (2)  
Buzzer  
Wi-Fi Network

---

## Software Components

Arduino IDE  
Firebase Realtime Database  
Android Application  
ESP32 Firmware

---

## System Workflow

1 RFID card is scanned  
2 ESP32 verifies UID  
3 Door opens if authorized  
4 Environmental data collected  
5 Data uploaded to Firebase  
6 Android app displays live data  
7 Alerts triggered if conditions unsafe

---

## Cyber Security Feature

The system includes a lightweight IoT honeypot that detects:

Port scanning attacks  
Brute force login attempts  
HTTP flood attempts

Attack information is logged into Firebase.

---

## Firebase Database Structure

warehouse1
logs
status

warehouse2
logs
status

---

## Future Improvements

SMS alerts  
Push notifications  
Solar-powered system  
Automatic fan control  
Cloud dashboard

---

## Author
Harini P M


