# Smart Parking System with ESP32 and SG90 Servo

This project involves creating a simple smart parking system using an ESP32 microcontroller, an SG90 microservo, an infrared sensor, and an LCD screen to display parking status. The system detects when a car enters or exits a parking spot and controls a servo to open and close the barrier accordingly.

## Components Used

### 1. SG90 Micro Servo
**Description**: A compact micro servo ideal for applications requiring precise position control. It operates with a voltage range of 4.8V to 6V and provides a rotation range of 0° to 180°. The lightweight design, with a maximum torque of 1.8 kg·cm at 5V, makes it suitable for small mechanisms like barriers or controlled movement systems.  
**Specs**:  
- Voltage: 4.8V to 6V  
- Torque: 1.8 kg·cm at 5V  
- Rotation range: 0° to 180°

![image](https://github.com/user-attachments/assets/b1efd6ea-9656-45b1-9b05-41fedd25c86c)


### 2. FC51 Infrared Sensor
**Description**: A compact infrared obstacle detection device that operates with a voltage range of 3.3V to 5V. It has an adjustable detection range from 2 cm to 30 cm. The sensor includes an emitter and receiver IR, and its digital output simplifies integration with microcontrollers to detect the presence or absence of objects.  
**Specs**:  
- Voltage: 3.3V to 5V  
- Detection range: 2 cm to 30 cm

![image](https://github.com/user-attachments/assets/608f2ef6-9cc8-446e-ac23-00c5c8deb13d)


### 3. LCD Screen (16x2)
**Description**: A 16x2 LCD screen used to display the parking lot status, including messages about car entries and exits and available parking spaces. It is controlled via I2C communication for easy integration with the ESP32.

![image](https://github.com/user-attachments/assets/55065169-1081-43cb-9c3f-968b67a59e75)


### 4. ESP32
**Description**: A versatile microcontroller with Wi-Fi and Bluetooth capabilities, perfect for IoT projects. The ESP32 is used in this project to read sensor inputs, control the servo, and display information on the LCD screen.

![image](https://github.com/user-attachments/assets/2daca45d-032c-414c-8065-4d3cacb71dfc)


### 5. Jumper Wires
**Description**: Flexible wires used for making connections between components like the ESP32, sensors, and the servo.

![image](https://github.com/user-attachments/assets/461ecd5e-c48a-482f-aec2-86449d8ec808)


## Circuit Connections

### Infrared Sensors (FC51):
- Sensor A (Entrance) → GPIO 15 (Sensor Input Pin)
- Sensor B (Exit) → GPIO 23 (Sensor Input Pin)

### SG90 Micro Servo:
- Servo signal → GPIO 19 (Servo Control Pin)
- Power (VCC) → 5V
- Ground (GND) → GND

### LCD Screen (16x2):
- VCC → 5V
- GND → GND
- SDA → GPIO 21 (I2C Data Pin)
- SCL → GPIO 22 (I2C Clock Pin)

## How It Works

- **Car Entry**: When a car enters, the sensor A (Entrance) detects it. If the parking lot isn't full, the system opens the servo barrier by rotating it to 180° and then closes it after a 2-second delay. The total number of cars is updated on the LCD screen.

- **Car Exit**: When a car exits, sensor B (Exit) detects it. The system opens the servo barrier and then closes it, similarly to the entry process. The available parking spots are updated on the LCD.

- **Parking Lot Full**: If the parking lot reaches its maximum capacity, the system will display "Full" on the LCD, and no more cars will be allowed to enter.

- **Error Handling**: If both sensors are triggered at the same time, the system displays an error message on the LCD.

## Code Overview

- The code reads inputs from two infrared sensors (sensor A and sensor B) to detect car entry and exit.
- It controls the servo motor to open and close the barrier.
- It updates the LCD to display the current status of the parking lot (e.g., "Entering a car", "Car exiting", "Full", or "Available space").
- It prevents overflow by limiting the total number of cars in the parking lot.

## Future Improvements

- Add a real-time clock (RTC) to track entry and exit times.
- Implement Wi-Fi integration to monitor the parking lot status remotely.
- Use a more advanced display system (e.g., touchscreen or web interface).

## License

This project is open-source. Feel free to modify and use it in your own projects. Attribution is appreciated.

## Video
https://www.youtube.com/shorts/U_qBq4s-B_o
