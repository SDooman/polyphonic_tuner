//
//  main.c
//  chord_namer_2
//
//  Created by Nick DeMarco on 8/16/15.
//  Copyright (c) 2015 Nick DeMarco. All rights reserved.
//

#include <stdio.h>
#include <string.h>     /* strcat */
#include <stdlib.h>     /* strtol */
#include "masks.h"

const char *binary(int x);
int numberOfNotesInChord(int chord);
void printDescription(int root, char desc);
void detectChord(int chord);

char intToLetter[12] = {'C', 'c', 'D', 'd', 'E', 'F', 'f', 'G', 'g', 'A', 'a', 'B'};

const int majMask = CBIT; // C Major Triad as mask
const int minMask = 137;  // C Minor Triad as mask
const int dom7Mask = 1169; // C dominant seventh as mask
const int majMin7Mask = 2193; // C majorMinor mask

// putting test arguments here for easier debugging:

int argumentCount = 4;
int arguments[4] = {E, G, As, C};

int main(int argc, const char * argv[]) {
  
  int i;
  int v;
  int result = 0;
  
  for (i = 0; i < argumentCount; i++) {
    arguments[i] %= 12;                 // argument reduced to 0-11
    v = 1 << arguments[i];              // v = 1 with <arguments[i]> 0's
    result = result | v;
  }
  
  //printf("Result in binary: %s\n", binary(result));
  //printf("---Result in dec: %d\n", result);
  detectChord(result);
}

// prints number in binary
const char *binary(int x) {
  static char b[13];
  b[0] = '\0';
  
  int z;
  for (z = 2048; z > 0; z >>= 1)
  {
    strcat(b, ((x & z) == z) ? "1" : "0");
  }
  
  return b;
}

// gets number of notes in chord
int numberOfNotesInChord(int chord){
  int count = 0;
  while(chord!=0){
    chord = chord&(chord - 1); // this always eliminates the least significant 1 bit
    count++;
  }
  return count;
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
}

void printDescription(int root, char desc){
  char rootChar = intToLetter[root];
  switch (desc) {
    case 'M':
      printf("The chord is a %c Major chord.\n", rootChar);
      break;
      
    case 'm':
      printf("The chord is a %c Minor chord.\n", rootChar);
      break;
      
    case 'V':
      printf("The chord is a %c Dominant 7th.\n", rootChar);
      break;
    
    case 'v':
      printf("The chord is a %c Major Minor 7th.\n", rootChar);
      break;
      
    default:
      printf("ERROR: We should never get here. See printDescription.");
  }
}

 /*********************************************
 Chord-Bit Representation:
 
 11 10 9  8  7  6  5  4  3  2  1  0
 
 B  A# A  G# G  F# F  E  D# D  C# C
 -  -  -  -  -  -  -  -  -  -  -  -
 0  0  0  0  0  0  0  0  0  0  0  0 -> Nothing
 
 0  0  0  0  1  0  0  1  0  0  0  1 -> G, E, C - > CEG, C Triad (000010010001) = 145
 
 1  0  0  0  1  0  0  0  0  1  0  0 -> B, G, D - > GBD, G Triad (100010000100) = 2180
 
 
 Seventh Chord Stuff: (NEED TO KNOW NUMBER OF NOTES)
 0  0  1  0  1  0  0  1  0  0  0  1 -> A, G, E, C - ACEG, AMaj7 (001010010001) = 657 (How to detect?)
 
 1  0  1  0  0  1  0  0  0  1  0  0 -> Left shift 2,
 
 0  0  1  0  0  0  0  0  0  0  0  0 -> AND (if not 0, there is a major second) - misses edges.
 
 How can we check if Cs and B or C and As are together? Shifting loses bits. ALSO SHIFT LEFT 10!
 
 1  0  0  1  0  0  1  0  0  0  1  0 -> Cs7 - Cs and B both on. How to detect edge adjacency?
 
 0  1  0  0  1  0  0  0  1  0  0  0 -> We can first left shift 2, but this doesn't catch it.
 
 0  0  0  0  0  0  0  0  0  0  1  0 -> But if we right shift 10, this DOES catch it. The formula then is:
 
 (orig & (orig << 2)) | (orig & (orig >> 10))
 
 
 Finding Root in basic triads:
 
 11 10 9  8  7  6  5  4  3  2  1  0
 
 B  A# A  G# G  F# F  E  D# D  C# C
 -  -  -  -  -  -  -  -  -  -  -  -
 0  0  0  0  1  0  0  1  0  0  0  1 - C Major

 0  0  0  1  0  0  1  0  0  0  1  0 - Cs Major
 
 0  0  1  0  0  1  0  0  0  1  0  0 - D Major
 
 0  1  0  0  1  0  0  0  1  0  0  0 - Ds Major
 
 1  0  0  1  0  0  0  1  0  0  0  0 - E Major
 
 0  0  1  0  0  0  1  0  0  0  0  1 - F Major
 
 0  1  0  0  0  1  0  0  0  0  1  0 - FsMajor
 
 1  0  0  0  1  0  0  0  0  1  0  0 - G Major
 
 0  0  0  1  0  0  0  0  1  0  0  1 - Gs Major (C = bs)
 
 0  0  1  0  0  0  0  1  0  0  1  0 - A Major
 
 0  1  0  0  0  0  1  0  0  1  0  0 - As Major
 
 1  0  0  0  0  1  0  0  1  0  0  0 - B Major
*/
