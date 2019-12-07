#include <iostream>

#include "curvebase.hpp"
#include "xline.hpp"
#include "yline.hpp"
#include "xcurve.hpp"

using namespace std;


int main() {
	XLine xline = XLine(-10, 5, 3);
	YLine yline1 = YLine(0, 3, 5);
	XCurve xcurve = XCurve(-10, 5);
	YLine yline2 = YLine(0, 3, -10);
}