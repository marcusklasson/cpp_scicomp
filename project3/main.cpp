#include <iostream>
#include <cmath>

#include "domain.hpp"
#include "curvebase.hpp"
#include "xline.hpp"
#include "yline.hpp"
#include "xcurve.hpp"

using namespace std;

int main() {
	XCurve s1 = XCurve(-10, 5);	// lower horizontal curve
	YLine s2 = YLine(0, 3, 5); // right vertical line
	XLine s3 = XLine(-10, 5, 3); //upper horizontal line
	YLine s4 = YLine(0, 3, -10); // left vertical line 

	Domain d = Domain(s1, s2, s3, s4);
	d.generateGrid(5, 5);
	d.print();
	d.write();

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