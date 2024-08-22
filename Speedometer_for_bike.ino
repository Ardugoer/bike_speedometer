
//  This speedometer shows up to 999.99 km/hr or 999.99 Mi/hr
//  This speedometer does not count distance
//  This speedometer uses one magnet per revolution
//  Wiring for speedometer is in Wiring1.bmp and wiring2.bmp

#include <LiquidCrystal.h>
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

// <> 

float time = 100;
unsigned long present = 0;
unsigned long present2 = 0;
unsigned long past = 0;
unsigned long past2 = 0;
unsigned int interval = 1000;       // time in milliseconds between LCD refreshes

unsigned int wheelCircum = 2194;    // wheel circumference in millimeters currently set for 27.5 inch wheel

float kmph = 0;
float mph = 0;

float intermid = 0;
float intermid2 = 0;
float intermid3 = 0;
float intermid4 = 0;

uint8_t showMiles = LOW;

void setup() {

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(A1, INPUT);           // show miles (switches at the same time tachometer turns on)

delay(250);

  showMiles = digitalRead(A1);

  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("Tachometer      ");
  lcd.setCursor(0, 1);
  lcd.print("Starting up...  ");
  delay(2500);
  lcd.setCursor(0, 0);
  lcd.print("Current Speed:  ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  attachInterrupt(digitalPinToInterrupt(2), zeroing, FALLING);
}

void zeroing () {
  time = present2 - past2;
past2 = present2;
}

void loop() {
  present2 = millis();
  present = millis();

intermid = 1000 / time;
intermid2 = intermid * wheelCircum;
intermid3 = intermid2 * 3600;
intermid4 = intermid3 / 1000000;
kmph = intermid4;

  if(kmph >= 999.99) {
    kmph = 999.99;
  }

  if(mph >= 999.99) {
    mph = 999.99;
  }


  mph = kmph / 1.60;

  if (showMiles == HIGH && present - past >= interval) {
    lcd.setCursor(0, 1);
    lcd.print("      ");
    lcd.setCursor(0, 1);
    lcd.print(mph);
    lcd.setCursor(6, 1);
    lcd.print(" Mi/hr   ");
    past = present;
  }

  if (showMiles == LOW && present - past >= interval) {
    lcd.setCursor(0, 1);
    lcd.print("      ");
    lcd.setCursor(0, 1);
    lcd.print(kmph);
    lcd.setCursor(6, 1);
    lcd.print(" km/hr   ");
    past = present;
  }

}
