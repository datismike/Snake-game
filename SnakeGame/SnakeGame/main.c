#include <Windows.h>
#include "stack.h"
#include "field.h"

Stack *snake;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR szCmdLine, int nCmdShow)
{
	snake = newStack();

	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = WINDOW_CLASS_NAME;
	wcex.hIconSm = wcex.hIcon;
	RegisterClassEx(&wcex);

	HWND hWnd = CreateWindow(
		wcex.lpszClassName,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		FIELD_WIDTH * CELL_WIDTH,
		FIELD_HEIGHT * CELL_HEIGHT,
		NULL, NULL, hInstance, NULL
	);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hDC = BeginPaint(hWnd, &ps);
			HDC hCmpDC = CreateCompatibleDC(hDC);
			RECT rect;
			GetClientRect(hWnd, &rect);
			int fWidth = rect.right - rect.left;
			int fHeight = rect.bottom - rect.top;
			HBITMAP hBitmap = CreateCompatibleBitmap(hDC, fWidth, fHeight);
			SelectObject(hCmpDC, hBitmap);

			LOGBRUSH lBrush;
			HBRUSH hBrush;

			// Draw field background
			lBrush.lbColor = BACKGROUND_COLOR;
			lBrush.lbStyle = BS_SOLID;
			hBrush = CreateBrushIndirect(&lBrush);
			FillRect(hCmpDC, &rect, hBrush);

			// Draw snake
			lBrush.lbColor = CELL_COLOR;
			hBrush = CreateBrushIndirect(&lBrush);
			SelectObject(hCmpDC, hBrush);
			for (PNode node = snake->getBottomNode(snake); node != NULL; node = node->next)
			{
				Rectangle(hCmpDC, node->data.x + CELL_MARGIN, node->data.y + CELL_MARGIN, node->data.x + CELL_WIDTH - CELL_MARGIN, node->data.y + CELL_HEIGHT - CELL_MARGIN);
			}

			SetStretchBltMode(hDC, COLORONCOLOR);
			BitBlt(hDC, 0, 0, fWidth, fHeight, hCmpDC, 0, 0, SRCCOPY);

			DeleteObject(hBrush);
			DeleteObject(hBitmap);
			DeleteDC(hCmpDC);
			DeleteDC(hDC);
			EndPaint(hWnd, &ps);
			break;
		}
		case WM_TIMER:
		{

			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		default:
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
}