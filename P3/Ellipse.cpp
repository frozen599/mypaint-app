#include "stdafx.h"
#include "Ellipse.h"

bool Row::isRow()
{
	return true;
}

int Row::isResize(LPARAM lParam, RECT rec)
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



void Row::setPos(RECT _rec)
{
	pos = _rec;
}

void Row::setColor(COLORREF _color)
{
	color = _color;
}

RECT Row::getPos()
{
	return pos;
}

COLORREF Row::getColor()
{
	return color;
}

bool Row::isSelect(LPARAM lParam)
{
	POINTS clickpoint = MAKEPOINTS(lParam);
	int a, b, func;
	int r;

	a = abs(pos.left + ((pos.right - pos.left) / 2));
	b = abs(pos.top + (pos.bottom - pos.top) / 2);
	r = abs((pos.right - pos.left) / 2);
	func = pow(clickpoint.x - a, 2) + pow(clickpoint.y - b, 2);
	if (func <= pow(r, 2))
		return true;
	return false;
}

void Row::selected(HWND hWnd)
{
	HDC dc;
	HPEN pen;
	dc = GetDC(hWnd);
	pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	SelectObject(dc, pen);
	Ellipse(dc, abs(pos.left + ((pos.right - pos.left) / 2)) - 5, pos.top - 5, abs(pos.left + ((pos.right - pos.left) / 2)) + 5, pos.top + 5);
	Ellipse(dc, abs(pos.left + ((pos.right - pos.left) / 2)) - 5, pos.bottom - 5, abs(pos.left + ((pos.right - pos.left) / 2)) + 5, pos.bottom + 5);
	Ellipse(dc, pos.left - 5, abs(pos.top + (pos.bottom - pos.top) / 2) - 5, pos.left + 5, abs(pos.top + (pos.bottom - pos.top) / 2) + 5);
	Ellipse(dc, pos.right - 5, abs(pos.top + (pos.bottom - pos.top) / 2) - 5, pos.right + 5, abs(pos.top + (pos.bottom - pos.top) / 2) + 5);
}

void Row::redrawObject(HWND hWnd)
{
	HDC dc = GetDC(hWnd);
	HPEN pen;
	pen = CreatePen(PS_SOLID, 2, color);
	SelectObject(dc, pen);
	Ellipse(dc, pos.left, pos.top, pos.right, pos.bottom);
}

void Row::redrawObject(HDC dc)
{
	HPEN pen;
	pen = CreatePen(PS_SOLID, 2, color);
	SelectObject(dc, pen);
	Ellipse(dc, pos.left, pos.top, pos.right, pos.bottom);
}

int Row::makeChange(HWND hWnd, LPARAM lParam)
{
	return getResizePos(lParam);
}

void Row::reSize(HWND hWnd, LPARAM lParam, WPARAM wParam, int& loc)
{
	RECT rec1;
	GetClientRect(hWnd, &rec1);
	switch (loc)
	{
		case 0:
		{
			if (!(wParam & MK_LBUTTON)) { loc = -1; return; }
			
			int x_move_lenght = LOWORD(lParam)-x_current;
			int y_move_lenght = HIWORD(lParam)-y_current;

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
			InvalidateRect(hWnd, &rec1, TRUE);
		}
		break;
		case 2:
		{
			if (!(wParam & MK_LBUTTON)) { loc = -1; return; }

			RECT rec1;
			GetClientRect(hWnd, &rec1);
			pos.top = HIWORD(lParam);
			InvalidateRect(hWnd, &rec1, TRUE);
		}
		break;
		case 3:
		{
			if (!(wParam & MK_LBUTTON)) { loc = -1; return; }


			RECT rec1;
			GetClientRect(hWnd, &rec1);
			pos.right = LOWORD(lParam);
			InvalidateRect(hWnd, &rec1, TRUE);
		}
		break;
		case 4:
		{
			if (!(wParam & MK_LBUTTON)) { loc = -1; return; }


			RECT rec1;
			GetClientRect(hWnd, &rec1);
			pos.bottom = HIWORD(lParam);
			InvalidateRect(hWnd, &rec1, TRUE);
		}
		break;
	}
}

int Row::getResizePos(LPARAM lParam)
{
	POINTS clickpoint = MAKEPOINTS(lParam);
	RECT rec;

	rec.left = rec.right = pos.left;
	rec.top = rec.bottom = abs(pos.top + (pos.bottom - pos.top) / 2);
	if (isResize(lParam, rec))
		return 1;

	rec.left = rec.right = abs(pos.left + ((pos.right - pos.left) / 2));
	rec.top = rec.bottom = pos.top;
	if (isResize(lParam, rec))
		return 2;

	rec.left = rec.right = pos.right;
	rec.top = rec.bottom = abs(pos.top + (pos.bottom - pos.top) / 2);
	if (isResize(lParam, rec))
		return 3;

	rec.left = rec.right = abs(pos.left + ((pos.right - pos.left) / 2));
	rec.top = rec.bottom = pos.bottom;
	if (isResize(lParam, rec))
		return 4;
	
	if (isSelect(lParam))
	{
		x_current = LOWORD(lParam);
		y_current = HIWORD(lParam);
		return 0;
	}

	return -1;
}