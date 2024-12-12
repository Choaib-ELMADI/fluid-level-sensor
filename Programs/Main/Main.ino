#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

float outputVoltage;
float inputVoltage;
float niveau;
float voltage;

const float a = -0.022;
const float b = 8.646;

void setup() {
    Serial.begin(9600);
    u8g2.begin();
}

void loop() {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.clearBuffer();

    u8g2.setCursor(10, 15);
    u8g2.print("Mesures (mm)");

    outputVoltage = analogRead(A0);
    outputVoltage = (float)map(outputVoltage, 0, 1023, 0, 5);
    inputVoltage = (17 / 6.8) * outputVoltage;
    voltage = b - inputVoltage;

    u8g2.setCursor(0, 30);
    u8g2.print("Input    : " + String(inputVoltage) + "V");

    niveau = (inputVoltage - b) / a;
    u8g2.setCursor(0, 45);
    u8g2.print("Niveau  : " + String(niveau));

    u8g2.setCursor(0, 60);
    u8g2.print("Voltage : " + String(voltage) + "V");

    u8g2.sendBuffer();
}
