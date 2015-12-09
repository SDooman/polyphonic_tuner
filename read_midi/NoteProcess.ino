String intToLetter[12] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

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
//const int halfDim7Maskp4 = 1097 + 32; // C half diminished 7th mask
//const int fullDim7Maskp4 = 585 + 32; // C fully diminished 7th mask
const int minMaj7Maskp4 = 2185 + 32; // C minor major 7th mask
const int majMin7Maskp4 = 1169 + 32; // C dominant seventh as mask
const int majMaj7Maskp4 = 2193 + 32; // C majorMinor mask

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

void detectChord(int notes){
  int root;
  message.remove(0);
  subMessage.remove(0);
  
  for (root = 0; root < 12; root++){ // only 12 possible rotations
    switch (notes) {
        
      case majMask:
        message = intToLetter[root];
        message += " Major";
        makesChord = true;
        return;
      
      case minMask:
        message = intToLetter[root];
        message += " Minor";
        makesChord = true;
        return;

      case augMask:
        message = intToLetter[root];
        message += " Aug";
        makesChord = true;
        return;

      case dimMask:
        message = intToLetter[root];
        message += " Dim";
        makesChord = true;
        return;

      case minMin7Mask:
        message = intToLetter[root];
        message += " Min Min 7";
        makesChord = true;
        return;

      case halfDim7Mask:
        message = intToLetter[root];
        message += " Half Dim 7";
        makesChord = true;
        return;

      case fullDim7Mask:
        message = intToLetter[root];
        message += " Full Dim 7";
        makesChord = true;
        return;

      case majMin7Mask:
        message = intToLetter[root];
        message += " Maj Min 7";
        makesChord = true;
        return;
        
      case majMaj7Mask:
        message = intToLetter[root];
        message += " Maj Maj 7";
        makesChord = true;
        return;

      case minMaj7Mask:
        message = intToLetter[root];
        message += " Min Maj 7";
        makesChord = true;
        return;

      /**************/

      case majMaskpb2:
        message = intToLetter[root];
        message += " Major + b2";
        makesChord = true;
        return;
      
      case minMaskpb2:
        message = intToLetter[root];
        message += " Minor + b2";
        makesChord = true;
        return;

      case augMaskpb2:
        message = intToLetter[root];
        message += " Aug + b2";
        makesChord = true;
        return;

      case dimMaskpb2:
        message = intToLetter[root];
        message += " Dim + b2";
        makesChord = true;
        return;

      case minMin7Maskpb9:
        message = intToLetter[root];
        message += " Min Min 7 b9";
        makesChord = true;
        return;

      case halfDim7Maskpb9:
        message = intToLetter[root];
        message += " Half Dim 7 b9";
        makesChord = true;
        return;

      case fullDim7Maskpb9:
        message = intToLetter[root];
        message += " Full Dim 7 b9";
        makesChord = true;
        return;

      case majMin7Maskpb9:
        message = intToLetter[root];
        message += " Maj Min 7 b9";
        makesChord = true;
        return;
        
      case majMaj7Maskpb9:
        message = intToLetter[root];
        message += " Maj Maj 7 b9";
        return;

      case minMaj7Maskpb9:
        message = intToLetter[root];
        message += " Min Maj 7 b9";
        makesChord = true;
        return;

      /************/

      case majMaskp2:
        message = intToLetter[root];
        message += " Major + 2";
        makesChord = true;
        return;
      
      case minMaskp2:
        message = intToLetter[root];
        message += " Minor + 2";
        makesChord = true;
        return;

      case augMaskp2:
        message = intToLetter[root];
        message += " Aug + 2";
        makesChord = true;
        return;

      case dimMaskp2:
        message = intToLetter[root];
        message += " Dim + 2";
        makesChord = true;
        return;

      case minMin7Maskp9:
        message = intToLetter[root];
        message += " Min Min 7 + 9";
        makesChord = true;
        return;

      case halfDim7Maskp9:
        message = intToLetter[root];
        message += " Half Dim 7 + 9";
        makesChord = true;
        return;

      case fullDim7Maskp9:
        message = intToLetter[root];
        message += " Full Dim 7 +9";
        makesChord = true;
        return;

      case majMin7Maskp9:
        message = intToLetter[root];
        message += " Maj Min 7 + 9";
        makesChord = true;
        return;
        
      case majMaj7Maskp9:
        message = intToLetter[root];
        message += " Maj Maj 7 + 9";
        makesChord = true;
        return;

      case minMaj7Maskp9:
        message = intToLetter[root];
        message += " Min Maj 7 + 9";
        makesChord = true;
        return;

      /************/

      case majMaskp4:
        message = intToLetter[root];
        message += " Major + 4";
        makesChord = true;
        return;
      
      case minMaskp4:
        message = intToLetter[root];
        message += " Minor + 4";
        makesChord = true;
        return;

      case augMaskp4:
        message = intToLetter[root];
        message += " Aug + 4";
        makesChord = true;
        return;

      case dimMaskp4:
        message = intToLetter[root];
        message += " Dim + 4";
        makesChord = true;
        return;

      case minMin7Maskp4:
        message = intToLetter[root];
        message += " Min Min 7 + 4";
        makesChord = true;
        return;

      /*
      case halfDim7Mask:
        message = intToLetter[root];
        message += " Half Dim 7";
        makesChord = true;
        return;
        
      case fullDim7Mask:
        message = intToLetter[root];
        message += " Full Dim 7";
        return;
      */
      case majMin7Maskp4:
        message = intToLetter[root];
        message += " Maj Min 7 + 4";
        makesChord = true;
        return;
        
      case majMaj7Maskp4:
        message = intToLetter[root];
        message += " Maj Maj 7 + 4";
        makesChord = true;
        return;

      case minMaj7Maskp4:
        message = intToLetter[root];
        message += " Min Maj 7 + 4";
        makesChord = true;
        return;

      default:                        // no masks matched

        if (1 & notes){               // first bit is on, need to rotate it.
          notes = (notes >> 1) | 2048;// turn on last bit
        } else {
          notes = notes >> 1;         // otherwise just shift
        }
        break;
    }
  }

  //No triadic chord was found so print notes being played

  makesChord = false;
  message = "hey";
  subMessage = "now";
  
  /*for(root = 0; root < 12; root++) {
    //if current first bit is on, turn it on in message
    if(1 & notes){
      message += intToLetter[root];
      if(root % 2) {
        subMessage += "b";
      } else {
        subMessage += " ";
      }
    } else {
      message += " ";
      subMessage += " ";
    }
    
    //Rotate to determine whether next note is being played
    if (1 & notes){               // first bit is on, need to rotate it.
      notes = (notes >> 1) | 2048;// turn on last bit
    } else {
      notes = notes >> 1;         // otherwise just shift
    }
  }*/
}
