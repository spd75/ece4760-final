#pragma once

#define FRAME_RATE 31000                            // Desired period for desired frame rate

#define SCREEN_WIDTH 640                            // Width of VGA screen
#define SCREEN_HEIGHT 480                           // Width of VGA screen
#define WIDTH_OFFSET 5                              // Offset on screen width
#define START_Y 50                                  // Point at which NoteBars spawn and begin to move down screen
#define START_Y_OFFSET 7                            // Offset so that NoteBars don't erase the starting line
#define SCORELINE_POS 302                           // Position where scoreline is located

#define INITIAL_BLOCK_HEIGHT 36                     // Original NoteBar height
#define MIN_BLOCK_SPACING 10                        // Minimum spacing required between notebars
#define INITIAL_BLOCKSPEED 3                        // Original NoteBar speed (speed at which it moves down the screen)
#define INITIAL_TIMING 400000                       // Initial period for timing
#define INITIAL_MULTIPLIER 3                        // Original multiplier which is added to score when note is hit correctly

#define SPI_PORT 0                                  // SPI PORTS
#define PIN_CS   5
#define PIN_SCK  6
#define PIN_MOSI 7
#define LDAC     8

#define DAC_config_chan_A 0b0011000000000000        // Channel A on DAC 
#define DAC_config_chan_B 0b1011000000000000        // Channel B on DAC

#define NUM_SONGS 7                                 // Number of songs on game
#define SONG_LENGTH 112                             // Length of songs (in notes)
#define SONG_SWITCHES 18                            // Max number of note switches allowed per songs
#define NUM_COLUMNS 5                               // Number of columns in game

#define GL 196                                      // Frequency for G3
#define C 261                                       // Frequency for C4 (middle C)
#define D 293                                       // Frequency for D4
#define E 329                                       // Frequency for E4
#define F 349                                       // Frequency for F4
#define G 392                                       // Frequency for G4
#define A 440                                       // Frequency for A4
#define B 493                                       // Frequency for B4
#define CH 523                                      // Frequency for C5
#define DH 587                                      // Frequency for D5
#define EH 659                                      // Frequency for E5
#define FH 698                                      // Frequency for F5

#define ATTACK_TIME             150                 // Attack time of synth notes
#define DECAY_TIME              12000               // Decay time of synth notes
#define NOTE_DURATION           14000               // Duration of synth note

#define two32 4294967296.0                          // 2^32 (a constant)
#define Fs 40000.0                                  // Sample rate
#define sine_table_size 256                         // Size of sine table for sampling

// FIX 15 functions
typedef signed int fix15 ;
#define multfix15(a,b) ((fix15)((((signed long long)(a))*((signed long long)(b)))>>15))
#define float2fix15(a) ((fix15)((a)*32768.0)) 
#define fix2int15(a) ((int)(a >> 15))
#define int2fix15(a) ((fix15)(a << 15))
#define divfix(a,b) (fix15)( (((signed long long)(a)) << 15) / (b))