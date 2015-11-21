#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 4, 5, 6, 7, 8);
#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

const int MIDI_NOTES = 127;
boolean notes[MIDI_NOTES];
#define NOTE_ON 144
#define NOTE_OFF 128
byte last_cmd = 0;
byte last_note = 0;

// This function will be automatically called when a NoteOn is received.
// It must be a void-returning function with the correct parameters,
// see documentation here:
// http://arduinomidilib.fortyseveneffects.com/a00022.html
void handleNoteOn(byte channel, byte pitch, byte velocity) {
  setNote(pitch, velocity > 0);
}
void handleNoteOff(byte channel, byte pitch, byte velocity)
{
  setNote(pitch, false);
}

void setup() {
  // Connect the handleNoteOn function to the library,
  // so it is called upon reception of a NoteOn.
  MIDI.setHandleNoteOn(handleNoteOn);  // Put only the name of the function
  // Do the same for NoteOffs
  MIDI.setHandleNoteOff(handleNoteOff);
  // Initiate MIDI communications, listen to all channels
  MIDI.begin(MIDI_CHANNEL_OMNI);
  
  for(int i = 0; i < MIDI_NOTES; i++) {
    notes[i] = false;
  }
}

void setNote(byte note, boolean status) {
  notes[note] = status;
  if (status) {
    last_note = note;  
  }
}

void readStream() {
  if (Serial.available()) {
    byte b = Serial.read();
    if (isCommand(b)) {
      last_cmd = b;
      return;
    } //else it's a data byte

    while(!Serial.available()) {
      //busy loop, sorry mom
    }

    byte v = Serial.read();
    switch (last_cmd) {
      case NOTE_ON:
        setNote(b, v > 0);
        break;
      case NOTE_OFF:
        setNote(b, false);
        break;
      default:
        break;
    }
  } 
}

boolean isCommand(byte b) {
  return b > 127;
}

void loop() {
  MIDI.read();
  lcd.clear();
  lcd.print(last_note);
}
