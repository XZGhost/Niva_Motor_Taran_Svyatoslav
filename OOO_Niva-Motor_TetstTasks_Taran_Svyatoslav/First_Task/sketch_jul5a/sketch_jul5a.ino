#include <EEPROM.h>

const int ledPin = 13; 
const int analogInPin = A0; 
int sensorValue = 0; 
unsigned long previousMillis = 0; 
const long interval = 1000; 
const int eepromSize = 10; 
int eepromIndex = 0; 

void setup() {
  pinMode(ledPin, OUTPUT); 
  Serial.begin(9600); 
}

void loop() {
  // получ знач с АЦП
  sensorValue = analogRead(analogInPin);

  // мигаем светодиодом со скоростью, зависящей от значения с АЦП
  digitalWrite(ledPin, HIGH);
  delay(map(sensorValue, 0, 1023, 500, 50));
  digitalWrite(ledPin, LOW);
  delay(map(sensorValue, 0, 1023, 500, 50));

  // отпр знач на комп каждую секунду
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    Serial.println(sensorValue);
  }

  // записываем знач во флэш-память каждые 5 секунд
  if (currentMillis % 5000 == 0) {
    EEPROM.write(eepromIndex, sensorValue);
    eepromIndex = (eepromIndex + 1) % eepromSize;
  }

  // очищаем флэш-память после записи 10 значений
  if (eepromIndex == 0) {
    for (int i = 0; i < eepromSize; i++) {
      EEPROM.write(i, 255); 
    }
  }
}