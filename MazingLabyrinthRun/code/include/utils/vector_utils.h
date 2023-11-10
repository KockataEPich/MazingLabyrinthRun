#ifndef VECTOR_UTILS_HEADER
#define VECTOR_UTILS_HEADER
#include <stdexcept>
#include <vector>

namespace vec_utils {

template<typename T>
void pop_at_index(int index, std::vector<T>& vector) {
	if (index >= vector.size()) throw std::runtime_error("Vector size is bigger than index!");
	if (index != vector.size() - 1) std::swap(vector.at(index), vector.at(vector.size() - 1));
	vector.pop_back();
}

/// @Warning unstable as the order of vector is not the same
template<typename T>
void pop_front(std::vector<T>& vector) {
	pop_at_index(0, vector);
}
}  // namespace vec_utils
#endif