#include <U8g2lib.h>
#include <Wire.h>

const float a = -0.022;
const float b = 8.646;
int8_t type = -1;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

int voltageInPin = 525;
float inputVoltage, trueInputVoltage;
float level, voltage;

void drawGraph(int8_t);
void drawPint(int, int, int8_t);

void setup() {
    Serial.begin(9600);
    u8g2.begin();
}

void loop() {
    inputVoltage = voltageInPin * (5.0 / 1023.0);
    trueInputVoltage = (16.15 / 6.58) * inputVoltage;

    if (trueInputVoltage > b) {
        trueInputVoltage = b;
    }

    voltage = b - trueInputVoltage;
    level = (trueInputVoltage - b) / a;

    u8g2.clearBuffer();

    drawGraph(type);

    int x = 300;
    int y = a * x + b;
    drawPoint(x, y, type);

    u8g2.sendBuffer();
}

void drawGraph(int8_t type) {
    u8g2.setFont(u8g2_font_ncenB08_tr);

    if (type == 1) {
        u8g2.setCursor(0, 64);
        u8g2.print("Niveau");
        u8g2.setCursor(84, 8);
        u8g2.print("Tension");
        u8g2.drawLine(0, 0, 128, 64);
    } else {
        u8g2.setCursor(90, 64);
        u8g2.print("Niveau");
        u8g2.setCursor(0, 8);
        u8g2.print("Tension");
        u8g2.drawLine(0, 64, 128, 0);
    }
}

void drawPoint(int x, int y, int8_t type) {
    u8g2.setFont(u8g2_font_ncenB10_tr);

    if (type == 1) {
        x = map(x, 0, 393, 0, 128);
        y = map(y, 0, b, 64, 0);
        u8g2.drawRFrame(x - 2, y - 2, 4, 4, 2);
    } else {
        x = map(x, 0, 393, 0, 128);
        y = map(y, 0, b, 0, 64);
        u8g2.drawRFrame(x - 2, y - 2, 4, 4, 2);
    }
}
