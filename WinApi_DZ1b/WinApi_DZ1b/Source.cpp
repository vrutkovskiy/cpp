//2.	Написать приложение, которое «угадывает» задуманное пользователем число от 1 до 100. 
//Для запроса к пользователю использовать окна сообщений.После того, как число отгадано, 
//необходимо вывести количество попыток, потребовавшихся для этого, и предоставить пользователю 
//возможность сыграть еще раз, не завершая программу. Окна сообщений следует оформить 
//кнопками и иконками в соответствии с конкретной ситуацией.
//При выполнении вышеприведенных заданий ввиду отсутствия необходимости  создания 
//главного окна приложения, реализацию алгоритма можно привести непосредственно в главной 
//функции программы.Тогда каркас приложения может иметь следующий вид :
#include <Windows.h>
#include <string>
#include <tchar.h>
#include <ctime>
using namespace std;

typedef /*std::*/basic_string<TCHAR> tstring;

#ifdef _UNICODE

#define to_tstring to_wstring
#else
#define to_tstring to_string
#endif

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstprev, LPSTR lPCmdLine, int nCmdShow)
{
	srand(time(unsigned(0)));

	tstring greet = _T("Вас приветствует игра Угадайка!\n\n\
Правила игры:\nКомпьютер попытается угадать загаданное Вами число\n\
от 0 до 99. Если число угадано нажмите ДА, иначе нажмите НЕТ и\n\
компьютер продолжит угадывать. Для выхода нажмите Отмена или закройте окно.");

	int x = IDCANCEL;
	int count = 0;

	do{
		++count;
		if (count == 1)
		{
			x = MessageBox(NULL, greet.c_str(), _T("WinApi DZ №1b"),
				MB_OKCANCEL /*Кнопка OK*/ | MB_ICONINFORMATION /*Иконка рядом с текстом*/);
			if (x == IDCANCEL)
				break;
		}
		
		int numb = rand() % 100;
		
		tstring str = _T("Вы загадали : ");
		str += to_tstring(numb);
		str += _T(" ?");

		x = MessageBox(NULL, str.c_str(), _T("WinApi DZ №1b"),
			MB_YESNOCANCEL /*Кнопка OK*/ | MB_ICONQUESTION /*Иконка рядом с текстом*/);

		if (x == IDYES)
		{
			str = _T("Компьютер угадал ваше число с ");
			str += to_tstring(count);
			str += _T(" попытки.");
			str += _T("\n\nХотите сыграть еще раз?");
			x = MessageBox(NULL, str.c_str(), _T("WinApi DZ №1b"),
				MB_OKCANCEL /*Кнопка OK*/ | MB_ICONEXCLAMATION /*Иконка рядом с текстом*/);
			if (x == IDCANCEL)
				break;
			else
				count = 0;
		}

	} while (x != IDCANCEL);

	return 0;
}