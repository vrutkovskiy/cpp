//1.	Написать приложение, обладающее следующей функциональностью :
//•	при нажатии клавиши <Enter> главное окно позиционируется в левый верхний угол экрана 
//с размерами(300х300) и начинает перемещаться по периметру экрана с определённой скоростью;
//•	при нажатии клавиши <Esc> перемещение окна прекращается.
//
//2.	Написать приложение, обладающее следующей функциональностью :
//•	при последовательном нажатии ЛЕВОЙ КЛАВИШИ МЫШИ дочерние окна главного окна 
//приложения «Калькулятор» минимизируются;
//•	при последовательном нажатии клавиши ПРАВОЙ КЛАВИШИ МЫШИ дочерние окна восстанавливаются в 
//обратном порядке, т.е.дочернее окно, которое минимизировалось последним, первым будет восстановлено.

#include <Windows.h>
#include <tchar.h>
#include <string>
#include <vector>

typedef std::basic_string<TCHAR> tstring;

#ifdef _UNICODE
#define to_tstring std::to_wstring
#else
#define to_tstring std::to_string
#endif

BOOL CALLBACK EnumChildFunction(HWND hW, LPARAM Lp);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szWindowClass[] = TEXT("ПРИЛОЖЕНИЕ");
std::vector<HWND> vhand;

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex = { 0 };

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	/*wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));*/

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			MB_ICONWARNING);

		return 1;
	}

	static TCHAR szTitle[] = _T("Движение окна. Окна калькулятора мини/макси");

	// The parameters to CreateWindow explained:
	// szWindowClass: the name of the application
	// szTitle: the text that appears in the title bar
	// WS_OVERLAPPEDWINDOW: the type of window to create
	// CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
	// 500, 100: initial size (width, length)
	// NULL: the parent of this window
	// NULL: this application does not have a menu bar
	// hInstance: the first parameter from WinMain
	// NULL: not used in this application
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 200,
		NULL,
		NULL,
		hInstance,
		NULL
		);
	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Win32 Guided Tour"),
			NULL);  // вместо последнего NULL можно передать кнопку MB_OK или две кнопки сразу  MB_OK | MB_Cancel

		return 1;
	}

	// The parameters to ShowWindow explained:
	// hWnd: the value returned from CreateWindow
	// nCmdShow: the fourth parameter from WinMain
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);		//переводит нажатую клавишу в ее код  (нажал кнопку посылается сообщение WM_CHAR с кодом нажатой кнопки )
		// если ее убрать то будет выдавать состояние нажата/отпущена KEY_UP/KEY_DOWN  --- WM_CHAR не будет
		DispatchMessage(&msg);		// обрабатывает сообщения
	}

	return (int)msg.wParam;

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
// wparam получает код нажатой клавиши в данном случае, LPARAM - координаты курсора в данном случае 2байта и 2 байта
// лучше пользоваться xPos = GET_X_LPARAM(lParam); yPos = GET_Y_LPARAM(lParam);
{
	static int begin = 0;	//начало движения окна
	static int side = 1;	//сторона движения окна
	static int move = 0;	//сдвиг от края экрана
	static int count = 0;	//количество кругов

	switch (message)
	{
		case WM_LBUTTONDOWN:
		{
			//EnumWindows(EnumFunction, lParam);
			HWND hCalc = FindWindow(TEXT("CalcFrame"), TEXT("Калькулятор"));
			if (hCalc)
			{
				EnumChildWindows(hCalc, EnumChildFunction, (LPARAM)hWnd);
			}
			break;
		}
		case WM_RBUTTONDOWN:
		{
			if (!vhand.empty())
			{
				ShowWindow(vhand.back(), SW_SHOWNORMAL);  //SW_MAXIMIZE / SW_SHOWNOACTIVATE / SW_RESTORE
				vhand.pop_back();
			}
			break;
		}
		case WM_KEYDOWN:
		{
			RECT pWndsize;
			GetWindowRect(hWnd, &pWndsize);
			switch (wParam)
			{
				case VK_RETURN:
				{
					if (begin == 0)
					{
						MoveWindow(hWnd, 0, 0, 300, 300, TRUE);
						begin = 1;
					}
					SetTimer(hWnd, 0, 2, NULL);
					break;
				}
				case VK_ESCAPE:
				{
					KillTimer(hWnd, NULL);
				}
			}
			break;
		}
		case WM_TIMER:
		{
			int xMaxres = GetSystemMetrics(SM_CXSCREEN);	//максимальная ширина главного экрана 
			int yMaxres = GetSystemMetrics(SM_CYSCREEN);	//максимальная высота главного экрана
			RECT pWndsize;
			GetWindowRect(hWnd, &pWndsize);
			if (side == 1)
				if (pWndsize.left < (xMaxres - (pWndsize.right - pWndsize.left) - move))
					MoveWindow(hWnd, pWndsize.left + 10, pWndsize.top, pWndsize.right - pWndsize.left,
					pWndsize.bottom - pWndsize.top, TRUE);
				else
					side = 2;
			if (side == 2)
				if (pWndsize.top < (yMaxres - (pWndsize.bottom - pWndsize.top) - move))
					MoveWindow(hWnd, pWndsize.left, pWndsize.top + 10, pWndsize.right - pWndsize.left,
					pWndsize.bottom - pWndsize.top, TRUE);
				else
					side = 3;
			if (side == 3)
				if (pWndsize.left > 0 + move)
					MoveWindow(hWnd, pWndsize.left - 10, pWndsize.top, pWndsize.right - pWndsize.left,
					pWndsize.bottom - pWndsize.top, TRUE);
				else
					side = 4;
			if (side == 4)
				if (pWndsize.top > 0 + move)
					MoveWindow(hWnd, pWndsize.left, pWndsize.top - 10, pWndsize.right - pWndsize.left,
					pWndsize.bottom - pWndsize.top, TRUE);
				else
				{
					side = 1;
					move += 50;
					++count;
				}
			if (count == 14)
			{
				side = 1;
				begin = 0;
				move = 0;
				count = 0;
				KillTimer(hWnd, NULL);
			}
			break;
		}
		case WM_DESTROY:
			PostQuitMessage(0);  // генерирует сообщение wm_quit возвращает наружу 0
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
	}

	return 0;
}

BOOL CALLBACK EnumChildFunction(HWND hW, LPARAM Lp)
{
	TCHAR buf[256];
	TCHAR bufClass[256];
	GetClassName(hW, bufClass, 256);
	tstring condition = bufClass;
	if (!condition.compare(_T("Button")))
	{
		GetWindowText(hW, buf, 256);
		vhand.push_back(hW);
		ShowWindow(hW, SW_MINIMIZE);
	}
	
	return 1;
}