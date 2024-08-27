import ngrid;
import <iostream>;
import <string>;
import <format>;

using namespace std;

void test2603()
{
    NDGrid<int, 3> my3DGrid{ 4 };
    my3DGrid[2][1][2] = 5;
    my3DGrid[1][1][1] = 5;
    cout << my3DGrid[2][1][2] << endl;
}

template<typename T>
void process(const T& t)
{
    if constexpr (is_integral_v<T>)
    {
        cout << t << " is an integral type " << endl;
    }
    else
    {
        cout << t << " is a non-integral type" << endl;
    }
}

void test2602()
{
    process(123);
    process("Test"s);
}

template<typename T1, typename T2>
void same(const T1& t1, const T2& t2)
{
    bool areTypeTheSame{ is_same_v<T1, T2> };
    cout << format(" '{}' and '{}' are {} types.", t1, t2, (areTypeTheSame ? "the same" : "different")) << endl;
}

void test2604()
{
    same(1, 32);
    same(3.01, "Test"s);
}

class IsDoable
{
public:
    void doit() const { cout << "IsDoable doit()" << endl; }
};

class Derived : public IsDoable{};

template<typename T>
enable_if_t<is_base_of_v<IsDoable, T>, void> callDoit(const T& t)
{
    t.doit();
}

template<typename T>
enable_if_t<!is_base_of_v<IsDoable, T>, void> callDoit(const T&)
{
    cout << "cannot call doit" << endl;
}

template<typename T>
void callDoit2(const T& [[maybe_unused]] t)
{
    if constexpr (is_base_of_v<IsDoable, T>)
    {
        t.doit();
    }
    else
    {
        cout << "can not doit()" << endl;
    }
}

void test2607()
{
    Derived d;
    callDoit(d);
    callDoit(2);

    callDoit2(d);
    callDoit2(1.0);
}

int main2622()
{
    test2607();
    system("pause");
    return 0;
}
