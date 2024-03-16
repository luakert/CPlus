#include <iostream>

using namespace std;

class Base
{
public:
	Base()
	{
		cout << "Base construct" << endl;
	}

	virtual ~Base()
	{
		cout << "Base deconstruct" << endl;
	}
};

class Derived : public Base
{
public:
	Derived()
	{
		m_string = new char[30];
		cout << "derived construct " << endl;
	}

	~Derived()
	{
		delete[] m_string;
		cout << "derived deconstruct" << endl;
	}
private:
	char* m_string;
};

void test1001()
{
	Base* ptr{ new Derived() };
	delete ptr;
}

class Base1
{
public:
	virtual ~Base1() = default;
	Base1() = default;
	Base1(float f) {}
};

class Base2
{
public:
	virtual ~Base2() = default;
	Base2() = default;
	Base2(float f) {}
};

class Derived2 :public Base1, public Base2
{
public:
	using Base1::Base1;
	using Base2::Base2;
	Derived2(char c);
	Derived2(float f) : Base1(f), Base2(f) {}
};

void test1002()
{
	Derived2 d{ 1.2f };
}


int main()
{
	test1002();
	system("pause");
}



