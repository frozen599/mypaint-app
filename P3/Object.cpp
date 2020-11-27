#include "stdafx.h"
#include "Object.h"

int Object::isResize(LPARAM lParam, RECT rec)
{
	return 1;
}
int Object::getResizePos(LPARAM lParam)
{
	return 1;
}
bool Object::isText()
{
	return false;
}

bool Object::isRec()
{
	return false;
}

bool Object::isRow()
{
	return false;
}

bool Object::isLine()
{
	return false;
}

void  Object::setPos(RECT _rec)
{
	
}
void  Object::setColor(COLORREF _color)
{

}
void  Object::setFont(LOGFONT _font)
{

}
void  Object::setString(WCHAR* string)
{

}

RECT  Object::getPos()
{
	RECT a;
	a.bottom = 1;
	a.left = 1;
	a.right = 1;
	a.top = 1;
	return a;
}
COLORREF  Object::getColor()
{
	return 1;
}
int getType()
{
	return 1;
}
LOGFONT Object::getFont()
{
	LOGFONT* a;
	a = new LOGFONT();
	return *a;
}
const wchar_t*  Object::getString()
{
	return L"Hello";
}

bool  Object::isSelect(LPARAM lParam)
{
	return true;
}
void  Object::selected(HWND hWnd)
{

}

void  Object::redrawObject(HWND hWnd)
{

}

void  Object::redrawObject(HDC dc)
{

}

int  Object::makeChange(HWND hWnd, LPARAM lParam)
{
	return 1;
}
void  Object::reSize(HWND hWnd, LPARAM lParam, WPARAM wParam, int& loc)
{

}