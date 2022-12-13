
// Struct which defines a NoteBar -- each bar that represents a Note in game
typedef struct NoteBar {
  int yPos;                 // yPosition of NoteBar
  int numCol;               // number of column the NoteBar is located in
  struct NoteBar* prev;     // Previous NoteBar (can act as linked list)
  struct NoteBar* next;     // Next NoteBar (can act as linked list)
  int clickedState;         // Marks whether the NoteBar has been clicked (0 for NO, 1 for YES)
  int passed;               // Marks whether the NoteBar has passed the scorelien (0 for NO, 1 for YES)
  int flashed;              // Marks whether the NoteBar's LED has flashed (0 for NO, 1 for YES)
} NoteBar;

NoteBar* generateNoteBar(int col);
NoteBar* getFirstNoteBar();
void freeAllNoteBars();
void resetCanStartsAndFirstTrackers();
NoteBar* moveNoteBar(NoteBar* noteBar, int buttonsPressed[], int *score, int *noteBarsPast, int ledNum, int blockSpeed, int blockHeight, int multiplier);