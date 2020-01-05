#ifndef MYARRAY_HPP
#define MYARRAY_HPP

template <class T, int N> // N is a non-type parameter
class myArray {

private:
	T m_array[N];

public:
	T* getArray();

	T& operator[](int index);
};

template <class T, int N>
T* myArray<T, N>::getArray() {
	return m_array;
}

template <class T, int N>
T& myArray<T, N>::operator[](int index) {
	return m_array[index];
}

#endif