#ifndef _TIME_PICKER_H
#define _TIME_PICKER_H

#include "Point.h"

enum AmOrPmType{
	AM_TYPE, PM_TYPE
};

typedef struct _timePicker{
	int hour;
	int minute;
	int amOrPm;
	int editType;
	Point startPositionToPrint;
}TimePicker;

void TimePicker_Create(TimePicker* timePicker, int startPositionXToPrint, int startPositionYToPrint);
void TimePicker_Print(TimePicker* timePicker);
void TimePicker_ProcessKey(TimePicker* timePicker);
const int TimePicker_GetSelectedHour(TimePicker* timePicker);
const int TimePicker_GetSelectedMinute(TimePicker* timePicker);
const int TimePicker_GetSelectedAmOrPm(TimePicker* timePicker);

#endif