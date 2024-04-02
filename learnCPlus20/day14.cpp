#include <iostream>
#include <filesystem>
#include <fstream>
#include <ostream>
#include <vector>
#include <stdexcept>

using namespace std;
using namespace std::filesystem;

vector<int> readIntegerFile(string_view fileName)
{
	ifstream inputstream{ fileName.data() };
	if (inputstream.fail())
	{
		throw invalid_argument{ "unable to open the file" };
	}

	vector<int> ints;
	int temp;
	while (inputstream >> temp)
	{
		ints.push_back(temp);
	}

	if (!inputstream.eof())
	{
		throw runtime_error{ " Error reading the files" };
	}

	return ints;
}

void test1401()
{
	path pth{ current_path() };
	pth /= "day14.tt";

	try
	{
		vector<int> result = readIntegerFile(pth.string());
		for (const auto& value : result)
		{
			cout << value << " ";
		}
		cout << endl;

	}
	catch (const invalid_argument& e)
	{
		cout << " open file fail " << e.what() << endl;
	}
	catch (const runtime_error& e)
	{
		cout << " read file error " << e.what() << endl;
	}
	catch (...)
	{
		cout << " occur other error " << endl;
	}
}

int main()
{
	test1401();
	system("pause");
}

