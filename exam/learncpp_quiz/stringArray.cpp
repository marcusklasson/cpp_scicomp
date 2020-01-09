#include <iostream>
#include <string>
#include <algorithm> // For std::sort

using namespace std;

void printNames(const string* array, const int length) {
	for (int i = 0; i < length; ++i) {
		cout << "Name #" << i+1 << ": " << array[i] << "\n";
	}
}

int main () {

	int n_names;
	cout << "How many names would you like to enter? ";
	cin >> n_names;

	string *names = new string[n_names];

	for (int i = 0; i < n_names; ++i) {
		cout << "Enter name #" << i+1 << ": ";
		cin >> names[i];
	}
	cout << "\n";

	sort(names, names + n_names);
	cout << "Here is your sorted list:\n";
	printNames(names, n_names);

	delete[] names;

	return 0;
}