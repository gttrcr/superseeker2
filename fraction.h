#pragma once

#include "BigInt.hpp"

typedef BigInt def_t;

template <typename T = def_t>
class fraction
{
private:
    T _num, _den;

    T gcd(T num1, T num2)
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

    T gcd()
    {
        return gcd(_num, _den);
    }

public:
    fraction() = default;

    fraction(def_t n, def_t d = 1)
    {
        _num = n;
        _den = d;
    }

    fraction(unsigned int n, unsigned int d = 1)
    {
        _num = n;
        _den = d;
    }

    fraction(const std::string n, const std::string d = "1")
    {
        _num = n;
        _den = d;
    }

    T num() const
    {
        return _num;
    }

    T den() const
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
        T u = gcd();
        T fnum = (u != 0) ? _num / u : _num;
        T fden = (u != 0) ? _den / u : _den;
        _num = fnum;
        _den = fden;
    }

    std::string print()
    {
        simplify();
        return _num.to_string() + (_den == 1 ? "" : "/" + _den.to_string());
    }
};

template <typename T = def_t>
bool operator==(const fraction<T> &lhs, const fraction<T> &rhs)
{
    fraction lhs_c(lhs);
    fraction rhs_c(rhs);
    lhs_c.simplify();
    rhs_c.simplify();
    return lhs_c.num() == rhs_c.num() && lhs_c.den() == rhs_c.den();
}

template <typename T = def_t>
bool operator!=(const fraction<T> &lhs, const fraction<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T = def_t>
fraction<T> operator-(fraction<T> f1, const fraction<T> &f2)
{
    return f1 -= f2;
}

template <typename T = def_t>
fraction<T> operator*(fraction<T> lhs, const fraction<T> &rhs)
{
    return lhs *= rhs;
}

template <typename T = def_t>
fraction<T> operator/(fraction<T> lhs, const fraction<T> &rhs)
{
    return lhs /= rhs;
}