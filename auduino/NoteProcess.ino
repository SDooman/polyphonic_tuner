String intToLetter[12] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
String intToLetterPrefix[12] = {"C", "C", "D", "D", "E", "F", "F", "G", "G", "A", "A", "B"};
boolean intToLetterIsBlackKey[12] = {false, true, false, true, false, false, true, false, true, false, true, false};

const int majMask = 145; // C Major Triad as mask
const int minMask = 137;  // C Minor Triad as mask
const int dimMask = 73; // C Diminished Triad as mask
const int augMask = 273; // C Augmented Triad as mask
const int minMin7Mask = 1161; // C minor minor 7th mask
const int halfDim7Mask = 1097; // C half diminished 7th mask
const int fullDim7Mask = 585; // C fully diminished 7th mask
const int minMaj7Mask = 2185; // C minor major 7th mask
const int majMin7Mask = 1169; // C dominant seventh as mask
const int majMaj7Mask = 2193; // C majorMinor mask

const int majMaskpb2 = 147; // C Major Triad as mask + b2
const int minMaskpb2 = 139;  // C Minor Triad as mask+ b2
const int dimMaskpb2 = 75; // C Diminished Triad as mask+ b2
const int augMaskpb2 = 275; // C Augmented Triad as mask+ b2
const int minMin7Maskpb9 = 1163; // C minor minor 7th mask+ b9
const int halfDim7Maskpb9 = 1099; // C half diminished 7th mask+ b9
const int fullDim7Maskpb9 = 587; // C fully diminished 7th mask+ b9
const int minMaj7Maskpb9 = 2187; // C minor major 7th mask+ b9
const int majMin7Maskpb9 = 1171; // C dominant seventh as mask+ b9
const int majMaj7Maskpb9 = 2195; // C majorMinor mask+ b9

const int majMaskp2 = 149; // C Major Triad as mask + 2
const int minMaskp2 = 141;  // C Minor Triad as mask + 2
const int dimMaskp2 = 77; // C Diminished Triad as mask + 2
const int augMaskp2 = 277; // C Augmented Triad as mask + 2
const int minMin7Maskp9 = 1165; // C minor minor 7th mask +9
const int halfDim7Maskp9 = 1101; // C half diminished 7th mask +9
const int fullDim7Maskp9 = 589; // C fully diminished 7th mask +9
const int minMaj7Maskp9 = 2189; // C minor major 7th mask +9
const int majMin7Maskp9 = 1173; // C dominant seventh as mask +9
const int majMaj7Maskp9 = 2197; // C majorMinor mask +9

const int majMaskp4 = 145 + 32; // C Major Triad as mask
const int minMaskp4 = 137 + 32;  // C Minor Triad as mask
const int dimMaskp4 = 73 + 32; // C Diminished Triad as mask
const int augMaskp4 = 273 + 32; // C Augmented Triad as mask
const int minMin7Maskp4 = 1161 + 32; // C minor minor 7th mask
const int minMaj7Maskp4 = 2185 + 32; // C minor major 7th mask
const int majMin7Maskp4 = 1169 + 32; // C dominant seventh as mask
const int majMaj7Maskp4 = 2193 + 32; // C majorMinor mask

/*
 * Converts the notes array into an int which represents which of 12 notes in
 * the major scale are being played. Arduino ints are 16 bits, but we
 * only use the last 12. Note that we eliminate octave information.
 * 
 * If some notes are currently on, we will call the detectChord method, which
 * will identify the chord and print a description.
 */
void array_to_chord() {
  int result = 0;
  for(int i = 0; i < MIDI_NOTES; i++){
    if(notes[i]){
      result |= 1 << (i % 12);
    }
  }
  
  analyze(result);
}

/*
 * Attempts to analyze a chord and if it cannot not, defers to displayNotes
 * which prints the individual notes being played.
 *
 */
void analyze(int chord) {
    detectChord(chord);

    if (!makesChord) {
      displayNotes(chord);
    }
}

/*
 * Displays individual notes in the chord by cycling through it and consulting
 * the intToLetterPrefix array. Note names are put into message, and
 * any sharps are displayed in submessage.
 *
 * The message/submessage variables are the interface with the lcd display.
 * 
 *              ________________
 *  message    |C  D            |
 *             +----------------+
 *  submessage |   #            |
 *             ------------------
 */ 
void displayNotes(int chord) {
  //No triadic chord was found so print notes being played
  for (int root = 0; root < 12; root++) {
    //if current first bit is on, turn it on in message
    if ((chord >> root) & 1) {
      message += intToLetterPrefix[root];
      if (intToLetterIsBlackKey[root]) {
        subMessage += "#";
      } else {
        subMessage += " ";
      }
    } else {
      message += " ";
      subMessage += " ";
    }
  }
}

/*
 * Detects which chord is currently being played.
 * It expects a 12-bit int which represents the chord. It checks the chord 
 * agains each mask and if it gets a match it displays the root and quality.
 * If not, it rotates the chord and tries again.
 */
void detectChord(int chord) {
  message = "";
  subMessage="";

  makesChord = true;
  for (int root = 0; root < 12; root++) { // only 12 possible rotations
    switch (chord) {
        
      case majMask:
        message = intToLetter[root];
        message += " Major";
        return;
      
      case minMask:
        message = intToLetter[root];
        message += " Minor";
        return;

      case augMask:
        message = intToLetter[root];
        message += " Aug";
        return;

      case dimMask:
        message = intToLetter[root];
        message += " Dim";
        return;

      case minMin7Mask:
        message = intToLetter[root];
        message += " Min Min 7";
        return;

      case halfDim7Mask:
        message = intToLetter[root];
        message += " Half Dim 7";
        return;

      case fullDim7Mask:
        message = intToLetter[root];
        message += " Full Dim 7";
        return;

      case majMin7Mask:
        message = intToLetter[root];
        message += " Maj Min 7";
        return;
        
      case majMaj7Mask:
        message = intToLetter[root];
        message += " Maj Maj 7";
        return;

      case minMaj7Mask:
        message = intToLetter[root];
        message += " Min Maj 7";
        return;

      /**************/

      case majMaskpb2:
        message = intToLetter[root];
        message += " Major + b2";
        return;
      
      case minMaskpb2:
        message = intToLetter[root];
        message += " Minor + b2";
        return;

      case augMaskpb2:
        message = intToLetter[root];
        message += " Aug + b2";
        return;

      case dimMaskpb2:
        message = intToLetter[root];
        message += " Dim + b2";
        return;

      case minMin7Maskpb9:
        message = intToLetter[root];
        message += " Min Min 7 b9";
        return;

      case halfDim7Maskpb9:
        message = intToLetter[root];
        message += " Half Dim 7 b9";
        return;

      case fullDim7Maskpb9:
        message = intToLetter[root];
        message += " Full Dim 7 b9";
        return;

      case majMin7Maskpb9:
        message = intToLetter[root];
        message += " Maj Min 7 b9";
        return;
        
      case majMaj7Maskpb9:
        message = intToLetter[root];
        message += " Maj Maj 7 b9";
        return;

      case minMaj7Maskpb9:
        message = intToLetter[root];
        message += " Min Maj 7 b9";
        return;

      /************/

      case majMaskp2:
        message = intToLetter[root];
        message += " Major + 2";
        return;
      
      case minMaskp2:
        message = intToLetter[root];
        message += " Minor + 2";
        return;

      case augMaskp2:
        message = intToLetter[root];
        message += " Aug + 2";
        return;

      case dimMaskp2:
        message = intToLetter[root];
        message += " Dim + 2";
        return;

      case minMin7Maskp9:
        message = intToLetter[root];
        message += " Min Min 7 + 9";
        return;

      case halfDim7Maskp9:
        message = intToLetter[root];
        message += " Half Dim 7 + 9";
        return;

      case fullDim7Maskp9:
        message = intToLetter[root];
        message += " Full Dim 7 +9";
        return;

      case majMin7Maskp9:
        message = intToLetter[root];
        message += " Maj Min 7 + 9";
        return;
        
      case majMaj7Maskp9:
        message = intToLetter[root];
        message += " Maj Maj 7 + 9";
        return;

      case minMaj7Maskp9:
        message = intToLetter[root];
        message += " Min Maj 7 + 9";
        return;

      /************/

      case majMaskp4:
        message = intToLetter[root];
        message += " Major + 4";
        return;
      
      case minMaskp4:
        message = intToLetter[root];
        message += " Minor + 4";
        return;

      case augMaskp4:
        message = intToLetter[root];
        message += " Aug + 4";
        return;

      case dimMaskp4:
        message = intToLetter[root];
        message += " Dim + 4";
        return;

      case minMin7Maskp4:
        message = intToLetter[root];
        message += " Min Min 7 + 4";
        return;
        
      case majMin7Maskp4:
        message = intToLetter[root];
        message += " Maj Min 7 + 4";
        return;
        
      case majMaj7Maskp4:
        message = intToLetter[root];
        message += " Maj Maj 7 + 4";
        return;

      case minMaj7Maskp4:
        message = intToLetter[root];
        message += " Min Maj 7 + 4";
        return;

      default:                        // no masks matched

        if (1 & chord){               // first bit is on, need to rotate it.
          chord = (chord >> 1) | 2048;// turn on last bit
        } else {
          chord = chord >> 1;         // otherwise just shift
        }
        break;
    }
  }

  makesChord = false;
}
