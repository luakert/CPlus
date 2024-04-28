#include <iostream>
#include <iterator>
#include <memory>
#include <vector>

using namespace std;

template <typename IteratorType>
void iteratorTraitsTest(IteratorType it)
{
	typename iterator_traits<IteratorType>::value_type temp;
	temp = *it;
	cout << temp << endl;
}


int main()
{
	vector v{ 5 };
	iteratorTraitsTest(cbegin(v));

	system("pause");
}