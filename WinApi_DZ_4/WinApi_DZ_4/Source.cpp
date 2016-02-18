//Разработать приложение, созданное на основе диалогового окна, и обладающее следующей функциональностью.
//•	Пользователь «щелкает» левой кнопкой мыши по форме диалога и, не отпуская кнопку, 
//ведёт по ней мышку, а в момент отпускания кнопки по полученным координатам 
//прямоугольника(как известно, двух точек на плоскости достаточно для создания прямоугольника) 
//создаётся «статик», который содержит свой порядковый номер(имеется в виду порядок появления «статика» на форме).
//•	Минимальный размер «статика» составляет 10х10, а при попытке создания элемента 
//управления меньших размеров пользователь должен увидеть соответствующее предупреждение.
//•	При щелчке правой кнопкой мыши над поверхностью «статика» в заголовке окна должна 
//появиться информация о статике(порядковый номер «статика», ширина и высота, а также 
//координаты «статика» относительно родительского окна). В случае если в точке щелчка 
//находится несколько «статиков», то предпочтение отдается «статику» с наибольшим порядковым номером.
//•	При двойном щелчке левой кнопки мыши над поверхностью «статика» он должен 
//исчезнуть с формы(для этого можно воспользоваться функцией DestroyWindow, вызывая 
//её для соответствующего объекта «статика»).В случае если в точке щелчка находится 
//несколько «статиков», то предпочтение отдается «статику» с наименьшим порядковым номером.
//При разработке приложения рекомендуется использовать библиотеку STL.

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

TCHAR szWindowClass[] = TEXT("ПРИЛОЖЕНИЕ");

HINSTANCE hInst;

int APIENTRY _tWinMain(HINSTANCE hInstance /*дескриптор текущего приложения*/, HINSTANCE hPrevInstance/*дескриптор предыдущего приложения*/,
	LPTSTR lpCmdLine/*переданные параметры программе*/, INT nCmdShow/*возможность отображение консоли*/)
{
	hInst = hInstance;
	HWND hDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc); //создает немодальный диалог 
	ShowWindow(hDlg, TRUE);

	MSG msg = { 0 };
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1)/*принимает строку, а IDD это число*/, NULL, DlgProc);
	// создает модальный диалог Invisible = TRUE/FALSE без разницы (запрещает дальнейшее выполнение программы пока открыт)
	return msg.wParam; //post_quit_message последнее сообщение вернет
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static int xPos1, xPos2, yPos1, yPos2;
	static int count = 0;

	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{	
						xPos1 = GET_X_LPARAM(lParam);		// координаты
						yPos1 = GET_Y_LPARAM(lParam);
						break;
	}
	case WM_LBUTTONUP:
	{
						xPos2 = GET_X_LPARAM(lParam);		// координаты
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
						  MessageBox(NULL, _T("Вы выделили слишком маленький участок\n поэтому размеры установлены 20х20 пикселей"), 
							  _T("ВНИМАНИЕ!!!"), MB_OK | MB_ICONINFORMATION);
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
					 DestroyWindow(hWnd); //для createdialog 
					 PostQuitMessage(0);
					 //EndDialog(hWnd, 0); //дискриптор, возвращаемое значение для dialogbox
					 return TRUE;
	}
	}
	return FALSE;
}