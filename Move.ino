
void Forward() {
  analogWrite(pwmLeft, speedLeft_Fwd);
  analogWrite(pwmRight, speedRight_Fwd);
  
  digitalWrite(motorLeft_Fwd, HIGH);  
  digitalWrite(motorLeft_Bwd, LOW);
  
  digitalWrite(motorRight_Fwd, HIGH); 
  digitalWrite(motorRight_Bwd, LOW);
}

void Backward() {
  analogWrite(pwmLeft, speedLeft_Bwd);
  analogWrite(pwmRight, speedRight_Bwd);
  
  digitalWrite(motorLeft_Fwd, LOW);  
  digitalWrite(motorLeft_Bwd, HIGH);
  
  digitalWrite(motorRight_Fwd, LOW); 
  digitalWrite(motorRight_Bwd, HIGH);
}

void TurnLeft() {
  // ล้อซ้ายถอยหลัง ล้อขวาเดินหน้า (หมุนตัวอยู่กับที่)
  analogWrite(pwmLeft, speedLeft_Fwd); 
  analogWrite(pwmRight, speedRight_Fwd);
  
  digitalWrite(motorLeft_Fwd, LOW);  
  digitalWrite(motorLeft_Bwd, HIGH);
  
  digitalWrite(motorRight_Fwd, HIGH); 
  digitalWrite(motorRight_Bwd, LOW);
}

void TurnRight() {
  // ล้อซ้ายเดินหน้า ล้อขวาถอยหลัง (หมุนตัวอยู่กับที่)
  analogWrite(pwmLeft, speedLeft_Fwd);
  analogWrite(pwmRight, speedRight_Fwd);
  
  digitalWrite(motorLeft_Fwd, HIGH);  
  digitalWrite(motorLeft_Bwd, LOW);
  
  digitalWrite(motorRight_Fwd, LOW); 
  digitalWrite(motorRight_Bwd, HIGH);
}

// ---------------------------------------------------------
// ฟังก์ชันถอยหลังจัดลำตัวให้ตั้งฉาก (อัปเกรดระบบ Soft Start)
// ---------------------------------------------------------
void autoRear() {
  bool leftReady = false;
  bool rightReady = false;
  
  Serial.println("-> เริ่มถอยหลังจัดระเบียบ (Rear Align) แบบนุ่มนวล");

  // 1. ออกตัวถอยหลังด้วย Soft Start ก่อนเลย ป้องกันรถกระชากเป๋
  BackwardSoft(); 

  // 2. หลังจากรถไหลออกตัวแบบสมูทแล้ว ค่อยเข้าลูปดักจับเส้นดำ
  while (!leftReady || !rightReady) {
    int valRearLeft = digitalRead(sensorRearLeft_Pin);
    int valRearRight = digitalRead(sensorRearRight_Pin);

    // --- จัดการล้อซ้าย ---
    if (valRearLeft == BLACK_LINE && !leftReady) {
      leftReady = true;
      // เจอเส้นปุ๊บ สั่งเบรกไฟฟ้าล้อซ้ายทันที
      digitalWrite(motorLeft_Fwd, HIGH);
      digitalWrite(motorLeft_Bwd, HIGH);
      analogWrite(pwmLeft, 255);
    } else if (!leftReady) {
      // ถ้าซ้ายยังไม่เจอเส้น ให้ถอยหลังต่อไปด้วยความเร็วฐาน
      digitalWrite(motorLeft_Fwd, LOW);
      digitalWrite(motorLeft_Bwd, HIGH);
      analogWrite(pwmLeft, speedLeft_Bwd);
    }

    // --- จัดการล้อขวา ---
    if (valRearRight == BLACK_LINE && !rightReady) {
      rightReady = true;
      // เจอเส้นปุ๊บ สั่งเบรกไฟฟ้าล้อขวาทันที
      digitalWrite(motorRight_Fwd, HIGH);
      digitalWrite(motorRight_Bwd, HIGH);
      analogWrite(pwmRight, 255);
    } else if (!rightReady) {
      // ถ้าขวายังไม่เจอเส้น ให้ถอยหลังต่อไปด้วยความเร็วฐาน
      digitalWrite(motorRight_Fwd, LOW);
      digitalWrite(motorRight_Bwd, HIGH);
      analogWrite(pwmRight, speedRight_Bwd);
    }
  }
  
  delay(200); // หน่วงเวลา 0.2 วินาทีให้มอเตอร์ล็อกแกนสนิท
  Stop(); // สั่งคลายไฟ ปล่อยมอเตอร์พัก
  Serial.println("-> จัดระเบียบเสร็จสิ้น! ท้ายรถขนานเส้น 100%");
}

void ForwardSoft() {
  // 1. สั่งทิศทางเดินหน้าเตรียมไว้ก่อน
  digitalWrite(motorLeft_Fwd, HIGH);  
  digitalWrite(motorLeft_Bwd, LOW);
  
  digitalWrite(motorRight_Fwd, HIGH); 
  digitalWrite(motorRight_Bwd, LOW);

  // 2. ค่อยๆ เร่งไฟแบบขั้นบันได (แบ่งเป็น 10 สเตป สเตปละ 20 มิลลิวินาที)
  int steps = 15; 
  int delayPerStep = 20; 

  for (int i = 1; i <= steps; i++) {
    // คำนวณความเร็วที่ค่อยๆ เพิ่มขึ้น
    int currentLeft = (speedLeft_Fwd / steps) * i;
    int currentRight = (speedRight_Fwd / steps) * i;
    
    analogWrite(pwmLeft, currentLeft);
    analogWrite(pwmRight, currentRight);
    
    delay(delayPerStep); // หน่วงเวลาให้ล้อค่อยๆ ปั่น
  }
  
  // 3. จบการเร่ง ยืนยันการจ่ายความเร็วตามที่ตั้งไว้เป๊ะๆ อีกครั้ง
  analogWrite(pwmLeft, speedLeft_Fwd);
  analogWrite(pwmRight, speedRight_Fwd);
}

void BackwardSoft() {
  // 1. สั่งเกียร์ถอยหลังเตรียมไว้ก่อน
  digitalWrite(motorLeft_Fwd, LOW);  
  digitalWrite(motorLeft_Bwd, HIGH);
  
  digitalWrite(motorRight_Fwd, LOW); 
  digitalWrite(motorRight_Bwd, HIGH);

  // 2. ค่อยๆ เร่งไฟแบบขั้นบันได (แบ่งเป็น 10 สเตป สเตปละ 20 มิลลิวินาที)
  int steps = 15; 
  int delayPerStep = 20; 

  for (int i = 1; i <= steps; i++) {
    // คำนวณความเร็วที่ค่อยๆ เพิ่มขึ้น (ใช้ความเร็วถอยหลัง)
    int currentLeft = (speedLeft_Bwd / steps) * i;
    int currentRight = (speedRight_Bwd / steps) * i;
    
    analogWrite(pwmLeft, currentLeft);
    analogWrite(pwmRight, currentRight);
    
    delay(delayPerStep); // หน่วงเวลาให้ล้อค่อยๆ ปั่น
  }
  
  // 3. จบการเร่ง ยืนยันการจ่ายความเร็วตามที่ตั้งไว้เป๊ะๆ อีกครั้ง
  analogWrite(pwmLeft, speedLeft_Bwd);
  analogWrite(pwmRight, speedRight_Bwd);
}