#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include <string.h>



// **********************************
//
// MARY HAD A LITTLE LAMB
//
// **********************************
const uint8_t Song2_NoteColumns[SONG_LENGTH] = {
    0, 0, 3, 3, 4, 4, 3, 3, 3, 2, 2, 1, 1, 0, 4, 4, 
    ...............................................
};

const uint8_t Song2_NoteDeltas[SONG_LENGTH] = {
    0, 2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 4, 2,
    ...............................................
};

const uint8_t Song2_NoteFreqChanges[SONG_SWITCHES] = {
    7, 21, 7, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99
};

const uint16_t Song2_NoteFreqs[SONG_SWITCHES][NUM_COLUMNS] = {
    {C, D, E, G, A}, {C, D, E, F, G}, {C, D, E, G, A}, {C, D, E, F, G}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}
};








// **********************************
//
// MARY HAD A LITTLE LAMB
//
// **********************************
const uint8_t Song1_NoteColumns[SONG_LENGTH] = {
    2, 1, 0, 1, 2, 2, 2, 1, 1, 1, 2, 4, 4, 2, 1, 0, 
    1, 2, 2, 2, 2, 1, 1, 2, 1, 0, 9, 9, 9, 9, 9, 9, 
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9
};

const uint8_t Song1_NoteDeltas[SONG_LENGTH] = {
    0, 2, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 4, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 9, 9, 9, 9, 9, 
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9
};

const uint8_t Song1_NoteFreqChanges[SONG_SWITCHES] = {
    99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99
};

const uint16_t Song1_NoteFreqs[SONG_SWITCHES][NUM_COLUMNS] = {
    {C, D, E, F, G}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}
};


// **********************************
//
// TWINKLE TWINKLE LITTLE STAR
//
// **********************************
const uint8_t Song2_NoteColumns[SONG_LENGTH] = {
    0, 0, 3, 3, 4, 4, 3, 3, 3, 2, 2, 1, 1, 0, 4, 4, 
    3, 3, 2, 2, 1, 4, 4, 3, 3, 2, 2, 1, 0, 0, 3, 3, 
    4, 4, 3, 3, 3, 2, 2, 1, 1, 0, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9
};

const uint8_t Song2_NoteDeltas[SONG_LENGTH] = {
    0, 2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 4, 2,
    2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 4, 2, 2, 2,
    2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 4, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9
};

const uint8_t Song2_NoteFreqChanges[SONG_SWITCHES] = {
    7, 21, 7, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99
};

const uint16_t Song2_NoteFreqs[SONG_SWITCHES][NUM_COLUMNS] = {
    {C, D, E, G, A}, {C, D, E, F, G}, {C, D, E, G, A}, {C, D, E, F, G}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}
};



// **********************************
//
// JINGLE BELLS
//
// **********************************
const uint8_t Song3_NoteColumns[SONG_LENGTH] = {
    2, 2, 2, 2, 2, 2, 2, 4, 0, 1, 2, 3, 3, 3, 3, 3,
    2, 2, 2, 2, 1, 1, 2, 1, 4, 2, 2, 2, 2, 2, 2, 2,
    4, 0, 1, 2, 3, 3, 3, 3, 3, 2, 2, 2, 4, 4, 3, 1,
    0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9
};

const uint8_t Song3_NoteDeltas[SONG_LENGTH] = {
    0, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 8, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 4, 4, 2, 2, 4, 2, 2, 4,
    2, 2, 2, 2, 8, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9
};

const uint8_t Song3_NoteFreqChanges[SONG_SWITCHES] = {
    99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99
};

const uint16_t Song3_NoteFreqs[SONG_SWITCHES][NUM_COLUMNS] = {
    {C, D, E, F, G}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
};


// **********************************
//
// ODE TO JOY
//
// **********************************
const uint8_t Song4_NoteColumns[SONG_LENGTH] = {
    2, 2, 3, 4, 4, 3, 2, 1, 0, 0, 1, 2, 2, 1, 1, 2,
    2, 3, 4, 4, 3, 2, 1, 0, 0, 1, 2, 1, 0, 0, 1, 1,
    2, 0, 1, 2, 3, 2, 0, 1, 2, 3, 2, 1, 0, 1, 0, 2,
    2, 3, 4, 4, 3, 2, 1, 0, 0, 1, 2, 1, 0, 0, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9
};

const uint8_t Song4_NoteDeltas[SONG_LENGTH] = {
    0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 1, 4,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 1, 4, 2,
    2, 2, 2, 2, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 1, 4, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9
};

const uint8_t Song4_NoteFreqChanges[SONG_SWITCHES] = {
    46, 1, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99
};

const uint16_t Song4_NoteFreqs[SONG_SWITCHES][NUM_COLUMNS] = {
    {C, D, E, F, G}, {GL, D, E, F, G}, {C, D, E, F, G}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
};

// **********************************
//
// OLD MCDONALD
//
// **********************************
const uint8_t Song5_NoteColumns[SONG_LENGTH] = {
    2, 2, 2, 0, 1, 1, 0, 4, 4, 3, 3, 2, 0, 2, 2, 2,
    0, 1, 1, 0, 4, 4, 3, 3, 2, 0, 0, 2, 2, 2, 0, 0,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 0, 1, 1, 0, 4, 4, 3, 3, 2, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9
};

const uint8_t Song5_NoteDeltas[SONG_LENGTH] = {
    0, 2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 6, 2, 2, 2,
    2, 2, 2, 2, 4, 2, 2, 2, 2, 6, 1, 1, 2, 2, 2, 1,
    1, 2, 2, 4, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 2, 2,
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9
};

const uint8_t Song5_NoteFreqChanges[SONG_SWITCHES] = {
    99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99
};

const uint16_t Song5_NoteFreqs[SONG_SWITCHES][NUM_COLUMNS] = {
    {D, E, G, A, B}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
};



// **********************************
//
// SILENT NIGHT
//
// **********************************
const uint8_t Song6_NoteColumns[SONG_LENGTH] = {
    1, 2, 1, 0, 1, 2, 1, 0, 4, 4, 2, 3, 3, 0, 1, 1,
    4, 3, 2, 1, 2, 1, 0, 1, 1, 4, 3, 2, 1, 2, 1, 0,
    3, 3, 4, 3, 1, 2, 4, 4, 3, 2, 3, 2, 1, 0, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9
};

const uint8_t Song6_NoteDeltas[SONG_LENGTH] = {
    0, 3, 1, 2, 6, 3, 1, 2, 6, 4, 2, 6, 4, 2, 6, 4,
    2, 3, 1, 2, 3, 1, 2, 6, 4, 2, 3, 1, 2, 3, 1, 2,
    6, 4, 2, 3, 1, 2, 6, 6, 2, 2, 2, 3, 1, 2, 6, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9
};

const uint8_t Song6_NoteFreqChanges[SONG_SWITCHES] = {
    8, 8, 7, 2, 7, 5, 2, 3, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99
};

const uint16_t Song6_NoteFreqs[SONG_SWITCHES][NUM_COLUMNS] = {
    {E, G, A, B, CH}, {G, A, B, CH, DH}, {E, G, A, B, CH}, {G, A, B, CH, DH}, {E, G, A, B, CH}, {A, B, C, DH, FH}, 
    {E, B, CH, DH, EH}, {C, D, E, G, CH}, {C, D, F, G, CH}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
};


// **********************************
//
// Let It Be
//
// **********************************
const uint8_t Song7_NoteColumns[SONG_LENGTH] = {
    1, 1, 1, 1, 2, 0, 1, 1, 3, 4, 4, 4, 4, 3, 3, 2,
    2, 3, 3, 4, 3, 3, 2, 4, 3, 3, 2, 1, 0, 0, 1, 1, 
    1, 1, 2, 0, 1, 1, 3, 4, 4, 4, 4, 3, 3, 2, 2, 3, 
    3, 4, 3, 3, 2, 4, 3, 3, 2, 1, 0, 0, 9, 9, 9, 9, 
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9
};

const uint8_t Song7_NoteDeltas[SONG_LENGTH] = {
    0, 1, 1, 2, 1, 2, 2, 2, 2, 1, 2, 1, 1, 2, 1, 2,
    1, 4, 1, 2, 2, 1, 2, 2, 1, 1, 2, 2, 2, 2, 4, 1, 
    1, 2, 1, 2, 2, 2, 2, 1, 2, 1, 1, 2, 1, 2, 1, 4, 
    1, 2, 2, 1, 2, 2, 1, 1, 2, 2, 2, 2, 4, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9
};

const uint8_t Song7_NoteFreqChanges[SONG_SWITCHES] = {
    10, 7, 6, 6, 1, 10, 7, 6, 6, 1, 99, 99, 99, 99, 99, 99, 99, 99
};

const uint16_t Song7_NoteFreqs[SONG_SWITCHES][NUM_COLUMNS] = {
    {E, G, A, CH, DH}, {A, B, CH, DH, EH}, {B, CH, DH, EH, FH}, {F, G, CH, DH, EH}, {E, G, CH, DH, EH}, {E, G, A, CH, DH}, 
    {A, B, CH, DH, EH}, {B, CH, DH, EH, FH}, {F, G, CH, DH, EH}, {E, G, CH, DH, EH}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
};



void selectSong(int songToSelect, uint8_t nC[SONG_LENGTH], uint8_t nD[SONG_LENGTH], uint8_t nFC[SONG_SWITCHES], uint16_t nF[SONG_SWITCHES][NUM_COLUMNS]) {
  if (songToSelect == 0) {
    memcpy(nC, Song1_NoteColumns, SONG_LENGTH);
    memcpy(nD, Song1_NoteDeltas, SONG_LENGTH);
    memcpy(nFC, Song1_NoteFreqChanges, SONG_SWITCHES);
    memcpy(nF, Song1_NoteFreqs, SONG_SWITCHES * NUM_COLUMNS);
  } else if (songToSelect == 1) {
    memcpy(nC, Song2_NoteColumns, SONG_LENGTH);
    memcpy(nD, Song2_NoteDeltas, SONG_LENGTH);
    memcpy(nFC, Song2_NoteFreqChanges, SONG_SWITCHES);
    memcpy(nF, Song2_NoteFreqs, SONG_SWITCHES * NUM_COLUMNS);
  } else if (songToSelect == 2) {
    memcpy(nC, Song3_NoteColumns, SONG_LENGTH);
    memcpy(nD, Song3_NoteDeltas, SONG_LENGTH);
    memcpy(nFC, Song3_NoteFreqChanges, SONG_SWITCHES);
    memcpy(nF, Song3_NoteFreqs, SONG_SWITCHES * NUM_COLUMNS);
  } else if (songToSelect == 3) {
    memcpy(nC, Song4_NoteColumns, SONG_LENGTH);
    memcpy(nD, Song4_NoteDeltas, SONG_LENGTH);
    memcpy(nFC, Song4_NoteFreqChanges, SONG_SWITCHES);
    memcpy(nF, Song4_NoteFreqs, SONG_SWITCHES * NUM_COLUMNS);
  } else if (songToSelect == 4) {
    memcpy(nC, Song5_NoteColumns, SONG_LENGTH);
    memcpy(nD, Song5_NoteDeltas, SONG_LENGTH);
    memcpy(nFC, Song5_NoteFreqChanges, SONG_SWITCHES);
    memcpy(nF, Song5_NoteFreqs, SONG_SWITCHES * NUM_COLUMNS);
  } else if (songToSelect == 5) {
    memcpy(nC, Song6_NoteColumns, SONG_LENGTH);
    memcpy(nD, Song6_NoteDeltas, SONG_LENGTH);
    memcpy(nFC, Song6_NoteFreqChanges, SONG_SWITCHES);
    memcpy(nF, Song6_NoteFreqs, SONG_SWITCHES * NUM_COLUMNS);
  } else {
    memcpy(nC, Song7_NoteColumns, SONG_LENGTH);
    memcpy(nD, Song7_NoteDeltas, SONG_LENGTH);
    memcpy(nFC, Song7_NoteFreqChanges, SONG_SWITCHES);
    memcpy(nF, Song7_NoteFreqs, SONG_SWITCHES * NUM_COLUMNS);
  }
}
