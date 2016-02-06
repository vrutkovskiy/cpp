//2. Создать класс Triangle для представления треугольника.Поля данных являются сторонами треугольника.
//Определить подходящие исключения.Должны быть реализованы операции получения и изменения полей данных, вычисления площади, вычисления периметра, вычисления высот, вычисления углов,
//определения вида треугольника(равносторонний, равнобедренный, прямоугольный).
//В случае возникновения ошибок методы должны генерировать исключения.

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

class Triangle
{
	double a = 0;
	double b = 0;
	double c = 0;
public:
	Triangle() = default;
	Triangle(const double& usera, const double& userb, const double& userc) :
		a(usera), b(userb), c(userc)
	{}

	Triangle(const Triangle& obj) : a(obj.a), b(obj.b), c(obj.c)
	{}
	const Triangle& operator=(const Triangle& obj)
	{
		a = obj.a;
		b = obj.b; 
		c = obj.c;
	}

	~Triangle() = default;

	class Donotexist		//exeption1
	{};
	class Zero				//exeption2
	{};
	class Wronginput		//exeption3
	{};

	void show_sides() const
	{
		cout << "a = " << a << " " 
			<< "b = " << b << " " 
			<<"c = " << c << endl;
	}
	
	const double& get_sidea() const
	{
		return a;
	}
	const double& get_sideb() const
	{
		return b;
	}
	const double& get_sidec() const
	{
		return c;
	}

	void set_sides(const double& usera, const double& userb, const double& userc)
	{
		a = usera;
		b = userb;
		c = userc;
	}

	double perimeter() const
	{
		return a + b + c;
	}

	double square() const
	{
		double p, s;
		p = perimeter()/2;
		s = sqrt(p*(p-a)*(p-b)*(p-c));
		return s;
	}

	void get_hights() const
	{
		double s = square();
		cout << setprecision(3) << "h1 = " << 2 * s / a << " "
			<< "h2 = " << 2 * s / b << " "
			<< "h3 = " << 2 * s / c << endl;
	}

	void get_kind() const
	{
		if (a == b && a == c)
			cout << "Equilateral triangle" << endl;
		else 
			if (a == b || b == c || a == c)
				cout << "Isosceles triangle" << endl;
				else
					cout << "Regular triangle" << endl;
	}
	// сравнение чисел с плавающей точкой (один из вариантов). нужно разбираться.
	/*bool areEqual(double x, double y)
	{
		static double SMALL_NUM = 1.0E-5;
		if (fabs(x) < SMALL_NUM && fabs(y) < SMALL_NUM)
			return fabs(x - y) < SMALL_NUM;
		else
			return fabs(x - y) < fabs(x) * SMALL_NUM;
	}*/
	void get_angles() const
	{
		int angle1, angle2, angle3;
		// потеря точности
		angle1 = static_cast<int>(acos((pow(b, 2) + pow(c, 2) - pow(a, 2)) / (2 * b * c)) * 180 / 3.14);
		angle2 = static_cast<int>(acos((pow(a, 2) + pow(c, 2) - pow(b, 2)) / (2 * a * c)) * 180 / 3.14);
		angle3 = static_cast<int>(acos((pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * a * b)) * 180 / 3.14);
		cout << "Angle1 = " << angle1 << " "
			<< "Angle2 = " << angle2 << " "
			<< "Angle3 = " << angle3 << endl;
		if (angle1 == 90 || angle2 == 90 || angle3 == 90)
			cout << "Rectangular triangle" << endl;
	}
};

ostream& operator<<(ostream& os, const Triangle& obj)
{
	return os << obj.get_sidea() << obj.get_sideb() << obj.get_sidec();
}

int main()
{
	double a;
	double b;
	double c;
	char choice = 'n';
		
	try
	{
		Triangle tr1(5, 7, 7);
		cout << tr1 << endl;

		do{
			cout << "Enter three sides of the triangle : " << endl;
			if(!(cin >> a >> b >> c))
				throw Triangle::Wronginput();
			if (a <= 0 || b <= 0 || c <= 0)
				throw Triangle::Zero();
			if (((a + b) <= c) || ((a + c) <= b) || ((b + c) <= a))
				throw Triangle::Donotexist();
			
			tr1.set_sides(a, b, c);
			tr1.show_sides();
			cout << "PERIMETER = " << tr1.perimeter() << endl;
			cout << "SQUARE = " << setprecision(4) << tr1.square() << endl;
			cout << "HIGHTS : ";
			tr1.get_hights();
			tr1.get_kind();
			tr1.get_angles();

			cout << "\nEXIT y/n" << endl;
			cin >> choice;
		} while (choice != 'y');
	}
	catch (Triangle::Wronginput&)
	{
		cout << "You cannot enter letters" << endl;
	}
	catch (Triangle::Zero&)
	{
		cout << "Sides cannot be less or equal to 0" << endl;
	}
	catch (Triangle::Donotexist&)
	{
		cout << "You cannot build a triangle whith this sides" << endl;
	}
	catch (...)
	{
		cout << "Unexpected error" << endl;
	}

	return 0;
}