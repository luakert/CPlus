module;

export module grid;
import <vector>;
import <optional>;
import <cstddef>;
import <stdexcept>;
import <format>;
import <utility>;

export template<typename T>
class Grid
{
public:
	explicit Grid(size_t width = DefaultWidth, size_t height = DefaultHeight);
	virtual ~Grid() = default;

	Grid(const Grid& src) = default;
	Grid& operator=(const Grid& rhs) = default;

	Grid(Grid&& src) = default;
	Grid& operator=(Grid&& rhs) = default;

	std::optional<T>& at(size_t x, size_t y);
	const std::optional<T>& at(size_t x, size_t y) const;

	size_t getHeight() const { return m_height; }
	size_t getWidth() const { return m_width; }

	static const size_t DefaultWidth{ 10 };
	static const size_t DefaultHeight{ 10 };

private:
	void verifyCoordinate(size_t x, size_t y) const;

	std::vector<std::vector<std::optional<T>>> m_cells;
	size_t m_width{ 0 };
	size_t m_height{ 0 };
};

template <typename T>
Grid<T>::Grid(size_t width, size_t height) : m_width{ width }, m_height{ height }
{
	m_cells.resize(m_width);
	for (auto& colum : m_cells)
	{
		colum.resize(m_height);
	}
}

template <typename T>
void Grid<T>::verifyCoordinate(size_t x, size_t y) const
{
	if (x >= m_width || y >= m_height)
	{
		throw std::out_of_range{ std::format("{} must be less than {}", x, m_width) };
	}
}

template <typename T>
const std::optional<T>& Grid<T>::at(size_t x, size_t y) const
{
	verifyCoordinate(x, y);
	return m_cells[x][y];
}

template <typename T>
std::optional<T>& Grid<T>::at(size_t x, size_t y)
{
	return const_cast<std::optional<T>&>(as_const(*this).at(x, y));
}