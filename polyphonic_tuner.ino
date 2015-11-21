#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 4, 5, 6, 7, 8);
void setup() {
  lcd.begin(16, 2);
  // put your setup code here, to run once:

}

void loop() {
  lcd.setCursor(1, 0);
  lcd.print("HEY");
  // put your main code here, to run repeatedly:

}
