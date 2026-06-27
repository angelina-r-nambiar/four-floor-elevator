# Four-Floor Elevator Control System

An Arduino-based control system that simulates or controls an elevator servicing four distinct floors (Floors 0, 1, 2, and 3). 

## 🚀 Features
* **4-Floor Tracking:** Smoothly processes input requests across four levels.
* **Dual Display Feedback:** * A **Seven-Segment Display** for an instant, clear floor number readout.
  * An **LCD Display** to show detailed status updates (e.g., "Moving Up", "Floor 2").
* **Push-Button Interface:** Simple, direct floor-calling mechanism.

## 🛠️ Hardware Components
* **Arduino Board** (Microcontroller)
* **Seven-Segment Display**
* **16x2 LCD Display**
* **Push Buttons** (for floor selection)
* **Connecting Wires**
* **HC-SR04 ultrasonic distance sensor**

## 📁 Project Structure
* `src/` : Contains the main `.ino` Arduino sketch.
* `README.md` : Project documentation.

  ## 📹 Working Demo
  https://github.com/user-attachments/assets/8b129124-b722-4018-98ae-aeb03ee649f9

  ## 🧠 Proximity Sensor & Logic
The system includes an **HC-SR04 Ultrasonic Sensor** placed near the entrance. When a user steps within range, the sensor triggers an interrupt or state change, prompting the I2C LCD to display a custom welcome message before activating the floor-selection buttons.

### 📌 Pin Mapping Table

| Component | Arduino Pin | Description |
| :--- | :--- | :--- |
| **Ultrasonic Trig** | Pin 3 | Sends the sonic burst |
| **Ultrasonic Echo** | Pin 4 | Receives the sonic reflection |
| **Buttons (0 to 3)** | Pins 12, 13, 9, 8 | Floor request inputs |
| **Seven-Segment** | A0, A1, A2, A3, 2, 10, 11 | Displays floor number (A-G) |
| **I2C LCD Display** | A4 (SDA), A5 (SCL) | Displays status & welcome messages |

* **Smart Proximity Welcome:** Uses an ultrasonic sensor to detect an approaching user and print a dynamic greeting on the LCD display.


  
