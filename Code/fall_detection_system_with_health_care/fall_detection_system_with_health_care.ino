#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <MAX30100_PulseOximeter.h>
#include <TinyGPS++.h>

// Objects
Adafruit_MPU6050 mpu;
LiquidCrystal_I2C lcd(0x27, 20, 4);
SoftwareSerial gsm(9, 10);     // GSM
SoftwareSerial gps(3, 4);      // GPS
TinyGPSPlus gpsData;
PulseOximeter pox;

// Pins
const int pulseSensorPin = A0;
const int redLedPin = 5;
const int buzzerPin = 6;

bool alertSent = false;

void setup() {
  Serial.begin(9600);
  
  gsm.begin(9600);
  gps.begin(9600);
  
  lcd.begin(20, 4);
  lcd.backlight();

  if (!mpu.begin()) {
    lcd.print("MPU Failed!");
    while (1);
  }

  if (!pox.begin()) {
    lcd.print("MAX30100 Failed!");
    while (1);
  }

  pinMode(redLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  lcd.print("System Ready");
  delay(2000);
  lcd.clear();
}

void loop() {

  pox.update();   // VERY IMPORTANT

  // ===== MPU6050 =====
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  lcd.setCursor(0, 0);
  lcd.print("Acc X:");
  lcd.print(a.acceleration.x);

  // Fall detection (strong threshold)
  if (abs(a.acceleration.x) > 15 ||
      abs(a.acceleration.y) > 15 ||
      abs(a.acceleration.z) > 15) {
    triggerAlert("Fall Detected!");
  }

  // ===== Pulse Sensor =====
  int pulseValue = analogRead(pulseSensorPin);

  lcd.setCursor(0, 1);
  lcd.print("Pulse:");
  lcd.print(pulseValue);

  if (pulseValue > 800) {
    triggerAlert("High Pulse!");
  }

  // ===== SpO2 =====
  float spo2 = pox.getSpO2();

  lcd.setCursor(0, 2);
  lcd.print("SpO2:");
  lcd.print(spo2);

  if (spo2 < 90 && spo2 > 0) {
    triggerAlert("Low SpO2!");
  }

  delay(1000);
}

void triggerAlert(String msg) {

  if (alertSent) return;   // prevent spam

  digitalWrite(redLedPin, HIGH);
  digitalWrite(buzzerPin, HIGH);

  float lat = 26.765844;
  float lon = 83.364944;

  // ===== Read GPS =====
  gps.listen();
  unsigned long start = millis();
  while (millis() - start < 3000) {
    while (gps.available()) {
      gpsData.encode(gps.read());
    }
  }

  if (gpsData.location.isValid()) {
    lat = gpsData.location.lat();
    lon = gpsData.location.lng();
  }

  String location = "https://maps.google.com/?q=" + String(lat, 6) + "," + String(lon, 6);

  // ===== Send SMS =====
  gsm.listen();
  sendSMS(msg + "\nLocation: " + location);

  digitalWrite(redLedPin, LOW);
  digitalWrite(buzzerPin, LOW);

  alertSent = true;  // send only once
}

void sendSMS(String msg) {

  gsm.println("AT+CMGF=1");
  delay(1000);

  gsm.println("AT+CMGS=\"+918948253069\"");
  delay(1000);

  gsm.print(msg);
  delay(500);

  gsm.write(26);
  delay(3000);
}