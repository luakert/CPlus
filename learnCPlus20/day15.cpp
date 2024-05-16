import mytestarray;

#include <iostream>;
using namespace std;

void printMyArray(const MyArray<int>& myarray)
{
    size_t total = myarray.getSize();
    cout << total << endl;
    for (size_t i = 0; i < total; i++)
    {
        cout << myarray[i] << " ";
    }
    cout << endl;
}

int main15()
{
    MyArray<int> my;
    for (size_t i = 0; i < 10; i++)
    {
        my[i] = 1;
    }

    printMyArray(my);
    system("pause");
    return 0;
}
