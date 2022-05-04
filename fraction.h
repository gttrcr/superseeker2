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

    fraction &operator/=(const fraction &rhs)
    {
        _den = _den * rhs._num;
        _num = _num * rhs._den;
        return *this;
    }

    fraction &operator-=(fraction const &rhs)
    {
        _num = _num * rhs._den - rhs._num * _den;
        _den = _den * rhs._den;
        return *this;
    }

    std::string print() const
    {
        return _num.to_string() + (_den == 1 ? "" : "/" + _den.to_string());
    }
};

BigInt gcd(BigInt num1, BigInt num2)
{
    BigInt ret;
    for (int i = 1; i <= num1 && i <= num2; i++)
    {
        if (num1 % i == 0 && num2 % i == 0)
        {
            ret = i;
        }
    }

    return ret;
}

fraction simplify(const fraction &f)
{
    BigInt u = gcd(f.num(), f.den());
    BigInt fnum = (u != 0) ? f.num() / u : f.num();
    BigInt fden = (u != 0) ? f.den() / u : f.den();

    return fraction(fnum, fden);
}

bool operator==(const fraction &lhs, const fraction &rhs)
{
    fraction lhssimplify = simplify(lhs);
    fraction rhssimplify = simplify(rhs);
    return lhssimplify.num() == rhssimplify.num() && lhssimplify.den() == rhssimplify.den();
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

fraction operator/(fraction lhs, const fraction &rhs)
{
    return lhs /= rhs;
}