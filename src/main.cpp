#include <M5Cardputer.h>
#include "USBHIDGamepad.h"

USBHIDGamepad Gamepad;

int x = 120;

float X = 0.0, Y = 0.0, Z = 0.0;
const float alpha = 0.12; //smoothing parameter the lower, the smoother (0.01 to 1.0)

void setup() {
    M5.begin();
    M5Cardputer.begin();
    Gamepad.begin();
    M5Cardputer.Display.setTextSize(3.0, 3.0); 
}

void loop() {
    M5.update();
    M5Cardputer.update();
    
    if (M5Cardputer.Keyboard.isChange()){
        //sensitivity settings 
        if (M5Cardputer.Keyboard.isKeyPressed(';')){
            x += 5;
            M5Cardputer.Display.clear();
            M5Cardputer.Display.setCursor(20, 20);
            M5Cardputer.Display.print(x);
        }
        if (M5Cardputer.Keyboard.isKeyPressed('.')){
            x -= 5;
            M5Cardputer.Display.clear();
            M5Cardputer.Display.setCursor(20, 20);
            M5Cardputer.Display.print(x);
        }
    }

    
    if (M5Cardputer.Keyboard.isKeyPressed('1')) {
        Gamepad.pressButton(4);
    } else {
        Gamepad.releaseButton(4);
    }

    if (M5Cardputer.Keyboard.isKeyPressed('2')) {
        Gamepad.pressButton(2);
    } else {
        Gamepad.releaseButton(2);
    }

    if (M5Cardputer.Keyboard.isKeyPressed('q')) {
        Gamepad.pressButton(3);
    } else {
        Gamepad.releaseButton(3);
    }

    if (M5Cardputer.Keyboard.isKeyPressed('`')) {
        Gamepad.pressButton(1);
    } else {
        Gamepad.releaseButton(1);
    }
    
    
    float rX, rY, rZ;
    M5.Imu.getAccelData(&rX, &rY, &rZ);

    // smoothing
    X = (alpha * rX) + ((1.0 - alpha) * X);
    //Y = (alpha * rY) + ((1.0 - alpha) * Y);

    int wheelPos = map(X * 100, x * -1, x, 127, -128);
    wheelPos = constrain(wheelPos, -128, 127);

    Gamepad.leftStick((int8_t)wheelPos, 0);

    delay(5); 
}