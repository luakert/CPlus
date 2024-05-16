module;
#include <cstddef>
export module round_robin;
import <stdexcept>;
import <iostream>;
import <vector>;

export template<typename T>
class RoundRobin
{
public:
    explicit RoundRobin(size_t numExpected = 0);
    virtual ~RoundRobin() = default;
    RoundRobin(const RoundRobin& serc) = delete;
    RoundRobin& operator=(const RoundRobin& rhs) = delete;

    RoundRobin(RoundRobin&& src) noexcept = default;
    RoundRobin& operator=(RoundRobin&& rhs) noexcept = default;

    void add(const T& elements);

    void Remove(const T& elements);

    T& getNext();

private:
    std::vector<T> m_elements;
    typename std::vector<T>::iterator m_nextElements;
};

template<typename T>
RoundRobin<T>::RoundRobin(size_t num)
{
    m_elements.reserve(num);
    m_nextElements = begin(m_elements);
}

template<typename T>
void RoundRobin<T>::add(const T& element)
{
    ptrdiff_t pos{ m_nextElements - begin(m_elements) };
    std::cout << "pos =" << pos << std::endl;
    m_elements.push_back(element);
    m_nextElements = begin(m_elements) + pos;
}

template<typename T>
void RoundRobin<T>::Remove(const T& element)
{
    for (auto it {begin(m_elements)}; it != end(m_elements); ++it)
    {
        if (*it == element)
        {
            ptrdiff_t newpos;

            if (m_nextElements == end(m_elements) - 1 && m_nextElements == it)
            {
                newpos = 0;
            }
            else if (m_nextElements <= it)
            {
                newpos = m_nextElements - begin(m_elements);
            }
            else {
                newpos = m_nextElements - begin(m_elements) - 1;
            }

            m_elements.erase(it);
            m_nextElements = begin(m_elements) + newpos;

            return;
        }

    }
}

template<typename T>
T& RoundRobin<T>::getNext()
{
    if (m_elements.empty())
    {
        throw std::out_of_range("No elements in the first");
    }

    auto& toReturn{ *m_nextElements };
    ++m_nextElements;
    if (m_nextElements == end(m_elements))
    {
        m_nextElements = begin(m_elements);
    }

    return toReturn;
}
