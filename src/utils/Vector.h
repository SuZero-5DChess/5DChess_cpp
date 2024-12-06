#pragma once

#include <vector>
#include <initializer_list>
#include <iostream>

class Vector {
public:
    Vector(std::initializer_list<int> values);

    Vector() = default;

    Vector operator-(const Vector& other) const;
    Vector operator+(const Vector& other) const;
    Vector operator*(int other) const;
    bool operator==(const Vector& other) const;
    const int& operator[](size_t index) const;

    void print() const;

    size_t size() const;
    const std::vector<int>& getData() const { return data; }

private:
    std::vector<int> data;
};

namespace std {

    template <>
    struct hash<Vector> {
        size_t operator()(const Vector& v) const {
            size_t hash_value = 0;
            for (int i : v.getData()) {
                hash_value ^= hash<int>()(i) + 0x9e3779b9 + (hash_value << 6) + (hash_value >> 2);
            }
            return hash_value;
        }
    };
}

std::ostream& operator<<(std::ostream& os, const Vector& vec);
std::ostream& operator<<(std::ostream& os, const std::vector<Vector>& vec);

