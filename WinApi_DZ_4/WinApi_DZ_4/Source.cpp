//����������� ����������, ��������� �� ������ ����������� ����, � ���������� ��������� �����������������.
//�	������������ �������� ����� ������� ���� �� ����� ������� �, �� �������� ������, 
//���� �� ��� �����, � � ������ ���������� ������ �� ���������� ����������� 
//��������������(��� ��������, ���� ����� �� ��������� ���������� ��� �������� ��������������) 
//�������� �������, ������� �������� ���� ���������� �����(������� � ���� ������� ��������� �������� �� �����).
//�	����������� ������ �������� ���������� 10�10, � ��� ������� �������� �������� 
//���������� ������� �������� ������������ ������ ������� ��������������� ��������������.
//�	��� ������ ������ ������� ���� ��� ������������ �������� � ��������� ���� ������ 
//��������� ���������� � �������(���������� ����� ��������, ������ � ������, � ����� 
//���������� �������� ������������ ������������� ����). � ������ ���� � ����� ������ 
//��������� ��������� ���������, �� ������������ �������� �������� � ���������� ���������� �������.
//�	��� ������� ������ ����� ������ ���� ��� ������������ �������� �� ������ 
//��������� � �����(��� ����� ����� ��������������� �������� DestroyWindow, ������� 
//� ��� ���������������� ������� ��������).� ������ ���� � ����� ������ ��������� 
//��������� ���������, �� ������������ �������� �������� � ���������� ���������� �������.
//��� ���������� ���������� ������������� ������������ ���������� STL.

#include <Windows.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <Windowsx.h>  //for mouse coordinates
#include "resource.h" 
#include <memory>		// for swap 

typedef std::basic_string<TCHAR> tstring;

#ifdef _UNICODE
#define to_tstring std::to_wstring
#else
#define to_tstring std::to_string
#endif

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szWindowClass[] = TEXT("����������");

HINSTANCE hInst;

int APIENTRY _tWinMain(HINSTANCE hInstance /*���������� �������� ����������*/, HINSTANCE hPrevInstance/*���������� ����������� ����������*/,
	LPTSTR lpCmdLine/*���������� ��������� ���������*/, INT nCmdShow/*����������� ����������� �������*/)
{
	hInst = hInstance;
	HWND hDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc); //������� ����������� ������ 
	ShowWindow(hDlg, TRUE);

	MSG msg = { 0 };
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1)/*��������� ������, � IDD ��� �����*/, NULL, DlgProc);
	// ������� ��������� ������ Invisible = TRUE/FALSE ��� ������� (��������� ���������� ���������� ��������� ���� ������)
	return msg.wParam; //post_quit_message ��������� ��������� ������
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static int xPos1, xPos2, yPos1, yPos2;
	static int count = 0;

	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{	
						xPos1 = GET_X_LPARAM(lParam);		// ����������
						yPos1 = GET_Y_LPARAM(lParam);
						break;
	}
	case WM_LBUTTONUP:
	{
						xPos2 = GET_X_LPARAM(lParam);		// ����������
						yPos2 = GET_Y_LPARAM(lParam);
						SendMessage(hWnd, WM_CREATE, 0,0);
						break;
	}
	case WM_CREATE:
	{
					  if (xPos2 < xPos1)
						  std::swap(xPos2, xPos1);
					  if (yPos2 < yPos1)
						  std::swap(yPos2, yPos1);
					  int hWidth = xPos2 - xPos1;
					  int hHight = yPos2 - yPos1;
					  if (hWidth < 10 || hHight < 10)
					  {
						  MessageBox(NULL, _T("�� �������� ������� ��������� �������\n ������� ������� ����������� 20�20 ��������"), 
							  _T("��������!!!"), MB_OK | MB_ICONINFORMATION);
						  hWidth = 20;
						  hHight = 20;
					  }

					  tstring counter = to_tstring(++count);
					  CreateWindowEx(0, _T("STATIC"), counter.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER,
						  xPos1, yPos1, hWidth, hHight, hWnd, 0, hInst, 0);
					  break;
	}
	case WM_LBUTTONDBLCLK:
	{
							 FindWindowEx();
							 break;
	}
	case WM_RBUTTONDOWN:
	{
					
						   break;
	}
	case WM_CLOSE:
	{
					 DestroyWindow(hWnd); //��� createdialog 
					 PostQuitMessage(0);
					 //EndDialog(hWnd, 0); //����������, ������������ �������� ��� dialogbox
					 return TRUE;
	}
	}
	return FALSE;
}