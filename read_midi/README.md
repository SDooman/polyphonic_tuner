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


