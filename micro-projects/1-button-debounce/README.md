# 1. Button debounce + press classification

* Input: key button
* Output: LED / serial
* Detect short, long, double press

## Circuit
![Circuit](./circuit.png)

## Schematics
![Schematics](./schematics.jpg)

## Demo
<p align="center">
  <img src="./demo.gif" alt="Video Demonstration" width="500">
</p>

### Demo Context
- LED classification:
    - Yellow = Click
    - Red = Hold
    - Blue = Double-Click
- I lacked 1 more jumper so I just made all resistors to hit GND and only needed 1 jumper for each LED afterwards. Saved 2 jumpers, had only 10.

## Solution
- See the [code I made for this project](./solution.ino)
