#include "sensors.h"

float readUltrasonic() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    
    long duration = pulseIn(ECHO_PIN, HIGH);
    return duration * 0.034 / 2;
}

bool readPIR() {
    return digitalRead(PIR_PIN);
}

float readLDR() {
    int ldrValue = analogRead(LDR_PIN);
    return (ldrValue / 4095.0) * 100;
}
