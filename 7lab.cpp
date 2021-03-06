// 7lab.cpp: Определяет точку входа для приложения.
//

#include "stdafx.h"
#include "7lab.h"

#define MAX_LOADSTRING 100
#define ID_CLEARBUTTON 777

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HWND hwnd;
HWND hwnd2;

int X = 0, Y = 0;
const int l = 100;
bool drawCheck = false;
int x[l];
int y[l];
int counter = 0;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void drawObj(HDC);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY7LAB, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
            DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY7LAB));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND — обработать меню приложения
//  WM_PAINT — отрисовать главное окно
//  WM_DESTROY — отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
	{	
		
		HWND hw = CreateWindowEx(NULL,
		L"BUTTON",
		L"CLEAR",
		WS_VISIBLE|
		WS_CHILD,
		0,
		0,
		150,
		85,
		hWnd,
		(HMENU)ID_CLEARBUTTON,
		hInst,
		NULL);
		
		CreateWindowEx(NULL,
			L"BUTTON",
			L"CLEAR",
			WS_VISIBLE |
			WS_CHILD,
			150,
			85,
			150,
			85,
			hWnd,
			(HMENU)ID_CLEARBUTTON,
			hInst,
			NULL);

		for (int i = 0; i < l; i++)
		{
			x[i] = -100;
			y[i] = -100;
		}
	}
	break;
	case WM_LBUTTONDOWN:
	{
		X = LOWORD(lParam);
		Y = HIWORD(lParam);
		drawCheck = true;
		x[counter] = X;
		y[counter] = Y;
		counter++;
		if (counter == l)
			counter = 0;
		InvalidateRect(hWnd, NULL, true);
	}break;
    case WM_COMMAND:
        {
	        int wmId = LOWORD(wParam);
            switch (wmId)
            {
			case ID_CLEARBUTTON:
			{
				drawCheck = false;
				for (int i = 0; i < l; i++)
				{
					x[i] = -100;
					y[i] = -100;
				}
				counter = 0;
				InvalidateRect(hWnd, NULL, TRUE);
			}
			break;
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			drawObj(hdc);//функция для рисования домика
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void drawObj(HDC hdc)
{
	if (drawCheck) 
	{
		HPEN pen,pen2,pen3,pen4,pen5,pen6;
		pen = CreatePen(PS_SOLID, 5, RGB(255,255,0));
		pen2 = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
		pen3 = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
		pen4 = CreatePen(PS_SOLID, 5, RGB(255, 255, 0));
		pen5 = CreatePen(PS_SOLID, 5, RGB(0, 255, 100));
		pen6 = CreatePen(PS_SOLID, 5, RGB(100, 100, 100));

		for (int i = 0; i < l; i++) 
		{
			SelectObject(hdc, pen);
			MoveToEx(hdc, x[i] - 25, y[i] + 25, NULL);
			LineTo(hdc, x[i], y[i] - 25);
			LineTo(hdc, x[i] + 25, y[i] + 25);
			LineTo(hdc, x[i] - 25, y[i] + 25);
			
		    SelectObject(hdc, pen2);
			MoveToEx(hdc, x[i] - 25, y[i] + 30, NULL);
			LineTo(hdc, x[i] - 25, y[i] + 30);
			LineTo(hdc, x[i] + 25, y[i] + 30);
			LineTo(hdc, x[i] + 25, y[i] + 80);
			LineTo(hdc, x[i] - 25, y[i] + 80);
			LineTo(hdc, x[i] - 25, y[i] + 30);
			MoveToEx(hdc, x[i] - 15, y[i] + 45, NULL);
			LineTo(hdc, x[i] - 15, y[i] + 45);
			LineTo(hdc, x[i] + 15, y[i] + 45);
			LineTo(hdc, x[i] + 15, y[i] + 65);
			LineTo(hdc, x[i] - 15, y[i] + 65);
			LineTo(hdc, x[i] - 15, y[i] + 45);
			MoveToEx(hdc, x[i] - 15, y[i] + 55, NULL);
			LineTo(hdc, x[i] - 15, y[i] + 55);
			LineTo(hdc, x[i] + 15, y[i] + 55);
			MoveToEx(hdc, x[i], y[i] + 45, NULL);
			LineTo(hdc, x[i], y[i] + 45);
			LineTo(hdc, x[i], y[i] + 65);
		
		    SelectObject(hdc, pen3);
			MoveToEx(hdc, x[i] - 15, y[i] + 45, NULL);
			LineTo(hdc, x[i] - 15, y[i] + 45);
			LineTo(hdc, x[i] + 15, y[i] + 45);
			LineTo(hdc, x[i] + 15, y[i] + 65);
			LineTo(hdc, x[i] - 15, y[i] + 65);
			LineTo(hdc, x[i] - 15, y[i] + 45);
			MoveToEx(hdc, x[i] - 15, y[i] + 55, NULL);
			LineTo(hdc, x[i] - 15, y[i] + 55);
			LineTo(hdc, x[i] + 15, y[i] + 55);
			MoveToEx(hdc, x[i], y[i] + 45, NULL);
			LineTo(hdc, x[i], y[i] + 45);
			LineTo(hdc, x[i], y[i] + 65);
		
		    SelectObject(hdc, pen4);
			MoveToEx(hdc, x[i] - 10, y[i] , NULL);
			LineTo(hdc, x[i]-10, y[i] );
			LineTo(hdc, x[i] - 10, y[i] -15);
			LineTo(hdc, x[i] -20, y[i] - 15);
			LineTo(hdc, x[i] - 20, y[i]+12);
			LineTo(hdc, x[i] - 10, y[i]);
		
		    SelectObject(hdc, pen5);
			MoveToEx(hdc, x[i] - 50, y[i] +85, NULL);
			LineTo(hdc, x[i] - 50, y[i] + 85);
			LineTo(hdc, x[i] - 40, y[i] + 90);
			LineTo(hdc, x[i] - 30, y[i] + 85);
			LineTo(hdc, x[i] - 20, y[i] + 90);
			LineTo(hdc, x[i] - 10, y[i] + 85);
			LineTo(hdc, x[i] , y[i] + 90);
			LineTo(hdc, x[i] +10, y[i] + 85);
			LineTo(hdc, x[i] +20, y[i] + 90);
			LineTo(hdc, x[i] +30, y[i] + 85);
			LineTo(hdc, x[i] +40, y[i] + 90);
			LineTo(hdc, x[i] + 50, y[i] + 85);
		
		    SelectObject(hdc, pen6);
			MoveToEx(hdc, x[i] - 15, y[i] -20, NULL);
			LineTo(hdc, x[i] - 15, y[i] -20);
			MoveToEx(hdc, x[i] - 18, y[i] - 24, NULL);
			LineTo(hdc, x[i] - 18, y[i] - 24);
			MoveToEx(hdc, x[i] - 21, y[i] - 28, NULL);
			LineTo(hdc, x[i] - 21, y[i] - 28);
		}
		DeleteObject(pen);
		DeleteObject(pen2);
		DeleteObject(pen3);
		DeleteObject(pen4);
		DeleteObject(pen5);
		DeleteObject(pen6);
	}
}
