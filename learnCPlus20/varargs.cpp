import <iostream>;
import <string>;
import <string_view>;
import <tuple>;

using namespace std;

void handleValue(int value) {
    cout << "Integer:" << value << endl;
}

void handleValue(double value) { cout << "Double:" << value << endl; }

void handleValue(string_view value) { cout << "String:" << value << endl; }

void processValues(){}

template<typename T1, typename... Tn>
void processValues(T1 arg1, Tn... args)
{
    handleValue(arg1);
    processValues(args...);
}

void processValuesRValueRefs() {}

template<typename T1, typename...Tn>
void processValuesRValueRefs(T1&& arg1, Tn&&... args)
{
    handleValue(forward<T1>(arg1));
    processValuesRValueRefs(forward<Tn>(args)...);
}

template<unsigned char f>
class Factorial
{
public:
    static const unsigned long long value = (f * Factorial<f - 1>::value);
};

template<>
class Factorial<0>
{
public:
    static const unsigned long long value{ 1 };
};


void test2601()
{
    processValues(1, 2, .13, "test", 1.1f);
    cout << endl;
    processValuesRValueRefs(1, 3.12, 4, "testR", 1.3f);
    cout << Factorial<6>::value << endl;
}

int main2601()
{
    system("pause");
    return 0;
}
