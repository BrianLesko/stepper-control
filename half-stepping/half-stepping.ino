// Brian Lesko, 12/12/23, Control a bipolar hybrid stepper motor
// Partial stepping yeilds lower vibration and smoother movement than full stepping.

int delayLength = 1;

void setup() {
  //motor direction toggle pins
  pinMode(12, OUTPUT); //CH A direction
  pinMode(13, OUTPUT); //CH B direction
  pinMode(9, OUTPUT); //disable CH A
  pinMode(8, OUTPUT); //disable CH B
}

void loop(){
  state = halfStep(delayLength, 200, false); 
  while (true){} // Stop
}

void halfStep(int delayLength, int steps, bool backwards, int startAt) {
  // AB > B > A-B+ > A- > A-B- > B- > A+B- > A
  // half stepping has maximum torque on double activations but less torque on single activation steps, it is much smoother and quieter
  // Source: https://www.monolithicpower.com/bipolar-stepper-motors-part-i-control-modes#:~:text=In%20half%2Dstep%20mode%2C%20both,phase%20to%20two%2Dphase%20operation.

  int n = 8
  int i = 0;
  while (i < steps) {

    digitalWrite(9, LOW);  //ENABLE CH A
    digitalWrite(8, LOW); //ENABLE CH B
  
    if (i>0) | (startAt == 0) {    // AB
      digitalWrite(12, HIGH);   //Sets direction of CH A as +
      digitalWrite(13, HIGH);   //Sets direction of CH B as + 
      analogWrite(3, 255);   //Moves CH A
      analogWrite(11, 255);   //Moves CH B
      delay(delayLength);
      i++;
    }

    if (i>0) | (startAt == 1) {     // B 
      digitalWrite(9, HIGH);  //DISABLE CH A
      digitalWrite(8, LOW); //ENABLE CH B
      digitalWrite(13, HIGH);   //Sets direction of CH B
      if (backwards){digitalWrite(13, LOW);}
      analogWrite(11, 255);   //Moves CH B
      delay(delayLength);
      i++;
    }

    if (i>0) | (startAt == 2) {    //A-B
      digitalWrite(9, LOW);  //ENABLE CH A
      digitalWrite(12, LOW);   //Sets direction of CH A as -
      digitalWrite(13, HIGH);   //Sets direction of CH B as + 
      analogWrite(3, 255);   //Moves CH A
      analogWrite(11, 255);   //Moves CH B
      delay(delayLength);
      i++;
    }

    if (i>0) | (startAt == 3) {    // A-
      digitalWrite(9, LOW);  //ENABLE CH A
      digitalWrite(8, HIGH); //DISABLE CH B
      digitalWrite(12, LOW);   //Sets direction of CH A
      analogWrite(3, 255);   //Moves CH A
      delay(delayLength);
      i++;
    }

    if (i>0) | (startAt == 4) {    //A-B-
      digitalWrite(9, LOW);  //ENABLE CH A
      digitalWrite(12, LOW);   //Sets direction of CH A as -
      digitalWrite(13, LOW);   //Sets direction of CH B as - 
      analogWrite(3, 255);   //Moves CH A
      analogWrite(11, 255);   //Moves CH B
      delay(delayLength);
      i++;
    }

    if (i>0) | (startAt == 5) {     // B-
      digitalWrite(9, HIGH);  //DISABLE CH A
      digitalWrite(8, LOW); //ENABLE CH B
      digitalWrite(13, LOW);   //Sets direction of CH B
      if (backwards){digitalWrite(13, HIGH);}
      analogWrite(11, 255);   //Moves CH B
      delay(delayLength);
      i++;
    }

    if (i>0) | (startAt == 6) {     // AB-
      digitalWrite(9, LOW);  //ENABLE CH A
      digitalWrite(12, HIGH);   //Sets direction of CH A as +
      digitalWrite(13, LOW);   //Sets direction of CH B as - 
      analogWrite(3, 255);   //Moves CH A
      analogWrite(11, 255);   //Moves CH B
      delay(delayLength);
      i++;
    }

    if (i>0) | (startAt == 7) {    // A 
      digitalWrite(9, LOW);  //ENABLE CH A
      digitalWrite(8, HIGH); //DISABLE CH B
      digitalWrite(12, HIGH);   //Sets direction of CH A
      analogWrite(3, 255);   //Moves CH A
      delay(delayLength);
      i++;
    }
  }
  state = n%i;
  return state;
}