module employee;
import <iostream>;
import <format>;

using namespace std;

namespace Records {
    Employee::Employee(const string& firstName, const string& lastName) :m_firstName{ firstName }, m_lastName{ lastName } {}
    void Employee::promote(int raiseAmount)
    {
        setSalary(getSalary() + raiseAmount);
    }

    void Employee::demote(int der)
    {
        setSalary(getSalary() - der);
    }

    void Employee::hire() { m_hired = true; };
    void Employee::fire() { m_hired = false; };

    const string& Employee::getFirstName() const
    {
        return m_firstName;
    }

    void Employee::setEmployeeNumber(int employeeNumber)
    {
        m_employeeNumber = employeeNumber;
    }

    int Employee::getEmployeeNumber() const
    {
        return m_employeeNumber;
    }

    void Employee::setlastName(const string& lastName)
    {
        m_lastName = lastName;
    }

    const string& Employee::getlastName() const
    {
        return m_lastName;
    }

    bool Employee::isHire() const {
        return m_hired;
    }
    int Employee::getSalary() const
    {
        return m_salary;
    }

        void Employee::setSalary(int salary)
    {
        m_salary = salary;
    }

    void Employee::display() const
    {
        cout << format("Employee: {}, {}", getlastName(), getFirstName()) << endl;
        cout << "-------------------------" << endl;
        cout << (isHire() ? "Current Employee" : "Former Employee") << endl;
        cout << format("Employee Number: {}", getEmployeeNumber()) << endl;
        cout << format("Salary: ${}", getSalary()) << endl;
        cout << endl;
    }
}