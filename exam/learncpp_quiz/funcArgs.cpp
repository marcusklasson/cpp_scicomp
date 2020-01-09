#include <iostream>

double max(double x, double y) {
	return x > y ? x : y;
} 

void swap(double& x, double& y) {
	double x1 = x;
	x = y;
	y = x1;
}

int main() {
	double x = 1.0, y = 0.0;
	std::cout << "Maximum: " << max(y,x) << std::endl; 	

	std::cout << "Before swap: x: " << x << ", y: " << y << std::endl;
	swap(x,y); 
	std::cout << "After swap: x: " << x << ", y: " << y << std::endl;
	int array[]{1, 2, 3, 4};
	std::cout << array[3] << std::endl; 
}