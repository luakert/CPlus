export module employee;
import <string>;

namespace Records {
    const int DefaultStartingSalary{ 30'000 };
    export const int DefaultRaiseAndDemeritAmount{ 1'000 };


    export class Employee
    {
    public:
        Employee(const std::string& fileName, const std::string& lastName);

        void promote(int raiseAmount = DefaultRaiseAndDemeritAmount);
        void demote(int demr = DefaultRaiseAndDemeritAmount);
        void hire();
        void fire();
        void display() const;

        void setFirstName(const std::string& firtName);
        const std::string& getFirstName() const;

        void setlastName(const std::string& lastName);
        const std::string& getlastName() const;

        void setEmployeeNumber(int employeeNumber);
        int getEmployeeNumber() const;

        void setSalary(int newSalary);
        int getSalary() const;

        bool isHire() const;
    private:
        std::string m_firstName;
        std::string m_lastName;
        int m_employeeNumber{ -1 };
        int m_salary{ DefaultStartingSalary };
        bool m_hired{ false };
    };
}