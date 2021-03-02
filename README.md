# Module 2: Secret Locker
COMS BC 3930

Through this module, I created an interactive locker that allows you to unlock a secret box if given the correct password. The locker has 5 modes, which allow for different functions to occur depending on the state. Both the Raspberry Pi and ESP32 are used for this module. Unlike Module 1, the Raspberry Pi is only used for its power source as the whole program is being runned through the ESP32.

## Materials:
- Raspberry Pi
- ESP32
- 1 analog joystick
- 2 large buttons
- 1 SPST switch
- 1 LEDPixel
- 1 Servo
- 1 PWM

## Hardware Configuration
### Joystick
GND - GND <br />
5V  - 3.5V <br />
VRX - Pin 12 <br />
VRY - Pin 13 <br />
SW  - Pin 9 <br />

### Buttons
Blue Button  - Pin 15 <br />
Green Button - Pin 14 <br />

### Switch
Pin 5

### LEDPixel
S - Pin 2 <br />
V - 3.5V <br />
G - GND <br />

### Servo
Signal - Pin 18 <br />
VCC    - 5V <br />
GND    - GND <br />

### PWM
Pin 4

## Modes
1. Locker Combination has not begun
    1. All inputs (besides the blue button) are at rest and states aren't saved.
    2. Python script is run which allows user to set a passcode.
    3. Waiting on blue button to start.
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

## Executing Program
### On Raspberry Pi
1. Go to [Arduino Site](https://www.arduino.cc/en/software)
2. Download Linux ARM 32-bit
3. Extract file and install the Arduino IDE in dowloaded directory (eg. Downloads)
```bash
cd Downloads
tar -xvf arduino-1.8.13-linuxarm.tar.xz
cd arduino-1.8.13
sudo ./install.sh
```
4. Clone esp32-locker
```bash
git clone https://github.com/jxm033f/esp32-locker.git
```
5. Open Arduino IDE -> File -> Open -> password_protected.ino <br />
        1. File is located esp32-locker/password_protected
6. Upload Code which will allow it to run through the ESP32
7. Then run setting_locker.py on Terminal
```bash
python3 setting_locker.py
```

### On Normal Computer
1. Go to [Arduino Site](https://www.arduino.cc/en/software)
2. Download appropiate software and install the Arduino IDE

Follow Steps 4-7 from executing on a Raspberry Pi
* You will need to change line 30 on setting_locker.py to your correct port

## Images
![Front View](https://user-images.githubusercontent.com/11239829/109461118-b2fe6480-7a2f-11eb-962d-6110937e424b.jpg)
![Top View](https://user-images.githubusercontent.com/11239829/109461141-bb569f80-7a2f-11eb-9156-28cfd674450a.jpg)
![Side View](https://user-images.githubusercontent.com/11239829/109461128-b7c31880-7a2f-11eb-9d9b-35b5b2e10c72.jpg)
![Inside View](https://user-images.githubusercontent.com/11239829/109461123-b560be80-7a2f-11eb-8e0b-67ce48e2a3a6.jpg)

## Links
[Blog Post](http://edblogs.columbia.edu/comsx3930-001-2021-1/2021/03/01/module-2-secret-locker/) <br />
[Locker Video](https://youtu.be/M6yTO8w6JTk) <br />
