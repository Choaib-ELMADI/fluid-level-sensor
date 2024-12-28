#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

const uint8_t buttonPin = A0;
bool buttonPressed = false;
uint8_t state = 0;

void setup() {
    Serial.begin(9600);
    u8g2.begin();

    pinMode(buttonPin, INPUT);
}

void loop() {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.clearBuffer();

    if (digitalRead(buttonPin) && !buttonPressed) {
        state++;
        if (state > 2) {
            state = 0;
        }
        buttonPressed = true;
    } else if (!digitalRead(buttonPin)) {
        buttonPressed = false;
    }

    Serial.print("State: ");
    Serial.println(state);

    u8g2.setCursor(0, 30);
    u8g2.print("State: " + String(state));

    u8g2.sendBuffer();
}
