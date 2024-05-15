#include <vector>
#include <span>
#include <format>
#include <array>
#include <list>
#include <stdexcept>
#include <format>
#include <ranges>
#include <string_view>
#include <iostream>
#include <functional>

import round_robin;
import packet_buffer;

using namespace std;

template<typename T>
void printVector(const vector<T>& vect)
{
	for (const auto& element : vect)
	{
		cout << element << " ";
	}
	cout << endl;
}

void test1801()
{
	//int a = 10;
	//vector ve{ a };
	//ve[0] = 11;
	//cout << format("first ele ={} a={}", *ve.begin(), a) << endl;

	string str1{ "hello" };
	string str2{ "world" };

	vector vec2{ str1, str2 };
	printVector(vec2);
	vector<reference_wrapper<string>> vec{ ref(str1) };
	vec.push_back(ref(str2));

	vec.at(1).get() += "!";
	cout << str1 << " " << str2 << endl;

	printVector(vec2);
}

void test1802()
{
	vector<int> vectone{ 1, 2, 3, 5 };
	vector<int> vecttwo;

	vectone.insert(cbegin(vectone) + 3, 4);
	for (int i = 6; i < 10; i++)
	{
		vecttwo.push_back(i);
	}

	printVector(vectone);
	printVector(vecttwo);

	vectone.insert(cend(vectone), cbegin(vecttwo), cend(vecttwo));
	printVector(vectone);

	vectone.erase(cbegin(vectone) + 1, cbegin(vectone) + 5);
	printVector(vectone);

	vecttwo.clear();
	vecttwo.insert(cbegin(vecttwo), 10, 100);

	vecttwo.pop_back();
	printVector(vecttwo);

	// move vector construction
	vector<string> vecstr;
	string tmp(5, 'a');
//	vector vectthir{ move(tmp) };
	vecstr.push_back(move(tmp));
	cout << tmp << endl;
	cout << vecstr[0] << endl;

	// emplace
	vector<string> vecemplace;
	vecemplace.emplace_back(5, 'b');
	cout << vecemplace.at(0) << endl;
}

vector<int> createVectorofSize(size_t size)
{
	vector<int> vec(size);
	for (int contents = 0; auto& i : vec)
	{
		i = contents++;
	}
	return vec;
}

void test1803()
{
	// support move and move construction
	vector<int> myvect;
	myvect = createVectorofSize(123);
	auto result{ myvect | views::take(10) };
	for (auto& element : result)
	{
		cout << element << " ";
	}
	cout << endl;
}

class Process final
{
public:
	explicit Process(string_view name) :m_name{ move(name) } {};
	void doWorkDuringTimeSlice() {
		cout << "Process " << m_name << " work during time slice" << endl;
	}

	bool operator==(const Process&) const = default;

private:
	string m_name;
};

class Scheduler final
{
public:
	explicit Scheduler(const vector<Process>& process)
	{
		for (auto& pro : process)
		{
			m_processes.add(pro);
		}
	}

	void scheduleTimeSlice()
	{
		try
		{
			m_processes.getNext().doWorkDuringTimeSlice();

		}
		catch (const out_of_range&)
		{
			cerr << " no more process" << endl;
		}
	}

	void removeProcess(const Process& process)
	{
		m_processes.Remove(process);
	}

private:
	RoundRobin<Process> m_processes;
};

void test1804()
{
	vector process{ Process{"1"}, Process{"2"}, Process{"3"} };
	Scheduler sch{ process };
	for (size_t i = 0; i < 4; i++)
	{
		sch.scheduleTimeSlice();
	}

	sch.removeProcess(process[1]);
	cout << " removed second process" << endl;

	for (size_t i = 0; i < 4; i++)
	{
		sch.scheduleTimeSlice();
	}
}

void test1805()
{
	list<string> dict{ "aaa", "bbb" };
	list<string> words{ "chis", "word" };

	dict.push_back("ean");
	dict.push_back("new");

	if (!words.empty())
	{
		// auto listlastwords{ --cend(words) };
		auto listlastwords{ cbegin(words) };
		auto it{ cbegin(dict) };
		for (; it!= cend(dict);++it)
		{
			if (*it > *listlastwords)
			{
				break;
			}
		}

		dict.splice(it, words);
	}

	for (const auto& word : dict)
	{
		cout << word << endl;
	}
}

void printArr(span<const int> values)
{
	for (const auto& value: values)
	{
		cout << value << " ";
	}
	cout << endl;
}

void test1806()
{
	vector v{ 11, 22, 33, 44, 55, 66 };
	printArr(v);

	span mySpan{ v };
	printArr(mySpan);

	span subspan(mySpan.subspan(2, 3));
	printArr(subspan);

	printArr({ v.data() + 2, 3 });

	array<int, 5> arr{ 5, 4, 3, 2, 1 };
	printArr(arr);

	int carr[]{ 9,8, 7,5 };
	printArr(carr);
	printArr({ carr + 2, 2 });
}

class IPPacket final
{
private:
	int m_id;
public:
	explicit IPPacket(int id) :m_id{id}{}

	int getId() { return m_id; }
};

void test1807()
{
	PacketBuffer<IPPacket> ipackets{ 3 };
	for (int i = 0; i < 4; i++)
	{
		if (!ipackets.bufferPacket(IPPacket{i}))
		{
			cout << format("packet {} dropped queue is full", i) << endl;

		}
	}

	while (true)
	{
		try
		{
			IPPacket packet{ ipackets.getNextPacket() };
			cout << "packets id =" << packet.getId() << endl;
		}
		catch (const std::out_of_range&)
		{
			cout << " queue is empty" << endl;
			break;
		}
	}
}

class Error final
{
private:
	int m_priority;
	string m_message;
public:
	Error(int priority, string message): m_priority{priority}, m_message {message}{}
	int getPriority() const { return m_priority; }
	const string& getErrorMessage() const { return m_message; }

	auto operator<=> (const Error& rhs) const
	{
		return getPriority() <=> rhs.getPriority();
	}
};

ostream& operator<<(ostream& os, const Error& err)
{
	os << format("{} priority {}", err.getPriority(), err.getErrorMessage());
	return os;
}

class  ErrorCorrelator final
{
private:
	priority_queue<Error> m_errors;
public:
	void addError(const Error& error) { m_errors.push(error); }
	[[nodiscard]] Error getError()
	{
		if (m_errors.empty())
		{
			throw out_of_range("No more errors");
		}

		Error err{ m_errors.top() };
		m_errors.pop();
		return err;
	}
};

void test1808()
{
	ErrorCorrelator	ec;
	ec.addError(Error{ 3, "unable to read file" });
	ec.addError(Error{ 1, "unable to open file" });
	ec.addError(Error{ 10, "unable to all file" });

	while (true)
	{

		try
		{
			Error e{ ec.getError() };
			cout << e << endl;
		}
		catch (const std::out_of_range&)
		{
			
			cout << "Finish processing errors" << endl;
			break;
		}
	}
}

int main()
{
	test1808();
	system("pause");
}