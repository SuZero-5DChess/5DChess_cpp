#include "Vector.h"

Vector::Vector(std::initializer_list<int> values) : data(values) {}

Vector Vector::operator-(const Vector& other) const {
    if (data.size() != other.data.size()) {
        throw std::invalid_argument("Vectors must be of the same size");
    }

    Vector result;
    for (size_t i = 0; i < data.size(); ++i) {
        result.data.push_back(data[i] - other.data[i]);
    }

    return result;
}

Vector Vector::operator+(const Vector& other) const {
    if (data.size() != other.data.size()) {
        throw std::invalid_argument("Vectors must be of the same size");
    }

    Vector result;
    for (size_t i = 0; i < data.size(); ++i) {
        result.data.push_back(data[i] + other.data[i]);
    }

    return result;
}

Vector Vector::operator*(int other) const {
    Vector result;
    for (size_t i = 0; i < data.size(); ++i) {
        result.data.push_back(data[i] * other);
    }

    return result;
}
bool Vector::operator==(const Vector& other) const {

    return data == other.data;
}

const int& Vector::operator[](size_t index) const {
    if (index >= data.size()) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

void Vector::print() const {
    for (int val : data) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

size_t Vector::size() const {
    return data.size();
}
