
#include "stdafx.h"			
#include <cstdlib>
#include <iostream>
using namespace std;


class Rectangle
{
	int sidea;
	int sideb;

public:
	void setparameters();
	void print();
	int set_sidea();
};


int _tmain(int argc, _TCHAR* argv[])
{

	Rectangle obj[4];

	for (int i = 0; i < 4; i++)
	{
		obj[i].setparameters();
		obj[i].print();

	}


	return 0;

}
void Rectangle::setparameters()
{
	static int i = 0;

	sidea = 1 + i;
	sideb = 2 + i;
	i++;

}

void Rectangle::print()
{
	cout << sidea << " * " << sideb << " = " << sidea*sideb << "\n";

}