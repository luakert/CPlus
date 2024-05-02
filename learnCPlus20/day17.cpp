#include <iostream>
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

int main()
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
	system("pause");
}