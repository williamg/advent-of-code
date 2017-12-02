#include <iostream>
using namespace std;

unsigned charToDigit (char c)
{
	return static_cast<unsigned> (c - '0');
}

int main (int argc, char **argv)
{
	// Const correctness is key :)
	string const input = [] () {
		string s;
		cin >> s;
		return s;
	} ();

	size_t const numDigits = input.size ();
	unsigned sum = 0;
	unsigned digit = charToDigit (input[0]);

	for (size_t i = 0; i < numDigits; ++i)
	{
		unsigned nextDigit = charToDigit (input[(i + 1) % numDigits]);

		if (digit == nextDigit)
			sum += digit;

		digit = nextDigit;
	}

	cout << sum << endl;
	return 0;
}
