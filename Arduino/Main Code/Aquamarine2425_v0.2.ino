#include <Wire.h>


//Simplified Logitech Extreme 3D Pro Joystick Report Parser
#include <usbhid.h>
#include <hiduniversal.h>
#include <usbhub.h>

#include "le3dp_rptparser.h"

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB                                             Usb;
USBHub                                          Hub(&Usb);
HIDUniversal                                    Hid(&Usb);
JoystickEvents                                  JoyEvents;
JoystickReportParser                            Joy(&JoyEvents);

// Include Adafruit PWM Library
#include <Adafruit_PWMServoDriver.h>

#define MIN_SPEED     1000
#define MAX_SPEED     2000
#define IDLE_SPEED    1500
#define FREQUENCY       50

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

float joyX;
float joyY;
float twist;
int slider;
int hat;
int BA;
int BB;

void setup() {
  //====Initialise Serial monitor====
  Serial.begin(115200);
  Serial.println("Start");
  //====Initialise joystick (USB)
  if (Usb.Init() == -1)
    Serial.println("OSC did not start."); //something went wrong

  delay(200);

  if (!Hid.SetReportParser(0, &Joy))
    ErrorMessage<uint8_t>(PSTR("SetReportParser"), 1  );

  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
  delay(7000);

}

int lateralMotors[2][2] = {
  {IDLE_SPEED, IDLE_SPEED},
  {IDLE_SPEED, IDLE_SPEED}
};

float mapf(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float mapped(float inVal, float inMin, float inMax, float deadZoneMin, float deadZoneMax) {

  if (inVal < deadZoneMin) {
    return mapf(inVal, deadZoneMin, inMin, 0, 1);
  }
  if (inVal > deadZoneMax) {
    return mapf(inVal, deadZoneMax, inMax, 0, -1);
  }
  else {
    return 0;
  }
}

double calibration(double in){
  return in*1.0741757+2.5991215;
}
void loop() {

  Usb.Task();


  slider = JoyEvents.getSlider();
  hat = JoyEvents.getHat();
  BA = JoyEvents.getBA();
  BB = JoyEvents.getBB();

  joyY = 0 - mapped(JoyEvents.getJoyY(), 0, 1023, 450, 574); //takes negative value of mapping
  joyX = mapped(JoyEvents.getJoyX(), 0, 1023, 400, 624);
  twist = mapped(JoyEvents.getTwist(), 0, 255, 70, 184);

  float theta = atan2(joyY, joyX);
  float power = hypot(joyY, joyX);

  float sine = sin(theta - PI / 4);
  float cosine = cos(theta - PI / 4);
  float maximum = max(abs(sine), abs(cosine));

  float leftFront = power * cosine / maximum + twist;
  float rightFront = power * sine / maximum - twist;
  float leftRear = power * sine / maximum + twist;
  float rightRear = power * cosine / maximum - twist;

  if ((power + abs(twist)) > 1) {
    leftFront /= power + abs(twist);
    rightFront /= power + abs(twist);
    leftRear /= power + abs(twist);
    rightRear /= power + abs(twist);
  }



  leftFront = pow(leftFront, 3);
  rightFront = pow(rightFront, 3);
  leftRear = pow(leftRear, 3);
  rightRear = pow(rightRear, 3);

  lateralMotors[0][0] = calibration(mapf(leftFront, -1.00, 1.00, MIN_SPEED, MAX_SPEED));
  lateralMotors[0][1] = calibration(mapf(rightFront, -1.00, 1.00, MIN_SPEED, MAX_SPEED));
  lateralMotors[1][0] = calibration(mapf(leftRear, -1.00, 1.00, MIN_SPEED, MAX_SPEED));
  lateralMotors[1][1] = calibration(mapf(rightRear, -1.00, 1.00, MIN_SPEED, MAX_SPEED));
  
  pwm.writeMicroseconds(0, lateralMotors[0][0]);
  pwm.writeMicroseconds(2, lateralMotors[0][1]);
  pwm.writeMicroseconds(4, lateralMotors[1][0]);
  pwm.writeMicroseconds(6, lateralMotors[1][1]);

  //y = 0.9309x - 2.3636


      /*
        if (BA == 1) {
          i += 1;
        }
        if (BA == 2) {
          i -= 1;
        }

        pwm.writeMicroseconds(0, i);
        pwm.writeMicroseconds(2, i);
        pwm.writeMicroseconds(4, i);
        pwm.writeMicroseconds(6, i);
      */
  Serial.print(" Percentage: ");
  Serial.print(leftFront);
  Serial.print(" ");
  Serial.print(rightFront);
  Serial.print(" ");
  Serial.print(leftRear);
  Serial.print(" ");
  Serial.print(rightRear);

  Serial.print(" PWM: ");
  Serial.print(lateralMotors[0][0]);
  Serial.print(" ");
  Serial.print(lateralMotors[0][1]);
  Serial.print(" ");
  Serial.print(lateralMotors[1][0]);
  Serial.print(" ");
  Serial.println(lateralMotors[1][1]);




}
