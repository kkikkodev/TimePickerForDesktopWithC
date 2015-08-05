#include <stdio.h>
#include <conio.h>
#include <time.h>
#include "TimePicker.h"
#include "Util.h"

enum Boolean{
	False, True
};

enum KeyCode{
	ENTER = 13, UP = 72, DOWN = 80, RIGHT = 77, LEFT = 75
};

enum EditType{
	HOUR_EDIT_TYPE, MINUTE_EDIT_TYPE, AM_OR_PM_EDIT_TYPE
};

#define GMT (+9)

#define EDIT_TYPE_COUNT 3

#define HOURS_PER_DAY 24
#define MINUTES_PER_HOUR 60

const static char* amOrPmToPrint[] = { "AM", "PM" };

static void _TimePicker_ProcessLeftKey(TimePicker* timePicker);
static void _TimePicker_ProcessRightKey(TimePicker* timePicker);
static void _TimePicker_ProcessUpKey(TimePicker* timePicker);
static void _TimePicker_ProcessDownKey(TimePicker* timePicker);

void TimePicker_Create(TimePicker* timePicker, int startPositionXToPrint, int startPositionYToPrint){
	time_t now = time(NULL);
	struct tm* time = gmtime(&now);
	CursorUtil_Hide();
	timePicker->hour = (time->tm_hour + GMT) % HOURS_PER_DAY;
	timePicker->minute = time->tm_min;
	timePicker->amOrPm = AM_TYPE;
	if (timePicker->hour > (HOURS_PER_DAY / 2)){
		timePicker->hour -= (HOURS_PER_DAY / 2);
		timePicker->amOrPm = PM_TYPE;
	}
	timePicker->editType = HOUR_EDIT_TYPE;
	timePicker->startPositionToPrint.x = startPositionXToPrint;
	timePicker->startPositionToPrint.y = startPositionYToPrint;
}

void TimePicker_Print(TimePicker* timePicker){
	int x = timePicker->startPositionToPrint.x;
	int y = timePicker->startPositionToPrint.y;
	FontUtil_ChangeFontColor(WHITE);
	if (timePicker->editType == HOUR_EDIT_TYPE){
		FontUtil_ChangeFontColor(LIGHT_YELLOW);
	}
	DigitalPattern_Print(x, y, timePicker->hour / 10, HOUR_LEFT);
	DigitalPattern_Print(x, y, timePicker->hour % 10, HOUR_RIGHT);
	FontUtil_ChangeFontColor(WHITE);
	DigitalPattern_Print(x, y, ':', DELIMITER_BETWEEN_HOUR_AND_MINUTE);
	if (timePicker->editType == MINUTE_EDIT_TYPE){
		FontUtil_ChangeFontColor(LIGHT_YELLOW);
	}
	DigitalPattern_Print(x, y, timePicker->minute / 10, MINUTE_LEFT);
	DigitalPattern_Print(x, y, timePicker->minute % 10, MINUTE_RIGHT);
	FontUtil_ChangeFontColor(WHITE);
	if (timePicker->editType == AM_OR_PM_EDIT_TYPE){
		FontUtil_ChangeFontColor(LIGHT_YELLOW);
	}
	CursorUtil_GotoXY(timePicker->startPositionToPrint.x + 42, timePicker->startPositionToPrint.y + 4);
	printf("%s", amOrPmToPrint[timePicker->amOrPm]);
	FontUtil_ChangeFontColor(WHITE);
}

void TimePicker_ProcessKey(TimePicker* timePicker){
	while (True){
		if (_kbhit()){
			int key = _getch();
			if (key == ENTER){
				break;
			}
			switch (key){
			case 0xE0:
				if (_kbhit()){
					key = _getch();
					if (key == LEFT){
						_TimePicker_ProcessLeftKey(timePicker);
					}
					else if (key == RIGHT){
						_TimePicker_ProcessRightKey(timePicker);
					}
					else if (key == UP){
						_TimePicker_ProcessUpKey(timePicker);
					}
					else if (key == DOWN){
						_TimePicker_ProcessDownKey(timePicker);
					}
					TimePicker_Print(timePicker);
				}
				break;
			}
		}
	}
}

const int TimePicker_GetSelectedHour(TimePicker* timePicker){
	return timePicker->hour;
}

const int TimePicker_GetSelectedMinute(TimePicker* timePicker){
	return timePicker->minute;
}

const int TimePicker_GetSelectedAmOrPm(TimePicker* timePicker){
	return timePicker->amOrPm;
}

static void _TimePicker_ProcessLeftKey(TimePicker* timePicker){
	timePicker->editType = (timePicker->editType - 1 + EDIT_TYPE_COUNT) % EDIT_TYPE_COUNT;
}

static void _TimePicker_ProcessRightKey(TimePicker* timePicker){
	timePicker->editType = (timePicker->editType + 1) % EDIT_TYPE_COUNT;
}

static void _TimePicker_ProcessUpKey(TimePicker* timePicker){
	if (timePicker->editType == HOUR_EDIT_TYPE){
		timePicker->hour = (timePicker->hour + 1) % (HOURS_PER_DAY / 2 + 1);
		if (timePicker->hour == 0){
			timePicker->hour = 1;
		}
	}
	else if (timePicker->editType == MINUTE_EDIT_TYPE){
		timePicker->minute = (timePicker->minute + 1) % MINUTES_PER_HOUR;
	}
	else if (timePicker->editType == AM_OR_PM_EDIT_TYPE){
		timePicker->amOrPm = 1 - timePicker->amOrPm;
	}
}

static void _TimePicker_ProcessDownKey(TimePicker* timePicker){
	if (timePicker->editType == HOUR_EDIT_TYPE){
		timePicker->hour = (timePicker->hour - 1 + (HOURS_PER_DAY / 2 + 1)) % (HOURS_PER_DAY / 2 + 1);
		if (timePicker->hour == 0){
			timePicker->hour = HOURS_PER_DAY / 2;
		}
	}
	else if (timePicker->editType == MINUTE_EDIT_TYPE){
		timePicker->minute = (timePicker->minute - 1 + MINUTES_PER_HOUR) % MINUTES_PER_HOUR;
	}
	else if (timePicker->editType == AM_OR_PM_EDIT_TYPE){
		timePicker->amOrPm = 1 - timePicker->amOrPm;
	}
}