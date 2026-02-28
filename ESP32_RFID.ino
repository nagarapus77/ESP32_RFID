#include <MFRC522.h>
#include <Wire.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
MFRC522 rf(5,4);

// char data[50];
byte i;
void setup() {
  // put your setup code here, to run once:
  Wire.begin(21,22);
  SPI.begin();
rf.PCD_Init();
lcd.init();
lcd.backlight();
Serial.begin(115200);
pinMode(2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!(rf.PICC_IsNewCardPresent())) return;
  if(!(rf.PICC_ReadCardSerial())) return;

  lcd.clear();
lcd.setCursor(0, 0);
lcd.print("CARD IS READED");
lcd.setCursor(0, 1);
lcd.print("UID:");

for(i=0;i<rf.uid.size;i++){
  Serial.print(rf.uid.uidByte[i],HEX);
  lcd.print(rf.uid.uidByte[i],HEX);
}
lcd.print("      ");
Serial.println();
digitalWrite(2,HIGH);
delay(500);
digitalWrite(2,LOW);

delay(2000);
}
