import grid;
import <iostream>;
import <concepts>;

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

template<typename Retype = long long, typename T1, typename T2>
Retype add(const T1& t1, const T2& t2) { return t1 + t2; }

void test1203()
{
	auto result{ add(1, 2) };
	std::cout << std::format("result is {} and type is {}", result, typeid(result).raw_name()) << std::endl;
}

const std::string message{ "Test" };
const std::string& getString() { return message; }

void test1204()
{
	auto s1{ getString() };
	std::cout << std::format("result is {} and type is {} stirng&  {} is const", s1, std::is_same<decltype(s1), std::string&>::value, std::is_const<decltype(s1)>::value) << std::endl;

	const auto& s2{ getString() };
	std::cout << std::format("result is {} and type is {} string&, {} is const", s2, std::is_same<decltype(s2), std::string&>::value, std::is_const<decltype(s2)>::value) << std::endl;

	// 太繁琐 decltype(getString()) s3{ getString() };
	decltype(auto) s4{ getString() };
	std::cout << std::format("result is {} and type is {} string& {} is const", s4, std::is_same<decltype(s4), std::string&>::value, std::is_const<decltype(message)>::value) << std::endl;
}

template<typename T>
concept Incrementable = requires(T x) { ++x; x++;};
void testconcept(){}

template<typename T>
// concept c = requires {typename T::value_type; };
// concept b = requires (const T x) { { x.size() }->std::convertible_to<size_t>; };
// concept f = requires(const T a, const T b)
// {
// 	{ a < b }->std::convertible_to<bool>;
// };
concept e = requires (T t) {
	requires sizeof(T) == 4;
	t++; t--; ++t; --t;
};
void testconcept2(){}

template <typename T>
// concept IsDerivedFromFoo = std::derived_from<T, Grid<T>>;
concept IsConvertibleToBool = std::convertible_to<T, bool>;
void testconcept3(){}

// 函数模板使用类型约束有几种不同的语法方式
// 第一种不使用typename而是使用类型约束
template<std::convertible_to<bool> T>
void handle(const T& t);

// 第二种使用requires子句
template<typename T> requires IsConvertibleToBool<T>
void processTest(const T& t){}

template<typename T> requires std::convertible_to<T, bool> 
void processTest2(const T& t){}
// 可以在函数头之后指定requires子句
template<typename T> 
void processTest(const T& t) requires std::default_initializable<T>&& std::copy_constructible<T>;

// 模板函数
void process3(const IsConvertibleToBool auto& v);

template<typename T>
size_t Find(const T& value, const T* arr, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		if (arr[i] == value)
		{
			return i;
		}

	}
	return -1;
}

template<std::floating_point T>
size_t Find(const T& value, const T* arr, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		if (AreEqe(arr[i], value))
		{
			return i;
		}

	}
	return -1;
}

template<std::floating_point T>
bool AreEqe(T x, T y, int precision = 2)
{
	return fabs(x - y) <= std::numeric_limits<T>::epsilon() * fabs(x + y) * precision ||
		fabs(x - y) < std::numeric_limits<T>::min();
}

int main()
{
	test1204();
	system("pause");
}