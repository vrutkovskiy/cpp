//1.	Написать приложение, позволяющее вывести на экран краткое резюме с помощью последовательности окон сообщений
//(количество окон сообщений – не менее трёх).На заголовке последнего окна сообщения должно отобразиться 
//среднее число символов на странице(общее число символов в резюме поделить на количество окон сообщений).

#include <Windows.h>
#include <string>
#include <tchar.h>
using namespace std;

typedef /*std::*/basic_string<TCHAR> tstring;

#ifdef _UNICODE

#define to_tstring /*std::*/to_wstring
#else
#define to_tstring /*std::*/to_string
#endif

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstprev, LPSTR lPCmdLine, int nCmdShow)
{
	tstring resume = _T("APIENTRY меняется дефайном на WINAPI(потом на __stdcall)\n\n\
HINSTANCE hInstance - дискриптор текущего приложения \
(содержит адрес начала кода программы в ее адресном пространстве)\n\n\
HINSTANCE hPrevInstance - дискриптор предыдущего приложения\n\n\
LPSTR lPCmdLine - указатель на начало командной строки, введенной при запуске программы\n\n\
int nCmdShow - это значение содержит желаемый вид окна (например, свернутый или развернутый)");

	MessageBox(NULL, resume.c_str(), _T("WinApi DZ №1a"), 
		MB_OK /*Кнопка OK*/| MB_ICONINFORMATION /*Иконка рядом с текстом*/);

	tstring resume2 = _T("WNDCLASSEX //структура(класс) окна, которая содержит: \n\n\
UINT cbSize; //размер данной структуры\n\n\
UINT style; //стили данного класса (перерисовка при изменении размеров, включение даблклика и т.д.)\n\n\
WNDPROC lpfnWndProc; //указатель на процедуру окна\n\n\
int cbClsExtra; //дополнительное количество байт для выделения под данный класс (по дефолту 0)\n\n\
int cbWndExtra; //дополнительное количество байт для выделения под данное окно (по дефолту 0)\n\n\
HINSTANCE hInstance; // дискриптор текущего приложения (инициализируется аргументом из WinMain)\n\n");

	MessageBox(NULL, resume2.c_str(), _T("WinApi DZ №1a"),
		MB_OK /*Кнопка OK*/ | MB_ICONINFORMATION /*Иконка рядом с текстом*/);

	tstring resume3 = _T("HICON hIcon; //дискриптор класса(ресурса) иконок\n\n\
HCURSOR hCursor; //дискриптор класса(ресурса) курсоров\n\n\
HBRUSH hbrBackground; //дискриптор класса заливки фона (можно так же указать значение цвета)\n\n\
LPCTSTR lpszMenuName; //указатель на строку char'ов (заканчивающуюся '/0') указывающий на \
имя ресурса класса меню (NULL - отсутствие меню)\n\n\
LPCTSTR lpszClassName; //имя класса может быть строкой char'ов не более 256!!!\
(зарегистрированных???) или АТОМ -------------НЕПОНЯТНО----------\n\n\
HICON hIconSm; //дискриптор маленькой иконки, если он равен NULL, то\
система ищет иконку подходящего размера в классе hIcon.");

	int size = (resume3.size()+resume2.size()+resume.size())/3;

	tstring head = _T("Среднее кол-во символов на странице = ");
	head += to_tstring(size);

	MessageBox(NULL, resume3.c_str(), head.c_str(),
		MB_OK /*Кнопка OK*/ | MB_ICONINFORMATION /*Иконка рядом с текстом*/);

	return 0;
}