#pragma once
#include <windows.h>
#include <vector>
#include "Object.h"
#ifndef DRAW_STRUCT

typedef struct tagDRAW
{
	int selectIndex;
	COLORREF currentColor;
	LOGFONT currentFont;
	std::vector<Object*> store;
}DRAW, * PDRAW;



#endif // 
