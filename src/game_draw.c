// Include custom libraries
#include "game_draw.h"
#include "global.h"
#include "vga_graphics.h"
// Include standard libraries
#include <stdio.h>

// Names of all songs
char songNames[NUM_SONGS][28] = {
    "   mary had a little lamb   ",
    "twinkle twinkle little star ",
    "        jingle bells        ",
    "         ode to joy         ",
    "     old mcdonalds farm     ",
    "        silent night        ",
    "         let it be          "
};

// Draws screen entirely black
void drawScreenBlack() {
  fillRect(0, 0, SCREEN_WIDTH + 10, SCREEN_HEIGHT + 10, BLACK);
}

// Draws screen entirely white
void drawScreenWhite() {
  fillRect(0, 0, SCREEN_WIDTH + 10, SCREEN_HEIGHT + 10, WHITE);
}

// Draws the score lines
void drawScoreLine() {
  drawHLine(0, START_Y + SCORELINE_POS - 2, SCREEN_WIDTH, BLACK);
  drawHLine(0, START_Y + SCORELINE_POS - 1, SCREEN_WIDTH, BLACK);
  drawHLine(0, START_Y + SCORELINE_POS, SCREEN_WIDTH, BLACK);
}

// Draws the game lines
void drawGameLines(int startingXs[], int endingXs[], int numColumns) {
  // Draw line at top
  drawHLine(0, START_Y, SCREEN_WIDTH, BLACK);
  drawVLine(endingXs[0], START_Y, SCREEN_HEIGHT - START_Y, BLACK);
  drawVLine(startingXs[numColumns - 1], START_Y, SCREEN_HEIGHT - START_Y, BLACK);

  // Loops through and draws all the column lines
  for (int i = 1; i < numColumns - 1; i++) {
    drawVLine(startingXs[i], START_Y, SCREEN_HEIGHT - START_Y, BLACK);
    drawVLine(endingXs[i], START_Y, SCREEN_HEIGHT - START_Y, BLACK);
  }

  drawScoreLine();
}

// Writes labels for game play
void drawLabels() {
  char gameLabel[] = "Syynth Hero";
  char scoreLabel[] = "Score:";

  // Draw syynth hero text in top left
  setTextSize(3);
  setCursor(10, 13);
  writeString(gameLabel);

  // Draw score text in top right
  setTextSize(3);
  setCursor(320, 13);
  writeString(scoreLabel);
}

// Draw the score 
void drawScore(int score) {
  char scoreText[12];

  fillRect(430, 13, 180, 32, WHITE);
  setCursor(430, 13);
  sprintf(scoreText, "%d", score);
  writeString(scoreText);
}

// Draw menu buttons for the home screen
void drawMenuScreenButtons(int curButtonSelected) {
  int width = 320;
  int height = 50;
  int buttonX = 160;
  int buttonY = 160;
  int buttonDY = 60;
  char buttonColors[] = {GREEN, CYAN, BLUE, RED};   // Colors for buttons
  char labels[5][16] = {"   start game   ", " different song ", "   difficulty   ", " leave the game "};  // Labels for buttons

  // Loop through all buttons
  for (int i = 0; i < 4; i++) {
    int curY = buttonY + buttonDY * i;
    fillRect(buttonX, curY, width, height, WHITE);  // Erase previous text
    // Draw selected button
    if (i == curButtonSelected) {
      fillRect(buttonX, curY, width, height, buttonColors[i]);
      setTextColor(WHITE);
    } 
    // Draw non-selected button
    else {
      drawRect(buttonX, curY, width, height, buttonColors[i]);
      setTextColor(BLACK);
    }
    // Draw text for each button
    setCursor(buttonX + 60, curY + 17);
    writeStringWithLength(labels[i], 16);
  }
}

// Draw menu screen
void drawMenuScreen(int curButtonSelected) {
  char gameLabel[] = "Syynth Hero";
  char subtextLabel[] = "where synthing legends are made";

  // Draw "Syynth Hero" on top of screen
  setTextColor(BLACK);
  setCursor(190, 35);
  setTextSize(4);
  writeString(gameLabel);

  // Draw "where synthing legends are made" in top middle of screen
  setCursor(135, 75);
  setTextSize(2);
  writeString(subtextLabel);
  drawMenuScreenButtons(curButtonSelected);
}

// Draw buttons for paused screen
void drawPausedScreenButtons(int curButtonSelected) {
  int height = 50;
  int width = 260;
  int buttonX = 190;
  int buttonY = 180;
  int buttonDY = 60;
  char buttonColors[] = {GREEN, CYAN, RED};   // Colors for buttons
  char labels[3][11] = {"resume game", "  restart  ", " main menu "}; // Labels for buttons

  setTextSize(2);
  // Loop through all buttons
  for (int i = 0; i < 3; i++) {
    int curY = buttonY + buttonDY * i;
    fillRect(buttonX, curY, width, height, WHITE);
    // Draw selected button
    if (i == curButtonSelected) {
      fillRect(buttonX, curY, width, height, buttonColors[i]);
      setTextColor(WHITE);
    } 
    // Draw non-selected button
    else {
      drawRect(buttonX, curY, width, height, buttonColors[i]);
      setTextColor(BLACK);
    }
    // Draw text for each button
    setCursor(buttonX + 60, curY + 17);
    writeStringWithLength(labels[i], 11);
  }
}

// Draw paused screen
void drawPausedScreen(int curButtonsSelected) {
  char gameLabel[] = "Game Paused";

  // Draw game paused label in middle of screen
  setTextColor(BLACK);
  setCursor(190, 100);
  setTextSize(4);
  writeString(gameLabel);
  drawPausedScreenButtons(curButtonsSelected);
}

// Draw game over screen buttons
void drawGameOverScreenButtons(int curButtonSelected) {
  int height = 50;
  int width = 260;
  int buttonX = 190;
  int buttonY = 210;
  int buttonDY = 60;
  char buttonColors[] = {CYAN, RED};   // Colors for buttons
  char labels[2][11] = {"  restart  ", " main menu "};  // Labels for buttons

  setTextSize(2);
  // Loop through all buttons
  for (int i = 0; i < 2; i++) {
    int curY = buttonY + buttonDY * i;
    fillRect(buttonX, curY, width, height, WHITE);
    // Draw selected button
    if (i == curButtonSelected) {
      fillRect(buttonX, curY, width, height, buttonColors[i]);
      setTextColor(WHITE);
    }
    // Draw non-selected button
    else {
      drawRect(buttonX, curY, width, height, buttonColors[i]);
      setTextColor(BLACK);
    }
    // Draw text for each button
    setCursor(buttonX + 60, curY + 17);
    writeStringWithLength(labels[i], 11);
  }
}

// Draw game over screen
void drawGameOverScreen(int curButtonSelected) {
  char gameLabel[] = "Game Over";

  setTextColor(BLACK);
  setCursor(210, 100);
  setTextSize(4);
  writeString(gameLabel);
  drawGameOverScreenButtons(curButtonSelected);
}

// Draw difficulty screen buttons
void drawDifficultyScreenButtons(int curButtonSelected) {
  int height = 50;
  int width = 260;
  int buttonX = 190;
  int buttonY = 148;
  int buttonDY = 60;
  char buttonColors[] = {BLUE, MAGENTA, CYAN, RED}; // Colors for buttons
  char labels[4][14] = { "   beginner   ", " intermediate ", "    harder    ", "  super tuff  " };  // Labels for buttons

  setTextSize(2);
  // Loop through all buttons
  for (int i = 0; i < 4; i++) {
    int curY = buttonY + buttonDY * i;
    fillRect(buttonX, curY, width, height, WHITE);
    // Draw selected button
    if (i == curButtonSelected) {
      fillRect(buttonX, curY, width, height, buttonColors[i]);
      setTextColor(WHITE);
    } 
    // Draw non-selected button
    else {
      drawRect(buttonX, curY, width, height, buttonColors[i]);
      setTextColor(BLACK);
    }
    // Draw text for each button
    setCursor(buttonX + 46, curY + 17);
    writeStringWithLength(labels[i], 14);
  }
}

// Draw difficulty screen
void drawDifficultyScreen(int curButtonSelected) {
  char gameLabel[] = "Choose Difficulty";

  // Draw choose difficulty label at top center of screen
  setTextColor(BLACK);
  setCursor(126, 40);
  setTextSize(4);
  writeString(gameLabel);
  drawDifficultyScreenButtons(curButtonSelected);
}

// Draw song selection screen
void drawSongSelectionScreen(int curSongSelected) {
  char gameLabel[] = "Select a Song";

  // Draw "Select a Song" label at top center of screen
  setTextColor(BLACK);
  setCursor(170, 40);
  setTextSize(4);
  writeString(gameLabel);
  drawSongSelectionScreenButtons(curSongSelected);
}

// Draw song selection screen buttons
void drawSongSelectionScreenButtons(int curSongSelected) {
  int height = 50;
  int width = 420;
  int buttonX = 110;
  int buttonY = 128;
  int buttonDY = 60;
  char buttonColors[] = {BLUE, MAGENTA, CYAN, RED, GREEN};  // Colors for buttons
  char labels[4][14] = { "   beginner   ", " intermediate ", "    harder    ", "  super tuff  " };  // Labels for buttons

  setTextSize(2);
  // If selection is within first 5 options draw like all other buttons
  if (curSongSelected < 5) {
    for (int i = 0; i < 5; i++) {
      int curY = buttonY + buttonDY * i;
      fillRect(buttonX, curY, width, height, WHITE);
      // Draw selected button
      if (i == curSongSelected) {
        fillRect(buttonX, curY, width, height, buttonColors[i]);
        setTextColor(WHITE);
      } 
      // Draw non-selected button
      else {
        drawRect(buttonX, curY, width, height, buttonColors[i]);
        setTextColor(BLACK);
      }
      // Draw text for each button
      setCursor(buttonX + 44, curY + 17);
      writeStringWithLength(songNames[i], 28);
    }
  } 
  // If selection is greater than first 5 buttons than add scrolling effect
  else {
    for (int i = curSongSelected - 4; i <= curSongSelected; i++) {
      int s = i - curSongSelected + 4;
      int curY = buttonY + buttonDY * (s);
      fillRect(buttonX, curY, width, height, WHITE);
      // Draw selected button
      if (i == curSongSelected) {
        fillRect(buttonX, curY, width, height, buttonColors[s]);
        setTextColor(WHITE);
      } 
      // Draw non-selected button
      else {
        drawRect(buttonX, curY, width, height, buttonColors[s]);
        setTextColor(BLACK);
      }
      // Draw text for each button
      setCursor(buttonX + 44, curY + 17);
      writeStringWithLength(songNames[i], 28);
    }
  }
}
