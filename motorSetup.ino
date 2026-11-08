void motorSetup() {
  pinMode(motorLeft_Fwd, OUTPUT);
  pinMode(motorLeft_Bwd, OUTPUT);
  pinMode(pwmLeft, OUTPUT);
  
  pinMode(motorRight_Fwd, OUTPUT);
  pinMode(motorRight_Bwd, OUTPUT);
  pinMode(pwmRight, OUTPUT);

  Stop(); // มั่นใจว่าเปิดเครื่องมามอเตอร์จะไม่หมุนเอง
}

void Stop() {
  // หยุดแบบปล่อยไหล
  digitalWrite(motorLeft_Fwd, LOW); 
  digitalWrite(motorLeft_Bwd, LOW);
  analogWrite(pwmLeft, 0);
  
  digitalWrite(motorRight_Fwd, LOW); 
  digitalWrite(motorRight_Bwd, LOW);
  analogWrite(pwmRight, 0);
}

void Brake() {
  // หยุดแบบล็อกแกนมอเตอร์ (Hard Brake)
  digitalWrite(motorLeft_Fwd, HIGH); 
  digitalWrite(motorLeft_Bwd, HIGH);
  analogWrite(pwmLeft, 255);
  
  digitalWrite(motorRight_Fwd, HIGH); 
  digitalWrite(motorRight_Bwd, HIGH);
  analogWrite(pwmRight, 255);
}