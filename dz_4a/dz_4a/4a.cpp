//1. Создать абстрактный базовый класс Figure с виртуальными методами вычисления площади и периметра.
//Создать производные классы : Rectangle(прямоугольник), Circle(круг), Trapezium(трапеция) со своими функциями площади и периметра.
//Площадь трапеции S = (а + b) h / 2.
//Площадь круга S = R^2.

#include <iostream>
using namespace std;

class IFigure
{
	double a = 0;
	double b = 0;
public:
	IFigure()
	{}
	IFigure(const double& usera, const double& userb) : a(usera), b(userb)
	{}

	IFigure(const IFigure& obj) = delete;
	const IFigure& operator=(const IFigure& obj) = delete;
	
	virtual double square() = 0;
	
	virtual double perimeter() = 0;
	
	virtual ~IFigure()=0
	{
		cout << "~IFigure()" << endl;
	}
};

class Rectangle : public IFigure
{
	double a = 0;
	double b = 0;
public:
	Rectangle()
	{}
	Rectangle(const double& usera, const double& userb) : a(usera), b(userb)
	{}

	Rectangle(const Rectangle& obj) = delete;
	const Rectangle& operator=(const Rectangle& obj) = delete;

	double square() override
	{
		return a*b;
	}
	double perimeter() override
	{
		return 2*(a+b);
	}

	void getsides()
	{
		cout << "a = " << a <<" "<< "b = " << b << endl;
	}
	
	~Rectangle()
	{
		cout << "~Rectangle()" << endl;
	}
};

class Circle : public IFigure
{
	double r;
	const double pi = 3.14;
public:
	Circle()
	{}
	Circle(const double& userr) : r(userr)
	{}

	Circle(const Circle& obj) = delete;
	const Circle& operator=(const Circle& obj) = delete;

	double square() override
	{
		return r * r;
	}
	double perimeter() override
	{
		return 2 * pi * r;
	}

	void getradius()
	{
		cout << "r = " << r << endl;
	}

	~Circle()
	{
		cout << "~Circle()" << endl;
	}
};

class Trapezium : public IFigure
{
	double a = 0;
	double b = 0;
	double c = 0;
	double d = 0;
	double h = 0;
public:
	Trapezium()
	{}
	Trapezium(const double& usera, const double& userb, const double& userc,\
		const double& userd, const double& userh) :
		a(usera), b(userb), c(userc), d(userd), h(userh)
	{}

	Trapezium(const Trapezium& obj) = delete;
	const Trapezium& operator=(const Trapezium& obj) = delete;

	double square() override
	{
		return (a + b)* h / 2;
	}
	double perimeter() override
	{
		return (a + b + c + d);
	}

	void getsides()
	{
		cout << "a = " << a << " " << "b = " << b << " " 
			<<"c = "<< c << " " << "d = " << d << " " << "h = " << h <<endl;
	}

	~Trapezium()
	{
		cout << "~Trapezium()" << endl;
	}
};

int main()
{
	cout << "RECTANGLE" << endl;
	Rectangle rc1(5,4);
	rc1.getsides();
	cout << "Perimeter = " <<rc1.perimeter() << " " << "Square = " <<rc1.square() << endl;

	cout << endl << "CIRCLE" << endl;
	Circle cr1(14);
	cr1.getradius();
	cout << "Perimeter = " << cr1.perimeter() << " " << "Square = " << cr1.square() << endl;

	cout << endl << "TRAPEZIUM" << endl;
	Trapezium tr1(12, 17, 5, 6, 6);
	tr1.getsides();
	cout << "Perimeter = " << tr1.perimeter() << " " << "Square = " << tr1.square() << endl;
	
	return 0;
}