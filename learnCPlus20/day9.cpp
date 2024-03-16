#include <iostream>
#include <string>

using namespace std;

class TextHolder
{
public:
	TextHolder(string text): m_text {move(text)} {}
	const string& getText() const & { return m_text; }
	string&& getText() && { return move(m_text); }

private:
	string m_text;
};

void test0901()
{
	TextHolder txtHolder{ "next time" };

	cout << TextHolder{ "Hello world" }.getText() << endl;
	cout << move(txtHolder).getText() << endl;
}

int main9()
{
	test0901();
	system("pause");
	return 10;
}