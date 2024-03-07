module database;
import <stdexcept>;

using namespace Records;

namespace Records {
	Employee& DataBase::addEmployee(const std::string& firstName, const std::string& lastName)
	{
		Employee emp{ firstName, lastName };
		emp.setEmployeeNumber(m_nextEmployeeNumber++);
		emp.hire();
		m_employees.push_back(emp);
		return m_employees.back();
	}

	Employee& DataBase::getEmploy(const std::string& firtName, const std::string& lastName)
	{
		for (auto& emp : m_employees)
		{
			if (emp.getFirstName() == firtName && emp.getlastName() == lastName)
			{
				return emp;
			}
		}
		throw std::logic_error{ "No employee Found" };
	}

	Employee& DataBase::getEmployee(int employeeNumber)
	{
		for (auto& emp : m_employees)
		{
			if (emp.getEmployeeNumber() == employeeNumber)
			{
				return emp;
			}
		}
		throw std::logic_error{ "No employee Found" };
	}

	void DataBase::displayAll() const
	{
		for (const auto& emp : m_employees)
		{
			emp.display();
		}
	}

	void DataBase::displayCurrent() const
	{
		for (const auto& emp : m_employees)
		{
			if (emp.isHire())
			{
				emp.display();
			}
		}
	}

	void DataBase::displayFormer() const
	{
		for (const auto& emp : m_employees)
		{
			if (!emp.isHire())
			{
				emp.display();
			}
		}
	}
}