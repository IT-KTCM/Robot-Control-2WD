# การตั้งค่าและการใช้งานโค้ดควบคุมหุ่นยนต์ด้วย ESP8266 และ Blynk

## คำอธิบายโค้ด
โค้ดนี้เป็นโปรแกรมควบคุมหุ่นยนต์ผ่านแอป Blynk โดยใช้ ESP8266 และมอเตอร์ไดรเวอร์ เช่น L298N หรือ L293D

### คุณสมบัติหลักของโค้ด:
1. **เชื่อมต่อ Wi-Fi**: ใช้ชื่อ Wi-Fi และรหัสผ่านที่กำหนด
2. **ควบคุมการเคลื่อนที่**: เดินหน้า, ถอยหลัง, เลี้ยวซ้าย, เลี้ยวขวา และหยุด
3. **รับคำสั่งจาก Blynk**: ใช้ Virtual Pin V1 เพื่อส่งคำสั่ง

## การตั้งค่าฮาร์ดแวร์

### อุปกรณ์ที่จำเป็น:
- **ESP8266 (NodeMCU)**
- **มอเตอร์ไดรเวอร์ (L298N หรือลักษณะใกล้เคียง)**
- **มอเตอร์ DC 2 ตัว**
- **แหล่งจ่ายไฟ**: สำหรับ ESP8266 และมอเตอร์ไดรเวอร์ (แนะนำแหล่งจ่ายไฟ 5V หรือ 12V ขึ้นอยู่กับมอเตอร์)

### การเชื่อมต่อพิน:
| พิน ESP8266  | เชื่อมต่อกับ           |
|--------------|-------------------------|
| D1 (GPIO5)   | IN1 (ทิศทางมอเตอร์ซ้าย) |
| D2 (GPIO4)   | IN2 (ทิศทางมอเตอร์ซ้าย) |
| D3 (GPIO0)   | IN3 (ทิศทางมอเตอร์ขวา) |
| D4 (GPIO2)   | IN4 (ทิศทางมอเตอร์ขวา) |
| D5 (GPIO14)  | ENA (PWM มอเตอร์ซ้าย)   |
| D6 (GPIO12)  | ENB (PWM มอเตอร์ขวา)   |

### การเชื่อมต่อแหล่งจ่ายไฟ:
- ต่อ **Vin** ของมอเตอร์ไดรเวอร์กับแหล่งจ่ายไฟ (5V หรือ 12V ขึ้นอยู่กับมอเตอร์)
- ต่อ **GND** ของแหล่งจ่ายไฟ, ESP8266, และมอเตอร์ไดรเวอร์เข้าด้วยกัน

## การตั้งค่าในโค้ด

### Wi-Fi Configuration
ในโค้ดให้เปลี่ยนชื่อ Wi-Fi และรหัสผ่านให้ตรงกับเครือข่ายของคุณ:
```cpp
char ssid[] = "MyWiFi";       // ชื่อ Wi-Fi ของคุณ
char pass[] = "zxcvbnm1234";  // รหัสผ่าน Wi-Fi
```

### การตั้งค่า Blynk:
- เปิดแอป **Blynk**
- สร้างโปรเจคใหม่
- ใส่ **Template ID**, **Template Name**, และ **Auth Token** ที่ Blynk ให้มา
  ```cpp
  #define BLYNK_TEMPLATE_ID "TMPL6wTa21f79"
  #define BLYNK_TEMPLATE_NAME "robot control"
  #define BLYNK_AUTH_TOKEN "__9_ZJEmPY5ScAwg6cvQtj52rzZMlVbx"
  ```

## การตั้งค่าในแอป Blynk

### การเพิ่ม Widget
1. เปิดโปรเจคในแอป Blynk
2. เพิ่ม **Button Widget**
   - **Virtual Pin**: V1
   - กำหนดค่าต่าง ๆ ดังนี้:
     | ปุ่ม         | ค่า (Value) | ความหมาย       |
     |--------------|-------------|----------------|
     | เดินหน้า    | 1           | Move Forward   |
     | ถอยหลัง     | 2           | Move Backward  |
     | เลี้ยวซ้าย  | 3           | Turn Left      |
     | เลี้ยวขวา   | 4           | Turn Right     |
     | หยุด        | ค่าอื่น ๆ   | Stop           |

## คำสั่งควบคุมในโค้ด

### ฟังก์ชันการเคลื่อนที่
- **เดินหน้า**:
  ```cpp
  void moveForward() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 255);
    analogWrite(ENB, 255);
  }
  ```
- **ถอยหลัง**:
  ```cpp
  void moveBackward() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA, 255);
    analogWrite(ENB, 255);
  }
  ```
- **เลี้ยวซ้าย**:
  ```cpp
  void turnLeft() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 255);
    analogWrite(ENB, 255);
  }
  ```
- **เลี้ยวขวา**:
  ```cpp
  void turnRight() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA, 255);
    analogWrite(ENB, 255);
  }
  ```
- **หยุด**:
  ```cpp
  void stopMoving() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
  }
  ```

### รับค่าจาก Blynk
- เมื่อปุ่มใน Blynk ส่งค่า **Virtual Pin V1** มา:
  ```cpp
  BLYNK_WRITE(V1) {
    int command = param.asInt();
    Serial.println(command);
    if (command == 1) {
      Serial.println("Forward (เดินหน้า)");
      moveForward();
    } else if (command == 2) {
      Serial.println("Backward (ถอยหลัง)");
      moveBackward();
    } else if (command == 3) {
      Serial.println("Left (เลี้ยวซ้าย)");
      turnLeft();
    } else if (command == 4) {
      Serial.println("Right (เลี้ยวขวา)");
      turnRight();
    } else {
      Serial.println("Stop (หยุด)");
      stopMoving();
    }
  }
  ```

## การอัปโหลดโค้ด
1. ใช้ **Arduino IDE**
2. เลือกบอร์ดเป็น **NodeMCU 1.0 (ESP-12E Module)**
3. เชื่อมต่อบอร์ดผ่าน USB
4. อัปโหลดโค้ดไปยังบอร์ด

## การตรวจสอบการทำงาน
- เปิด Serial Monitor เพื่อตรวจสอบสถานะการเชื่อมต่อ Wi-Fi และการทำงานของหุ่นยนต์
- ใช้แอป Blynk เพื่อควบคุมการเคลื่อนที่ของหุ่นยนต์
