#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 4, 5, 6, 7, 8);


const int MIDI_NOTES = 127;
boolean notes[MIDI_NOTES];
byte noteOn = 144;
byte noteOff = 128;
byte currentNote = 0;

int noteOns = 0;


void setup() {
  Serial.begin(31250);
  for(int i = 0; i < MIDI_NOTES; i++) {
    notes[i] = false;
  }
}

void setNote(byte note, boolean status) {
  notes[note] = status;
}

enum Read_Mode {
  STREAM,
  NOTE_ON,
  NOTE_OFF
};

Read_Mode rm = STREAM;

void readStream() {
  if (Serial.available()) {
    byte commandByte = Serial.read();
    if (commandByte == noteOn) {
      rm = NOTE_ON;
    } else if (commandByte == noteOff) {
      rm = NOTE_OFF;
    } else {
      rm = STREAM;
    }
  }  
}

void readMIDI() {
  switch(rm) {
    case STREAM: return readStream();
    case NOTE_ON: 
      noteOns++;
      return readNoteOn();
    case NOTE_OFF: return readNoteOff();
  }
}

void readNoteOn() {
  if (Serial.available() < 2) {
    return;
  }

  byte note = Serial.read();
  byte velocity = Serial.read();
  setNote(note, true);
   
  rm = STREAM;
}

void readNoteOff() {
  if (Serial.available() < 2) {
    return;
  }

  byte note = Serial.read();
  byte velocity = Serial.read();
  setNote(note, false);

  rm = STREAM;
}


void loop() {
  readMIDI(); 
  lcd.setCursor(0, 1);
  lcd.print(noteOns);
}
