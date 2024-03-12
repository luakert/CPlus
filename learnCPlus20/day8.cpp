#include <vector>
#include <initializer_list>
#include <stdexcept>
#include <iostream>

class EventBus
{
public:
	EventBus(std::initializer_list<double> args)
	{
		if (args.size() % 2 != 0)
		{
			throw std::invalid_argument{ "initializer should " };
		}

		m_sequence.reserve(args.size());
		//for (const auto& value : args)
		//{
		//	m_sequence.push_back(value);
		//}
		m_sequence.assign(args);
	}

	void dump() const
	{
		for (const auto& value : m_sequence)
		{
			std::cout << value << ",";
		}
		std::cout << std::endl;
	}

private:
	std::vector<double> m_sequence;
};
