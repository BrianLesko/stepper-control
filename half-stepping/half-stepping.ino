// Brian Lesko, 12/12/23, Control a bipolar hybrid stepper motor

// A stepper motor can rotate continuously, acheive accurate and repeatable increments, and does not require a feedback loop
// A Bipolar Hybrid stepper is what is used in this code. It has two coils, A and B, each with its own pair of wires
// A bipolar hybrid stepper can be controlled in various ways

// Partial stepping yeilds lower vibration and smoother movement than full stepping.
// However, the torque is lower, and algorithm is more complicated than full stepping.
// Half stepping is the next tier for finer movement and uses this set of coil activations to do one step:
// The phases are AB > B > A-B+ > A- > A-B- > B- > A+B- > A

// Finer movement yet can also be implemented in quarter stepping, eigth stepping and so on - often times partial stepping is called microstepping

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