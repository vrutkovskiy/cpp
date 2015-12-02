#include <iostream>				
#include <cstring>
using namespace std;

#define BREAKER 1   //1 - program to work
					//2 - to check write protection

struct game_resource
{
	mutable char *name = nullptr;
	mutable int life = 100;
	mutable unsigned *count = nullptr;
};

class Game1
{
	game_resource personage;
	mutable unsigned size = 0;

public:		
	Game1() : personage{}, size(0) //default constructor	
	{}
	void assign(const char *persname);
	Game1(const char *persname)
	{
		assign(persname);
	}
#if BREAKER == 1
	Game1(const Game1 &newpers) :size(newpers.size)
	{
		personage.name = newpers.personage.name;
		personage.life = newpers.personage.life;
		newpers.personage.name = nullptr;
		personage.count = newpers.personage.count;
		++(*personage.count);			
		newpers.size = 0;
		newpers.personage.life = 0;
	}
	const Game1 &operator=(const Game1 &newpers)  
	{
		if (this == &newpers)
			return *this;
		else
		{
			size = newpers.size;
			personage.name = newpers.personage.name;
			personage.life = newpers.personage.life;
			newpers.personage.name = nullptr;
			personage.count = newpers.personage.count;
			++(*personage.count);
			newpers.size = 0;
			newpers.personage.life = 0;
			return *this;
		}
	}
#endif

#if BREAKER == 2
	Game1(const Game1 &newpers) = delete;
	const Game1 &operator=(const Game1 &newpers) = delete;
#endif
	void get_game_res() const
	{
		if (personage.name)
			cout << "	Name = " << personage.name << "	Adress of pointer - " << &personage.name << "	Adress of Name - " << (int*)personage.name << endl;
		else
			cout << "	Name = ---"<< endl;
		cout << "	Life = " << personage.life << endl;
		if (personage.count)
			cout << "	Count of personages = " << *personage.count << endl;
		else
			cout << "	Count of personages = 0" << endl;
		if (size)
			cout << "	Length of personage name = " << size - 1 << endl;
		else
			cout << "	Length of personage name = " << size << endl;
		
	}

	~Game1()
	{
		--(*personage.count);
		if (personage.name && *personage.count == 1)
		{
			delete[] personage.name;
		}
		personage.name = nullptr;
	}
};

class Game2
{
	game_resource personage;
	mutable unsigned size = 0;
public:
	Game2() : personage{}, size(0) //default constructor	
	{}
	void assign(const char *persname);
	Game2(const char *persname)
	{
		assign(persname);
	}
	Game2(const Game2 &newpers) :size(newpers.size)
	{
		personage.name = new char[size];
		strcpy_s(personage.name, size, newpers.personage.name);
		personage.life = newpers.personage.life;
		
	}
	const Game2 &operator=(const Game2 &newpers)
	{
		if (this == &newpers)
			return *this;
		else
		{
			size = newpers.size;
			personage.name = new char[size];
			strcpy_s(personage.name, size, newpers.personage.name);
			personage.life = newpers.personage.life;
			return *this;
		}
	}

	void get_game_res() const
	{
		if (personage.name)
			cout << "	Name = " << personage.name << "	Adress of pointer - " << &personage.name << "	Adress of Name - " << (int*)personage.name << endl;
		else
			cout << "	Name = ---" << endl;
		cout << "	Life = " << personage.life << endl;
		if (size)
			cout << "	Length of personage name = " << size - 1 << endl;
		else
			cout << "	Length of personage name = " << size << endl;

	}

	~Game2()
	{
		
		if (personage.name)
		{
			delete[] personage.name;
			personage.name = nullptr;
		}
	}
};

int main()
{
	int menu1;

	do{
		cout << "MENU:" << endl;
		cout << "1. Remouving copying (transfer of rights)" << endl;
		cout << "2. Ordinary copying (cross ownership)" << endl;
		cout << "3. Exit" << endl;

		fflush(stdin);
		cin >> menu1;

		if (menu1 == 1)
		{
			cout << "Creating personage 1:" << endl;
			Game1 pers1{ "Ivan" };
			pers1.get_game_res();
			cout << "Creating personage 2:" << endl;
			Game1 pers2{ "Fiodor" };
			pers2.get_game_res();

			cout << endl << "Copying personage 2 to 3 (CONSTRUCTOR pers3 = pers2):" << endl;
			Game1 pers3 = pers2;
			cout << "Personage 3:" << endl;
			pers3.get_game_res();
			cout << "Personage 2:" << endl;
			pers2.get_game_res();

			cout << endl << "Copying personage 1 to 2 (pers2 = pers1):" << endl;
			pers2 = pers1;
			cout << "Personage 2:" << endl;
			pers2.get_game_res();
			cout << "Personage 1:" << endl;
			pers1.get_game_res();
		}
		else
			if (menu1 == 2)
			{
				cout << "Creating personage 1:" << endl;
				Game2 pers1{ "Ivan" };
				pers1.get_game_res();
				cout << "Creating personage 2:" << endl;
				Game2 pers2{ "Fiodor" };
				pers2.get_game_res();

				cout << endl << "Copying personage 2 to 3 (CONSTRUCTOR pers3 = pers2):" << endl;
				Game2 pers3 = pers2;
				cout << "Personage 3:" << endl;
				pers3.get_game_res();
				cout << "Personage 2:" << endl;
				pers2.get_game_res();

				cout << endl << "Copying personage 1 to 2 (pers2 = pers1):" << endl;
				pers2 = pers1;
				cout << "Personage 2:" << endl;
				pers2.get_game_res();
				cout << "Personage 1:" << endl;
				pers1.get_game_res();
			}
			else
				if (menu1 == 3)
					break;
				else
					cout << "Enter 1,2 or 3" << endl;
	} while (true);
	
	return 0;
}
void Game1::assign(const char *persname)
{
	if (personage.name)
	{
		delete[] personage.name;
		personage.name = nullptr;
	}
	if (persname && *persname)
	{
		size = strlen(persname) + 1;
		personage.name = new char[size];
		strcpy_s(personage.name, size, persname);
		personage.count = new unsigned int(1);
	}
}
void Game2::assign(const char *persname)
{
	if (personage.name)
	{
		delete[] personage.name;
		personage.name = nullptr;
	}
	if (persname && *persname)
	{
		size = strlen(persname) + 1;
		personage.name = new char[size];
		strcpy_s(personage.name, size, persname);
	}
}
