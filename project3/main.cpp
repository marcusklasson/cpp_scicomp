#include <iostream>
#include <cmath>

#include "domain.hpp"
#include "curvebase.hpp"
#include "xline.hpp"
#include "yline.hpp"
#include "xcurve.hpp"

using namespace std;

int main() {
	XLine xline = XLine(-10, 5, 3); //upper horizontal line
	YLine yline1 = YLine(0, 3, 5); // right vertical line
	YLine yline2 = YLine(0, 3, -10); // left vertical line 
	XCurve xcurve = XCurve(-10, 5);	// lower horizontal curve

	Domain d = Domain(xline, yline1, xcurve, yline2);
	//cout << "x(1) = " << xline.x(1) << endl;
	//cout << "x(0.5) = " << xline.x(0.5) << endl;
	//cout << "x(0) = " << xline.x(0) << endl;

	//cout << "y1(1) = " << yline1.y(1) << endl;
	//cout << "y1(0) = " << yline1.y(0) << endl;

	//cout << "y2(1) = " << yline2.y(1) << endl;
	//cout << "y2(0.5) = " << yline2.y(0.5) << endl;

	
	//cout << "fx(3) = " << xcurve.x(1) << endl;
	//cout << "fx(3) = " << xcurve.y(1) << endl;
}