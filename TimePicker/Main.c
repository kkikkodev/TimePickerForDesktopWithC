#include <stdio.h>
#include <stdlib.h>
#include "TimePicker.h"

int main(int argc, char* argv[]){
	TimePicker timePicker = { 0, };
	int startPositionXToPrint;
	int startPositionYToPrint;
	printf("타임 피커 시작 위치 입력 (x, y) : ");
	scanf("%d %d", &startPositionXToPrint, &startPositionYToPrint);
	system("cls");
	TimePicker_Create(&timePicker, startPositionXToPrint, startPositionYToPrint);
	TimePicker_Print(&timePicker);
	TimePicker_ProcessKey(&timePicker);
	printf("\n\n선택된 시각 : %d 시 %d 분 (%s)\n", TimePicker_GetSelectedHour(&timePicker),
		TimePicker_GetSelectedMinute(&timePicker),
		TimePicker_GetSelectedAmOrPm(&timePicker) == AM_TYPE ? "AM" : "PM");
	return 0;
}