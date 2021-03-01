# Module 2: Locker
COMS BC 3930

Through this module, I created an interactive locker that allows you to unlock a secret box.

## Materials:
- Raspberry Pi (used for Power)
- ESP32 (runs Arduino program)
- 1 analog joystick
- 2 large buttons
- 1 SPST switch
- 1 LEDPixel
- 1 Servo
- 1 PWM

## Hardware Configuration
### Joystick

### Buttons

### Switch

### LEDPixel

### Servo

### PWM


## Modes
1. Locker Combination has not begun
    1. All inputs (besides the blue button) are at rest and states aren't saved.
    2. Waiting on blue button to start.
2. Locker Combination has begun
    1. All inputs save their values based on user input.
    2. Waiting on blue button to be pressed to check password.
3. Locker Combination is correct
    1. All inputs (besides the blue button) are at rest and don't save any of their states.
    2. Servo turns clockwise 90 degrees which releases secret box.
    3. Waiting on blue button to lock box when ready and clear the password.
4. Locker Combination is incorrect
    1. All inputs (besides the blue button) are at rest and states aren't saved.
    2. Waiting on blue button to retry inputting the password.
5. Locker Combination has restarted
    1. If password was correct, the servo locks the box.
    2. All inputs save their values based on user input.
    3. Waiting on blue button to be pressed to check password.
