// ==========================================
// 1. ประกาศตัวแปรพินมอเตอร์
// ==========================================
const int motorLeft_Fwd = 27;  
const int motorLeft_Bwd = 26;  // ใช้ขา 15 แทน 14 ที่มีปัญหา
const int pwmLeft = 33;        

const int motorRight_Fwd = 12; 
const int motorRight_Bwd = 13; 
const int pwmRight = 32;       

// ==========================================
// 2. ประกาศตัวแปรพินเซนเซอร์เส้น
// ==========================================
//const int sensorFrontLeft_Pin = 34;
//const int sensorFrontRight_Pin = 35;
const int sensorRearLeft_Pin = 34;
const int sensorRearRight_Pin = 35;
const int BLACK_LINE = HIGH; 

// ==========================================
// 3. ตั้งค่าความเร็ว (เปลี่ยนค่าได้ที่นี่ที่เดียว)
// ==========================================
int speedLeft_Fwd = 240.5;  
int speedRight_Fwd = 245; 
int speedLeft_Bwd = 240;  
int speedRight_Bwd = 245; 

// ==========================================
// 4. ตัวแปรสำหรับ MPU6050 (ไจโร)
// ==========================================
#include <Wire.h>
// ถ้าใช้ไลบรารี MPU6050 ให้ include ตรงนี้เพิ่ม
float Yaw_Angle = 0.0;

void setup() {
  Serial.begin(115200);
  
  // เรียกใช้ฟังก์ชันตั้งค่าจากแท็บอื่นๆ
  motorSetup();
  sensorSetup();

  
  Serial.println("--- System Ready ---");
  delay(2000); // หน่วงเวลาก่อนเริ่มทำงาน
 
  ForwardSoft();
  delay(1000);
  Stop();

  autoRear();


  TurnLeft();
  delay(600);
  Stop();

  Forward();
  delay(1000);
  
  BackwardSoft();
  delay(2000);
  Stop();
  
}

void loop() {
  // ทดสอบเรียกใช้ฟังก์ชันอ่านค่าเซนเซอร์
  readSensors();
  
  // ตัวอย่าง: ถ้าอยากเทสเดินหน้า ให้เอาคอมเมนต์ออก
  //motorForward();
}