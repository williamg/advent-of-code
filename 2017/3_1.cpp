#include <assert.h>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

// Sign function taken from StackOverflow
template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

struct point_t
{
	int x;
	int y;
	unsigned val;
};

int main ()
{
	unsigned val;
	cin >> val;

	unsigned const nearestSqrt = static_cast<unsigned> (floor (sqrt (val)));
	unsigned const innerShellSqrt =
		(nearestSqrt % 2) == 0 ? nearestSqrt - 1 : nearestSqrt;
	unsigned const innerShellCorner = pow (innerShellSqrt, 2);

	int const innerShell = (innerShellSqrt - 1) / 2;

	// Early return if the value happens to be the sqrt on the inner shell
	if (val == innerShellCorner)
	{
		cout << 2 * innerShell << endl;
		return 0;
	}

	// The value is definitely on the outer shell
	int const outerShell = innerShell + 1;
	int const outerShellSide = innerShellSqrt + 2;

	vector<point_t const> const corners ({
		{ outerShell, -(outerShell - 1), innerShellCorner + 1 },
		{ outerShell, outerShell, innerShellCorner + 1 + outerShellSide - 2},
		{ -outerShell, outerShell, innerShellCorner + 1 + outerShellSide - 2 + outerShellSide - 1},
		{ -outerShell, -outerShell, innerShellCorner + 3 * outerShellSide - 3 },
		{ outerShell, -outerShell, static_cast<unsigned> (pow (innerShellSqrt + 2, 2)) }
	});

	auto const betweenPoints = [&corners, val] () {
		for (size_t i = 1; i < corners.size (); ++i)
		{
			if (val >= corners[i].val)
				continue;

			return pair<point_t const, point_t const> {
				corners[i - 1],
				corners[i]
			};
		}

		assert (false);
	} ();

	pair<int, int> const diffUnitVec = {
		sgn (betweenPoints.second.x - betweenPoints.first.x),
		sgn (betweenPoints.second.y - betweenPoints.first.y)
	};

	int const valDiff = val - betweenPoints.first.val;

	point_t const valPoint = {
		betweenPoints.first.x + valDiff * diffUnitVec.first,
		betweenPoints.first.y + valDiff * diffUnitVec.second,
		val
	};

	cout << abs (valPoint.x) + abs (valPoint.y) << endl;
	return 0;
}
