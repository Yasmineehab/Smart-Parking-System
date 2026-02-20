# Smart Parking System using Arduino

An automated parking management system designed to reduce congestion and manage car entry/exit efficiently using IR sensors and a Servo motor.

## 🛠️ Components Used
* Arduino Uno
* 2x IR Sensors (Entry & Exit)
* Servo Motor (Gate Control)
* LCD Display (I2C Module)
* Jumper Wires & Breadboard

## 🚀 Features
* **Real-time Monitoring:** Tracks available parking slots.
* **Automated Gate:** Opens when a car is detected and closes after passing.
* **Smart Display:** Shows "Welcome" with slot count or "Parking Full" message.

## 💻 Logic & Implementation
The system uses **C++** with the following logic:
1. **Entry:** If a car is detected at the entry IR and slots are available, the servo opens the gate and decrements the counter.
2. **Exit:** If a car is detected at the exit IR, the servo opens the gate and increments the counter.
3. **Safety:** The gate closes only after both sensors confirm the car has fully passed.
