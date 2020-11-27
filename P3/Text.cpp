#include "stdafx.h"
#include "Text.h"

int Text::isResize(LPARAM lParam, RECT rec)
{
	POINTS clickpoint = MAKEPOINTS(lParam);
	int a, b, func;
	int r;

	a = abs(rec.left + ((rec.right - rec.left) / 2));
	b = abs(rec.top + (rec.bottom - rec.top) / 2);
	r = abs((rec.right - rec.left) / 2);
	func = pow(clickpoint.x - a, 2) + pow(clickpoint.y - b, 2);
	if (func <= pow(r, 2) || func >= pow(r, 2) + 10)
		return true;
	return false;
}


void Text::setPos(RECT _rec)
{
	pos = _rec;
}

void Text::setColor(COLORREF _color)
{
	color = _color;
}

RECT Text::getPos()
{
	return pos;
}

COLORREF Text::getColor()
{
	return color;
}

bool Text::isSelect(LPARAM lParam)
{
	POINTS clickpoint = MAKEPOINTS(lParam);

	if ((clickpoint.x >= pos.left && clickpoint.x <= pos.right && clickpoint.y >= pos.top && clickpoint.y <= pos.bottom) || clickpoint.x <= pos.left && clickpoint.x >= pos.right && clickpoint.y >= pos.top && clickpoint.y <= pos.bottom)
		return true;
	return false;
}

void Text::selected(HWND hWnd)
{
	HDC dc;
	HPEN pen;
	dc = GetDC(hWnd);
	pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	SelectObject(dc, pen);
	Ellipse(dc, pos.left - 5, pos.top - 5, pos.left + 5, pos.top + 5);
	Ellipse(dc, pos.left - 5, pos.bottom - 5, pos.left + 5, pos.bottom + 5);
	Ellipse(dc, pos.right - 5, pos.top - 5, pos.right + 5, pos.top + 5);
	Ellipse(dc, pos.right - 5, pos.bottom - 5, pos.right + 5, pos.bottom + 5);
}

void Text::redrawObject(HWND hWnd)
{
	HDC dc = GetDC(hWnd);
	HFONT tfont;
	dc = GetDC(hWnd);
	tfont = CreateFontIndirect(&cfont);
	SetTextColor(dc, color);
	SelectObject(dc, tfont);
	TextOut(dc, pos.left, pos.top, text_str.c_str(), text_str.size());
}

void Text::redrawObject(HDC dc)
{
	HFONT tfont;
	tfont = CreateFontIndirect(&cfont);
	SetTextColor(dc, color);
	SelectObject(dc, tfont);
	TextOut(dc, pos.left, pos.top, text_str.c_str(), text_str.size());
}

int Text::makeChange(HWND hWnd, LPARAM lParam)
{
	return getResizePos(lParam);
}

void Text::reSize(HWND hWnd, LPARAM lParam, WPARAM wParam, int& loc)
{
	RECT rec1;
	GetClientRect(hWnd, &rec1);
	switch (loc)
	{
	case 0:
	{
		if (!(wParam & MK_LBUTTON)) { loc = -1; return; }

		int x_move_lenght = LOWORD(lParam) - x_current;
		int y_move_lenght = HIWORD(lParam) - y_current;

		x_current = LOWORD(lParam);
		y_current = HIWORD(lParam);

		pos.left += x_move_lenght;
		pos.right += x_move_lenght;
		pos.bottom += y_move_lenght;
		pos.top += y_move_lenght;
		InvalidateRect(hWnd, &rec1, TRUE);
	}
	break;

	default:
		break;
	}
	
}

int Text::getResizePos(LPARAM lParam)
{
	POINTS clickpoint = MAKEPOINTS(lParam);

	if (isSelect(lParam))
	{
		x_current = LOWORD(lParam);
		y_current = HIWORD(lParam);
		return 0;
	}

	return -1;
}

LOGFONT Text::getFont()
{
	return cfont;
}

const wchar_t* Text::getString()
{
	return text_str.c_str();
}

void Text::setFont(LOGFONT _font)
{
	cfont = _font;
}

void Text::setString(WCHAR* string)
{
	std::wstring tmp1(string);
	text_str = tmp1;
}

bool Text::isText()
{
	return true;
}