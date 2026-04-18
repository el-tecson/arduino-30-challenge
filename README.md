# Arduino Embedded Systems Foundations (10 Micro-Projects)

A structured set of 10 progressively designed Arduino micro-projects focused on building core embedded systems skills such as input handling, sensor processing, state machines, and non-blocking logic design.

This project serves as a foundational training ground for understanding how embedded systems behave under real-world constraints using an Arduino UNO platform.

---

## 🎯 Objective

The goal of this challenge is to develop practical competence in embedded systems programming by building small, focused systems that demonstrate:

- Digital and analog input handling  
- Sensor data processing and filtering  
- State machine design  
- Event-driven programming  
- Non-blocking logic implementation  
- System reliability and fail-safe behavior  

---

## 🧠 Core Skills Covered

- Button debouncing and input classification  
- Multi-state LED control systems  
- Software-based task scheduling  
- Priority-based interrupt-like logic (software simulation)  
- Sensor thresholding and hysteresis  
- Signal filtering and noise reduction  
- Time-based system control  
- Fail-safe and watchdog logic concepts  
- Basic embedded diagnostics via serial monitoring  

---

## 🔧 Hardware Used

- Arduino UNO  
- LEDs  
- Push buttons  
- Buzzer  
- Potentiometer / analog sensors  
- Ball switch  
- Basic resistors and breadboard setup  

---

## 📦 Project Structure

Each micro-project is self-contained but builds on concepts from previous ones.

### Micro-Projects Overview

| Micro-Project | Documentation |
|----------------|--------------|
| 1. Button debounce and press classification | [View README](./micro-projects/1-button-debounce/README.md) |
| 2. Multi-LED state machine | [View README](./micro-projects/2-state-machine/README.md) |
| 3. Non-blocking task scheduler | [View README](./micro-projects/3-task-scheduler/README.md) |
| 4. Priority override system | [View README](./micro-projects/4-priority-override/README.md) |
| 5. Buzzer alert patterns (non-blocking) | [View README](./micro-projects/5-non-blocking-buzzer-alert/README.md) |
| 6. Analog threshold + hysteresis control | [View README](./micro-projects/6-analog-threshold-and-hysteresis/README.md) |
| 7. Input smoothing and filtering | [View README](./micro-projects/7-input-smoothing-noise-filtering/README.md) |
| 8. Traffic light controller simulation | [View README](./micro-projects/8-traffic-light-controller/README.md) |
| 9. Fail-safe logic system | [View README](./micro-projects/9-fail-safe-logic-simulation/README.md) |
| 10. Software watchdog simulation | [View README](./micro-projects/10-software-watchdog/README.md) |
---

## 🧩 Design Philosophy

This project prioritizes **engineering thinking over feature complexity**.

Instead of building large applications, each micro-project isolates one concept and implements it in a minimal but functional way. This encourages:

- modular thinking  
- debugging discipline  
- system-level awareness  
- hardware-software interaction understanding  

The progression of the 10 micro-projects was structured with the assistance of ChatGPT as a planning and ideation tool. It helped refine sequencing, ensure logical difficulty progression, and clarify learning objectives. All implementation, hardware setup, and debugging were independently developed.

---

## ⚙️ How to Use

1. Upload each sketch individually to Arduino UNO  
2. Follow wiring diagrams for each micro-project  
3. Observe serial monitor outputs (if applicable)  
4. Modify parameters to test system behavior  

---

## 📌 Key Learning Outcome

By completing these 10 micro-projects, you gain the ability to:

> Design and implement small embedded systems using structured logic, rather than relying on copy-paste Arduino examples.

---

## 🚧 Future Work

This project originally began as a 30-micro-project challenge but was refined to focus on depth over quantity.

Future extensions may include:
- full system integration projects  
- sensor fusion experiments  
- real-world embedded applications  

---

## 🧑‍💻 Author

Built as part of early-stage embedded systems and computer engineering skill development.

---

## 📍 Notes

This project is intentionally kept hardware-light and USB-powered for accessibility and rapid iteration.

---
