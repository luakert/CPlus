#include <vector>
#include <format>
#include <ranges>
#include <iostream>
#include <functional>

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

int main()
{
	test1803();
	system("pause");
}