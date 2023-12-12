// Brian Lesko, 12/12/23, Control a bipolar hybrid stepper motor

// A stepper motor can rotate continuously, acheive accurate and repeatable increments, and does not require a feedback loop
// A Bipolar Hybrid stepper is what is used in this code. It has two coils, A and B, each with its own pair of wires
// A bipolar hybrid stepper can be controlled in various ways

// Partial stepping yeilds lower vibration and smoother movement than full stepping.
// However, the torque is lower, and algorithm is more complicated than full stepping.

  // Quarter step sequence
  // 1. A
  // 2. AB with B at half current
  // 3. B
  // 4. -A B with A at half current
  // 5. -A
  // 6. -A -B with B at half current
  // 7. -B
  // 8. A -B with A at half current
