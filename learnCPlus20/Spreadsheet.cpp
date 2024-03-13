module spreadsheet;
import <stdexcept>;
import <format>;
import <utility>;

Spreadsheet::Spreadsheet(size_t width, size_t height) :m_width{ width }, m_height{ height }
{
	m_cells = new SpreadsheetCell* [m_width];
	for (size_t i = 0; i < m_width; i++)
	{
		m_cells[i] = new SpreadsheetCell[m_height];
	}
}

Spreadsheet::~Spreadsheet()
{
	for (size_t i = 0; i < m_width; i++)
	{
		delete[] m_cells[i];
	}

	delete[] m_cells;
	m_cells = nullptr;
}

void Spreadsheet::swap(Spreadsheet& other) noexcept
{
	std::swap(m_width, other.m_width);
	std::swap(m_height, other.m_height);
	std::swap(m_cells,  other.m_cells);
}

Spreadsheet::Spreadsheet(const Spreadsheet& src) : Spreadsheet {src.m_width, src.m_height}
{
	for (size_t i = 0; i < m_width; i++)
	{
		for (size_t x = 0; x < m_height; x++)
		{
			m_cells[i][x] = src.m_cells[i][x];
		}
	}
}

Spreadsheet& Spreadsheet::operator=(const Spreadsheet& rhs)
{
	if (this==&rhs)
	{
		return *this;
	}
	Spreadsheet tmp{ rhs };
	swap(tmp);
	return *this;
}

void swap(Spreadsheet& first, Spreadsheet& second) noexcept
{
	first.swap(second);
}

Spreadsheet::Spreadsheet(Spreadsheet&& src) noexcept
{
	// moveFrom(src);
	swap(src);
}

Spreadsheet& Spreadsheet::operator=(Spreadsheet&& rhs) noexcept
{
//	if (this == &rhs)
//	{
//		return *this;
//	}
//
//	cleanup();
//	moveFrom(rhs);
	swap(rhs);
	return *this;
}


void Spreadsheet::cleanup() noexcept
{
	for (size_t i = 0; i < m_width; i++)
	{
		delete[] m_cells[i];
	}

	delete[] m_cells;
	m_cells = nullptr;
	m_height = m_width = 0;
}

void Spreadsheet::moveFrom(Spreadsheet& rhs) noexcept
{
	m_width = rhs.m_width;
	m_height = rhs.m_height;
	m_cells = rhs.m_cells;

	rhs.m_width = 0;
	rhs.m_height = 0;
	rhs.m_cells = nullptr;
}

void Spreadsheet::setCellAt(size_t x, size_t y, const SpreadsheetCell& cell)
{
	verifyCoordinate(x, y);
	m_cells[x][y] = cell;
}

SpreadsheetCell& Spreadsheet::getCellAt(size_t x, size_t y)
{
	verifyCoordinate(x, y);
	return m_cells[x][y];
}

void Spreadsheet::verifyCoordinate(size_t x, size_t y)const {
	if (!inRange(x, m_width))
	{
		throw std::out_of_range{ std::format("{} must be less than {}", x, m_width) };
	}

	if (!inRange(y, m_height))
	{
		throw std::out_of_range{ std::format("{} must be less than {}", y, m_height) };
	}
}
