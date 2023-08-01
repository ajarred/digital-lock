# Digital Lock Project

### Description
An Arduino mini-security project to apply learnings from lab class. This project is a simple digital lock system to control a servo motor which utilizes a keypad for entering the passcode, an LCD display for user interaction, a buzzer for audio feedback.

### Components
- Arduino UNO
- 3x4 matrix keypad
- I2C LCD display (16x2)
- Servo motor
- Piezoelectric buzzer
- Jumper wires
- Breadboard

### Usage
- Power up Arduino board.
- System starts off closed.
- LCD prompts user to enter the 4-key passcode.
- Use the keypad to enter the 4-key passcode.
- If the entered 4-key passcode matches the stored passcode, the system will unlock the servo motor.
- The LCD will display a success message and may be locked again when pressing a certain key.
- If the entered 4-key passcode is incorrect, the LCD will display an error message, buzzer outputs corresponding audio feedback and the lock will remain closed.
- If there are 5 incorrect inputs of the 4-key passcode, the user will be *Rick Rolled*

### Image
![image](https://github.com/ajarred/digital-lock/assets/69410244/20ca42a3-577e-4db5-9656-b7bbde1bf5ba)
