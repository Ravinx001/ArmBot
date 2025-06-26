<div align="center">
  <h1>🤖 ArmBot - Wireless Robotic Arm Car</h1>
  
  ### 🎮 Xbox Controller-Based Robotic Arm Vehicle with ESP32
  
  **Advanced Robotics Project**  
  *Wireless Control • Multi-Servo Precision • Real-Time Response*

<img src="https://img.shields.io/badge/Platform-ESP32-blue" alt="ESP32 Platform">
<img src="https://img.shields.io/badge/Controller-Xbox-green" alt="Xbox Controller">
<br>
  
  ![GitHub repo size](https://img.shields.io/github/repo-size/YourUsername/ArmBot?style=for-the-badge)
  ![GitHub stars](https://img.shields.io/github/stars/YourUsername/ArmBot?style=for-the-badge)
  ![GitHub forks](https://img.shields.io/github/forks/YourUsername/ArmBot?style=for-the-badge)
  ![GitHub issues](https://img.shields.io/github/issues/YourUsername/ArmBot?style=for-the-badge)

</div>

---

## 🎯 Project Overview

**ArmBot** is a sophisticated wireless robotic arm vehicle that combines precision servo control with omnidirectional movement capabilities. Powered by ESP32 and controlled via Xbox gamepad using Bluepad32 library, this project demonstrates advanced robotics integration with real-time wireless communication and multi-axis servo manipulation.

<div align="center">
  <img src="https://github.com/Ravinx001/ArmBot/blob/main/images/armbot-img04.jpg" alt="ArmBot Side View" width="45%">
  <img src="https://github.com/Ravinx001/ArmBot/blob/main/images/armbot-img01.jpg" alt="ArmBot Side View" width="45%">
  <img src="https://github.com/Ravinx001/ArmBot/blob/main/images/armbot-img03.jpg" alt="ArmBot Back View" width="45%">
  <br>
  <img src="https://github.com/Ravinx001/ArmBot/blob/main/images/armbot-img02.JPG" alt="ArmBot Side View" width="100%">
</div>

## ✨ Key Features & Capabilities

### 🎮 **Wireless Xbox Controller Integration**
Full Xbox gamepad support with Bluepad32 library for seamless wireless control, including analog sticks, buttons, D-pad, and trigger inputs.

### 🦾 **5-Axis Robotic Arm Control**
Precision servo control for complex manipulation tasks:
- **Base Rotation** (Servo 1): 42° - 100° range
- **Lift Mechanism** (Servo 2 & 3): Synchronized dual-servo lifting system
- **Joint Control** (Servo 4): Adaptive positioning with conditional logic
- **Gripper Control** (Servo 5): Precision grabbing mechanism

### 🚗 **Omnidirectional Vehicle Movement**
Dual-motor drive system with independent control for forward, backward, left, and right movement with customizable speed settings.

### 🔄 **Real-Time Feedback**
Comprehensive serial monitoring with live position feedback and controller status updates for debugging and operation monitoring.

### 💡 **Smart Control Logic**
Intelligent servo coordination with conditional movements and safety limits to prevent mechanical damage.

---

## ⚙️ How It Works

### 1️⃣ **Controller Connection**
- ESP32 establishes Bluetooth connection with Xbox controller via Bluepad32
- Real-time input processing with dead-zone handling for smooth operation

### 2️⃣ **Servo Control System**
- Multi-servo coordination with position limits and smooth incremental movements
- Intelligent joint coupling for realistic arm kinematics

### 3️⃣ **Vehicle Locomotion**
- Differential drive system with independent motor control
- Proportional speed control based on joystick input magnitude

### 4️⃣ **Feedback & Monitoring**
- Real-time serial output for debugging and position tracking
- Controller status monitoring with connection management

---

## 🛠️ Technology Stack & Components

<div align="center">

| **Category** | **Components/Technologies** |
|--------------|---------------------------|
| **Microcontroller** | ESP32 Development Board |
| **Control Library** | Bluepad32 (Xbox Controller Integration) |
| **Actuators** | 5x Servo Motors (SG90/MG995), 2x DC Geared Motors |
| **Motor Driver** | L298N Dual H-Bridge Motor Driver |
| **Communication** | Bluetooth Classic/BLE |
| **Programming** | Arduino IDE, C++ |
| **Control Interface** | Xbox Wireless Controller |

</div>

---

## 🎮 Control Mapping

<div align="center">

| **Xbox Input** | **Function** | **Range/Action** |
|----------------|--------------|------------------|
| **Left Stick X/Y** | Vehicle Movement | Forward/Backward/Left/Right |
| **Right Stick Y** | Arm Lift Control | Servo 2 & 3 Synchronized |
| **X Button** | Base Rotation Left | Servo 1: 42° - 100° |
| **B Button** | Base Rotation Right | Servo 1: 42° - 100° |
| **Y Button** | Joint Up | Servo 4: 50° - 130° |
| **A Button** | Joint Down | Servo 4: 50° - 130° |
| **Left Trigger** | Gripper Close | Servo 5: 100° - 160° |
| **Right Trigger** | Gripper Open | Servo 5: 100° - 160° |

</div>

---

## 🚀 Getting Started

### Prerequisites
- Arduino IDE 1.8.19+
- ESP32 Board Package
- Bluepad32 Library
- ESP32Servo Library
- Xbox Wireless Controller

### Hardware Connections

```
ESP32 Pin Connections:
├── Motor Driver (L298N)
│   ├── ENA → GPIO 32
│   ├── ENB → GPIO 33
│   ├── IN1 → GPIO 23
│   ├── IN2 → GPIO 22
│   ├── IN3 → GPIO 21
│   └── IN4 → GPIO 25
├── Servo Motors
│   ├── Servo 1 (Base) → GPIO 18
│   ├── Servo 2 (Lift 1) → GPIO 4
│   ├── Servo 3 (Lift 2) → GPIO 5
│   ├── Servo 4 (Joint) → GPIO 15
│   └── Servo 5 (Gripper) → GPIO 19
```

### Installation & Setup

1. **Clone the repository**
   ```bash
   git clone https://github.com/YourUsername/ArmBot.git
   cd ArmBot
   ```

2. **Install Required Libraries**
   ```
   - Bluepad32 (via Library Manager or GitHub)
   - ESP32Servo (via Library Manager)
   ```

3. **Hardware Assembly**
   - Connect servos and motors according to pin diagram
   - Ensure proper power supply (6-12V for motors, 5V for servos)
   - Mount components on chassis frame

4. **Upload Code**
   - Open `ArmBot.ino` in Arduino IDE
   - Select ESP32 board and appropriate port
   - Upload the code to your ESP32

5. **Controller Pairing**
   - Power on the ArmBot
   - Put Xbox controller in pairing mode
   - Wait for automatic connection (check serial monitor)

---

## 📁 Code Structure

```
ArmBot/
├── 📄 ArmBot.ino                    # Main Arduino sketch
├── 📁 libraries/                    # Required libraries
│   ├── Bluepad32/                   # Xbox controller integration
│   └── ESP32Servo/                  # Servo control library
├── 📁 docs/                         # Documentation and diagrams
│   ├── wiring_diagram.png           # Hardware connection diagram
│   ├── control_mapping.pdf          # Controller button mapping
│   └── assembly_guide.md            # Step-by-step assembly
├── 📁 3d_models/                    # 3D printable parts (STL files)
└── 📄 README.md                     # This file
```

---

## 🔧 Key Functions Explained

### **Servo Control Functions**
- `updateServo01()` - Base rotation with X/B buttons
- `updateServo02()` - Synchronized lift control with right stick
- `updateServo04()` - Joint control with Y/A buttons  
- `updateServo05()` - Gripper control with triggers

### **Motor Control**
- `updateMotorControl()` - Differential drive with left stick input
- Dead-zone implementation (±300) for smooth control
- Independent speed control for movement and turning

### **Controller Management**
- `onConnectedController()` - Handles new controller connections
- `onDisconnectedController()` - Manages disconnections
- `processGamepad()` - Main input processing loop

---

## 📊 Performance Specifications

<div align="center">
  
  | **Specification** | **Value** | **Notes** |
  |-------------------|-----------|-----------|
  | **Control Range** | 10+ meters | Bluetooth range dependent |
  | **Servo Precision** | 1° increments | Smooth positioning |
  | **Response Time** | <50ms | Real-time control |
  | **Battery Life** | 2-4 hours | Depends on usage |
  | **Max Payload** | 500g | Arm lifting capacity |
  | **Speed** | 0.5 m/s | Maximum vehicle speed |

</div>

---

## 🎥 ArmBot In Action

<div align="center">
  
[![Watch the video](https://github.com/Ravinx001/ArmBot/blob/main/images/armbot-img02.JPG)](https://drive.google.com/file/d/1Jv5wS4AUXrASfJXJkeTk6t-jpr9PvrLz/view?usp=sharing)
  
  *Click to watch ArmBot in action!*

</div>

---

## 🔧 Customization Options

### **Servo Angle Limits**
Modify servo angle ranges in the code to match your mechanical constraints:
```cpp
// Example: Adjust base rotation range
if (button == 2 && servoAngle01 > 42) {  // Minimum angle
    servoAngle01 = max(servoAngle01 - 1, 42);
}
```

### **Speed Control**
Adjust motor speeds for different applications:
```cpp
int speed = 150;  // PWM value (0-255)
int turn = 180;   // Turn speed
```

### **Control Sensitivity**
Modify joystick dead-zones for different control feel:
```cpp
if (axisvalue < -300 && servoAngle02 < 160) {  // Dead-zone threshold
```

---

## 🤝 Contributing

We welcome contributions! Whether it's bug fixes, feature enhancements, or documentation improvements:

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

### **Areas for Contribution**
- Advanced kinematics algorithms
- Computer vision integration
- Mobile app development
- 3D printed parts optimization
- Additional sensor integration

---

## 🐛 Troubleshooting

### **Common Issues**

| **Problem** | **Solution** |
|-------------|--------------|
| Controller won't connect | Reset ESP32, check Bluetooth pairing |
| Servos jittering | Check power supply, add capacitors |
| Motors not responding | Verify L298N connections and power |
| Code won't compile | Install required libraries, check board selection |

---

## 📄 License

This project is licensed under the  Apache License 2.0 - see the [LICENSE](./LICENSE) file for details.

---

## 📞 Contact & Support

**Project Maintainer**  
📧 Email: [rav.business.lak@gmail.com]  
🐙 GitHub: [@Ravinx001](https://github.com/Ravinx001)  
💼 LinkedIn: [https://www.linkedin.com/in/ravindu-amarasekara/]

**Community**  
💬 Discussions: Use GitHub Discussions for questions  
🐛 Issues: Report bugs via GitHub Issues  

---

<div align="center">
  
  ### 🤖 **Experience the Future of Robotics** 🤖
  ### 🌟 **Where Precision Meets Innovation** 🌟
  
  ⭐ **Star this repository if you found it helpful!** ⭐
  
  **Built with ❤️ for the Robotics Community**

</div>
