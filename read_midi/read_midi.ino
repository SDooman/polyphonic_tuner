#include <MIDI.h>
#include <midi_Defs.h>
#include <midi_Message.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

String message = "";
boolean wasChanged = false;

const int MIDI_NOTES = 127;
boolean notes[MIDI_NOTES];
#define NOTE_ON 144
#define NOTE_OFF 128

/* This callback function will be automatically called when noteOn is received
 * It modifies the notes array according to the message received.
 *
 * NOTE: some MIDI instruments turn notes off by sending a velocity of 0.
 */ 
void handleNoteOn(byte channel, byte pitch, byte velocity) {
  setNote(pitch, velocity > 0);
}

/* This callback function will be automatically called when noteOff is received
 * It modifies the notes array according to the message received.
 *
 */ 
void handleNoteOff(byte channel, byte pitch, byte velocity) {
  setNote(pitch, false);
}

void setup() {
  // Connect the handleNoteOn function to the library,
  // so it is called upon reception of a NoteOn.
  MIDI.setHandleNoteOn(handleNoteOn);
  // Do the same for NoteOffs
  MIDI.setHandleNoteOff(handleNoteOff);
  // Initiate MIDI communications, listen to all channels
  MIDI.begin(MIDI_CHANNEL_OMNI);

  // Initialize notes array.  
  for(int i = 0; i < MIDI_NOTES; i++) {
    notes[i] = false;
  }
}


/*
 * Manipulates the notes array.
 */
void setNote(byte note, boolean status) {
  notes[note] = status;
  wasChanged = true;
}


void loop() {
  MIDI.read();
  
  if(wasChanged){
    wasChanged = false;
    array_to_chord();
    lcd.clear();
    lcd.print(message);
  }
  
}
