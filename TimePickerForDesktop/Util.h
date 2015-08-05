#ifndef _UTIL_H
#define _UTIL_H

// ex) 12:24:36
enum DigitalPatternType{
	HOUR_LEFT, // left digit of hour -> 1
	HOUR_RIGHT, // right digit of hour -> 2
	DELIMITER_BETWEEN_HOUR_AND_MINUTE, // colon between hour and minute -> : 
	MINUTE_LEFT, // left digit of minute -> 3
	MINUTE_RIGHT, // right digit of minute -> 4
	DELIMITER_BETWEEN_MINUTE_AND_SECOND, // colon between minute and second -> :
	SECOND_LEFT, // left digit of second -> 5
	SECOND_RIGHT // right digit of second -> 6
};

enum FontColor{
	BLACK, BLUE, GREEN, JADE, RED, PURPLE, YELLOW, WHITE, GRAY,
	LIGHT_BLUE, LIGHT_GREEN, LIGHT_JADE, LIGHT_RED, LIGHT_PURPLE, LIGHT_YELLOW, LIGHT_WHITE,
	WHITE_INVERSION = 240
};

void CursorUtil_GotoXY(int x, int y);
void CursorUtil_Show();
void CursorUtil_Hide();
void WindowUtil_ChangeWindowSize(int lines, int cols);
void FontUtil_ChangeFontColor(int color);
void ScreenUtil_ClearRectangle(int leftTopX, int leftTopY, int width, int height);
void DigitalPattern_Print(int x, int y, int digitalPattern, int digitalPatternType);

#endif