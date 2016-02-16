//1)	Написать приложение, позволяющее при нажатии левой кнопки мыши изменить текст 
//в заголовке окна стандартного приложения «Калькулятор», а при нажатии правой кнопки мыши 
//сместить вправо кнопку «пуск», изменив на ней надпись.
//2)	Написать приложение, обладающее следующей функциональностью :
//•	при нажатии кнопки <Enter> окно позиционируется в левый верхний угол экрана с размерами(300Х300);
//•	с помощью клавиш управления курсором осуществляется перемещение окна.

#include <Windows.h>
#include <tchar.h>
#include <string>

typedef std::basic_string<TCHAR> tstring;

#ifdef _UNICODE
#define to_tstring std::to_wstring
#else
#define to_tstring std::to_string
#endif

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szWindowClass[] = TEXT("ПРИЛОЖЕНИЕ");

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

	static TCHAR szTitle[] = _T("Изменение названия Калькулятора");

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
	switch (message)
	{
		case WM_LBUTTONDOWN:
		{
			HWND hCalc = FindWindow(_T("CalcFrame"), _T("Калькулятор"));	//ищет дескриптор калькулятора (если он открыт то найдет)
			//первый пареметр класс окна, второй имя окна		
			tstring newname = _T("СУПЕР КАЛЬКУЛЯТОР");
			if (hCalc)
				SetWindowText(hCalc, newname.c_str());	//hwnd(идентификатор программы) - смотреть через spy++
			break;
		}
		case WM_RBUTTONDOWN:
		{
			RECT pWndsize;
			HWND parent = FindWindow(_T("Shell_TrayWnd"), NULL);  
			HWND btnstart = FindWindowEx(parent, NULL,_T("Button"), _T("ПУСК")); //win7 не находит
			/*HWND btnstart = FindWindow(_T("Button"), _T("ПУСК"));*/
			if (btnstart)
				if (GetWindowRect(btnstart, &pWndsize)) // получить размеры окна
				{
					MoveWindow(btnstart, pWndsize.left + 10, pWndsize.top, 
						pWndsize.right - pWndsize.left, pWndsize.bottom - pWndsize.top, TRUE); 
					//смещение окна на 10 пикселей новая координата верннего левого угла Х и У, 
					//размеры окна, и последним параметром БУЛ тип - перерисовывать окно или нет
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
					MoveWindow(hWnd, 0, 0, 300, 300, TRUE);
					break;
				case VK_RIGHT:
					if (pWndsize.left < (1880 - (pWndsize.right - pWndsize.left)-200))
						MoveWindow(hWnd, pWndsize.left + 10, pWndsize.top, pWndsize.right - pWndsize.left,
						pWndsize.bottom - pWndsize.top, TRUE);
					break;
				case VK_LEFT:
					if (pWndsize.left > 0)
						MoveWindow(hWnd, pWndsize.left - 10, pWndsize.top, pWndsize.right - pWndsize.left,
						pWndsize.bottom - pWndsize.top, TRUE);
					break;
				case VK_UP:
					if (pWndsize.top > 0)
						MoveWindow(hWnd, pWndsize.left, pWndsize.top - 10, pWndsize.right - pWndsize.left,
						pWndsize.bottom - pWndsize.top, TRUE);
					break;
				case VK_DOWN:
					if (pWndsize.top <(1030 - (pWndsize.bottom - pWndsize.top)))
						MoveWindow(hWnd, pWndsize.left, pWndsize.top + 10, pWndsize.right - pWndsize.left,
						pWndsize.bottom - pWndsize.top, TRUE);
					break;
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