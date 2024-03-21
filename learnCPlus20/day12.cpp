import grid;
import <iostream>;

void test1201()
{
	Grid<int> myIntGrid;
	Grid<double> myDoubleGrid{ 11, 11 };
	myIntGrid.at(0, 0) = 10;
	int x{ myIntGrid.at(0,0).value_or(0) };
	std::cout << x << std::endl;

//	system("pause");
}

void test1202()
{
	Grid2<int, 10, 10> myGrid;
	Grid2<int, 10, 10> anthorGrid;

	myGrid.at(2, 3) = 42;
	anthorGrid = myGrid;
	std::cout << anthorGrid.at(2, 3).value_or(0) << std::endl;
}

int main()
{
	test1202();
	system("pause");
}