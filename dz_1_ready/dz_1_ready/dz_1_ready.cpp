#include <iostream>
#include <cstring>
using namespace std;

class String
{
	char *str = nullptr;
	unsigned size = 0;
public:
	String()  //�1 default constructor
	{}
	void assign(const char *s); //�2 changing of string
	String(const char *s) //�1 constructor whith 1 argument
	{
		assign(s);
	}
	char *get_str() //�3 return string
	{
		return str;
	}
	unsigned int get_size() //�4 length of string
	{
		return size;
	}
	void concat(const char *s); //�5 add newstring to existing one
	void insertchar(); //�6 insert the symbol
	void codeascii() //�7 code ascii
	{
		for (int i = 0; str[i] != '\0'; ++i)
			cout << str[i] << " = " << (int)str[i] << endl;
	}
	void toupregister()	//�8 to upper register
	{
		_strupr_s(str, size);
	}
	void tolowregister() //�9 to lower register
	{
		_strlwr_s(str, size);
	}
	~String()
	{
		if (str)
		{
			delete[] str;
			str = nullptr;
		}
	}
};
void String::assign(const char *s)
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
void String::concat(const char *s)
{
	if (s && *s)
	{
		int sizenew = strlen(s) + size;
		char *strnew = new char[sizenew];
		strcpy_s(strnew, size, str);
		delete[] str;
		strcat_s(strnew, sizenew, s);
		size = sizenew;
		str = strnew;
	}
}
void String::insertchar()
{
	char ch = 'X';		//symbol to insert
	unsigned int posit = 13;		//pisotoin to insert (only positiv!)
	if (posit >= 0 && posit <= size)
	{
		++size;
		char *newstr = new char[size];
		for (unsigned int i = 0; i< size - 1; ++i)
		{
			if (i < posit)
				newstr[i] = str[i];
			else
			if (i == posit)
			{
				newstr[i] = ch;
				newstr[i + 1] = str[i];
			}
			else
				newstr[i + 1] = str[i];
		}

		delete[] str;
		str = newstr;
	}
	else
		cout << "Enter right position" << endl;
}
int main()
{
	String obj1;					 // initialisation
	String obj2("How much watch?"); // initialisation 2
	cout << obj2.get_str() << endl;
	obj1.assign("Six clock.");
	cout << obj1.get_str() << endl;
	cout << "The length of your string - " << obj1.get_size() << endl;

	obj1.assign("Such much? ");
	obj1.concat("For whom how.");
	cout << obj1.get_str() << endl;
	cout << "The length of your string - " << obj1.get_size() << endl;

	obj1.insertchar();
	cout << obj1.get_str() << endl;

	obj1.toupregister();
	cout << obj1.get_str() << endl;

	obj1.tolowregister();
	cout << obj1.get_str() << endl;

	obj1.codeascii();
	cout << obj1.get_str() << endl;
	return 0;
}
