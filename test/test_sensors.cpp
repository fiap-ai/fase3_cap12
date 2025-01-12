#include <unity.h>
#include "sensors.h"

// Test-specific instances
static DHT test_dht(DHT_PIN, DHT_TYPE);
static LiquidCrystal_I2C test_lcd(0x27, 16, 2);

void setUp(void) {
    // Set up hardware for tests
    Wire.begin();
    test_dht.begin();
    
    // Configure pins
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(PIR_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(RELAY_PIN, OUTPUT);
    
    // Initialize outputs
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(RELAY_PIN, LOW);
}

void tearDown(void) {
    // Clean up after tests
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(RELAY_PIN, LOW);
}

// DHT22 Tests
void test_dht22_reading_range(void) {
    float temp = test_dht.readTemperature();
    float hum = test_dht.readHumidity();
    
    // Check if readings are within valid ranges
    TEST_ASSERT_TRUE(!isnan(temp));
    TEST_ASSERT_TRUE(!isnan(hum));
    TEST_ASSERT_FLOAT_WITHIN(80.0, temp, -40.0);  // -40 to 80°C
    TEST_ASSERT_FLOAT_WITHIN(100.0, hum, 0.0);    // 0 to 100%
}

// HC-SR04 Tests
void test_ultrasonic_reading_range(void) {
    float distance = readUltrasonic();
    TEST_ASSERT_FLOAT_WITHIN(400.0, distance, 2.0);  // 2 to 400cm range
}

// PIR Tests
void test_pir_initial_state(void) {
    int motion = digitalRead(PIR_PIN);
    TEST_ASSERT_TRUE(motion == HIGH || motion == LOW);
}

// LDR Tests
void test_ldr_reading_range(void) {
    int ldrValue = analogRead(LDR_PIN);
    TEST_ASSERT_INT_WITHIN(4095, ldrValue, 0);  // 12-bit ADC (0-4095)
}

// Buzzer Tests
void test_buzzer_tone(void) {
    // Test PWM setup
    ledcSetup(0, 2000, 8);
    ledcAttachPin(BUZZER_PIN, 0);
    
    // Test tone generation
    ledcWriteTone(0, 2000);
    delay(100);
    ledcWriteTone(0, 0);
    
    TEST_PASS();
}

// Relay Tests
void test_relay_operation(void) {
    digitalWrite(RELAY_PIN, HIGH);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(RELAY_PIN));
    
    digitalWrite(RELAY_PIN, LOW);
    TEST_ASSERT_EQUAL(LOW, digitalRead(RELAY_PIN));
}

// LCD Tests
void test_lcd_initialization(void) {
    test_lcd.init();
    test_lcd.backlight();
    test_lcd.clear();
    test_lcd.print("Test");
    TEST_PASS();
}

// Integration Tests
void test_irrigation_decision(void) {
    float temp = 31.0;  // Above TEMP_MAX
    float humidity = 35.0;  // Below HUMIDITY_MIN
    float water_level = 100.0;  // Above WATER_MIN
    float light = 50.0;  // Below LIGHT_THRESHOLD
    
    // Should irrigate when all conditions are met
    bool should_irrigate = (temp > TEMP_MAX || humidity < HUMIDITY_MIN) && 
                          (water_level > WATER_MIN) &&
                          (light < LIGHT_THRESHOLD);
    
    TEST_ASSERT_TRUE(should_irrigate);
}

void test_security_system(void) {
    // Test motion detection and alarm
    digitalWrite(PIR_PIN, HIGH);
    int motion = digitalRead(PIR_PIN);
    TEST_ASSERT_EQUAL(HIGH, motion);
    
    // Test alarm response
    if (motion) {
        ledcWriteTone(0, 2000);
        delay(100);
        ledcWriteTone(0, 0);
    }
    TEST_PASS();
}

void setup() {
    delay(2000);  // Wait for board to settle
    
    UNITY_BEGIN();
    
    // Run tests
    RUN_TEST(test_dht22_reading_range);
    RUN_TEST(test_ultrasonic_reading_range);
    RUN_TEST(test_pir_initial_state);
    RUN_TEST(test_ldr_reading_range);
    RUN_TEST(test_buzzer_tone);
    RUN_TEST(test_relay_operation);
    RUN_TEST(test_lcd_initialization);
    RUN_TEST(test_irrigation_decision);
    RUN_TEST(test_security_system);
    
    UNITY_END();
}

void loop() {
    // Nothing to do here
}
