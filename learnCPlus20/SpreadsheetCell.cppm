export module spreadsheet_cell;

import <string>;
import <string_view>;
export class SpreadsheetCell
{
public:
    SpreadsheetCell() = default;
    SpreadsheetCell(double initialValue);
    SpreadsheetCell(std::string_view initialValue);

    void setValue(double value);
    double getValue() const;

    void setString(std::string_view value);
    std::string getString() const;

    explicit operator double() const;
    operator std::string() const;

    operator auto() const { return getValue(); }
    operator const auto&() const { return getValue(); }

private:
    std::string doubleToString(double value) const;
    double stringToDouble(std::string_view value) const;

    double m_value{ 0 };
};

export SpreadsheetCell operator+(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs);