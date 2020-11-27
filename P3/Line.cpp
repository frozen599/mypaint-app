#include "stdafx.h"
#include "Line.h"

bool Line::isLine()
{
	return true;
}

int Line::isResize(LPARAM lParam, RECT rec)
{
	POINTS clickpoint = MAKEPOINTS(lParam);
	int a, b, func;
	int r;

	a = abs(rec.left + ((rec.right - rec.left) / 2));
	b = abs(rec.top + (rec.bottom - rec.top) / 2);
	r = 5;
	func = pow(clickpoint.x - a, 2) + pow(clickpoint.y - b, 2);
	if (func <= pow(r, 2))
		return true;
	return false;
}


void Line::setPos(RECT _rec)
{
	pos = _rec;
}

void Line::setColor(COLORREF _color)
{
	color = _color;
}

RECT Line::getPos()
{
	return pos;
}

COLORREF Line::getColor()
{
	return color;
}

bool Line::isSelect(LPARAM lParam)
{
	POINTS clickpoint = MAKEPOINTS(lParam);
	int a, b, func;

	a = pos.right - pos.left;
	b = pos.bottom - pos.top;
	func = b*(clickpoint.x - pos.left) - a*(clickpoint.y - pos.top);

	if (func >= 0 && func <= 200 || func <= 0 && func >= -200)
		return true;
	return false;
}

void Line::selected(HWND hWnd)
{
	HDC dc;
	HPEN pen;
	dc = GetDC(hWnd);
	pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	SelectObject(dc, pen);
	Ellipse(dc, pos.left - 5, pos.top - 5, pos.left + 5, pos.top + 5);
	Ellipse(dc, pos.right - 5, pos.bottom - 5, pos.right + 5, pos.bottom + 5);
}

void Line::redrawObject(HWND hWnd)
{
	HDC dc = GetDC(hWnd);
	HPEN pen;
	pen = CreatePen(PS_SOLID, 2, color);
	SelectObject(dc, pen);
	MoveToEx(dc, pos.left, pos.top, NULL);
	LineTo(dc, pos.right, pos.bottom);
}

void Line::redrawObject(HDC dc)
{
	HPEN pen;
	pen = CreatePen(PS_SOLID, 2, color);
	SelectObject(dc, pen);
	MoveToEx(dc, pos.left, pos.top, NULL);
	LineTo(dc, pos.right, pos.bottom);
}

int Line::makeChange(HWND hWnd, LPARAM lParam)
{
	return getResizePos(lParam);
}

void Line::reSize(HWND hWnd, LPARAM lParam, WPARAM wParam, int& loc)
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
		case 1:
		{
			if (!(wParam & MK_LBUTTON)) { loc = -1; return; }

			RECT rec1;
			GetClientRect(hWnd, &rec1);
			pos.left = LOWORD(lParam);
			pos.top = HIWORD(lParam);
			InvalidateRect(hWnd, &rec1, TRUE);
		}
		break;
		case 2:
		{
			if (!(wParam & MK_LBUTTON)) { loc = -1; return; }

			RECT rec1;
			GetClientRect(hWnd, &rec1);
			pos.right = LOWORD(lParam);
			pos.bottom = HIWORD(lParam);
			InvalidateRect(hWnd, &rec1, TRUE);
		}
		break;
	}
}

int Line::getResizePos(LPARAM lParam)
{
	POINTS clickpoint = MAKEPOINTS(lParam);
	RECT rec;
	rec.left = rec.right = pos.left;
	rec.top = rec.bottom = pos.top;
	if (isResize(lParam, rec))
		return 1;
	rec.left = rec.right = pos.right;
	rec.top = rec.bottom = pos.bottom;
	if (isResize(lParam, rec))
		return 2;
	if (isSelect(lParam))
	{
		x_current = LOWORD(lParam);
		y_current = HIWORD(lParam);
		return 0;
	}

	return -1;
}