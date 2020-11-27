#pragma once

#include "Object.h"
#include <string>
#include <vector>
#include <Windows.h>
#include "stdafx.h"

#ifndef T_HEADER
#define T_HEADER




class Text : public Object
{
public:
	int x_current;
	int y_current;
	// Font and text
	LOGFONT cfont;
	std::wstring text_str;

	// position of resize points
	int isResize(LPARAM lParam, RECT rec);
	int getResizePos(LPARAM lParam);

	// isText
	bool isText();

	// Setter
	void setPos(RECT _rec);
	void setColor(COLORREF _color);
	void setFont(LOGFONT _font);
	void setString(WCHAR* string);

	// Getter
	RECT getPos();
	COLORREF getColor();
	LOGFONT getFont();
	const wchar_t* getString();

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