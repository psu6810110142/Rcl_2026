void sensorSetup() {
  pinMode(sensorRearLeft_Pin, INPUT);
  pinMode(sensorRearRight_Pin, INPUT);
  
  // โค้ดเริ่มต้นการทำงานของ MPU6050 ใส่ตรงนี้
  Wire.begin();
  // mpu.initialize();
}

void readSensors() {
  int rL = digitalRead(sensorRearLeft_Pin);
  int rR = digitalRead(sensorRearRight_Pin);

  // โค้ดอ่านค่า MPU6050 อัปเดตตัวแปร Yaw_Angle ใส่ตรงนี้
  // Yaw_Angle = ...;

  // โชว์ค่าใน Serial Monitor
  Serial.print(" | หลังซ้าย: "); Serial.print(rL);
  Serial.print(" | หลังขวา: "); Serial.print(rR);
  Serial.print(" | Gyro Yaw: "); Serial.println(Yaw_Angle);
  
  delay(80); // หน่วงเวลาให้อ่านจอมอนิเตอร์ทัน (เฉพาะตอนใช้เทสค่าเซนเซอร์)
}