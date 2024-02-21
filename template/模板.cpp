#include<iostream>

using namespace std;

template<typename T>
void my_swap(T& a, T& b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

template<class T>
void sorrt_Arr(T arr[])
{
    int len = sizeof(arr) / sizeof(T);
    for (int i = 0; i < len; i++)
    {
        int max = i;
        for (int j = i + 1; j < len; j++)
        {
            if (arr[max] < arr[j])
            {
                max = j;
            }
        }

        if (max != i)
        {
            my_swap(arr[max], arr[i]);
        }
    }

}

template<typename T>
void printA(T arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << arr[i] << " " << end;
    }
    cout << endl;
}

void test1()
{
    int a = 1;
    int b = 2;
    char e ='e';
    double c = 3.0;
    double d = 4.0;
    cout << "交换前a =" << a << " b=" << b << endl;
    my_swap(a, b);
    cout << "交换后a =" << a << " b=" << b << endl;
    my_swap<double>(c, d);

    char charArr[] = "ceadf";
    sorrt_Arr(charArr);
    printA(charArr, 6);
}


void main()
{

    test1();
    system("pause");
    system("exit");
}