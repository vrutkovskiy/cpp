//1)	�������� ����������, ����������� ��� ������� ����� ������ ���� �������� ����� 
//� ��������� ���� ������������ ���������� ������������, � ��� ������� ������ ������ ���� 
//�������� ������ ������ �����, ������� �� ��� �������.
//2)	�������� ����������, ���������� ��������� ����������������� :
//�	��� ������� ������ <Enter> ���� ��������������� � ����� ������� ���� ������ � ���������(300�300);
//�	� ������� ������ ���������� �������� �������������� ����������� ����.

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

TCHAR szWindowClass[] = TEXT("����������");

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

	static TCHAR szTitle[] = _T("��������� �������� ������������");

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
			NULL);  // ������ ���������� NULL ����� �������� ������ MB_OK ��� ��� ������ �����  MB_OK | MB_Cancel

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
		TranslateMessage(&msg);		//��������� ������� ������� � �� ���  (����� ������ ���������� ��������� WM_CHAR � ����� ������� ������ )
		// ���� �� ������ �� ����� �������� ��������� ������/�������� KEY_UP/KEY_DOWN  --- WM_CHAR �� �����
		DispatchMessage(&msg);		// ������������ ���������
	}

	return (int)msg.wParam;

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)			
// wparam �������� ��� ������� ������� � ������ ������, LPARAM - ���������� ������� � ������ ������ 2����� � 2 �����
// ����� ������������ xPos = GET_X_LPARAM(lParam); yPos = GET_Y_LPARAM(lParam);
{
	switch (message)
	{
		case WM_LBUTTONDOWN:
		{
			HWND hCalc = FindWindow(_T("CalcFrame"), _T("�����������"));	//���� ���������� ������������ (���� �� ������ �� ������)
			//������ �������� ����� ����, ������ ��� ����		
			tstring newname = _T("����� �����������");
			if (hCalc)
				SetWindowText(hCalc, newname.c_str());	//hwnd(������������� ���������) - �������� ����� spy++
			break;
		}
		case WM_RBUTTONDOWN:
		{
			RECT pWndsize;
			HWND parent = FindWindow(_T("Shell_TrayWnd"), NULL);  
			HWND btnstart = FindWindowEx(parent, NULL,_T("Button"), _T("����")); //win7 �� �������
			/*HWND btnstart = FindWindow(_T("Button"), _T("����"));*/
			if (btnstart)
				if (GetWindowRect(btnstart, &pWndsize)) // �������� ������� ����
				{
					MoveWindow(btnstart, pWndsize.left + 10, pWndsize.top, 
						pWndsize.right - pWndsize.left, pWndsize.bottom - pWndsize.top, TRUE); 
					//�������� ���� �� 10 �������� ����� ���������� �������� ������ ���� � � �, 
					//������� ����, � ��������� ���������� ��� ��� - �������������� ���� ��� ���
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
			PostQuitMessage(0);  // ���������� ��������� wm_quit ���������� ������ 0
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
	}

	return 0;
}