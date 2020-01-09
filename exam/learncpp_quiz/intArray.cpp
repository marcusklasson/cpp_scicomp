#include <iostream>
#include <cassert> // for assert

class IntArray {
	int m_length{0};
	int* m_array{nullptr};

public:
	IntArray(int length) : m_length(length) {
		if (length > 0) {
			m_array = new int[length];
		}
	}

	IntArray(const IntArray& A) {
		m_length == A.m_length;
		m_array = nullptr;

		if (m_length > 0) {
			for (int i = 0; i < A.m_length; ++i) {
				m_array[i] = A.m_array[i];
			}
		}
	}

	~IntArray() {delete[] m_array;}

	IntArray& operator=(const IntArray& A);

	int& operator[](int index);

	friend std::ostream& operator<<(std::ostream& os, const IntArray& A);
};

IntArray& IntArray::operator=(const IntArray& A) {
	if (this != &A) {
		if (m_length > 0) {
			delete[] m_array;
		}

		m_length = A.m_length;
		if (m_length > 0) {
			m_array = new int[m_length];
			for (int i = 0; i < A.m_length; ++i) {
				m_array[i] = A.m_array[i];
			}

		} else {
			m_array = nullptr;
		}
	}
	return *this;
}

int& IntArray::operator[](int index) {
	assert(index >= 0);
	assert(index < m_length);
	return m_array[index];
}

std::ostream& operator<<(std::ostream& os, const IntArray& A) {
	if (A.m_length > 0) {
		auto begin{ &A.m_array[0] };
		auto end{ begin + A.m_length };

		for (auto ptr = begin ; ptr != end; ++ptr) { // ++ to move to next element 
			os << *ptr << ' '; // dereference to get value of current element
		}
	}
	return os;
}


IntArray fillArray()
{
	IntArray a(5);
 
	a[0] = 5;
	a[1] = 8;
	a[2] = 2;
	a[3] = 3;
	a[4] = 6;
 
	return a;
}
 
int main()
{
	IntArray a{ fillArray() };
	std::cout << a << '\n';
 	
	auto &ref{ a }; // we're using this reference to avoid compiler self-assignment errors
	a = ref;
 
	IntArray b(1);
	b = a;
 
	std::cout << b << '\n';
 	
	return 0;
}