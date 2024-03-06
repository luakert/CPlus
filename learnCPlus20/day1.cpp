// #include <iostream>
#include <utility>
//#include <format>
//#include <string>
import employee;

using namespace Records;
using namespace std;

void test03()
{
	Employee emp("jiang", "ming");
	emp.setEmployeeNumber(111);
	emp.setSalary(123);
	emp.promote();
	emp.promote(50);
	emp.hire();
	emp.display();
}

int main()
{
	// test01();
	test03();
	system("pause");
}