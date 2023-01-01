#ifndef VECTOR_UTILS_HEADER
#define VECTOR_UTILS_HEADER
#include <vector>

/// @Warning unstable as the order of vector is not the same
template <typename T>
void pop_front(std::vector<T>& vector){
	std::swap(vector.begin(), vector.end());
	vector.pop_back();
}

#endif