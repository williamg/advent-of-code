#include <iostream>
using namespace std;

enum class parseState_t
{
	GROUP,
	GARBAGE
};

int main ()
{
	int curDepth = 1;
	int curScore = 0;
	int garbage = 0;
	parseState_t state = parseState_t::GROUP;

	// Skip the first open brace
	char c;
	cin >> c;
	while (cin >> c)
	{
		switch (c)
		{
		case '{':
			if (state == parseState_t::GARBAGE)
				garbage++;
			else
				curDepth++;
			break;
		case '}':
			if (state == parseState_t::GARBAGE)
			{
				garbage++;
			}
			else
			{
				curScore += curDepth;
				curDepth--;
			}
			break;
		case '<':
			if (state == parseState_t::GARBAGE)
				garbage++;
			else
				state = parseState_t::GARBAGE;
			break;
		case '>':
			if (state != parseState_t::GROUP)
				state = parseState_t::GROUP;
			break;
		case '!':
			if (state == parseState_t::GARBAGE)
				cin >> c;
			break;
		default:
			if (state == parseState_t::GARBAGE)
				garbage++;
			break;
		}
	}

	cout << garbage << endl;
	return 0;
}
