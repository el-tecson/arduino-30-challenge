# 4. Priority override system

* Normal LED pattern
* Emergency input (ball switch) overrides everything

## Circuit
![Circuit](./circuit.png)
*(not 100% accurate since TinkerCad doesn't have the right ball switch or tilt switch)*

## Schematics
![Schematics](./schematics.jpg)

## Demo
<p align="center">
  <img src="./demo.gif" alt="Video Demonstration" width="500">
</p>

### Demo Context
- When Ball Switch is titled, it activates the emergency state where the pattern goes much faster.
- When Ball Switch is not tilted, it defaults to normal pattern speed.

## Solution
- See the [code I made for this project](./solution.ino)
