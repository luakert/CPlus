module;

#include <cstddef>

export module ngrid;

import <vector>;

export template<typename T, size_t N>
class NDGrid
{
public:
    explicit NDGrid(size_t size = DefaultSize) { resize(size); }
    virtual ~NDGrid() = default;

    NDGrid<T, N - 1>& operator[](size_t index) { return m_elements[index]; }
    const NDGrid<T, N - 1>& operator[](size_t index) const { return m_elements[index]; }
    void resize(size_t newSize)
    {
        m_elements.resize(newSize);
        for (auto& element : m_elements)
        {
            element.resize(newSize);
        }
    }

    size_t getSize() const { return m_elements.size(); }
    static const size_t DefaultSize{ 10 };

private:
    std::vector<NDGrid<T, N - 1>> m_elements;
};

export template <typename T>
class NDGrid<T, 1>
{
public:
    explicit NDGrid(size_t size = DefaultSize) { resize(size); }
    virtual ~NDGrid() = default;

    T& operator[](size_t index) { return m_elements[index]; }
    const T& operator[](size_t index) const { return m_elements[index]; }

    void resize(size_t newSize)
    {
        m_elements.resize(newSize);
    }

    size_t getSize() const { return m_elements.getSize(); }

    static const size_t DefaultSize{ 10 };
private:
    std::vector<T> m_elements;
};
