// Include relevant libraries
#include "game_draw.h"
#include "global.h"
#include "notebar.h"
#include "songs.h"
#include "sound.h"
#include "vga_graphics.h"
// Include standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
// Include Pico libraries
#include "pico/stdlib.h"
#include "pico/divider.h"
#include "pico/multicore.h"
// Include hardware libraries
#include "hardware/spi.h"
#include "hardware/pio.h"
#include "hardware/dma.h"
#include "hardware/flash.h"
#include "hardware/clocks.h"
#include "hardware/pll.h"
#include <hardware/sync.h>
// Include protothreads
#include "pt_cornell_rp2040_v1.h"

// Mark the start and end x positions of columns
int startingXs[5] = {0, 127, 254, 381, 508};                // Array that marks starting X positions for columns
int endingXs[5] = {127, 254, 381, 508, 655};                // Array that marks ending X positions for columns

// All Game Variables that can be controlled by difficulty
int blockHeight = INITIAL_BLOCK_HEIGHT;                     // Notebar height - changes with difficulty
int timing = INITIAL_TIMING;                                // Tempo of song - changes with difficulty
int blockSpeed = INITIAL_BLOCKSPEED;                        // Speed of y position of blocks - changes with difficulty
int multiplier = INITIAL_MULTIPLIER;                        // Number added to score when correct press - changes with difficulty

// Game State Variables
int gameOver = 0;                                           // If 1, then game is over. Otherwise 0
int songPosition = 0;                                       // Position in the NoteColumns array of a song. 0 indicates beginning of game
int freqPosition = 0;                                       // Position in the NoteFreqChanges array of song
int noteBarsPast = 0;                                       // Number of Notebars that have passed score line. 0 for beginning of game
int noteBarDelta = 0;                                       // Tracks interval in NoteBarDeltas 
int score = 0;                                              // Tracks score, 0 for beginning of game

// Button Variables
const int leds[6] = {0, 1, 2, 3, 4, 0};                     // GPIO ports for LEDS. ith position is led for ith button
const int buttons[6] = {9, 28, 11, 13, 14, 15};             // GPIO ports for buttons. ith position is GPIO for ith button
int buttonRepeats[6] = {0};                                 // Values used to track if a button has actually been let go (our buttons are buggy)
int buttonSignals[6] = {0};                                 // Values that indicate whether a button has been previously pressed

// Screen State Global Variables
int oldScreenState = -1;                                    // Previous state of screen
int curScreenState = 0;                                     // Current state of screen
int selectedButtonHomeScreen = 0;                           // Which option is selected on home screen
int selectedButtonPausedScreen = 0;                         // Which option is selected on paused screen
int selectedButtonGameOverScreen = 0;                       // Which option is selected on game over screen
int selectedButtonDifficultyScreen = 0;                     // Which option is selected on difficulty screen

// Songs
int selectedSong = 0;                                       // Int to track which song is currently selected
uint8_t curSong_NoteColumns[112];                           // NoteColumns for current song
uint8_t curSong_NoteDeltas[112];                            // NoteDeltas for current song
uint8_t curSong_NoteFreqChanges[18];                        // NoteFrequencyChanges for current song
uint16_t curSong_NoteFreqs[18][5];                          // NoteFrequencies for current song


// Interrupt called every 25 us on core 1 to run direct 
// digital synthesis and produce sound if button is clicked
bool soundGenerationInterrupt(struct repeating_timer *t) {
  soundGeneration();
  return true;
}

// Button hardware is faulty, so this runs every 900 us on core 0
// to check if button is clicked and  
bool buttonInterrupt(struct repeating_timer *t) {
  // Loop through buttons
  for (int i = 0; i < 6; i++) {
    // Check if button is ready to be clicked, was clicked, and update buttonSignals accordingly
    if (buttonRepeats[i] > 10 && !gpio_get(buttons[i])) {
      buttonSignals[i] = 1;
      buttonRepeats[i] = 0;
    } 
    // Increment corresponding button repeat to indicate button isn't being clicked this iteration
    else if (gpio_get(buttons[i]) && buttonRepeats[i] <= 10) {
      buttonRepeats[i] += 1;  
    }
  }

  return true;
}

// Checks if button was clicked recently
bool buttonPressed(int buttonNum) {
  // If button was recently clicked, return true and reset its buttonSignal value
  if (buttonSignals[buttonNum] == 1) {
    buttonSignals[buttonNum] = 0;
    return true;
  }
  return false;
}

// Reset all game values
void resetAllGameValues() {
  resetCanStartsAndFirstTrackers();
  freeAllNoteBars();
  score = 0;
  gameOver = 0;
  songPosition = 0;
  freqPosition = 0;
  noteBarsPast = 0;
  noteBarDelta = 0;

  // Turn off all LEDs
  for (int i = 0; i < 5; i++) {
    gpio_put(leds[i], 0);
  }
}

// Get frequency value that should be played based off the button that is pressed
int getNewCurFrequency(int buttonsPressed[]) {
  // Update freqPosition and noteBarDelta if this calls for a change in frequency
  if (noteBarsPast - noteBarDelta >= curSong_NoteFreqChanges[freqPosition]) {
    noteBarDelta += noteBarsPast - noteBarDelta;
    freqPosition += 1;
  }

  // Check if a button is pressed and if so return its frequency based off current song data
  for (int i = 0; i < NUM_COLUMNS; i++) {
    if (buttonsPressed[i]) {
      return curSong_NoteFreqs[freqPosition][i];
    }
  }

  return 0;
}

// Called when previousScreenState != currentScreenState -- essentially prepares for the new screen state
void changeScreen(int newScreenState) {
  // Reset all button selected values
  selectedButtonHomeScreen = 0;
  selectedButtonPausedScreen = 0;
  selectedButtonGameOverScreen = 0;
  selectedButtonDifficultyScreen = 0;

  drawScreenWhite();
  // Prepare for home screen
  if (newScreenState == 0) {
    resetAllGameValues();
    drawMenuScreen(selectedButtonHomeScreen);
    selectSong(selectedSong, curSong_NoteColumns, curSong_NoteDeltas, curSong_NoteFreqChanges, curSong_NoteFreqs);
  }
  // Prepare for game screen
  else if (newScreenState == 1) {
    drawLabels();
    drawScore(score);
    drawGameLines(startingXs, endingXs, NUM_COLUMNS);
  }
  // Prepare for paused screen
  else if (newScreenState == 2) {
    drawLabels();
    drawScore(score);
    drawHLine(0, START_Y, SCREEN_WIDTH, BLACK);
    drawPausedScreen(selectedButtonPausedScreen);
  }
  // Prepare for game over screen
  else if (newScreenState == 3) {
    drawLabels();
    drawScore(score);
    drawHLine(0, START_Y, SCREEN_WIDTH, BLACK);
    drawGameOverScreen(selectedButtonGameOverScreen);
  } 
  // Prepare for difficulty selection screen
  else if (newScreenState == 4) {
    drawDifficultyScreen(selectedButtonGameOverScreen);
  } 
  // Prepare for song selection screen
  else if (newScreenState == 5) {
    drawSongSelectionScreen(selectedSong);
  }
}

// Main game loop that runs on core 0
static PT_THREAD (protothread_anim(struct pt *pt)) {
  PT_BEGIN(pt);

  static int curFreq = 0;         // static int that represents frequency to be played - will be sent to core 1 when a button is pressed
  static int previousTime = 0;    // previousTime used to calculate time elapsed between game loops (only when running a game)
  static int beginTime = 0;       // beginTime of each loop (only when running a game)
  static int elapsed = 0;         // elapsed time between game loops (only when running a game)
  while (1) {
    // Change screen if curScreenState changes and update oldScreenState
    if (oldScreenState != curScreenState) {
      changeScreen(curScreenState);
      oldScreenState = curScreenState;
    }

    // State for the home screen
    if (curScreenState == 0) {
      // If move-selection button is pressed then rotate which button is selected and redraw buttons accordingly
      if (buttonPressed(2)) {
        selectedButtonHomeScreen = (selectedButtonHomeScreen + 1) % 4;
        drawMenuScreenButtons(selectedButtonHomeScreen);
      }

      int button5Pressed = buttonPressed(5);
      // If select button is pressed and 0th button is selected, change curScreenState to start game
      if (button5Pressed && selectedButtonHomeScreen == 0) {
        curScreenState = 1;
      } 
      // If select button is pressed and 1st button is selected, change curScreenState to song selection screen
      else if (button5Pressed && selectedButtonHomeScreen == 1) {
        curScreenState = 5;
      } 
      // If select button is pressed and 2nd button is selected, change curScreenState to select the game difficulty
      else if (button5Pressed && selectedButtonHomeScreen == 2) {
        curScreenState = 4;
      } 
      // If select button is pressed and 3rd button is selected, exit game 
      else if (button5Pressed && selectedButtonHomeScreen == 3) {
        drawScreenBlack();
        exit(0);
      }
    } 
    
    // State for the actual gameplay
    else if (curScreenState == 1) {
      // Update previousTime and beginTime values
      previousTime = beginTime;
      beginTime = time_us_32();
      elapsed += beginTime - previousTime;

      // If the timing is appropriate and curSong_NoteColumns[songPosition] is a valid value, generate a new noteBar and increment songPosition
      uint8_t nextColumn = curSong_NoteColumns[songPosition];
      if (elapsed > timing * curSong_NoteDeltas[songPosition] && nextColumn < 5) {
        generateNoteBar(nextColumn);
        songPosition += 1;
        elapsed = 0;
      } 
      // If curSong_NoteColumns[songPosition] is 9, this signals the game is over
      else if (nextColumn == 9) {
        gameOver = 1;
      }

      // Create an array to track which buttons were pressed
      int buttonsPressed[6] = {0};
      for (int i = 0; i < 6; i++) {
        if (buttonPressed(i)) {
          buttonsPressed[i] = 1;
        }
      }

      // Get a frequency value if a button was pressed and send it to core_1 so that it can play it
      curFreq = getNewCurFrequency(buttonsPressed);
      if (curFreq != 0) {
        PT_FIFO_WRITE(curFreq);
        curFreq = 0;
      }
  
      // Reset all values that track whether noteBars can start and which ones are first
      resetCanStartsAndFirstTrackers();

      // Loop over all NoteBars and draw them in their new position
      NoteBar* curBar = getFirstNoteBar();   
      while (curBar != NULL) {
        curBar = moveNoteBar(
          curBar, 
          buttonsPressed, 
          &score, &noteBarsPast, 
          leds[curBar->numCol], 
          blockSpeed, 
          blockHeight, 
          multiplier
        );
        drawScoreLine();
      }
      drawScore(score);

      // If gameOver == true and there are no more noteBars, then change curScreenState to gameOver state
      if (gameOver && getFirstNoteBar == NULL) {
        curScreenState = 3;
      }

      // If gameOver == true and there are no more noteBars, then change curScreenState to gameOver state
      if (buttonPressed(5)) {
        curScreenState = 2;
      }

      // YIELD to keep a consistent FRAME_RATE during gameplay
      PT_YIELD_usec(FRAME_RATE - (time_us_32() - beginTime));
    } 
    
    else if (curScreenState == 2) {
      // If move-selection button is pressed then rotate which button is selected and redraw buttons accordingly
      if (buttonPressed(2)) {
        selectedButtonPausedScreen = (selectedButtonPausedScreen + 1) % 3;
        drawPausedScreenButtons(selectedButtonPausedScreen);
      }

      int button5Pressed = buttonPressed(5);
      // If select button is pressed and 0th button is selected, change curScreenState to resume game
      if (button5Pressed && selectedButtonPausedScreen == 0) {
        curScreenState = 1;
      } 
      // If select button is pressed and 1st button is selected, reset all game values and change curScreenState to restart game
      else if (button5Pressed && selectedButtonPausedScreen == 1) {
        resetAllGameValues();
        curScreenState = 1;
      } 
      // If select button is pressed and 2nd button is selected, return to main menu
      else if (button5Pressed && selectedButtonPausedScreen == 2) {
        curScreenState = 0;
      }
    } 
    
    else if (curScreenState == 3) {
      // If move-selection button is pressed then rotate which button is selected and redraw buttons accordingly
      if (buttonPressed(2)) {
        selectedButtonGameOverScreen = (selectedButtonGameOverScreen + 1) % 2;
        drawGameOverScreenButtons(selectedButtonGameOverScreen);
      }

      int button5Pressed = buttonPressed(5);
      // If select button is pressed and 0th button is selected, go back to main screen
      if (button5Pressed && selectedButtonGameOverScreen == 1) {
        curScreenState = 0;
      } 
      // If select button is pressed and 1st button is selected, reset all game values and restart the game
      else if (button5Pressed && selectedButtonGameOverScreen == 0) {
        resetAllGameValues();
        curScreenState = 1;
      }
    } 
    
    else if (curScreenState == 4) {
      // If move-selection button is pressed then rotate which button is selected and redraw buttons accordingly
      if (buttonPressed(2)) {
        selectedButtonDifficultyScreen = (selectedButtonDifficultyScreen + 1) % 4;
        drawDifficultyScreenButtons(selectedButtonDifficultyScreen);
      }

      // Update all difficulty controlled values based on value of selectedButtonDifficultyScreen and then return to home screen
      if (buttonPressed(5)) {
        blockHeight = INITIAL_BLOCK_HEIGHT - (5 * selectedButtonDifficultyScreen);
        blockSpeed = INITIAL_BLOCKSPEED + selectedButtonDifficultyScreen;
        timing = INITIAL_TIMING - (80000 * selectedButtonDifficultyScreen);
        multiplier = INITIAL_MULTIPLIER + selectedButtonDifficultyScreen;
        curScreenState = 0;
      }
    }

    else if (curScreenState == 5) {
      // If move-selection button is pressed then rotate which button is selected and redraw buttons accordingly
      if (buttonPressed(2)) {
        // Change which song is selected
        selectedSong = (selectedSong + 1) % (NUM_SONGS);
        drawSongSelectionScreenButtons(selectedSong);
      }

      // If select button is pressed, go back to main menu
      if (buttonPressed(5)) {
        curScreenState = 0;
      }
    }
  }

  PT_END(pt);
}

// Main thread that runs on core 1 that constantly performs a PT_FIFO_READ
static PT_THREAD (protothread_sound(struct pt *pt)) {
  PT_BEGIN(pt);
  static int enterFreq = 0;
  while(1) {
    // When a value is given through PT_FIFO_READ, generate a sound 
    PT_FIFO_READ(enterFreq);
    generateSoundPlay((float) enterFreq);
  }
  PT_END(pt);
}

// Entry for core 1
void core1_main(){ 
  // Create alarm pool and add soundGenerationInterrupt to run every 25uS
  alarm_pool_t *core1pool;
  core1pool = alarm_pool_create(2, 16);
  struct repeating_timer timer_core_1;
  alarm_pool_add_repeating_timer_us(core1pool, -25, soundGenerationInterrupt, NULL, &timer_core_1);

  // Add main thread to core 1
  pt_add_thread(protothread_sound);
  
  // Start scheduler
  pt_schedule_start;
}

// ========================================
// === main
// ========================================
int main(){
  // initialize stio and VGA
  stdio_init_all();
  initVGA();

  // Flush out for FIFO to setup
  PT_FIFO_FLUSH;

  // Initialize all LEDs and Buttons
  for (int i = 0; i < 6; i++) {
    gpio_init(leds[i]);
    gpio_set_dir(leds[i], GPIO_OUT);
    gpio_init(buttons[i]);
    gpio_pull_up(buttons[i]);
  }

  // Initialize all SPI parameters
  spi_init(spi0, 20000000);
  // Format (channel, data bits per transfer, polarity, phase, order)
  spi_set_format(spi0, 16, 0, 0, 0);

  // Initialize SPI 
  gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);
  gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
  gpio_set_function(PIN_CS, GPIO_FUNC_SPI);

  gpio_init(LDAC);
  gpio_set_dir(LDAC, GPIO_OUT);
  gpio_put(LDAC, 0);

  // Initialize all sound 
  initializeForSoundProduction();

  // Initialize core 1 and give entry point
  multicore_launch_core1(&core1_main);

  // Create buttonInterrupt alarm to run every 900 uS
  struct repeating_timer timer_core_0;
  add_repeating_timer_us(-900, buttonInterrupt, NULL, &timer_core_0);

  // Add main thread for core 0
  pt_add(protothread_anim);

  // start scheduler
  pt_schedule_start;
} 