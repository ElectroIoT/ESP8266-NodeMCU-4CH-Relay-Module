# 🌟 **ESP8266 4-Relay Control with Arduino IoT Cloud** 🌟

This project demonstrates how to control **four relays** using an **ESP8266 (NodeMCU)** and the **Arduino IoT Cloud**. Relays can be toggled **locally** via physical switches or **remotely** through a cloud-based dashboard.

![Project Overview](/image/demo.jpg)

---

## 🎯 **Features**
- 🛠️ **Local Control**: Toggle relays with connected switches.
- 🌐 **Remote Control**: Use the Arduino IoT Cloud dashboard to manage relays online.
- 📶 **WiFi Feedback**: An LED indicates WiFi connectivity status.
- 🔄 **Synchronized State**: Updates from manual and remote operations are always in sync.

---

## 🛒 **Hardware Requirements**
1. **ESP8266 (NodeMCU)**
2. **4-Channel Relay Module**
3. **Push Buttons or Toggle Switches**
4. **Power Supply**
5. **Connecting Wires**

---

## 🖼️ **Circuit Diagram**
![alt_text, width="200"](/image/Circuit Diagram.JPG)
![alt_text, width="100"](/image/Circuit Diagram2.JPG)
![alt_text, width="100"](/image/PCB_3d.JPG)

### 🧩 **Connections**
- **Relays**:
  - Relay 1: GPIO 5 (D1)
  - Relay 2: GPIO 4 (D2)
  - Relay 3: GPIO 15 (D8)
  - Relay 4: GPIO 13 (D7)
- **Switches**:
  - Switch 1: GPIO 0 (D3)
  - Switch 2: GPIO 2 (D4)
  - Switch 3: GPIO 14 (D5)
  - Switch 4: GPIO 12 (D6)

---

## ⚙️ **Setup Instructions**

### 🛠️ **1. Install Required Libraries**
Install the following libraries from the Arduino IDE Library Manager:
- `ArduinoIoTCloud`
- `Arduino_ConnectionHandler`

### 🖥️ **2. Configure Arduino IoT Cloud**
1. Create a new "Thing" in the Arduino IoT Cloud.
2. Add the following variables:
   - `relay1` (type: `CloudSwitch`)
   - `relay2` (type: `CloudSwitch`)
   - `relay3` (type: `CloudSwitch`)
   - `relay4` (type: `CloudSwitch`)
3. Link each variable to a toggle switch on the dashboard.

### 🚀 **3. Flash the ESP8266**
1. Connect the ESP8266 to your computer.
2. Upload the provided code after replacing WiFi credentials and Arduino IoT Cloud keys.

### 🔌 **4. Wire the Components**
Follow the circuit diagram to connect relays, switches, and the ESP8266.

---

## 📜 **Code Explanation**

### **1. Pin Definitions**
```cpp
#define RelayPin1 5  // D1
#define RelayPin2 4  // D2
#define RelayPin3 15 // D8
#define RelayPin4 13 // D7

#define SwitchPin1 0  // D3
#define SwitchPin2 2  // D4
#define SwitchPin3 14 // D5
#define SwitchPin4 12 // D6

## 📜 **2. Cloud Integration**

CloudSwitch relay1;
CloudSwitch relay2;
CloudSwitch relay3;
CloudSwitch relay4;

## 📜 **3. Manual Control Logic**

void manual_control() {
  if (digitalRead(SwitchPin1) == LOW) {
    toggleState_1 = !toggleState_1;
    digitalWrite(RelayPin1, !toggleState_1);
    relay1 = toggleState_1;
  }
  // Repeat for other switches...
}

## 📜 **4. Remote Control Logic**

void onRelay1Change() {
  digitalWrite(RelayPin1, relay1 ? LOW : HIGH);
}

## 🎥 **Demo**
![alt_text, width="100"](/image/demo.JPG)

---

## 💡 **Future Improvements**
1. Add feedback mechanisms for relay states (e.g., LEDs).
2. Expand to control additional devices.
3. Integrate scheduling for automation.

## 💡 📧 ** Contact Us **

📧 Contact Us
For any questions or feedback, feel free to reach out at: electroiot@hotmail.com# ESP8266-NodeMCU-4CH-Relay-Module
