# 9. Fail-safe logic simulation

* Simulate sensor disconnect
* System enters safe mode

## Circuit
![Circuit](./circuit.png)

## Schematics
![Schematics](./schematics.jpg)

## Result
<p align="center">
  <img src="./demo.jpg" alt="Demonstration" width="500">
</p>

### Result Context
- **Blue LED Signal**: **Go Signal** lasts for 30 seconds.
- **Yellow LED Signal**: **Clearance Interval** lasts for 5 seconds.
- **Red LED Signal**: **Stop Signal** lasts for 60 seconds.
- **Interrupting the signal**: Rotate the potentiometer to the *desired signal* shown in the *pair of LEDs on the other side*, then press the button to instantly go to **Clearance Interval** *(yellow signal)* then afterwards go to the *desired signal*
- **Fail-safe behavior (sensor disconnect simulation)**:
    When the potentiometer is disconnected, it consistently outputs near-maximum readings (~1023). The system detects this abnormal condition and automatically enters **safe mode**, overriding manual input. In this state:
    - The control input is ignored
    - The system defaults to a **safe traffic behavior** (controlled state)
    - Prevents unintended or unsafe signal switching due to invalid sensor data

## Solution
- See the [code I made for this project](./solution.ino)
- **Note**: Started from the code of [micro-project 8](../8-traffic-light-controller/README.md). Code hasn't yet been tested.
