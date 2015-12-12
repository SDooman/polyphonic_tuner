Polyphonic Tuner
================

This is a device that can be connected to any MIDI instrument
and will analyze the notes that this MIDI instrument will
play.  If the MIDI device is playing a triadic chord, the tuner
will identify the root/quality of the chord and display it.
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
MIDI device.  However, 
