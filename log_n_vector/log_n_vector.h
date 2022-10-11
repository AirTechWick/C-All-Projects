//
// Created by erikr on 4/21/2021.
//

#ifndef HOMEWORK02_LOG_N_VECTOR_H
#define HOMEWORK02_LOG_N_VECTOR_H
#include <cmath>
#include <memory>
#include <vector>

template <typename T>
class LogNVector {
    // These member variables are suggested and not required!
    // Feel free to use change the variable names or types, as long as you
    // follow the spirit of the assignment.
    std::vector<std::unique_ptr<T[]> > arrays_;
    int size_, capacity_;
    int capacityIndex = 1;
public:
    LogNVector() {
        size_ = 0;
        capacity_ = 1;
        arrays_.push_back(std::make_unique<T[]>(capacity_));
    }

    LogNVector(const LogNVector& other) : LogNVector() { // deep copy constructor

        for (int a = 0; a < other.size_; ++a) {
            int i = log2(a + 1);
            int j = a - (pow(2,i) - 1);
            push_back((other.arrays_[i][j]));
        }

    }

    LogNVector(std::initializer_list<T> ilist) : LogNVector() {
        for (auto element : ilist) {
            push_back(element);
        }
    }

    ~LogNVector() {
    }

    int size() const noexcept {
        return size_;
    }
    int capacity() const noexcept {
        return capacity_;
    }
    void push_back(const T& value) {
        size_++;

        if (size_ >= capacity_)
        {
            capacityIndex++;
            const int new_capacity_ = (pow(2,capacityIndex)) - 1;
            std::unique_ptr<T[]> new_ptr_arrays = std::make_unique<T[]>(new_capacity_);

            arrays_.push_back(std::move(new_ptr_arrays));
            capacity_ = new_capacity_;
        }

        int indexForValue = size_ - 1;

        (*this)[indexForValue] = value;
    }
    const T& operator[](int index) const {

        int i = log2(index + 1);
        int j = index - (pow(2,i) - 1);

        return arrays_[i][j];
    }

    T& operator[](int index) {

        int i = log2(index + 1);
        int j = index - (pow(2,i) - 1);

        return arrays_[i][j];
    }
};

#endif //HOMEWORK02_LOG_N_VECTOR_H