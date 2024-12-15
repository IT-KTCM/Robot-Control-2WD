#define BLYNK_TEMPLATE_ID "TMPL6wTa21f79"
#define BLYNK_TEMPLATE_NAME "robot control"
#define BLYNK_AUTH_TOKEN "__9_ZJEmPY5ScAwg6cvQtj52rzZMlVbx"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Wi-Fi SSID และรหัสผ่าน
char ssid[] = "MyWiFi";       // ชื่อ Wi-Fi
char pass[] = "zxcvbnm1234";  // รหัสผ่าน Wi-Fi

// กำหนดพินควบคุมมอเตอร์
#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4
#define ENA D5
#define ENB D6

void setup() {

  // เริ่มต้น Serial Monitor สำหรับแสดงสถานะการเชื่อมต่อ
  Serial.begin(115200);
  delay(100);

  Serial.println("กำลังเชื่อมต่อ Wi-Fi...");
  // ตรวจสอบสถานะการเชื่อมต่อ WiFi และแสดงผลผ่าน Serial Monitor
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("เชื่อมต่อ Wi-Fi ไม่สำเร็จ กำลังพยายามใหม่...");
    delay(1000);
  } else {
    Serial.println("เชื่อมต่อ Wi-Fi สำเร็จ!");
    delay(3000);  // เพิ่ม delay เพื่อหลีกเลี่ยงการแสดงสถานะถี่เกินไป
  }
  // เริ่มการเชื่อมต่อ Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // กำหนดโหมดของพินที่ใช้ควบคุมมอเตอร์
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  digitalWrite(ENA, HIGH);
  digitalWrite(ENA, HIGH);
}

// ฟังก์ชันการเคลื่อนที่
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 255);  // ตั้งค่าความเร็ว (0-255)
  analogWrite(ENB, 255);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 255);  // ความเร็วขณะเลี้ยว
  analogWrite(ENB, 255);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

void stopMoving() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

// ฟังก์ชันรับคำสั่งจาก Blynk
BLYNK_WRITE(V1) {
  int command = param.asInt();  // รับค่าจาก Virtual Pin V1
                                // แสดงคำสั่งที่ได้รับจาก Blynk ใน Serial Monitor
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

void loop() {

  Blynk.run();
}
