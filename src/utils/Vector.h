#pragma once

#include <vector>
#include <initializer_list>
#include <stdexcept>
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

private:
    std::vector<int> data;
};

std::ostream& operator<<(std::ostream& os, const Vector& vec);
std::ostream& operator<<(std::ostream& os, const std::vector<Vector>& vec);