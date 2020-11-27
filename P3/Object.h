#pragma once
#include <string>
#include <vector>
#include <Windows.h>
#include "stdafx.h"

#ifndef OBJECT_HEADER
#define OBJECT_HEADER



#define LINE 0
#define ELLIPSE 1
#define REC 2
#define CTEXT 3

class Object
{
public:
	int type;
	RECT pos;
	COLORREF color;

	virtual int isResize(LPARAM lParam, RECT rec);
	virtual int getResizePos(LPARAM lParam);

	// isSomething
	virtual bool isText();
	virtual bool isRec();
	virtual bool isRow();
	virtual bool isLine();

	// Setter
	virtual void setPos(RECT _rec);
	virtual void setColor(COLORREF _color);
	virtual void setFont(LOGFONT _font);
	virtual void setString(WCHAR* string);

	// Getter
	virtual RECT getPos();
	virtual COLORREF getColor();
	/*virtual int getType();*/
	virtual LOGFONT getFont();
	virtual  const wchar_t* getString();

	//Check function
	virtual bool isSelect(LPARAM lParam);
	virtual void selected(HWND hWnd);

	// Redraw function
	virtual void redrawObject(HWND hWnd);
	virtual void redrawObject(HDC hdc);

	//Make change( resize + move )
	virtual int makeChange(HWND hWnd, LPARAM lParam);
	virtual void reSize(HWND hWnd, LPARAM lParam, WPARAM wParam, int& loc);
};

#endif

