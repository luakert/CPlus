#include <time.h>
#include <cstdio>
import <iostream>;
import <sstream>;
import <iomanip>;
import <fstream>;
import <locale>;
import <format>;

using namespace std;
void test1301()
{
	bool mybool{ true };
	std::cout << "this should be ture " << boolalpha << mybool << endl;
	
	cout.imbue(locale{ "" });
	double db1{ 3.1415 };
	double db2{6};
	std::cout << "this should be '5'" << setw(2) << noshowpoint << db2 << endl;
	std::cout << "this should be '5'" << setw(7) << db2 << endl;

	std::cout << "mokey is :" << put_money("120000") << endl;

	time_t t{ time(nullptr) };
	tm nowTime;
	localtime_s(&nowTime, &t);
	cout << "current time:" << put_time(&nowTime, "%c") << endl;
}

void test1302()
{
	string userInput;
	cin >> userInput;
	cout << format("intput is {}", userInput);
}

string readName(istream& stream)
{
	string name;
	char next;
	while (stream.get(next))
	{
		name += next;
	}
	return name;
}

void getReservationData()
{
	string questname;
	int partysize{ 0 };
	char ch;
	cin >> noskipws;
	while (cin>>ch)
	{
		if (isdigit(ch))
		{
			cin.unget();
			if (cin.fail())
			{
				cout << "unget() failed " << endl;
			}
			break;
		}
		questname += ch;
	}

	if (cin)
	{
		cin >> partysize;
	}

	if (!cin)
	{
		cerr << "Error getting partsize" << endl;
	}

	cout << format("Thank you '{}' party of {}", questname, partysize) << endl;
	if (partysize > 10)
	{
		cout << "An extra  will apply" << endl;
	}
}

class Muffin
{
public:
	Muffin(const string& name, int size): m_name {move(name)}, m_size(size) {}
	virtual ~Muffin() = default;

	friend ostream& operator<<(ostream& ostr, const Muffin& mu);

private:
	string m_name;
	int m_size{ 0 };

};

class Muffin3
{
public:
	Muffin3(const string& name, int size): m_name {move(name)}, m_size(size) {}
	virtual ~Muffin3() = default;

	friend ostream& operator<<(ostream& ostr, const Muffin3& mu);

private:
	string m_name;
	int m_size{ 0 };

};
ostream& operator<<(ostream& ostr, const Muffin& mu)
{
	// TODO: 在此处插入 return 语句
	ostr << "name:" << mu.m_name << " size:" << mu.m_size;
	return ostr;
}

ostream& operator<<(ostream& ostr, const Muffin3& mu)
{
	// TODO: 在此处插入 return 语句
	ostr << "name:" << mu.m_name << " size:" << mu.m_size;
	return ostr;
}

void test1303()
{
	string questtime;
	int partsize{ 0 };
	cin >> noskipws;
	while (true)
	{
		char ch { static_cast<char>(cin.peek()) };
		if (!cin)
		{
			break;
		}
		
		if (isdigit(ch))
		{
			break;
		}

		cin >> ch;
		if (!cin)
		{
			break;
		}
		questtime += ch;
	}

	if (cin)
	{
		cin >> partsize;
	}

	if (!cin)
	{
		cerr << "Error  getting part size " << endl;
		return;
	}

	cout << format("Thank you '{}' party of {}", questtime, partsize) << endl;
	if (partsize > 10)
	{
		cout << "An extra  will apply" << endl;
	}
}

void test1304()
{
	Muffin mu{ "james", 12 };
	cout << mu << endl;
	Muffin3 mu3{ "ovil", 23 };
	cout << mu3 << endl;
}

void test1305()
{
	ostringstream outStream;
	while (cin)
	{
		string nextToken;
		cout << "next token:";
		cin >> nextToken;
		if (!cin || nextToken == "done")
		{
			break;
		}
		outStream << nextToken << "\t";
	}

	cout << "The End result is " << outStream.str();

}

int test1306()
{
	ofstream fout{ "test.txt" };
	if (!fout)
	{
		cerr << "Error opening test.out for writing" << endl;
		return -1;
	}

	fout << "54321";
	streampos curPos{ fout.tellp() };
	if (curPos ==5)
	{
		cout << "test passed currently at position 5" << endl;
	} else {
		cout << "Test failed Not at position 5" << endl;
	}

	fout.seekp(2, ios_base::beg);
	fout << 0;
	fout.close();

	ifstream fin{ "test.txt" };
	if (!fin)
	{
		cerr << "Error reading form file open " << endl;
		return -1;
	}

	int testValue;
	fin >> testValue;
	if (fin.fail())
	{
		cerr << "Error reading value from file" << endl;
		return -1;
	}

	const int exceptedValue{ 54021 };
	if (exceptedValue == testValue)
	{
		cout << format("{} is equal {}", testValue, exceptedValue);
	}
	else
	{
		cout << "test is fail" << endl;
		return -1;
	}

	return 0;

}

int main()
{
	//test1302();
	test1306();
	//getReservationData();
	system("pause");
}

