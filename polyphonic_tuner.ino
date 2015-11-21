#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 4, 5, 6, 7, 8);

typedef enum {
  MAJOR,
  MINOR,
  AUGMENTED,
  DIMINISHED
} Quality;

struct {
  byte root;
  Quality quality;
} Chord;

void printQuality(Quality q) {
  switch (q) {
    case MAJOR:
      lcd.print("M");
      break;
    case MINOR:
      lcd.print("m");
      break;
    case AUGMENTED:
      lcd.print("Aug");
      break;
    case DIMINISHED:
      lcd.print("Dim");
      break;
    default:
      break;
  }
}

void printRoot(byte root) {
  switch (root) {
    case 0:
      lcd.print("C");
      break;
    case 1:
      lcd.print("C#");
      break;
    case 2:
      lcd.print("D");
      break;
    case 3:
      lcd.print("D#");
      break;
    case 4:
      lcd.print("Eb");
      break;
    case 5:
      lcd.print("F");
      break;
    case 6:
      lcd.print("F#");
      break;
    case 7:
      lcd.print("G");
      break;
    case 8:
      lcd.print("Ab");
      break;
    case 9:
      lcd.print("A");
      break;
    case 10:
      lcd.print("Bb");
      break;
    case 11:
      lcd.print("B");      
      break;
    default:
      break;
  }
}


void printChord(struct Chord* c) {
  lcd.setCursor(0, 1);
  printRoot(c->root);
  printQuality(c->quality);
}

void setup() {
  lcd.begin(16, 2);
}

void loop() {
  Chord c = {root: 0, quality: MAJOR};
  printChord(&c);
}
