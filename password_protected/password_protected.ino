#include "Freenove_WS2812_Lib_for_ESP32.h"
#include <ESP32Servo.h>

//Set up pins
#define button_count 14
#define button_er    15
#define servoPin     18
#define switch_onoff 5

//Set up RGB Wheel
#define leds_pin     2
#define leds_count   8
#define channel      0

//#define red_pin 4
//#define green_pin 2
//#define blue_pin 0

Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(leds_count, leds_pin, channel, TYPE_GRB);
Servo myservo;

bool er_isPressed = false;
bool hasStarted = false;
bool hasEntered = false;
bool hasRestart = false;
bool lockOpen = false;
bool waitToClose = false;

bool count_isPressed = false;
int count_password = -1;

int switch_password;

int xyzPins[] = {12, 13, 9};
int xyCornerDirection[4][3] = { {4095, 0, 1}, {0, 0, 7}, {0, 4095, 5}, {4095, 4095, 3} };
int xyCorners = 4;
int isCorner = false;

int led_position[8][2] = { {0, 3}, {1, 4}, {2, 5}, {3, 6}, {4, 7}, {5, 8}, {6, 1}, {7, 2} };
int m_color[2][3] = { {0, 0, 255}, {0, 0, 0} };
int led_password = -1;

//void clear_led() {
//  digitalWrite(red_pin, HIGH);
//  digitalWrite(green_pin, HIGH);
//  digitalWrite(blue_pin, HIGH);
//}

void clear_leds() {
  for (int i = 0; i < leds_count; i++) {
    strip.setLedColorData(i, m_color[1][0], m_color[1][1], m_color[1][2]);
  }
}

void fill_led(int led) {
  clear_leds();
  strip.setLedColorData(led, m_color[0][0], m_color[0][1], m_color[0][2]);
  strip.show();
  led_password = led_position[led][1];
}

bool check_password() {
  if (led_password == 6 && count_password == 0 && switch_password == 1) {
    return true;
  }
  return false;
}

void setup() {
  Serial.begin(9600);

  pinMode(button_count, INPUT_PULLUP);
  pinMode(button_er, INPUT_PULLUP);
  pinMode(switch_onoff, INPUT);
  pinMode(xyzPins[2], INPUT_PULLUP);

//  pinMode(red_pin, OUTPUT);
//  pinMode(green_pin, OUTPUT);
//  pinMode(blue_pin, OUTPUT);

//  clear_led();

  strip.begin();
  strip.setBrightness(10);
  clear_leds();
  strip.show();

  myservo.setPeriodHertz(50);
  myservo.attach(servoPin, 500, 2500);
}

void loop() {
  int count_Value = digitalRead(button_count);
  int er_Value = digitalRead(button_er);

  int x_Value = analogRead(xyzPins[0]);
  int y_Value = analogRead(xyzPins[1]);
  int z_Value = digitalRead(xyzPins[2]);

  if (!hasStarted) {
    if (er_Value == HIGH && er_isPressed) {
      er_isPressed = !er_isPressed;
      hasStarted = !hasStarted;
      delay(100);
    } else if (er_Value == LOW && !er_isPressed) {
      er_isPressed = !er_isPressed;
    }
  } else if (hasStarted) {
    if (!hasEntered) {
      switch_password = digitalRead(switch_onoff);
      
      if (count_Value == HIGH  && count_isPressed) {
        count_isPressed = !count_isPressed;
        count_password += 1;
        if (count_password == 10) {
          count_password = 0;
        }
        delay(100);
      } else if (count_Value == LOW && !count_isPressed) {
        count_isPressed = !count_isPressed;
      }

      Serial.printf("X,Y,Z: %d,\t%d,\t%d\n", x_Value, y_Value, z_Value);
      for (int curr = 0; curr < xyCorners; curr++) {
        if ((x_Value == xyCornerDirection[curr][0]) && (y_Value == xyCornerDirection[curr][1])) {
          fill_led(xyCornerDirection[curr][2]);
          isCorner = true;
        }
      }
      if (!isCorner) {
        if (x_Value == 4095) {
          fill_led(2);
        } else if (x_Value == 0) {
          fill_led(6);
        } else if (y_Value == 4095) {
          fill_led(4);
        } else if (y_Value == 0) {
          fill_led(0);
        }
      }
      isCorner = false;
    }

    if (er_Value == HIGH && er_isPressed && !hasEntered) {
      er_isPressed = !er_isPressed;
      hasEntered = !hasEntered;
      lockOpen = false;
      if (hasRestart) {
        hasRestart = !hasRestart;
      }
      delay(100);
    } else if (er_Value == HIGH && er_isPressed && hasEntered && !hasRestart) {
      er_isPressed = !er_isPressed;
      hasEntered = !hasEntered;
      hasRestart = !hasRestart;
      count_password = -1;

      if (waitToClose) {
        myservo.write(0);
        delay(500);
        waitToClose = false;
      }
      
      delay(100);
    } else if (er_Value == LOW && !er_isPressed) {
      er_isPressed = !er_isPressed;
    }

    if (hasEntered) {
      bool isCorrect = check_password();
      if (isCorrect) {
        Serial.println("Correct Password Entered");
        if (!lockOpen) {
          myservo.write(90);
          delay(500);
          lockOpen = !lockOpen;
          waitToClose = true;
        }
      } else {
        Serial.println("Incorrect Password Entered");
      }
    }
    
  }
}
