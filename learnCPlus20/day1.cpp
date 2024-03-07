// #include <iostream>
#include <utility>
//#include <format>
//#include <string>
import <iostream>;
import <stdexcept>;
import <exception>;
import <format>;
import <string>;
import database;
import employee;


using namespace Records;
using namespace std;

int displayMenu();
void doHire(DataBase& db);
void doFire(DataBase& db);
void doPromote(DataBase& db);

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

void test04()
{
	DataBase employeeDB;
	bool done{ false };
	while (!done)
	{
		int selection{ displayMenu() };
		switch (selection) {
		case 0:
			done = true;
			break;
		case 1:
			doHire(employeeDB);
			break;
		case 2:
			doFire(employeeDB);
			break;
		case 3:
			doPromote(employeeDB);
			break;
		case 4:
			employeeDB.displayAll();
			break;
		case 5:
			employeeDB.displayCurrent();
			break;
		case 6:
			employeeDB.displayFormer();
			break;
		default:
			cerr << "unknow command" << endl;
			break;
		}
	}
}

int displayMenu()
{
	// Note:
	//		One important note is that this code assumes that the user will
	//		"play nice" and type a number when a number is requested.
	//		When you read about I/O in Chapter 13, you will learn how to
	//		protect against bad input.

	int selection;
	cout << endl;
	cout << "Employee Database" << endl;
	cout << "-----------------" << endl;
	cout << "1) Hire a new employee" << endl;
	cout << "2) Fire an employee" << endl;
	cout << "3) Promote an employee" << endl;
	cout << "4) List all employees" << endl;
	cout << "5) List all current employees" << endl;
	cout << "6) List all former employees" << endl;
	cout << "0) Quit" << endl;
	cout << endl;
	cout << "---> ";
	cin >> selection;
	return selection;
}

void doHire(DataBase& db)
{
	string firstName;
	string lastName;

	cout << "Firt Name ";
	cin >> firstName;

	cout << "last Name";
	cin >> lastName;

	auto& emp{ db.addEmployee(firstName, lastName) };
	emp.hire();
	cout << format("Hired employee {} {} with employee number {}", firstName, lastName, emp.getEmployeeNumber()) << endl;
}

void doFire(DataBase& db)
{
	int employeeNumber;
	cout << "Employee number";
	cin >> employeeNumber;

	try
	{
		auto& emp = db.getEmployee(employeeNumber);
		emp.fire();
		cout << format("Employee {} terminated. ", employeeNumber) << endl;
	}
	catch (const std::logic_error& e)
	{
		cerr << format("unable to termin emp {]", e.what()) << endl;
	}
}

void doPromote(DataBase& db)
{
	int employeeNumber;
	int raiseAmount;

	cout << "Employee number? ";
	cin >> employeeNumber;

	cout << "How much of a raise? ";
	cin >> raiseAmount;

	try {
		Employee& emp = db.getEmployee(employeeNumber);
		emp.promote(raiseAmount);
	}
	catch (const std::logic_error& exception) {
		cerr << "Unable to promote employee: " << exception.what() << endl;
	}
}



int main()
{
	// test01();
	//test03();
	test04();
	system("pause");
}