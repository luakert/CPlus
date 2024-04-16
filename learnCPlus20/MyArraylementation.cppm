module;
#include <cstddef>
export module mytestarray:imp;

import :def;
import <utility>;
import <memory>;
import <stdexcept>;
import <iostream>;
import <format>;
export template<typename T>
MyArray<T>::MyArray()
{
	m_size = AllocSize;
	m_elements = new T[m_size]{};
}

export template<typename T>
MyArray<T>::~MyArray()
{
	delete[] m_elements;
	m_elements = nullptr;
}

export template<typename T>
MyArray<T>::MyArray(MyArray&& src) noexcept
	: m_elements {std::exchange(src.m_elements, nullptr)}
	, m_size {std::exchange(src.m_size, 0)} {}

export template<typename T>
MyArray<T>& MyArray<T>::operator=(MyArray&& rhs) noexcept
{
	if (this == &rhs)
	{
		return *this;
	}

	delete[] m_elements;
	m_elements = std::exchange(rhs.m_elements, nullptr);
	m_size = std::exchange(rhs.m_size, 0);
	return *this;
}

export template<typename T>
void MyArray<T>::resize(size_t newSize)
{
	auto newArray{ std::make_unique<T[]>(newSize) };
	for (size_t i = 0; i < m_size; i++)
	{
		newArray[i] = m_elements[i];
	}

	delete[] m_elements;
	m_size = newSize;
	m_elements = newArray.release();
}


export template<typename T>
void MyArray<T>::setElementAt(size_t x, const T& val)
{
	if (x >= m_size)
	{
		resize(x + AllocSize);
	}

	m_elements[x] = val;
}


export template<typename T>
T& MyArray<T>::operator[](size_t x)
{
	// TODO: 在此处插入 return 语句
	//std::cout << std::format("call no-const function") << std::endl;
	if (x >= m_size)
	{
		resize(x + AllocSize);
	}
	return m_elements[x];
}

export template<typename T>
const T& MyArray<T>::operator[](size_t x) const
{
	// TODO: 在此处插入 return 语句
//	std::cout << std::format("call const function") << std::endl;
	if (x >= m_size)
	{
		throw std::out_of_range{ "" };
	}
	return m_elements[x];
}

//export template<typename T>
//const T& MyArray<T>::operator[](size_t) const
//{
//	// TODO: 在此处插入 return 语句
//	std::cout << format("call const function") << std::endl;
//	if (x >= m_size)
//	{
//		static T nullValue{ T() };
//		return nullValue;
//	}
//	return m_elements[x];
//}


export template<typename T>
const T& MyArray<T>::getElementAt(size_t x) const
{
	if (x >= m_size)
	{
		throw std::out_of_range{ "" };
	}
	return m_elements[x];
}

export template<typename T>
size_t MyArray<T>::getSize() const noexcept
{
	return m_size;
}
