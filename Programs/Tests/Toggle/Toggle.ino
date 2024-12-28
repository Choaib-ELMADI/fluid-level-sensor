uint8_t state = 0;

void setup() {
    Serial.begin(9600);
    pinMode(13, INPUT);
}

void loop() {
    if (digitalRead(13)) {
        state++;
        if (state > 2) {
            state = 0;
        }
        while (digitalRead(13)) {
            delay(1);
        }
    }
    Serial.print("State: ");
    Serial.println(state);
}
