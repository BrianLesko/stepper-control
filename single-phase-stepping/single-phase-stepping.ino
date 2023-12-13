// Brian Lesko, 12/12/23, Control a bipolar hybrid stepper motor

// A stepper motor can rotate continuously, acheive accurate and repeatable increments, and does not require a feedback loop
// A Bipolar Hybrid stepper is what is used in this code. It has two coils, A and B, each with its own pair of wires
// A bipolar hybrid stepper can be controlled in various ways

// Single phase stepping is the simplest way to control a stepper motor.
// Despite its relative simplictiy, it still takes a set of four precicesly timed signals to complete a motor step
// The phases are A+ B+ A- B-

int delayLength = 2;

void setup() {
  //motor direction toggle pins
  pinMode(12, OUTPUT); //CH A direction
  pinMode(13, OUTPUT); //CH B direction
  pinMode(9, OUTPUT); //disable CH A
  pinMode(8, OUTPUT); //disable CH B
}

void loop(){
  singlePhaseStep(delayLength, false); // Forward step
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