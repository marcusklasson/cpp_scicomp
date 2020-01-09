#include <iostream>
#include <string>

using namespace std;

class Fruit {

private:
	string m_name, m_color;

public:
	Fruit(const string& name, const string& color) : m_name(name), m_color(color) { }

	const string& getName() const { return m_name; }
	const string& getColor() const {return m_color; }
};

class Apple : public Fruit {

protected:
	Apple(const string& name, const string& color) : Fruit(name, color) {}

public:
	Apple( const string& color) : Fruit("apple", color) {}
};

class GrannySmith : public Apple {

public:
	GrannySmith( ) : Apple( "granny smith apple", "green") {}
};

class Banana : public Fruit {

public:
	Banana(const string& name = "banana", const string& color = "yellow") : Fruit(name, color) {}
};


int main()
{
	Apple a{ "red" };
	Banana b;
	GrannySmith c;
 
	std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
	std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
	std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";
	
	return 0;
}