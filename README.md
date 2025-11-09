# Smart_Rover 🚘

An IoT-enabled autonomous rover designed for women's security and night patrolling.

## Features
- 4-wheeled rover with cameras, LiDAR, GPS, LoRa, LTE (SIM7600)
- Real-time obstacle avoidance and AI-based incident detection
- 4G LTE live video streaming
- Solar-powered continuous operation

## Project Structure
- `firmware/` → ESP32 rover control and sensors
- `backend_api/` → FastAPI backend for data collection
- `simulation/` → Gazebo/ROS simulation setup

## How to Run

### 1️⃣ Upload ESP32 firmware
Open `firmware/smart_rover_esp32.ino` in Arduino IDE and upload to your ESP32.

### 2️⃣ Run the backend API
```bash
pip install -r backend_api/requirements.txt
python backend_api/smart_rover_api.py
```

### 3️⃣ Run simulation (ROS)
```bash
roslaunch smart_rover simulation.launch
```

---
Developed by **Kowshika G.S**
