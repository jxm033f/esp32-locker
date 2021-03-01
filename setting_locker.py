import serial
import sys
import time

"""
Before inputting locker combination. Setting passcode.
"""

def check_count():
	global isValid
	if count in acceptableCount:
		isValid = True
	else:
		isValid = False

def check_frequency():
	global isValid
	if frequency in acceptableFrequency:
		isValid = True
	else:
		isValid = False

def check_joystick():
	global isValid
	if joystick in acceptableJoystick:
		isValid = True
	else:
		isValid = False

arduino = serial.Serial('/dev/ttyUSB0', 9600)
time.sleep(2)

start = time.time()
while ((str(arduino.readline())).find("Waiting for password") == -1):
	end = time.time()
	if (end - start > 5):
		sys.exit("Is not waiting for password")


#setting up password through user input
isValid = True
print("Setting Password Mode")

count = input("Choose a value (0 to 9): ")
acceptableCount = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"]
check_count()

while not isValid:
	count = input("Input is invalid. Choose a value (0 to 9): ")
	check_count()

frequency = input("Choose a frequency (LOW or HIGH): ")
frequency = frequency.upper()
acceptableFrequency = ["LOW", "HIGH"]
check_frequency()

while not isValid:
	frequency = input("Input is invalid. Choose a frequency (LOW or HIGH): ")
	frequency = frequency.upper()
	check_frequency()

frequencyTranslation = ["0", "1"]
if frequency == acceptableFrequency[0]:
	frequency = frequencyTranslation[0]
elif frequency == acceptableFrequency[1]:
	frequency = frequencyTranslation[1]

joystick = input("Choose a direction (N, S, E, W, NE, NW, SE or SW): ")
joystick = joystick.upper()
acceptableJoystick = ["N", "S", "E", "W", "NE", "NW", "SE", "SW"]
check_joystick()

while not isValid:
	joystick = input("Input is invalid. Choose a direction (N, S, E, W, NE, NW, SE or SW): ")
	joystick = joystick.upper()
	check_joystick()

joystickTranslation = ["1", "5", "3", "7", "2", "8", "5", "6"]
if joystick == acceptableJoystick[0]:
	joystick = joystickTranslation[0]
elif joystick == acceptableJoystick[1]:
	joystick = joystickTranslation[1]
elif joystick == acceptableJoystick[2]:
	joystick = joystickTranslation[2]
elif joystick == acceptableJoystick[3]:
	joystick = joystickTranslation[3]
elif joystick == acceptableJoystick[4]:
	joystick = joystickTranslation[4]
elif joystick == acceptableJoystick[5]:
	joystick = joystickTranslation[5]
elif joystick == acceptableJoystick[6]:
	joystick = joystickTranslation[6]
elif joystick == acceptableJoystick[7]:
	joystick = joystickTranslation[7]

message = "Message: " + count + " " + frequency + " " + joystick 

arduino.write(message.encode())