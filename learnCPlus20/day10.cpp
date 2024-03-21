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

class Base3
{
public:
	virtual ~Base3() = default;
	Base3() = default;
	Base3(const Base3& src){}
};

class Derived3 :public Base3
{
public:
	Derived3() = default;
	//使用基类的拷贝构造函数
	Derived3(const Derived3& src) : Base3{src}{}
	Derived3& operator=(const Derived3& src);
};

Derived3& Derived3::operator=(const Derived3& rhs) 
{
	if (&rhs == this) { return *this; }
	// 需要调用父类版本的operator=
	Base3::operator=(rhs);
	return *this;
}

class Loggable10
{
public:
	virtual ~Loggable10() = default;
	virtual std::string getLogMessage() const = 0;
};

class Foo : public Loggable10
{
public:
	std::string getLogMessage() const override { return "Hello world"; }
};

void logObject(const Loggable10& logObject)
{
	cout << typeid(logObject).name() << ":";
	cout << logObject.getLogMessage() << endl;
}

void test1002()
{
	Derived2 d{ 1.2f };
}

void test1003()
{
	Foo fo;
	logObject(fo);
}

int main10()
{
	test1003();
	system("pause");
	return 0;
}



