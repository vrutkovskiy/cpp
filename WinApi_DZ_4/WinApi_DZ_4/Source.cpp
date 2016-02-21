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
//•	При НАЖАТИИ СРЕДНЕЙ кнопки мыши над поверхностью «статика» он должен 
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

struct parametrs
{
	HWND parhW = { 0 };
	int xbegin = 0;
	int ybegin = 0;
	int xend = 0;
	int yend = 0;
	int parcounter = 0;

	parametrs() = default;
	parametrs(HWND& hW, int x, int y, int x2, int y2, int cnt) :
		parhW(hW), xbegin(x), ybegin(y), xend(x2), yend(y2), parcounter(cnt)
	{}
	//parametrs(parametrs& par)
	//{
	//	parhW = par.parhW;		// подправить. а то не хочет копировать. ПОДСКАЖИТЕ????
	//	xbegin = par.xbegin;
	//	ybegin = par.ybegin;
	//	xend = par.xend;
	//	yend = par.yend;
	//	parcounter = par.parcounter;
	//}
	/*parametrs& operator=(parametrs& par) = delete;*/ // подправить. тоже самое. ПОДСКАЖИТЕ????
	~parametrs() = default;
};
std::vector<parametrs> vectpar;

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
				MessageBox(NULL, 
					_T("Вы выделили слишком маленький участок\n поэтому размеры установлены 20х20 пикселей"), 
					_T("ВНИМАНИЕ!!!"), MB_OK | MB_ICONINFORMATION);
				hWidth = 20;
				hHight = 20;
				xPos2 = xPos1 + 20;
				yPos2 = yPos1 + 20;
			}
			tstring counter = to_tstring(++count);
			HWND hW = CreateWindowEx(0, _T("STATIC"), counter.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP,
				xPos1, yPos1, hWidth, hHight, hWnd, 0, hInst, 0);
			parametrs par1(hW, xPos1, yPos1, xPos2, yPos2, count); 
			vectpar.push_back(par1);
			break;
		}
		case WM_MBUTTONDOWN:
		{
			int xPos3 = GET_X_LPARAM(lParam);		// координаты
			int yPos3 = GET_Y_LPARAM(lParam);
			int min = 10000;		//минимальный каунтер
			int iteratmin = 0;	//итератор с минимальным каунтером
			int flag = 0;		
			for (unsigned i = 0; i < vectpar.size(); ++i)
				if (xPos3>vectpar.at(i).xbegin && xPos3<vectpar.at(i).xend
					&& yPos3>vectpar.at(i).ybegin && yPos3 < vectpar.at(i).yend)
				{
					if (min > vectpar.at(i).parcounter) //находим мин каунтер
					{
						min = vectpar.at(i).parcounter;
						iteratmin = i;
						flag = 1;
					}
				}
			if (flag)
			{
				DestroyWindow(vectpar.at(iteratmin).parhW); //удаляем окно
				vectpar.erase(vectpar.begin() + iteratmin);	//удаляем элемент из вектора и тут наверное HWND уже нету
				flag = 0;
			}
			break;
		}
		case WM_RBUTTONDOWN:
		{
			int	xPos3 = GET_X_LPARAM(lParam);		// координаты
			int yPos3 = GET_Y_LPARAM(lParam);
			int max = 0;	//максимальный каунтер
			int iteratmax = 0;	//итератор на максимальный куантер
			int flag = 0;
			for (unsigned i = 0; i < vectpar.size(); ++i)
				if ((xPos3>vectpar.at(i).xbegin && xPos3<vectpar.at(i).xend)
					&& (yPos3>vectpar.at(i).ybegin && yPos3 < vectpar.at(i).yend))
				{
					if (max < vectpar.at(i).parcounter)
					{
						max = vectpar.at(i).parcounter;
						iteratmax = i;
						flag = 1;
					}
				}
			if (flag)
			{
				/*TCHAR buf[256];*/
				/*GetWindowText(vectpar.at(i).parhW, buf, 256);*/
				tstring head = _T("№ статика = "); head += to_tstring(vectpar.at(iteratmax).parcounter);
				head += _T(", X1 = "); head += to_tstring(vectpar.at(iteratmax).xbegin);
				head += _T(", X2 = "); head += to_tstring(vectpar.at(iteratmax).xend);
				head += _T(", Y1 = "); head += to_tstring(vectpar.at(iteratmax).ybegin);
				head += _T(", y2 = "); head += to_tstring(vectpar.at(iteratmax).yend);
				head += _T(", ширина = "); head += to_tstring(vectpar.at(iteratmax).xend - vectpar.at(iteratmax).xbegin);
				head += _T(", высота = "); head += to_tstring(vectpar.at(iteratmax).yend - vectpar.at(iteratmax).ybegin);
				SetWindowText(hWnd, head.c_str());
				flag = 0;
			}
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