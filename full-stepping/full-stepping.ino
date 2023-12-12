// Brian Lesko, 12/12/23, Control a bipolar hybrid stepper motor

// A stepper motor can rotate continuously, acheive accurate and repeatable increments, and does not require a feedback loop
// A Bipolar Hybrid stepper is what is used in this code. It has two coils, A and B, each with its own pair of wires
// A bipolar hybrid stepper can be controlled in various ways

// Full stepping provdes the highest torque when controlling a stepper motor because it utilizes simultaneous coil activations.
// However, it produces more vibration than partial stepping, and is more complicated to implement than single phase stepping. 
// The phases are A+B+ > A-B+ > A-B- > A+B-

int delayLength = 2;

void setup() {
  //motor direction toggle pins
  pinMode(12, OUTPUT); //CH A direction
  pinMode(13, OUTPUT); //CH B direction
  pinMode(9, OUTPUT); //disable CH A
  pinMode(8, OUTPUT); //disable CH B
}

void loop(){
  fullStep(delayLength, false); // Forward step
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