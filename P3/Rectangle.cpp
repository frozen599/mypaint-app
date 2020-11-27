#include "stdafx.h"
#include "Rectangle.h"

bool Rec::isRec()
{
	return true;
}

int Rec::isResize(LPARAM lParam, RECT rec)
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

void Rec::setPos(RECT _rec)
{
	pos = _rec;
}

void Rec::setColor(COLORREF _color)
{
	color = _color;
}

RECT Rec::getPos()
{
	return pos;
}

COLORREF Rec::getColor()
{
	return color;
}

bool Rec::isSelect(LPARAM lParam)
{
	POINTS clickpoint = MAKEPOINTS(lParam);

	if (pos.bottom < pos.top)
	{
		if ((clickpoint.x >= pos.left && clickpoint.x <= pos.right && clickpoint.y <= pos.top && clickpoint.y >= pos.bottom) || clickpoint.x <= pos.left && clickpoint.x >= pos.right && clickpoint.y <= pos.top && clickpoint.y >= pos.bottom)
			return true;
	}
	else
	{
		if ((clickpoint.x >= pos.left && clickpoint.x <= pos.right && clickpoint.y >= pos.top && clickpoint.y <= pos.bottom) || clickpoint.x <= pos.left && clickpoint.x >= pos.right && clickpoint.y >= pos.top && clickpoint.y <= pos.bottom)
			return true;
	}
	return false;
}

void Rec::selected(HWND hWnd)
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

void Rec::redrawObject(HWND hWnd)
{
	HDC dc = GetDC(hWnd);
	HPEN pen;
	pen = CreatePen(PS_SOLID, 2, color);
	SelectObject(dc, pen);
	Rectangle(dc, pos.left, pos.top, pos.right, pos.bottom);
}

void Rec::redrawObject(HDC dc)
{
	HPEN pen;
	pen = CreatePen(PS_SOLID, 2, color);
	SelectObject(dc, pen);
	Rectangle(dc, pos.left, pos.top, pos.right, pos.bottom);
}

int Rec::makeChange(HWND hWnd, LPARAM lParam)
{
	return getResizePos(lParam);
}

void Rec::reSize(HWND hWnd, LPARAM lParam, WPARAM wParam, int& loc)
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
			pos.top = HIWORD(lParam);
			InvalidateRect(hWnd, &rec1, TRUE);
		}
		break;
		case 3:
		{
			if (!(wParam & MK_LBUTTON)) { loc = -1; return; }

			RECT rec1;
			GetClientRect(hWnd, &rec1);
			pos.left = LOWORD(lParam);
			pos.bottom = HIWORD(lParam);
			InvalidateRect(hWnd, &rec1, TRUE);
		}
		break;
		case 4:
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

int Rec::getResizePos(LPARAM lParam)
{
	POINTS clickpoint = MAKEPOINTS(lParam);
	RECT rec;

	rec.left = rec.right = pos.left;
	rec.top = rec.bottom = pos.top;
	if (isResize(lParam, rec))
		return 1;

	rec.left = rec.right = pos.right;
	rec.top = rec.bottom = pos.top;
	if (isResize(lParam, rec))
		return 2;

	rec.left = rec.right = pos.left;
	rec.top = rec.bottom = pos.bottom;
	if (isResize(lParam, rec))
		return 3;

	rec.left = rec.right = pos.right;
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