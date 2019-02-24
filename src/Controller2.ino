#include <Bounce.h>
#include <Keypad.h>

/**
 * Current mode.
 *
 * Currently this does nothing except call panic()
 * but this will allow me to add different modes,
 * maybe use different MIDI channels, etc.
 *
 * Maybe I can switch between a MIDI controller
 * and a computer keyboard input.
 */
int mode = 0;

// Rocker switch pins
const int ROCKER_1_PIN = 0;
const int ROCKER_2_PIN = 1;
const int ROCKER_3_PIN = 2;
const int ROCKER_4_PIN = 3;

// Toggle switch pins
const int TOGGLE_1_PIN = 5;
const int TOGGLE_2_PIN = 6;
const int TOGGLE_3_PIN = 7;
const int TOGGLE_4_PIN = 8;
const int TOGGLE_5_PIN = 9;
const int TOGGLE_6_PIN = 10;

// Jack connector pins
const int JACK_1_PIN = 11;
const int JACK_2_PIN = 12;

// Button matrix pins
const int ROW_1_PIN = 20;
const int ROW_2_PIN = 21;
const int ROW_3_PIN = 22;
const int ROW_4_PIN = 23;
const int COL_1_PIN = 16;
const int COL_2_PIN = 17;
const int COL_3_PIN = 18;
const int COL_4_PIN = 19;

// Mode LED
const int LED_1_PIN = 14;

// Mode select button
const int MODE_1_PIN = 4;

// Button Matrix setup
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'A', 'B', 'C', 'D'},
  {'E', 'F', 'G', 'H'},
  {'I', 'J', 'K', 'L'},
  {'M', 'N', 'O', 'P'}
};

byte row_pins[ROWS] = {ROW_1_PIN, ROW_2_PIN, ROW_3_PIN, ROW_4_PIN};
byte col_pins[COLS] = {COL_1_PIN, COL_2_PIN, COL_3_PIN, COL_4_PIN};

Keypad kpd = Keypad(makeKeymap(keys), row_pins, col_pins, ROWS, COLS);

/**
 * Map for push button MIDI notes.
 */
const int notes[14] = {
  // Arcade buttons
  48, 49,
  // Small buttons
  50, 51, 52, 53,
  54, 55, 56, 57,
  58, 59, 60, 61
};

/**
 * Map for rocker and toggle switch CC numbers
 */
const int SWITCH_CCS[10] = {
  22, // rocker_1
  23, // rocker_2
  24, // rocker_3
  25, // rocker_4
  26, // toggle_1
  27, // toggle_2
  28, // toggle_3
  29, // toggle_4
  30, // toggle_5
  31, // toggle_6
};

const int PEDAL_1_CC = 64; // 64 = sustain
const int PEDAL_2_CC = 16; // 16 = general use
const int BOUNCE_TIME = 10;

int midi_channel = 1;

Bounce rocker_1 = Bounce(ROCKER_1_PIN, BOUNCE_TIME);
Bounce rocker_2 = Bounce(ROCKER_2_PIN, BOUNCE_TIME);
Bounce rocker_3 = Bounce(ROCKER_3_PIN, BOUNCE_TIME);
Bounce rocker_4 = Bounce(ROCKER_4_PIN, BOUNCE_TIME);

Bounce toggle_1 = Bounce(TOGGLE_1_PIN, BOUNCE_TIME);
Bounce toggle_2 = Bounce(TOGGLE_2_PIN, BOUNCE_TIME);
Bounce toggle_3 = Bounce(TOGGLE_3_PIN, BOUNCE_TIME);
Bounce toggle_4 = Bounce(TOGGLE_4_PIN, BOUNCE_TIME);
Bounce toggle_5 = Bounce(TOGGLE_5_PIN, BOUNCE_TIME);
Bounce toggle_6 = Bounce(TOGGLE_6_PIN, BOUNCE_TIME);

Bounce mode_1 = Bounce(MODE_1_PIN, BOUNCE_TIME);

void setup() {
  pinMode(LED_1_PIN, OUTPUT);

  pinMode(ROCKER_1_PIN, INPUT);
  pinMode(ROCKER_2_PIN, INPUT);
  pinMode(ROCKER_3_PIN, INPUT);
  pinMode(ROCKER_4_PIN, INPUT);

  pinMode(TOGGLE_1_PIN, INPUT);
  pinMode(TOGGLE_2_PIN, INPUT);
  pinMode(TOGGLE_3_PIN, INPUT);
  pinMode(TOGGLE_4_PIN, INPUT);
  pinMode(TOGGLE_5_PIN, INPUT);
  pinMode(TOGGLE_6_PIN, INPUT);
}

void loop() {
  if (mode_1.update()) {
    if (mode_1.risingEdge()) {
      mode = (mode + 1) % 2;
      panic();
    }
  }

  if (rocker_1.update()) {
    if (rocker_1.risingEdge()) {
      usbMIDI.sendControlChange(SWITCH_CCS[0], 127, midi_channel);
    } else {
      usbMIDI.sendControlChange(SWITCH_CCS[0], 0, midi_channel);
    }
  }

  if (rocker_2.update()) {
    if (rocker_2.risingEdge()) {
      usbMIDI.sendControlChange(SWITCH_CCS[1], 127, midi_channel);
    } else {
      usbMIDI.sendControlChange(SWITCH_CCS[1], 0, midi_channel);
    }
  }

  if (rocker_3.update()) {
    if (rocker_3.risingEdge()) {
      usbMIDI.sendControlChange(SWITCH_CCS[2], 127, midi_channel);
    } else {
      usbMIDI.sendControlChange(SWITCH_CCS[2], 0, midi_channel);
    }
  }

  if (rocker_4.update()) {
    if (rocker_4.risingEdge()) {
      usbMIDI.sendControlChange(SWITCH_CCS[3], 127, midi_channel);
    } else {
      usbMIDI.sendControlChange(SWITCH_CCS[3], 0, midi_channel);
    }
  }

  if (toggle_1.update()) {
    if (toggle_1.risingEdge()) {
      usbMIDI.sendControlChange(SWITCH_CCS[4], 127, midi_channel);
    } else {
      usbMIDI.sendControlChange(SWITCH_CCS[4], 0, midi_channel);
    }
  }

  if (toggle_2.update()) {
    if (toggle_2.risingEdge()) {
      usbMIDI.sendControlChange(SWITCH_CCS[5], 127, midi_channel);
    } else {
      usbMIDI.sendControlChange(SWITCH_CCS[5], 0, midi_channel);
    }
  }

  if (toggle_3.update()) {
    if (toggle_3.risingEdge()) {
      usbMIDI.sendControlChange(SWITCH_CCS[6], 127, midi_channel);
    } else {
      usbMIDI.sendControlChange(SWITCH_CCS[6], 0, midi_channel);
    }
  }

  if (toggle_4.update()) {
    if (toggle_4.risingEdge()) {
      usbMIDI.sendControlChange(SWITCH_CCS[7], 127, midi_channel);
    } else {
      usbMIDI.sendControlChange(SWITCH_CCS[7], 0, midi_channel);
    }
  }

  if (toggle_5.update()) {
    if (toggle_5.risingEdge()) {
      usbMIDI.sendControlChange(SWITCH_CCS[8], 127, midi_channel);
    } else {
      usbMIDI.sendControlChange(SWITCH_CCS[8], 0, midi_channel);
    }
  }

  if (toggle_6.update()) {
    if (toggle_6.risingEdge()) {
      usbMIDI.sendControlChange(SWITCH_CCS[9], 127, midi_channel);
    } else {
      usbMIDI.sendControlChange(SWITCH_CCS[9], 0, midi_channel);
    }
  }
}

/**
 * Handle a button matrix key press event
 */
void keypadEvent(KeypadEvent key) {
  switch (kpd.getState()) {
    case PRESSED:
      switch (key) {
        case 'A':
          usbMIDI.sendNoteOn(notes[0], 96, midi_channel);
          break;
        case 'B':
          usbMIDI.sendNoteOn(notes[1], 96, midi_channel);
          break;
        case 'C':
          usbMIDI.sendNoteOn(notes[2], 96, midi_channel);
          break;
        case 'D':
          usbMIDI.sendNoteOn(notes[3], 96, midi_channel);
          break;
        case 'E':
          usbMIDI.sendNoteOn(notes[4], 96, midi_channel);
          break;
        case 'F':
          usbMIDI.sendNoteOn(notes[5], 96, midi_channel);
          break;
        case 'G':
          usbMIDI.sendNoteOn(notes[6], 96, midi_channel);
          break;
        case 'H':
          usbMIDI.sendNoteOn(notes[7], 96, midi_channel);
          break;
        case 'I':
          usbMIDI.sendNoteOn(notes[8], 96, midi_channel);
          break;
        case 'J':
          usbMIDI.sendNoteOn(notes[9], 96, midi_channel);
          break;
        case 'K':
          usbMIDI.sendNoteOn(notes[10], 96, midi_channel);
          break;
        case 'L':
          usbMIDI.sendNoteOn(notes[11], 96, midi_channel);
          break;
        case 'M':
          usbMIDI.sendNoteOn(notes[12], 96, midi_channel);
          break;
        case 'N':
          usbMIDI.sendNoteOn(notes[13], 96, midi_channel);
          break;
        case 'O':
          usbMIDI.sendControlChange(PEDAL_1_CC, 127, midi_channel);
          break;
        case 'P':
          usbMIDI.sendControlChange(PEDAL_2_CC, 127, midi_channel);
          break;
      }
      break;
    case RELEASED:
      switch (key) {
        case 'A':
          usbMIDI.sendNoteOff(notes[0], 0, midi_channel);
          break;
        case 'B':
          usbMIDI.sendNoteOff(notes[1], 0, midi_channel);
          break;
        case 'C':
          usbMIDI.sendNoteOff(notes[2], 0, midi_channel);
          break;
        case 'D':
          usbMIDI.sendNoteOff(notes[3], 0, midi_channel);
          break;
        case 'E':
          usbMIDI.sendNoteOff(notes[4], 0, midi_channel);
          break;
        case 'F':
          usbMIDI.sendNoteOff(notes[5], 0, midi_channel);
          break;
        case 'G':
          usbMIDI.sendNoteOff(notes[6], 0, midi_channel);
          break;
        case 'H':
          usbMIDI.sendNoteOff(notes[7], 0, midi_channel);
          break;
        case 'I':
          usbMIDI.sendNoteOff(notes[8], 0, midi_channel);
          break;
        case 'J':
          usbMIDI.sendNoteOff(notes[9], 0, midi_channel);
          break;
        case 'K':
          usbMIDI.sendNoteOff(notes[10], 0, midi_channel);
          break;
        case 'L':
          usbMIDI.sendNoteOff(notes[11], 0, midi_channel);
          break;
        case 'M':
          usbMIDI.sendNoteOff(notes[12], 0, midi_channel);
          break;
        case 'N':
          usbMIDI.sendNoteOff(notes[13], 0, midi_channel);
          break;
        case 'O':
          usbMIDI.sendControlChange(PEDAL_1_CC, 0, midi_channel);
          break;
        case 'P':
          usbMIDI.sendControlChange(PEDAL_2_CC, 0, midi_channel);
          break;
      }
      break;
    case HOLD:
      break;
    case IDLE:
      break;
  }
}

void panic() {
  for (int i = 0; i < 128; i++) {
    usbMIDI.sendNoteOff(i, 0, midi_channel);
  }
}
