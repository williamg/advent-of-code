#include <assert.h>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

// -1 -1
// -1 0 
// -1 1
// 0 -1
// 0 1
// 1 -1
// 1 0
// 1 1

class spiralShell_t
{
public:
	spiralShell_t (unsigned const shell_)
		: m_shell (shell_)
		, m_data ()
	{
		unsigned const numElements = [shell_] () {
			if (shell_ == 0)
				return 1U;

			unsigned const prevOdd = 2 * shell_ + 1;
			unsigned const nextOdd = prevOdd + 2;
			return static_cast<unsigned> (pow (nextOdd, 2) - pow (prevOdd, 2));
		} ();

		for (size_t i = 0; i < numElements; ++i)
			m_data.push_back (0);
	}

	void set (int x, int y, int val)
	{
		m_data[coordToIdx (x, y)] = val;
	}

	int get (int x, int y) const
	{
		return m_data[coordToIdx (x, y)];
	}

private:
	int coordToIdx (int x, int y) const
	{
		assert (static_cast<int> (abs (x)) == m_shell ||
		        static_cast<int> (abs (y)) == m_shell);

		if (x == 0 && y == 0)
			return 0;

		assert (m_data.size () % 4 == 0);

		if (x == m_shell && y > -m_shell) return 4 * (y - (-m_shell + 1));
		if (x < m_shell && y == m_shell) return 1 + 4 * ((m_shell - 1) - x);
		if (x == -m_shell && y < m_shell) return 2 + 4 * ((m_shell - 1) - y);

		assert (x > -m_shell && y == -m_shell);
		return 3 + 4 * (x - (-m_shell + 1));
	}

	int const m_shell;
	vector<int> m_data;
};

int sumNeighbors (int x, int y, int shell,
                  spiralShell_t *curShell, spiralShell_t *prevShell)
{
	vector<pair<int, int>> neighbors;

	int sum = 0;

	for (int dx = -1; dx <= 1; ++dx)
	{
		for (int dy = -1; dy <= 1; ++dy)
		{
			int const nx = x + dx;
			int const ny = y + dy;
			int const nshell = max (abs (nx), abs (ny));

			if (nshell == shell) sum += curShell->get (nx, ny);
			if (nshell == shell - 1) sum += prevShell->get (nx, ny);
		}
	}

	return sum;
}

struct bounds_t
{
	int start;
	int end;
	int inc;
};

int main ()
{
	int val;
	cin >> val;

	spiralShell_t *prevShell = new spiralShell_t (0);
	prevShell->set (0, 0, 1);

	int shell = 1;
	spiralShell_t *curShell = new spiralShell_t (shell);

	int lastVal = 1;

	while (true)
	{
		vector<pair<bounds_t, bounds_t>> bounds = {
			{ { shell, shell + 1, 0 }, { -shell + 1, shell + 1, 1 } },
			{ { shell - 1, -shell-1, -1 }, {shell, shell + 1, 0 } },
			{ { -shell, -shell+1, 0 }, { shell - 1, -shell-1, -1 } },
			{ { -shell + 1, shell+1, 1 }, { -shell, -shell+1, 0 } }
		};

		for (pair<bounds_t, bounds_t> const &xybound : bounds)
		{
			bounds_t const xb = xybound.first;
			bounds_t const yb = xybound.second;

			for (int x = xb.start, y = yb.start;
			     (x != xb.end) && (y != yb.end);
				 x += xb.inc, y += yb.inc)
			{
				lastVal = sumNeighbors (x, y, shell, curShell, prevShell);
				curShell->set (x, y, lastVal);

				if (lastVal > val)
				{
					cout << lastVal << endl;
					return 0;
				}
			}
		}

		delete prevShell;
		prevShell = curShell;

		curShell = new spiralShell_t (++shell);
	}
}
