module;
#include <cstddef>
export module spreadsheet;
export import spreadsheet_cell;

export class Spreadsheet
{
public:
	Spreadsheet(size_t width, size_t height);
	~Spreadsheet();

	Spreadsheet(const Spreadsheet& src);
	Spreadsheet& operator= (const Spreadsheet & rhs);

	Spreadsheet(Spreadsheet&& src) noexcept;
	Spreadsheet& operator=(Spreadsheet&& rhs) noexcept;

	void swap(Spreadsheet& other) noexcept;
	void setCellAt(size_t x, size_t y, const SpreadsheetCell& cell);
	SpreadsheetCell& getCellAt(size_t x, size_t y);
private:
	bool inRange(size_t walue, size_t upper) const;
	void cleanup() noexcept;
	void moveFrom(Spreadsheet& src) noexcept;
	void verifyCoordinate(size_t x, size_t y) const;
	size_t m_width{ 0 };
	size_t m_height{ 0 };
	SpreadsheetCell** m_cells{ nullptr };
};

export void swap(Spreadsheet& first, Spreadsheet& second) noexcept;
