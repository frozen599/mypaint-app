#pragma once

#include "Object.h"
#include <string>
#include <vector>
#include <Windows.h>
#include "stdafx.h"

#ifndef L_HEADER
#define L_HEADER




class Line : public Object
{
public:
	int x_current;
	int y_current;
	// position of resize points
	int isResize(LPARAM lParam, RECT rec);
	int getResizePos(LPARAM lParam);
	//Check Line
	bool isLine();
	//Setter
	void setPos(RECT _rec);
	void setColor(COLORREF _color);

	//Getter
	RECT getPos();
	COLORREF getColor();

	//Check function
	bool isSelect(LPARAM lParam);
	void selected(HWND hWnd);

	// Redraw function
	void redrawObject(HWND hWnd);
	void redrawObject(HDC hdc);

	//Make change( resize + move )
	int makeChange(HWND hWnd, LPARAM lParam);
	void reSize(HWND hWnd, LPARAM lParam, WPARAM wParam, int& loc);
};

#endif