import <iostream>;
import <string>;
import <tuple>;
import <utility>;

using namespace std;

template <typename TupleType, int n>
class TuplePrintHelper
{
public:
    TuplePrintHelper(const TupleType& t) {
        TuplePrintHelper<TupleType, n - 1> tp{ t };
        cout << get<n - 1>(t) << endl;
    }
};

template <typename TupleType>
class TuplePrintHelper<TupleType, 0>
{
public:
    TuplePrintHelper(const TupleType&) { }
};

template <typename T>
void tuplePrint(const T& t)
{
    TuplePrintHelper<T, tuple_size<T>::value> tph{ t };
}

int main2611()
{
    //tuple t1{ 167, "Testing"s, true};
    // tuplePrint(t1);
    system("pause");
    return 0;
}
