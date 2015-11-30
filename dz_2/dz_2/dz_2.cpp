
#include <iostream>				
#include <cstring>
using namespace std;

struct game_resource
{
	char *name = nullptr;
	mutable int life = 100;
	unsigned *count = nullptr;
};

class Game1
{
	game_resource personage;
	unsigned size = 0;
	
public:	
	//Game1() : personage{}, size(0) //default constructor	//does't working (don't understand)----???
	//{}
	void assign(const char *persname);
	Game1(const char *persname)
	{
		assign(persname);
	}
#if menu1 == 1

#endif
#if menu1 == 2

#endif
#if menu1 == 3
	Game1(const Game1 &newpers) = delete;
	const Game1 &operator=(const Game1 &newpers) = delete;
#endif
	void get_game_res() const
	{
		cout <<"Name = "<< personage.name<< endl;
		cout << "Life = " << personage.life << endl;
		cout << "Count of personages = " << *personage.count << endl;
		cout << "Length of personage name = " << size-1 << endl;
	}

	~Game1()
	{
		--(*personage.count);
		if (personage.name && *personage.count == 0)
		{
			delete[] personage.name;
		}
		personage.name = nullptr;
	}
};
int main()
{
	cout << "MENU:" << endl;
	cout << "1. Ordinary copying" << endl;
	cout << "2. Remouving copying" << endl;
	cout << "3. Prohibition of copying" << endl;
	cout << "4. Exit" << endl;

	int menu1;
	fflush(stdin);
	cin>>menu1;

	if (menu1 > 0 && menu1 < 4)
	{
		Game1 pers1{ "Ivan" };
		pers1.get_game_res();
		Game1 pers2{"Fiodor"};
		pers2.get_game_res();
		
		Game1 pers3 = pers2;
		pers3.get_game_res();
		pers2.get_game_res();

		pers2 = pers1;
		pers2.get_game_res();
		pers1.get_game_res();
	}
	else 
		if (menu1 == 4)
			goto end;
		else
			cout << "Enter 1,2,3 or 4" << endl;
	
	
	end:
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