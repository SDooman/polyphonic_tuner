char intToLetter[12] = {'C', 'c', 'D', 'd', 'E', 'F', 'f', 'G', 'g', 'A', 'a', 'B'};

#define CBIT 145
#define CsBIT 290
#define DBIT 580
#define DsBIT 1160
#define EBIT 2192
#define FBIT 545
#define FsBIT 1090
#define GBIT 2180
#define GsBIT 265
#define ABIT 529
#define AsBIT 1058
#define BBIT 2120

const int majMask = CBIT; // C Major Triad as mask
const int minMask = 137;  // C Minor Triad as mask
const int dom7Mask = 1169; // C dominant seventh as mask
const int majMin7Mask = 2193; // C majorMinor mask

void array_to_chord(){
  int result = 0;
  for(int i = 0; i < MIDI_NOTES; i++){
    if(notes[i]){
      result |= 1 << (i % 12);
    }
  }
  
  if(result){
    detectChord(result);
  }
  
}

void detectChord(int chord){
  int count;
  for (count = 0; count < 12; count++){ // only 12 possible rotations
    switch (chord) {
        
      case majMask:
        printDescription(count, 'M');
        return;
      
      case minMask:
        printDescription(count, 'm');
        return;
        
      case dom7Mask:
        printDescription(count, 'V');
        return;
        
      case majMin7Mask:
        printDescription(count, 'v');
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
  message = "";
}

void printDescription(int root, char desc){
  char rootChar = intToLetter[root];
  switch (desc) {
    case 'M':
      //print("%c Major chord", rootChar);
      message = String(rootChar);
      message += " Major";
      break;
      
    case 'm':
      message = String(rootChar);
      message += " Minor";
      break;
      
    case 'V':
      message = String(rootChar);
      message += " domV";
      break;
    
    case 'v':
      message = String(rootChar);
      message += " MajMaj7";
      break;
      
    default:
      printf("ERROR: pD");
  }
}
