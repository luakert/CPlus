#include <iostream>
#include <set>
#include <ranges>
#include <algorithm>
#include <iterator>
#include <memory>
#include <vector>
#include <format>


using namespace std;

template <typename IteratorType>
void iteratorTraitsTest(IteratorType it)
{
	typename iterator_traits<IteratorType>::value_type temp;
	temp = *it;
	cout << temp << endl;
}

template<typename Iter>
void myPrint(Iter begin, Iter end)
{
	for (auto iter{ begin }; iter != end; ++iter)
	{
		cout << *iter << " ";
	}
	cout << endl;
}

template<typename Iter>
auto myFind(Iter begin, Iter end, const typename iterator_traits<Iter>::value_type& value)
{
	for (auto iter{ begin }; iter != end; ++iter)
	{
		if (*iter == value)
		{
			return iter;
		}
	}

	return end;
}

template<typename InputIter, typename OutputIter>
void myCopy(InputIter begin, InputIter end, OutputIter target)
{
	for (auto iter{begin}; iter != end; ++iter, ++target)
	{
		*target = *iter;
	}
}

template<typename InputerIter>
auto sum(InputerIter begin, InputerIter end)
{
	auto sum{ *begin };
	for (auto iter = begin; iter != end; ++iter)
	{
		sum += *iter;
	}
	return sum;
}

void test1701()
{
	vector vector1{ 1, 2, 3, 4,5 };
	vector<int> vector2;
	back_insert_iterator<vector<int>> inserter{ vector2 };
	myCopy(cbegin(vector1), cend(vector1), inserter);
	myCopy(cbegin(vector1), cend(vector1), back_inserter(vector2));

	myCopy(cbegin(vector2), cend(vector2), ostream_iterator<int>{cout, " "});
}

void test1702()
{
	vector v{ 5 };
	iteratorTraitsTest(cbegin(v));

	vector v2{ 1, 2, 4,5,6,8 };
	myPrint(cbegin(v2), cend(v2));

	vector v3{ 11, 22, 33 };
	auto result{ myFind(cbegin(v3), cend(v3), 33) };
	if (result != cend(v3))
	{
		cout << format("Found values at postition {}", distance(cbegin(v3), result));
	}
	cout << endl;
	vector resourceVector{ 11, 23, 43, 564, 233 };
	vector<int> destVector(resourceVector.size());
	myCopy(cbegin(resourceVector), cend(resourceVector), begin(destVector));
	myCopy(cbegin(resourceVector), cend(resourceVector), ostream_iterator<int>{cout, " "});
	cout << endl;
	myCopy(cbegin(destVector), cend(destVector), ostream_iterator<int>{cout, " "});
	cout << endl;

}

void test1703()
{
	vector vectorone{ 1, 2, 3,4,5 };
	set<int> setone;

	insert_iterator<set<int>> insertIter{ setone, begin(setone) };
	myCopy(cbegin(vectorone), cend(vectorone), insertIter);
	myCopy(cbegin(vectorone), cend(vectorone), inserter(setone, begin(setone)));

	myCopy(cbegin(setone), cend(setone), ostream_iterator<int> {cout, " "});
	cout << endl;
	myCopy(cbegin(vectorone), cend(vectorone), insert_iterator{ setone, end(setone) });
	myCopy(cbegin(setone), cend(setone), ostream_iterator<int> {cout, " "});
	cout << endl;
}

void test1704()
{
	vector data{ 22, 11, 4, 45 };
	std::ranges::sort(data);
	myCopy(cbegin(data), cend(data), ostream_iterator<int>{cout, " "});
	cout << endl;
}

class PersonTest
{
public:
	PersonTest(string first, string last): m_firstname{move(first)}, m_lastname {move(last)} {}
	const string& getFirstName() const { return m_firstname; }
	const string& getLastName() const { return m_lastname; }
private:
	string m_firstname;
	string m_lastname;
};

void test1705()
{
	vector persons{ PersonTest {"zavid", "jax"}, PersonTest{"john", "steve"} };
	std:; ranges::sort(persons, {}, &PersonTest::getFirstName);
	// myPrint(cbegin(persons), cend(persons));
	for (auto iter = cbegin(persons); iter != cend(persons); ++iter)
	{
		cout << format("firstname:{}", iter->getFirstName()) << endl;
	}

	for (const auto& person : persons)
	{
		cout << format("firstname:{}", person.getFirstName()) << endl;
	}
}

void printRange(string_view message, auto& range)
{
	cout << message;
	for (const auto& value : range)
	{
		cout << value << " ";
	}
	cout << endl;
}

void test1706()
{
	vector values{ 1, 2, 3,4, 5,6,7,8 };
	printRange("origianl sequence:", values);

	auto result1{ values | views::filter([](const auto& value) {return value % 2 == 0; }) };
	printRange("only even values:", result1);

	auto result2{ result1 | views::transform([](const auto& value) {return value * 2.0; }) };
	printRange("values double:", result2);

	auto result3{ result2 | views::drop(2) };
	printRange("First two drop", result3);

	auto result4{ result3 | views::reverse };
	printRange("sequence reversed", result4);

	auto result5{ ranges::filter_view{values, [](const auto& value) {return value % 2 == 1; }} };
	printRange("constructtion: ", result5);


	vector values2 { 1, 2, 3,4, 5,6,7,8 };
	auto result6{ values2
					| views::filter([](const auto& value) {return value % 2 == 0; })
					| views::drop(2)
					| views::reverse };
	for (auto& value : result6)
	{
		value *= 10;
	}
	printRange("after modfiy: ", values2);
}

void test1707()
{
	for (auto value : ranges::istream_view<int>(cin)
		| views::take_while([](const auto& v) {return v < 5; })
		| views::transform([](const auto& v) {return v * 2; })
		)
	{
		cout << format(">{}\n", value);
	}
	cout << "Terminating..." << endl;
}

int main()
{
	test1707();

	system("pause");
}