#include <conio.h>
#include <windows.h>

const int MAX_X = 80;
const int MAX_Y = 24;
const int MIN_X = 0;
const int MIN_Y = 0;

void gotoxy(short int x, short int y);
void hidecursor(void);
void clear();