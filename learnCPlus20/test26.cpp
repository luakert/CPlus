import ngrid;
import <iostream>;

using namespace std;

int main26()
{
    NDGrid<int, 3> my3DGrid{ 4 };
    my3DGrid[2][1][2] = 5;
    my3DGrid[1][1][1] = 5;
    cout << my3DGrid[2][1][2] << endl;

    system("pause");
    return 0;
}
