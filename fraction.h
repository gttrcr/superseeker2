#pragma once

#include "BigInt.hpp"

class fraction
{
private:
    BigInt _num, _den;

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

    BigInt gcd()
    {
        return gcd(_num, _den);
    }

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

    void simplify()
    {
        BigInt u = gcd();
        BigInt fnum = (u != 0) ? _num / u : _num;
        BigInt fden = (u != 0) ? _den / u : _den;
        _num = fnum;
        _den = fden;
    }

    std::string print()
    {
        simplify();
        return _num.to_string() + (_den == 1 ? "" : "/" + _den.to_string());
    }
};

bool operator==(const fraction &lhs, const fraction &rhs)
{
    fraction lhs_c(lhs);
    fraction rhs_c(rhs);
    lhs_c.simplify();
    rhs_c.simplify();
    return lhs_c.num() == rhs_c.num() && lhs_c.den() == rhs_c.den();
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