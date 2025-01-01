#include <U8g2lib.h>
#include <Wire.h>

#define R1 6.58
#define R2 9.57

const float a = -0.022;
const float b = 8.646;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

const uint8_t buttonPin = A0;
bool buttonPressed = false;
uint8_t state = 0;

int voltageInPin = 0;
float inputVoltage, trueInputVoltage;
float level, voltage;

void drawGraph(float, float, int8_t);
void drawPint(float, float, int8_t);

void setup() {
    u8g2.begin();

    pinMode(buttonPin, INPUT);
}

void loop() {
    if (digitalRead(buttonPin) && !buttonPressed) {
        state++;
        if (state > 2) {
            state = 0;
        }
        buttonPressed = true;
    } else if (!digitalRead(buttonPin)) {
        buttonPressed = false;
    }

    voltageInPin = analogRead(A1);
    inputVoltage = voltageInPin * (5.0 / 1023.0);
    trueInputVoltage = ((R1 + R2) / R1) * inputVoltage;

    if (trueInputVoltage > b) {
        trueInputVoltage = b;
    }

    level = (trueInputVoltage - b) / a;

    voltage = b - trueInputVoltage;
    voltage = map(voltage, 0, b, b, 0);

    u8g2.clearBuffer();

    switch (state) {
    case 0:
        u8g2.setFont(u8g2_font_ncenB08_tr);
        u8g2.setCursor(20, 10);
        u8g2.print("Mesures (mm)");

        u8g2.setFont(u8g2_font_ncenB10_tr);
        u8g2.setCursor(0, 30);
        u8g2.print("Entree  :  " + String(trueInputVoltage) + " V");
        u8g2.setCursor(0, 45);
        u8g2.print("Niveau  :  " + String(level));
        u8g2.setCursor(0, 60);
        u8g2.print("CMD      :  " + String(voltage) + " V");
        break;
    case 1:
        drawGraph(level, trueInputVoltage, 1);
        drawPoint(level, trueInputVoltage, 1);
        break;
    case 2:
        drawGraph(level, trueInputVoltage, -1);
        drawPoint(level, trueInputVoltage, -1);
        break;
    }

    u8g2.sendBuffer();
}

void drawGraph(float x, float y, int8_t type) {
    u8g2.setFont(u8g2_font_ncenB08_tr);

    if (type == 1) {
        u8g2.setCursor(0, 64);
        u8g2.print("Niveau: " + String((int)x) + "mm");
        u8g2.setCursor(48, 8);
        u8g2.print("Tension: " + String(y) + "V");
        u8g2.drawLine(0, 0, 128, 64);
    } else {
        x = map(x, 0, 393, 393, 0);
        u8g2.setCursor(42, 64);
        u8g2.print("Niveau: " + String((int)x) + "mm");
        u8g2.setCursor(0, 8);
        u8g2.print("Tension: " + String(y) + "V");
        u8g2.drawLine(0, 64, 128, 0);
    }
}

void drawPoint(float x, float y, int8_t type) {
    u8g2.setFont(u8g2_font_ncenB10_tr);

    if (type == 1) {
        x = map(x, 0, 393, 0, 128);
        y = map(y, 0, b, 64, 0);
        u8g2.drawRFrame(x - 4, y - 4, 4, 4, 2);
    } else {
        x = map(x, 0, 393, 128, 0);
        y = map(y, 0, b, 64, 0);
        u8g2.drawRFrame(x - 4, y - 4, 4, 4, 2);
    }
}
