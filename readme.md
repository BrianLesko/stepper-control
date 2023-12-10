
# Stepper Control
This code implements the control of a motor for use in robotics projects. The type of motor used here is a hybrid bipolar stepper motor - it allows precise movement, holding torque, and continuous motion.However, stepper motors are more difficult to control than regular DC motors. Furthermore, a bipolar stepper is more difficult to control, and also more powerful, than other stepper motor types. This project is written in Arduino

&nbsp;

<div align="center"><img src="docs/preview.gif" width="800"></div>

&nbsp;

## Hardware
- `Arduino R4`: the microcontroller that the code runs on
- `Arduino motor carrier Rev3`: acts as the driver, delivers more power than the Arduino is capable of.
- `NEMA 17 hybrid bipolar stepper`: 1.8° Step Angle, 42.48 oz-in Holding Torque
- `9 volt battery`: The motor is powered by a 9 volt battery

&nbsp;

## Motor Specs
The NEMA motor used here has 200 steps per revolution - allowing movement of 1.8 degree increments when using maximal torque. Partial stepping can be implemented for smaller movements, but at the cost of less torque. 

The motor has two pairs of wires corresponding with two coils, often noted as A and B. To full step, the coils should be activated in phase with alternating polarity.

&nbsp;

## Full stepping 
To make a bipolar motor spin: 
 - Power the first coil.
 - Next power the second coil with reverse polarity.
 - Then power the first coil with reverse polarity.
 - Finally, power the second coil.
To reverse the motor direction of a bipolar stepper, simply reverse the polarity of the second coil.

&nbsp;

## Sources
[Randofo / instructables.com](https://www.instructables.com/Arduino-Motor-Shield-Tutorial/)

&nbsp;

## Repository Structure
```
repository/
├── stepper_forward/
│   └── stepper_forward.ino
└── docs/
    └── preview.png # preview photo for Github
```

&nbsp;

## Topics 
```
Arduino | Git | Motor control | Stepper motor | Hardware 
Self taught coding | Mechanical engineer | Robotics engineer | Brian Joseph Lesko | Brian Lesko
```
&nbsp;

<hr>

&nbsp;

<div align="center">



╭━━╮╭━━━┳━━┳━━━┳━╮╱╭╮        ╭╮╱╱╭━━━┳━━━┳╮╭━┳━━━╮
┃╭╮┃┃╭━╮┣┫┣┫╭━╮┃┃╰╮┃┃        ┃┃╱╱┃╭━━┫╭━╮┃┃┃╭┫╭━╮┃
┃╰╯╰┫╰━╯┃┃┃┃┃╱┃┃╭╮╰╯┃        ┃┃╱╱┃╰━━┫╰━━┫╰╯╯┃┃╱┃┃
┃╭━╮┃╭╮╭╯┃┃┃╰━╯┃┃╰╮┃┃        ┃┃╱╭┫╭━━┻━━╮┃╭╮┃┃┃╱┃┃
┃╰━╯┃┃┃╰┳┫┣┫╭━╮┃┃╱┃┃┃        ┃╰━╯┃╰━━┫╰━╯┃┃┃╰┫╰━╯┃
╰━━━┻╯╰━┻━━┻╯╱╰┻╯╱╰━╯        ╰━━━┻━━━┻━━━┻╯╰━┻━━━╯
  


&nbsp;


<a href="https://twitter.com/BrianJosephLeko"><img src="https://raw.githubusercontent.com/BrianLesko/BrianLesko/f7be693250033b9d28c2224c9c1042bb6859bfe9/.socials/svg-white/x-logo-white.svg" width="30" alt="X Logo"></a> &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; <a href="https://github.com/BrianLesko"><img src="https://raw.githubusercontent.com/BrianLesko/BrianLesko/f7be693250033b9d28c2224c9c1042bb6859bfe9/.socials/svg-white/github-mark-white.svg" width="30" alt="GitHub"></a> &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; <a href="https://www.linkedin.com/in/brianlesko/"><img src="https://raw.githubusercontent.com/BrianLesko/BrianLesko/f7be693250033b9d28c2224c9c1042bb6859bfe9/.socials/svg-white/linkedin-icon-white.svg" width="30" alt="LinkedIn"></a>

follow all of these or i will kick you

</div>


&nbsp;


