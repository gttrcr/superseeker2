#pragma once

#include "BigInt.hpp"

class fraction
{
private:
    BigInt _num, _den;

public:
    fraction() = default;

    fraction(unsigned int n, unsigned int d = 1)
    {
        _num = n;
        _den = d;
    }

    fraction(BigInt n, BigInt d = 1)
    {
        _num = n;
        _den = d;
    }

    BigInt num() const
    {
        return _num;
    }

    BigInt den() const
    {
        return _den;
    }

    fraction &operator*=(const fraction &rhs)
    {
        _den = _den * rhs._den;
        _num = _num * rhs._num;
        return *this;
    }

    fraction &operator-=(fraction const &rhs)
    {
        _num = _num * rhs._den - rhs._num * _den;
        _den = _den * rhs._den;
        return *this;
    }

    std::string print()
    {
        return _num.to_string() + (_den == 1 ? "" : "/" + _den.to_string());
    }
};

bool operator==(const fraction &lhs, const fraction &rhs)
{
    return lhs.num() == rhs.num() && lhs.den() == rhs.den();
}

bool operator!=(const fraction &lhs, const fraction &rhs)
{
    return !(lhs == rhs);
}

fraction operator-(fraction f1, const fraction &f2)
{
    return f1 -= f2;
}

fraction operator*(fraction lhs, const fraction &rhs)
{
    return lhs *= rhs;
}