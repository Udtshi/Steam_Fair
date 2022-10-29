#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f,16,2);
#define SensorPin A1
#define PhotoPin 2
#define OFFSET 0.00
int count = 0;
char *printed_text[] = {"Neutral", "Acid", "Base"};

void setup(){
  pinMode(PhotoPin, INPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("pH: ");
}

void loop(){
  /*
  while (digitalRead(PhotoPin));
  while (!digitalRead(PhotoPin));

  count ++;
  */
  int SensorValue = analogRead(SensorPin);
  int message_num;
  float phValue=(float)SensorValue * 5.0 / 1024;
  phValue = (phValue * 3.5) + OFFSET + 0.68;
  lcd.setCursor(4,0);
  lcd.print(phValue);
  Serial.print("pH:");
  Serial.println(phValue,2);

  if (6.95<phValue && phValue<7.04){
    message_num = 0;
  }else{
    if(phValue<6.94){
      message_num = 1;
    }else{
      message_num = 2;
    }
  }
  lcd.setCursor(0,1);
  lcd.print("       ");
  Serial.println(printed_text[message_num]);
  lcd.setCursor(0,1);
  lcd.print(printed_text[message_num]);
  delay(100);
}