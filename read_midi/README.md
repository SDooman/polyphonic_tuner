TEAM: skortchm, sdooman, ndemarco

Polyphonic Tuner
================

This is a device that can be connected to any MIDI instrument
and will analyze the notes that this MIDI instrument will
play.  If the MIDI device is playing a triadic chord, the tuner
will identify the root and quality of the chord and display it.
This device is designed for new musicians, particularly new 
pianists or guitarists.  This device will enable musicians to 
see exactly what they're playing and help develop their 
ear training.

Architecture
============

The basic system design of this device is outlined in 
Tasks Diagram.png.  The device is constantly reading from the
MIDI device, waiting for one of two kinds of MIDI commands:
Note On or Note Off.  For either of those, a task is executed
to update the internal representation of the currently played
notes, and analyzes the current notes.  Then the display is 
updated in an LCD update task.

Implementation
==============

Below is the parts list required for this tuner:
 * MIDI connector Digikey CP-2350-ND
 * 220Ohm 1/4watt resistor Digikey CF14JT220RCT-ND
 * 1N4148 diode Digikey1N4148-TAPCT-ND
 * 10kOhm 1/4watt resistor Digikey CF14JT10K0CT-ND
 * 470 Ohm 1/4watt resistor Digikey CF14JT470RCT-ND
 * 6N138 optocoupler Digikey 751-1263-5-ND
 * MIDI Cable
 * Parallex 2x16 LCD Screen
 * Arduino Uno

When implementing the hardware component of this project,
one of the challenges faced was figuring out how to interpret
MIDI events from the MIDI device.  While the MIDI protocol is
universal, some devices handle when notes finish playing differently.
In particular, some devices will send a Note On command when notes
finish playing, but with a velocity of 0 to signify the note 
finished.

Software Architecture
=====================

For the sake of this discussion, let us define some terms.

Note - A discrete melodic pitch of one of 12 qualities:
	A, A#, B, C, C#, D, D#, E, F, F#, G, G#
	(Notes with # are sharp - A# is read as A-sharp)

Chord - A set of notes, irrespective of octave.
	For the sake of this harmonic analysis, notes of similar quality, but different octave, are considered identical. 

Root - Every chord has a root note, which identifies the harmonic basis for the chord.

Quality - Every chord also has a quality, such as "major, minor, augmented," etc. 

Our algorithm, given a set of notes, seeks to identify the root and quality of this chord.

(For more information on harmonic theory, refer to : https://www.musictheory.net/lessons/40)

---

When a chord is represented in binary, we consider a 12-bit integer, where each of the bits represents a note that may or may not be in the set. We consider the least significant bit to represent C, and the most significant bit to represent B (This is done for compatibility with the MIDI protocol, explained more below). Therefore, a sample chord could be:

 11 10 9  8  7  6  5  4  3  2  1  0
 
 B  A# A  G# G  F# F  E  D# D  C# C
 -  -  -  -  -  -  -  -  -  -  -  -
 0  0  0  0  1  0  0  1  0  0  0  1 - C Major = 145 in decimal

 This algorithm uses a property of similar-harmonic chords. That is, all major chords, all minor chords, etc. Define a binary rotation as a left or right shift of a given integer, where significant bits that would otherwise be lost (the LSB on right shift, MSB on left shift) are instead "wrapped around." All chords of the same quality are simply binary rotations of each other. For example:

 11 10 9  8  7  6  5  4  3  2  1  0
 
 B  A# A  G# G  F# F  E  D# D  C# C
 -  -  -  -  -  -  -  -  -  -  -  -
 0  0  0  0  1  0  0  1  0  0  0  1 - C Major

 0  0  0  1  0  0  1  0  0  0  1  0 - C# Major

Notice that the relative orientation of the 1s does not change. In this case, the difference between a C Major representation and a C# major representation is just a left shift of 1. 

To demonstrate the "wrapping around" property of a binary rotation, consider the following example:


 11 10 9  8  7  6  5  4  3  2  1  0
 
 B  A# A  G# G  F# F  E  D# D  C# C
 -  -  -  -  -  -  -  -  -  -  -  -
 1  0  0  1  0  0  0  1  0  0  0  0 - E Major

 Given an E Major chord, we can find an F Major chord by performing a left shift. Notice that this would result in the loss of our MSB, and the information would be distorted. To prevent this, if the MSB is enabled before a left shift, the chord is rotated by performing a left shift and then an OR operator with 1, enabling the LSB.


 11 10 9  8  7  6  5  4  3  2  1  0
 
 B  A# A  G# G  F# F  E  D# D  C# C
 -  -  -  -  -  -  -  -  -  -  -  -
 1  0  0  1  0  0  0  1  0  0  0  0 - E Major

 0  0  1  0  0  0  1  0  0  0  0  1 - F Major

 Performing a right rotation would behave similarly - if the LSB is enabled before a right shift, we OR the result with 1<<12 to enable the MSB. 

 For reference, all major chords and their binary representations are provided below.

  11 10 9  8  7  6  5  4  3  2  1  0
 
 B  A# A  G# G  F# F  E  D# D  C# C
 -  -  -  -  -  -  -  -  -  -  -  -
 0  0  0  0  1  0  0  1  0  0  0  1 - C Major 	Root 0

 0  0  0  1  0  0  1  0  0  0  1  0 - Cs Major  Root 1
 
 0  0  1  0  0  1  0  0  0  1  0  0 - D Major   Root 2
 
 0  1  0  0  1  0  0  0  1  0  0  0 - Ds Major  Root 3
 
 1  0  0  1  0  0  0  1  0  0  0  0 - E Major   Root 4
 
 0  0  1  0  0  0  1  0  0  0  0  1 - F Major   Root 5
 
 0  1  0  0  0  1  0  0  0  0  1  0 - FsMajor   Root 6
 
 1  0  0  0  1  0  0  0  0  1  0  0 - G Major   Root 7
 
 0  0  0  1  0  0  0  0  1  0  0  1 - Gs Major  Root 8
 
 0  0  1  0  0  0  0  1  0  0  1  0 - A Major   Root 9
 
 0  1  0  0  0  0  1  0  0  1  0  0 - As Major  Root 10
 
 1  0  0  0  0  1  0  0  1  0  0  0 - B Major   Root 11

 Assume that for any kind of chord, rotations will preserve their quality, and any two rotations of any two chord qualities will not collide; that is, have an identical binary representation. Note that this assumption only applies for chords of 5 or fewer notes. Beyond 5 notes, harmonic analysis becomes ambigious and requires contextual information to determine. Further, our target user would likely not be building relatively dense chords - these are common in atonal music, and virtually impossible for guitarists, as there are only 6 strings on a standard guitar. 

 We define a quality-mask as binary representation of a chord of some quality, Q, with root C. Therefore, any other chord of quality Q is some number of right rotations away from the quality-mask. For example, notice that a (D major chord) == (C major chord << 2). It is easily verified that the number of right rotations required to turn a chord into a chord of the same quality with root C is unique for all chords of that quality. 

 Therefore, we can easily construct many quality-masks, these are just any chord quality with root C.

 To detect the harmonic quality of some chord, we first check if the chord matches any of our quality-masks. If so, we know that the given chord has a root of C, with a quality determined by the quality-mask. If no such match occurs, we rotate the given chord once, and check again. If any match occurs at this step, we know that our given chord has a root of 1 (related to C#). We repeat this process of rotating and checking 11 times, until we've exhausted every possible rotation of our 12 bit number. If no match occurs after these 11 rotations, we conclude that no chord has been detected. 

Evaluation
==========

This device will correctly display the notes being played for 
MIDI compliant devices, and can analyze chords with 4 or fewer
notes.  It also can identify chords with 5 notes, but some of 
these chords can be interpreted in multiple ways, so the 
algorithm will arbitrarily choose a matching identification.

The display of the current notes has no perceivable delays.

Related Work
============

The chord identification functionality appears in several
professional DAWs.  After significant testing on chords that
this tuner is capable of analyzing, we determined the accuracy
of our device to be consistent with Logic Pro.  However,
there is no stand-alone device that offers this functionality,
and these DAWs cost on the order of hundreds of dollars.

Future Work
===========

The original intent for this tuner was to be able to analyze
notes being played from any audio source, as well as from a 
MIDI device.  However, after research and some testing, we found that the ideal algorithm for the job, a Fast Hartley Transform, would be too costly to run on the hardware we had available. Further, given the sampling rate limitations of the Arduino Uno, we would need to significantly reduce our sampling range (< 4kHz) such that many frequencies for our target instruments (guitar, piano) would not be perceivable. If this project continues, we'll investigate the possiblity of dedicated FHT hardware that could be combined with our existing MIDI rig. 














