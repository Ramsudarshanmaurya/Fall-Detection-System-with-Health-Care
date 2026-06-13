#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MPU6050.h>
#include <MAX30100_PulseOximeter.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
MPU6050 mpu;
PulseOximeter pox;

SoftwareSerial gsm(7, 8); // RX, TX

float heartRate;
float spo2;

unsigned long lastReport = 0;

const char phoneNumber[] = "+91XXXXXXXXXX";

void sendSMS(String message)
{
  gsm.println("AT+CMGF=1");
  delay(1000);

  gsm.print("AT+CMGS=\"");
  gsm.print(phoneNumber);
  gsm.println("\"");

  delay(1000);

  gsm.print(message);

  delay(500);

  gsm.write(26);

  delay(5000);
}

void setup()
{
  Serial.begin(9600);
  gsm.begin(9600);

  Wire.begin();

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Health Monitor");

  mpu.initialize();

  if (!pox.begin())
  {
    lcd.clear();
    lcd.print("MAX30100 Error");
    while (1);
  }

  delay(2000);
  lcd.clear();
}

void loop()
{
  pox.update();

  heartRate = pox.getHeartRate();
  spo2 = pox.getSpO2();

  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  float accel =sqrt((long)ax * ax +(long)ay * ay +(long)az * az) / 16384.0;

  lcd.setCursor(0, 0);
  lcd.print("HR:");
  lcd.print((int)heartRate);
  lcd.print(" BPM ");

  lcd.setCursor(0, 1);
  lcd.print("S:");
  lcd.print((int)spo2);
  lcd.print("%   ");

  if (millis() - lastReport > 1000)
  {
    Serial.print("Heart Rate: ");
    Serial.print(heartRate);

    Serial.print(" BPM  SpO2: ");
    Serial.print(spo2);
    Serial.println("%");

    lastReport = millis();
  }

  // Fall Detection
  if (accel > 3.0)
  {
    lcd.clear();
    lcd.print("FALL DETECTED");

    sendSMS("Emergency Alert! Fall Detected. Please check immediately.");

    delay(10000);
    lcd.clear();
  }

  // Abnormal Heart Rate
  if (heartRate > 120 || heartRate < 50)
  {
    sendSMS("Warning! Abnormal Heart Rate Detected.");
    delay(10000);
  }

  // Low SpO2
  if (spo2 > 0 && spo2 < 90)
  {
    sendSMS("Warning! Low SpO2 Detected.");
    delay(10000);
  }
}
