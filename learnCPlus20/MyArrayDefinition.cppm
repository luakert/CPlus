module;
#include<cstddef>

export module mytestarray:def;
import <utility>;
import <memory>;
import <stdexcept>;
import <iostream>;
import <format>;
export template<typename T>
class MyArray
{
public:
	MyArray();
	virtual ~MyArray();

	MyArray& operator=(const MyArray& myarray) = delete;
	MyArray(const MyArray& myarray) = delete;

	MyArray(MyArray&& src) noexcept;
	MyArray& operator=(MyArray&& rhs) noexcept;

	T& operator[](size_t x);
	const T& operator[](size_t x) const;

	const T& getElementAt(size_t x) const;

	void setElementAt(size_t x, const T& value);

	size_t getSize() const noexcept;
private:
	static const size_t AllocSize{ 4 };
	void resize(size_t newSize);
	T* m_elements{ nullptr };
	size_t m_size{ 0 };
};
