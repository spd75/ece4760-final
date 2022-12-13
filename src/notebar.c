#include <stdio.h>
#include <stdlib.h>
#include "hardware/pio.h"
#include "global.h"
#include "notebar.h"
#include "vga_graphics.h"

int sXs[5] = {0, 127, 254, 381, 508};                           // Positions for starting columns lines
int eXs[5] = {127, 254, 381, 508, 655};                         // Positions for ending column lines
int canStarts[5] = {0};                                         // Tracks whether a notebar in each column can start due to close proximity of other NoteBars
int firstTracker[5] = {0};                                      // Tracks whether a notebar in each column has already been selected as "first" - 0 is already selected
char colors[5] = { MAGENTA, BLUE, GREEN, BLUE, MAGENTA };       // NoteBar color for each column

// The first NoteBar -- all NoteBars are connected through a linked-list that are connected to this
NoteBar* frontNoteBar = NULL;

// Returns the first NoteBar of the linked list
NoteBar* getFirstNoteBar() {
    return frontNoteBar;
}

// PRECONDITION: FIRST NOTE BAR CAN'T BE NULL
// Returns the last NoteBar of the linked list
NoteBar* getLastNoteBar() {
  NoteBar* curBar = getFirstNoteBar();

  // Loop over all NoteBars in LinkedList until next is NULL
  while (curBar->next != NULL) {
    curBar = curBar->next;
  }

  return curBar;
}

// Removes the entire list of NoteBars
void freeAllNoteBars() {
  // Return if no NoteBar exists
  if (frontNoteBar == NULL) {
    return;
  }

  // Loop over all NoteBars and free them from memory
  NoteBar* curBar = frontNoteBar;
  while (curBar->next != NULL) {
    curBar = curBar->next;
    free(curBar->prev);
  }

  // Free last NoteBar from memory and set front NoteBar to NULL
  free(curBar);
  frontNoteBar = NULL;
}

// Resets all values in canStarts and firstTracker to 1
void resetCanStartsAndFirstTrackers() {
  for (int i = 0; i < NUM_COLUMNS; i++) {
    canStarts[i] = 1;
    firstTracker[i] = 1;
  }
}

// Generate a new NoteBar and add it to the linked list
NoteBar* generateNoteBar(int col) {
  NoteBar* noteBar;
  noteBar = malloc(sizeof(NoteBar));

  // Initialize all values for NoteBar
  noteBar->yPos = START_Y + START_Y_OFFSET;
  noteBar->numCol = col;
  noteBar->clickedState = 0;
  noteBar->passed = 0;
  noteBar->flashed = 0;
  noteBar->next = NULL;

  // If no NoteBar currently exists, set frontNoteBar to this new nNoteBar
  if (frontNoteBar == NULL) {
    frontNoteBar = noteBar;
    noteBar->prev = NULL;
  } 
  // If NoteBar already exists, append it to the linked list 
  else {
    NoteBar* prevNoteBar = getLastNoteBar();
    noteBar->prev = prevNoteBar;
    prevNoteBar->next = noteBar;
  }

  return noteBar;
}

// Check if a NoteBar can be clicked, if so, was it clicked and if so, was it clicked correctly?
bool clickedCorrectly (NoteBar* noteBar, int buttonsPressed[], int blockHeight) {
  int isFirstClickable = 0;
  // Determine whether a NoteBar is the first in its column and is clickable
  if (firstTracker[noteBar->numCol] && noteBar->clickedState == 0) {
      isFirstClickable = 1;
      firstTracker[noteBar->numCol] = 0;
  }

  // Check if is clickable and if the corresponding button was pressed
  if (isFirstClickable && buttonsPressed[noteBar->numCol]) {
    // Clicked in timing
    if (noteBar->yPos >= (START_Y + SCORELINE_POS) - blockHeight && noteBar->yPos <= (START_Y + SCORELINE_POS)) {
      noteBar->clickedState = 1;
      return true;
    } 
    // Clicked out of timing
    else {
      noteBar->clickedState = -1;
    }
  }

  return false;
}

// Redraw NoteBar 
void redrawNoteBar(NoteBar* noteBar, int blockSpeed, int blockHeight) {
  int startX = sXs[noteBar->numCol];            // Starting X position of NoteBar which corresponds to column its in
  int width = eXs[noteBar->numCol] - startX;    // width of NoteBar
  char color = colors[noteBar->numCol];         // Color of NoteBar which corresponds to column its in

  // Erase previous drawing of NoteBar
  fillRect(startX + 1, noteBar->yPos - blockSpeed, width - 1, blockHeight, WHITE);
  fillRect(startX + 1, noteBar->yPos + blockSpeed - 1, width - 1, blockHeight, WHITE);

  // Draw NoteBar as CYAN if it was clicked correctly
  if (noteBar->clickedState == 1) {
    fillRect(startX + 1, noteBar->yPos, width - 1, blockHeight, CYAN);
  } 
  // Draw NoteBar as RED if it was clicked incorrectly
  else if (noteBar->clickedState == -1) {
    fillRect(startX + 1, noteBar->yPos, width - 1, blockHeight, RED);
  } 
  // Draw Notebar as column color if it wasn't clicked
  else {
    fillRect(startX + 1, noteBar->yPos, width - 1, blockHeight, color);
  }

  // Draw white line if NoteBar is at the bottom of the screen
  if (noteBar->yPos > 480 - blockHeight) {
    drawHLine(startX, 480, width, WHITE);
  }
}

// Checks if NoteBar is too close to start and sets canStart value accordingly
void checkIfNoteBarTooCloseToStartLine(NoteBar* noteBar, int blockSpeed, int blockHeight) {
  if (noteBar->yPos < START_Y + MIN_BLOCK_SPACING + blockHeight + blockSpeed) {
    canStarts[noteBar->numCol] = 0;
  }
}

// Checks if NoteBar is past the scoreLine and changes the NoteBar's clicked value accordingly
void checkIfNoteBarOnOrPastScoreLine(NoteBar* noteBar, int ledNum, int blockHeight, int *noteBarsPast) {
  if (!noteBar->flashed && noteBar->yPos >= (START_Y + SCORELINE_POS) - blockHeight && noteBar->yPos <= (START_Y + SCORELINE_POS)) {
    gpio_put(ledNum, 1);
  } 

  if (noteBar->yPos > SCORELINE_POS + START_Y) {
    if (noteBar->passed == 0) {
      gpio_put(ledNum, 0);
      *noteBarsPast += 1;
      noteBar->passed = 1;
    }
    if (noteBar->clickedState != 1) {
      noteBar->clickedState = -1;
    }
  }
}

// Updates NoteBar position
void updateNoteBarPositionAndDeleteIfOffScreen(NoteBar* noteBar, int blockSpeed) {
  // Delete NoteBar if it is off screen
  if (noteBar->yPos > 480) {
    if (noteBar->prev != NULL) {
      noteBar->prev->next = noteBar->next;
      noteBar->next->prev = noteBar->prev;
    } else {
      noteBar->next->prev = NULL;
      frontNoteBar = noteBar->next;
    }
    free(noteBar);
  } 
  // Update NoteBar position
  else {
    noteBar->yPos += blockSpeed;
  }
}

// Function that runs every iteration of the game loop to update each NoteBar individually
NoteBar* moveNoteBar(NoteBar* noteBar, int buttonsPressed[], int *score, int *noteBarsPast, int ledNum, int blockSpeed, int blockHeight, int multiplier) {
  // Check if NoteBar was clicked correctly and add multiplier to score if so
  if (clickedCorrectly(noteBar, buttonsPressed, blockHeight)) {
      *score += multiplier;
  }

  // Set nextNoteBar
  NoteBar* nextNoteBar = noteBar->next;
  if (canStarts[noteBar->numCol] == 0) {
    return nextNoteBar;
  }

  // Update all aspects of Notebar
  redrawNoteBar(noteBar, blockSpeed, blockHeight);
  checkIfNoteBarTooCloseToStartLine(noteBar, blockSpeed, blockHeight);
  checkIfNoteBarOnOrPastScoreLine(noteBar, ledNum, blockHeight, noteBarsPast);
  updateNoteBarPositionAndDeleteIfOffScreen(noteBar, blockSpeed);

  // Return next NoteBar so that gameLoop can run this function on the next NoteBar
  return nextNoteBar;
}