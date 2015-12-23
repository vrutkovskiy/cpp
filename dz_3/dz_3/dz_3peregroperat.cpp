/*
Написать класс для эффективной работы со строками, позволяющий форматировать и сравнивать строки, 
хранить в строках числовые значения и извлекать их. Для этого необходимо реализовать:
• перегруженные операции присваивания и конкатенации; 
• ввод/вывод строки;
• операции сравнения и приведения типов;
• преобразование в число любого типа;
• поиска символов и подстрок.
• обращение к элементам строки по индексу.
Весь функционал должен быть реализован в соответствии с хорошими практиками 
и необходимыми проверками.
Написать программу, демонстрирующую работу с этим классом. 
Программа должна содержать меню, позволяющее осуществить проверку всех методов класса.
*/
#include <iostream>			
#include <iomanip>
#include <cstring>
using namespace std;

class String
{
	char* str = nullptr;
	unsigned size = 0;

public:
	String() : str(nullptr), size(0)		//конструктор по умолчанию
	{}
	void assign(const char* s);				//метод для конструктора с одним аргументом
	explicit String(const char* s)			//конструктор с одним аргументом
	{
		assign(s);
	}
	String(const String& obj) :size(obj.size)	//конструктор копирования
	{
		if (obj.str)
		{
			str = new char[size];
			strcpy_s(str, size, obj.str);
		}
	}

	String& operator=(const String& obj)	// оператор копирования перегруженный
	{
		if (&obj == this)
			return *this;
		else
			if (obj.str)
			{
				if (str)
					delete[] str;
				size = obj.size;
				str = new char[size];
				strcpy_s(str, size, obj.str);
				return *this;
			}
	}

	bool operator>(const String& obj) const		//оператор > для строк перегруженный
	{
		return (strcmp(str, obj.str) > 0);
	}
	bool operator<(const String& obj) const		//оператор < для строк перегруженный
	{

		return obj.operator>(*this);	//можно так
		/*	return obj> *this;*/		//оператор > уже перегружен, можно и так

	}
	friend bool operator==(const String& tekobj, const String& obj);	//оператор == для строк перегруженный
	friend bool operator!=(const String& tekobj, const String& obj);	//оператор != для строк перегруженный
	friend ostream& operator<<(ostream& os, const String& obj);			//оператор вывода для строк перегруженный
	friend istream& operator>> (istream& is, String& str);				//оператор ввода для строк перегруженный

	String& operator+=(const String& obj)								//оператор += для строк перегруженный
	{
		if (obj.str && *obj.str)
		{
			if (str)
			{
				int sizenew = strlen(obj.str) + size;
				char *strnew = new char[sizenew];
				strcpy_s(strnew, size, str);
				delete[] str;
				strcat_s(strnew, sizenew, obj.str);
				size = sizenew;
				str = strnew;
				return *this;
			}
			else
				return operator=(obj);
		}
		else
			return *this;
	}

	void charactersearch(const char& userch)		//поиск символов
	{
		int flag = 0;
		for (unsigned i = 0; i < size; ++i)
		{
			if (str[i] == userch)
			{
				flag = 1;
				cout << endl << "Your character position is " << i << endl;
			}
		}
		if (flag == 0)
			cout << endl << "There is no such character" << endl;
	}

	void stringsearch(const String& userobj)		//поиск подстрок
	{
		int flag = 0;
		int numb=0;
		for (unsigned i = 0; i < size; ++i)
		{
			if (str[i] == userobj.str[0])
			{
				for (unsigned j = 1; j < userobj.size-1; ++j)
					if (str[i + j] == userobj.str[j])
						flag = 1;
					else
					{
						flag = 0;
						break;
					}
				if (flag == 1)
				{
					cout << endl << "Your string start position is "
					<< i + 1 << endl;
					++numb;
				}
			}
		}
		if (flag == 0 && numb == 0)
			cout << endl << "There is no such string" << endl;
	}

	void digitsearch()			//поиск цифр, и строку из цифр преобразуем в дабл
	{
		int flag = 0;
		char* tempstr=nullptr;
		double strtodoub;
		unsigned count = 0;
		for (unsigned i = 0; i < size; ++i)
		{
			if (isdigit(str[i]))
			{
				if (!tempstr)
					tempstr = new char[256];
				tempstr[count] = str[i];
				++count;
				flag = 1;
				if (i !=size-1) 
					if (!isdigit(str[i + 1]))
					{
						strtodoub = atof(tempstr);
						cout << strtodoub << " ";
						delete[] tempstr;
						tempstr = nullptr;
						count = 0;
					}
			}
		}
		if (flag == 0)
			cout << "There is no digits in the string" << endl;
	}

	operator char*()								//оператор приведения объекта к строке перегруженный
	{
		return str;
	}
	
	const char operator[](unsigned& i) const			//оператор [] перегруженный для строк
	{
		return str[i];
	}
	const char* get_str() const
	{
		return str ? str : "";
	}
	const String get_obj() const
	{
		return *this;
	}
	const unsigned get_size() const
	{
		return size;
	}

	~String()
	{
		if (str)
		{
			delete[] str;
		}
		str = nullptr;
	}
};

void String::assign(const char* s)
{
	if (str)
	{
		delete[] str;
		str = nullptr;
	}
	if (s && *s)
	{
		size = strlen(s) + 1;
		str = new char[size];
		strcpy_s(str, size, s);
	}
}
bool operator==(const String& tekobj, const String& obj) 
{
	if (tekobj.size != obj.size)				
		return false;
	else
		return !strcmp(tekobj.get_str(), obj.get_str());
}
bool operator!=(const String& tekobj, const String& obj)
{
	return !operator==(tekobj, obj);
}
ostream& operator<<(ostream& os, const String& obj) 
{
	if (obj.str)
		return os<<obj.str;
	return os;
}
istream& operator>> (istream& is, String& str)
{
	char tempstr[256];

	fgets(tempstr, 256, stdin);
	tempstr[strlen(tempstr) - 1] = '\0';
	fflush(stdin);
	if (str.str)
	{
		delete[]str.str;
		str.str = nullptr;
	}
	str.str = new char[strlen(tempstr) + 1];
	strcpy_s(str.str, strlen(tempstr) + 1, tempstr);
	str.size = strlen(str.str)+1;
	
	return is;
}

int main()
{
	int menu;
	String obj1("3Lon23don is the cap443ital of gre56at Britain.4");
	String obj2("Is there life on Mars?");
	String obj3;

	do
	{
		cout << endl;
		cout << "MENU" << endl;
		cout << "1. Enter two strings" << endl << "2. Print two strings" << endl
			<< "3. Compare two strings" << endl << "4. Concatenate two strings" << endl
			<< "5. Copy one string to another string" << endl << "6. Casting" << endl
			<< "7. Search for digit and string to double" << endl << "8. Character search" << endl
			<< "9. SubString search" << endl << "10. Show element" << endl
			<< "11. Exit (or any (exception 1-10) other digit)" << endl;

		fflush(stdin);
		cin >> menu;

		if (menu == 1)
		{
			cout << endl
			<< "Enter first string" << endl;
			fflush(stdin);
			cin >> obj1;
			cout << "Enter second string" << endl;
			fflush(stdin);
			cin >> obj2;
		}

		if (menu == 2)
		{
			cout << endl
			<< setw(29) << left<< "This is your first string: " << obj1 << endl
			<< setw(29) << left<< "This is your second string: " << obj2 << endl;
		}

		if (menu == 3)
		{
			cout << endl;
			if (obj1 == obj2 || !(obj1 != obj2))
			{
				cout << "obj1 == obj2" << endl
				<< "String 1 and String 2 is equal" << endl;
			}
			else
			{
				cout << "obj1 != obj2" << endl
				<< "String 1 and String 2 is NOT equal" << endl;
				if (obj1 > obj2 || !(obj1 < obj2))
				{
					cout << "obj1 > obj2" << endl
					<< "String 1 is bigger than String 2" << endl;
				}
				else
				{
					cout << "obj1 < obj2" << endl
					<< "String 1 is smaller than String 2" << endl;
				}
			}
		}

		if (menu == 4)
		{
			cout << endl
			<< "obj1 += obj2" << endl
			<< (obj1 += obj2) << endl;
		}

		if (menu == 5)
		{
			cout << endl;
			obj3 = obj1;
			cout << "obj3 = obj1" << endl
				<< "obj3: " << obj3 << endl;

			String obj4 = obj2;
			cout << "String obj4 = obj2" << endl
				<< "obj4: " << obj4 << endl;
		}

		if (menu == 6)
		{
			cout << endl;
			char * st1 = static_cast<char*>(obj1);
			cout << "char * st1 = static_cast<char*>(obj1); "
				<< endl << "st1 = " << st1 << endl;
		}

		if (menu == 7)
		{
			cout << endl;
			obj1.digitsearch();
			cout << endl;
		}

		if (menu == 8)
		{
			cout << endl << obj1 << endl;
			char ch;
			cout << "Enter character " << endl;
			fflush(stdin);
			cin >> ch;
			obj1.charactersearch(ch);
		}

		if (menu == 9)
		{
			cout << endl << obj1 << endl;
			String obj5;
			cout << "Enter your string" << endl;
			fflush(stdin);
			cin >> obj5;
			obj1.stringsearch(obj5);
		}

		if (menu == 10)
		{
			cout << endl << obj1<< endl;
			unsigned element;
			cout << "Enter element number from 1 to " << obj1.get_size()-1<< " ->i"<< endl;
			do{
				fflush(stdin);
				cin >> element;
				if (element<0 || element> obj1.get_size() - 1)
					cout << "Enter element number from 1 to " << obj1.get_size() - 1 << " ->i" << endl;
			} while (element<0 || element> obj1.get_size() - 1);
			cout << "str[i] = " << obj1[element-1] << endl;
		}

		if (menu < 1 || menu > 10)
			break;
	} while (true);
	
	return 0;
}
