// Brian Lesko, 12/10/23, Control a bipolar hybrid stepper motor

int delayLength = 2;

void setup() {
  //motor direction toggle pins
  pinMode(12, OUTPUT); //CH A direction
  pinMode(13, OUTPUT); //CH B direction
  pinMode(9, OUTPUT); //disable CH A
  pinMode(8, OUTPUT); //disable CH B
}

void loop(){
  halfStep(delayLength, false); // Forward step
}

void singlePhaseStep(int delayLength, bool backwards) {
  // Single phase stepping is activating one coil at a time
  // not as strong as full step
  // A+ B+ A- B-

  // A 
  digitalWrite(9, LOW);  //ENABLE CH A
  digitalWrite(8, HIGH); //DISABLE CH B
  digitalWrite(12, HIGH);   //Sets direction of CH A
  analogWrite(3, 255);   //Moves CH A
  
  delay(delayLength);
  
  // B 
  digitalWrite(9, HIGH);  //DISABLE CH A
  digitalWrite(8, LOW); //ENABLE CH B
  digitalWrite(13, HIGH);   //Sets direction of CH B
  if (backwards){digitalWrite(13, LOW);}
  analogWrite(11, 255);   //Moves CH B
  
  delay(delayLength);
  
  // A-
  digitalWrite(9, LOW);  //ENABLE CH A
  digitalWrite(8, HIGH); //DISABLE CH B
  digitalWrite(12, LOW);   //Sets direction of CH A
  analogWrite(3, 255);   //Moves CH A
  
  delay(delayLength);
  
  // B-
  digitalWrite(9, HIGH);  //DISABLE CH A
  digitalWrite(8, LOW); //ENABLE CH B
  digitalWrite(13, LOW);   //Sets direction of CH B
  if (backwards){digitalWrite(13, HIGH);}
  analogWrite(11, 255);   //Moves CH B
  
  delay(delayLength);
}

void fullStep(int delayLength, bool backwards) {
  // full step is much stronger than single phase step
  // A+B+ > A-B+ > A-B- > A+B-
  digitalWrite(9, LOW);  //ENABLE CH A
  digitalWrite(8, LOW); //ENABLE CH B

  // AB
  digitalWrite(12, HIGH);   //Sets direction of CH A as +
  digitalWrite(13, HIGH);   //Sets direction of CH B as + 
  analogWrite(3, 255);   //Moves CH A
  analogWrite(11, 255);   //Moves CH B

  delay(delayLength);

  //A-B
  digitalWrite(12, LOW);   //Sets direction of CH A as -
  digitalWrite(13, HIGH);   //Sets direction of CH B as + 
  analogWrite(3, 255);   //Moves CH A
  analogWrite(11, 255);   //Moves CH B

  delay(delayLength);

  //A-B-
  digitalWrite(12, LOW);   //Sets direction of CH A as -
  digitalWrite(13, LOW);   //Sets direction of CH B as -
  analogWrite(3, 255);   //Moves CH A
  analogWrite(11, 255);   //Moves CH B

  delay(delayLength);

  // AB-
  digitalWrite(12, HIGH);   //Sets direction of CH A as +
  digitalWrite(13, LOW);   //Sets direction of CH B as -
  analogWrite(3, 255);   //Moves CH A
  analogWrite(11, 255);   //Moves CH B

  delay(delayLength);

  // A-
  digitalWrite(9, HIGH);  //DISABLE CH A
  digitalWrite(8, LOW); //ENABLE CH B
  digitalWrite(13, LOW);   //Sets direction of CH B
  if (backwards){digitalWrite(13, HIGH);}
  analogWrite(11, 255);   //Moves CH B
  
}

void halfStep(int delayLength, bool backwards) {
  // AB > B > A-B+ > A- > A-B- > B- > A+B- > A
  // half stepping has maximum torque on double activations but less torque on single activation steps, it is much smoother and quieter
  // Source: https://www.monolithicpower.com/bipolar-stepper-motors-part-i-control-modes#:~:text=In%20half%2Dstep%20mode%2C%20both,phase%20to%20two%2Dphase%20operation.

  delayLength = delayLength/2;

  digitalWrite(9, LOW);  //ENABLE CH A
  digitalWrite(8, LOW); //ENABLE CH B

  // AB
  digitalWrite(12, HIGH);   //Sets direction of CH A as +
  digitalWrite(13, HIGH);   //Sets direction of CH B as + 
  analogWrite(3, 255);   //Moves CH A
  analogWrite(11, 255);   //Moves CH B

  delay(delayLength);

  // B 
  digitalWrite(9, HIGH);  //DISABLE CH A
  digitalWrite(8, LOW); //ENABLE CH B
  digitalWrite(13, HIGH);   //Sets direction of CH B
  if (backwards){digitalWrite(13, LOW);}
  analogWrite(11, 255);   //Moves CH B

  delay(delayLength);

  //A-B
  digitalWrite(9, LOW);  //ENABLE CH A
  digitalWrite(12, LOW);   //Sets direction of CH A as -
  digitalWrite(13, HIGH);   //Sets direction of CH B as + 
  analogWrite(3, 255);   //Moves CH A
  analogWrite(11, 255);   //Moves CH B

  delay(delayLength);

  // A-
  digitalWrite(9, LOW);  //ENABLE CH A
  digitalWrite(8, HIGH); //DISABLE CH B
  digitalWrite(12, LOW);   //Sets direction of CH A
  analogWrite(3, 255);   //Moves CH A

  delay(delayLength);

  //A-B-
  digitalWrite(8, LOW);  //ENABLE CH B
  digitalWrite(12, LOW);   //Sets direction of CH A as -
  digitalWrite(13, LOW);   //Sets direction of CH B as -
  analogWrite(3, 255);   //Moves CH A
  analogWrite(11, 255);   //Moves CH B

  delay(delayLength);

  // B-
  digitalWrite(9, HIGH);  //DISABLE CH A
  digitalWrite(8, LOW); //ENABLE CH B
  digitalWrite(13, LOW);   //Sets direction of CH B
  if (backwards){digitalWrite(13, HIGH);}
  analogWrite(11, 255);   //Moves CH B

  delay(delayLength);

  // AB-
  digitalWrite(9, LOW);  //ENABLE CH A  
  digitalWrite(12, HIGH);   //Sets direction of CH A as +
  digitalWrite(13, LOW);   //Sets direction of CH B as -
  analogWrite(3, 255);   //Moves CH A
  analogWrite(11, 255);   //Moves CH B

  delay(delayLength);

  // A 
  digitalWrite(9, LOW);  //ENABLE CH A
  digitalWrite(8, HIGH); //DISABLE CH B
  digitalWrite(12, HIGH);   //Sets direction of CH A
  analogWrite(3, 255);   //Moves CH A

  delay(delayLength);
}

void quarterStep(){
  // Quarter step sequence
  // 1. A
  // 2. AB with B at half current
  // 3. B
  // 4. -A B with A at half current
  // 5. -A
  // 6. -A -B with B at half current
  // 7. -B
  // 8. A -B with A at half current
  // Repeat sequence

  // discrepency between using half current or 0.71 or 1/(2)^.5
  // explanation: the vector sum of the currents in both coils provides the same magnitude of torque as a single coil at full activation
}

void sinusoidalStep(){
  // computationally more expensive with diminishing returns compared to a microstep level of say 128th or even 64th
  //Ia = Imax * cos(theta)
  //Ib = Imax * sin(theta)
}

