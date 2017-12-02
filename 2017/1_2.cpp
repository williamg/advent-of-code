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
	size_t const halfway = numDigits / 2;

	unsigned sum = 0;

	for (size_t i = 0; i < numDigits; ++i)
	{
		unsigned digit = charToDigit (input[i]);

		unsigned const nextIdx = (i + halfway) % numDigits;
		unsigned nextDigit = charToDigit (input[nextIdx]);

		if (digit == nextDigit)
			sum += digit;
	}

	cout << sum << endl;
	return 0;
}
