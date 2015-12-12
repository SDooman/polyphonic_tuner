#include <MIDI.h>
#include <LiquidCrystal.h>


// Initialize libraries
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
MIDI_CREATE_DEFAULT_INSTANCE();

String message = ""; // The interface with the LCD display - top row.
String subMessage = ""; // The interface with the LCD display - bottom row

boolean makesChord = false; // For determining if chord is triad
boolean wasChanged = false; // If we have received a noteOn or noteOff command recently.

const int MIDI_NOTES = 127;
boolean notes[MIDI_NOTES];

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

  lcd.begin(16,2);
  lcd.clear();
}


/*
 * Manipulates the notes array and notifies the main loop that it has changed
 */
void setNote(byte note, boolean status) {
  notes[note] = status;
  wasChanged = true;
}

/*
 * Displays the message and submessage in the LCD display.
 *              ________________
 *  message    |C  D            |
 *             +----------------+
 *  submessage |   #            |
 *             ------------------
 */
void display() {
  lcd.clear();
  lcd.print(message);

  if (!makesChord) { 
    lcd.setCursor(0,1);
    lcd.print(subMessage);
  }
}

void loop() {
  MIDI.read();
  
  if(wasChanged) {
    wasChanged = false;
    array_to_chord();
    display();
  }
  
}
