module;

export module grid;
import <vector>;
import <optional>;
import <cstddef>;
import <stdexcept>;
import <utility>;
import <format>;

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
    return const_cast<std::optional<T>&>(std::as_const(*this).at(x, y));
}

export template<typename T, size_t WIDTH, size_t HEIGHT>
class Grid2
{
public:
    Grid2() = default;
    virtual ~Grid2() = default;

    Grid2(const Grid2& src) = default;
    Grid2& operator=(const Grid2& src) = default;

    std::optional<T>& at(size_t x, size_t y);
    const std::optional<T>& at(size_t x, size_t y) const;

    size_t getHeight() const { return HEIGHT; }
    size_t getWidth() const { return WIDTH; }

private:
    void verfiy(size_t x, size_t y) const;
    std::optional<T> m_cells[WIDTH][HEIGHT];
};

template<typename T, size_t WIDTH, size_t HEIGHT>
void Grid2<T, WIDTH, HEIGHT>::verfiy(size_t x, size_t y) const
{
    if (x >= WIDTH || y >= HEIGHT)
    {
        throw std::out_of_range(std::format("{}or {} must be less than {}", x, y, WIDTH));
    }
}
template<typename T, size_t WIDTH, size_t HEIGHT>
const std::optional<T>& Grid2<T, WIDTH, HEIGHT>::at(size_t x, size_t y) const
{
    verfiy(x, y);
    return m_cells[x][y];
}

template<typename T, size_t WIDTH, size_t HEIGHT>
std::optional<T>& Grid2<T, WIDTH, HEIGHT>::at(size_t x, size_t y)
{
    return const_cast<std::optional<T>&>(std::as_const(*this).at(x, y));
}

export template<typename T>
class DeducationGuides
{
public:
    DeducationGuides(const T& t): m_content(t) {}
    const T& getContent() const { return m_content; }
    private:
        T m_content;
};

explicit DeducationGuides(const char*)->DeducationGuides<std::string>;

export template<typename T>
class Grid3
{
public:
    template<typename E>
    Grid3(const Grid3<E>& src);

    template<typename E>
    Grid3<T>& operator=(const Grid3<E>& rhs);

    void swap(Grid3& other) noexcept;

    std::optional<T>& at(size_t x, size_t y);
    const std::optional<T>& at(size_t x, size_t y) const;

    size_t getHeight() const { return m_height; };
    size_t getWidth() const { return m_width; }
private:
    size_t m_width{ 0 }, m_height{ 0 };
    std::vector<std::vector<std::optional<T>>> m_cells;

};

template<typename T>
template<typename E>
Grid3<T>::Grid3(const Grid3<E>& src) : Grid3{ src.getWidth, src.getHeight() }
{
    for (size_t i = 0; i < m_width; i++)
    {
        for (size_t j = 0; j < m_height; j++)
        {
            m_cells[i][j] = src.at(i, j);
        }
    }
}

template<typename T>
void Grid3<T>::swap(Grid3& other) noexcept
{
    std::swap(m_width, other.m_width);
    std::swap(m_height, other.m_height);
    std::swap(m_cells, other.m_cells);
}

template<typename T>
template<typename E>
Grid3<T>& Grid3<T>::operator=(const Grid3<E>& rhs)
{
    Grid3<T> tmp{ rhs };
    swap(tmp);
    return *this;
}

export template<typename T>
class GameBoard :public Grid<T>
{
public:
    explicit GameBoard(size_t width = Grid<T>::DefaultWidth, size_t height = Grid<T>::DefaultHeight);
    void move(size_t xSrc, size_t ySrc, size_t xDest, size_t yDest);
};

template <typename T>
GameBoard<T>::GameBoard(size_t width, size_t height): Grid<T>{width, height}{}

template<typename T>
void GameBoard<T>::move(size_t xSrc, size_t ySrc, rsize_t xDest, size_t yDest)
{
    Grid<T>::at(xDest, yDest) = std::move(Grid<T>::at(xSrc, ySrc));
    Grid<T>::at(xSrc, ySrc).reset();
}



