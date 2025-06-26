#include <Bluepad32.h>
#include <ESP32Servo.h>

#define ENA 32  // Enable pin for left wheels
#define ENB 33  // Enable pin for right wheels
#define IN1 23  // Motor A - Input 1
#define IN2 22  // Motor A - Input 2
#define IN3 21  // Motor B - Input 1
#define IN4 25  // Motor B - Input 2

ControllerPtr myControllers[BP32_MAX_GAMEPADS];
Servo myServo01;
Servo myServo02;
Servo myServo03;
Servo myServo04;
Servo myServo05;

int servoAngle01 = 75;
int servoAngle02 = 50;
int servoAngle03 = 60;
int servoAngle04 = 90;
int servoAngle05 = 160;

const int servoPin01 = 18;
const int servoPin02 = 4;
const int servoPin03 = 5;
const int servoPin04 = 15;
const int servoPin05 = 19;

void onConnectedController(ControllerPtr ctl) {
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (myControllers[i] == nullptr) {
      Serial.printf("Controller connected at index=%d\n", i);
      ControllerProperties properties = ctl->getProperties();
      Serial.printf("Model: %s, VID=0x%04x, PID=0x%04x\n", ctl->getModelName().c_str(), properties.vendor_id, properties.product_id);
      myControllers[i] = ctl;
      return;
    }
  }
  Serial.println("No available slot for new controller");
}

void onDisconnectedController(ControllerPtr ctl) {
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (myControllers[i] == ctl) {
      Serial.printf("Controller disconnected from index=%d\n", i);
      myControllers[i] = nullptr;
      return;
    }
  }
}

void dumpGamepad(ControllerPtr ctl) {
  int axisLX = ctl->axisX();
  int axisLY = ctl->axisY();

  int axisRX = ctl->axisRX();
  int axisRY = ctl->axisRY();

  int button = ctl->buttons();
  int dpad = ctl->dpad();

  int throttle = ctl->throttle();
  int brake = ctl->brake();

  Serial.printf("dpad: %4d, buttons: %4d, axis L: %4d, %4d, axis R: %4d, %4d, brake: %4d, throttle: %4d\n",
                dpad, button, axisLX, axisLY, axisRX, axisRY,
                brake, throttle);

  updateServo01(button);  //Base Move servo - input X / B
  updateServo02(axisRY);  //Up servo 1 - input Y / A
  // updateServo03(dpad);    //Up servo 2 - d pad Up / Down
  updateServo04(button);  //Up servo 3 - d pad Up / Down
  updateServo05(button);  //Up servo 4 - Throttle / Brake

  updateMotorControl(axisLX, axisLY);  // Car movement
}

void processGamepad(ControllerPtr ctl) {
  if (ctl->a()) {
    static int colorIdx = 0;
    const uint8_t colors[][3] = { { 255, 0, 0 }, { 0, 255, 0 }, { 0, 0, 255 } };
    ctl->setColorLED(colors[colorIdx % 3][0], colors[colorIdx % 3][1], colors[colorIdx % 3][2]);
    colorIdx++;
  }
  if (ctl->b()) {
    static int led = 0;
    ctl->setPlayerLEDs(++led & 0x0F);
  }
  if (ctl->x()) {
    ctl->playDualRumble(0, 250, 0x80, 0x40);
  }
  dumpGamepad(ctl);
}

void processControllers() {
  for (auto myController : myControllers) {
    if (myController && myController->isConnected() && myController->hasData()) {
      if (myController->isGamepad()) {
        processGamepad(myController);
      }
    }
  }
}

void updateServo01(int button) {

  if (button == 2 && servoAngle01 > 42) {  // Input B Right
    servoAngle01 = max(servoAngle01 - 1, 42);
    Serial.printf("Servo 1 Decreased\n\n");
  } else if (button == 4 && servoAngle01 < 100) {  // Input X Left
    servoAngle01 = min(servoAngle01 + 1, 100);
    Serial.printf("Servo 1 Increased\n\n");
  }

  myServo01.write(servoAngle01);
}

void updateServo02(int axisvalue) {

  if (axisvalue < -300 && servoAngle02 < 160) {  // Input RY Up
    servoAngle02 = min(servoAngle02 + 1, 160);
    servoAngle03 = min(servoAngle03 + 1, 120);

    myServo02.write(servoAngle02);
    myServo03.write(servoAngle03);

    Serial.printf("Servo 2 Increased\n\n");
    Serial.printf("Servo 3 Increased\n\n");

    if (servoAngle04 > 60) {
      servoAngle04 = max(servoAngle04 - 1, 60);

      myServo04.write(servoAngle04);

      Serial.printf("Servo 4 Decreased\n\n");
    }
  } else if (axisvalue > 300 && servoAngle02 > 50) {  // Input RY Down
    servoAngle02 = max(servoAngle02 - 1, 50);
    servoAngle03 = max(servoAngle03 - 1, 50);

    myServo02.write(servoAngle02);
    myServo03.write(servoAngle03);

    Serial.printf("Servo 2 Decreased\n\n");
    Serial.printf("Servo 3 Decreased\n\n");
  }
}

// void updateServo03(int dpad) {

//   if (dpad == 1 && servoAngle03 < 130) {
//     servoAngle03 = min(servoAngle03 + 1, 130);
//     Serial.printf("Servo 3 Increased\n\n");
//   } else if (dpad == 2 && servoAngle03 > 10) {
//     servoAngle03 = max(servoAngle03 - 1, 10);
//     Serial.printf("Servo 3 Decreased\n\n");
//   }

//   myServo03.write(servoAngle03);
// }

void updateServo04(int button) {

  if (button == 8 && servoAngle04 < 130) {  // Input Y
    servoAngle04 = min(servoAngle04 + 1, 130);
    Serial.printf("Servo 4 Increased\n\n");
  } else if (button == 1 && servoAngle04 > 50) {  // Input A
    servoAngle04 = max(servoAngle04 - 1, 60);
    Serial.printf("Servo 4 Decreased\n\n");
  } else if (button == 8 && servoAngle02 <= 50) {  // Input A
    servoAngle04 = min(servoAngle04 + 1, 170);
    Serial.printf("Servo 4 Increased\n\n");
  }

  myServo04.write(servoAngle04);
}

void updateServo05(int button) {

  if (button == 128 && servoAngle05 < 160) {
    servoAngle05 = min(servoAngle05 + 1, 160);
    Serial.printf("Servo 5 Increased\n\n");
  } else if (button == 64 && servoAngle05 > 100) {
    servoAngle05 = max(servoAngle05 - 1, 100);
    Serial.printf("Servo 5 Decreased\n\n");
  }

  myServo05.write(servoAngle05);
}

// Motor Control Function
void updateMotorControl(int x, int y) {
  // int speed = abs(y) / 4;  // Scale joystick value to PWM range (0-255)
  // int turn = abs(x) / 4;   // Scale turn value

  int speed = 150;  // Scale joystick value to PWM range (0-255)
  int turn = 180;   // Scale turn value

  if (y < -300) {  // Move Forward
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else if (y > 300) {  // Move Backward
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  } else if (x > 300) {  // Turn Right
    analogWrite(ENA, turn);
    analogWrite(ENB, turn);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else if (x < -300) {  // Turn Left
    analogWrite(ENA, turn);
    analogWrite(ENB, turn);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  } else {  // Stop
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
}

void setup() {
  Serial.begin(115200);
  Serial.printf("Firmware: %s\n", BP32.firmwareVersion());
  const uint8_t* addr = BP32.localBdAddress();
  Serial.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  myServo01.attach(servoPin01);
  myServo01.write(servoAngle01);

  myServo02.attach(servoPin02);
  myServo02.write(servoAngle02);

  myServo03.attach(servoPin03);
  myServo03.write(servoAngle03);

  myServo04.attach(servoPin04);
  myServo04.write(servoAngle04);

  myServo05.attach(servoPin05);
  myServo05.write(servoAngle05);

  BP32.setup(&onConnectedController, &onDisconnectedController);
  BP32.forgetBluetoothKeys();
  BP32.enableVirtualDevice(false);
}


void loop() {
  if (BP32.update()) {
    processControllers();
  }
}
