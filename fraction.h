#pragma once

typedef long long int def_t;
#define CONV_FUNC std::stoll

template <typename T>
class fraction
{
private:
    T _num, _den;

    T gcd(T a, T b)
    {
        if (b == 0)
            return a;
        else
            return gcd(b, a % b);
    }

    T gcd()
    {
        return gcd(_num, _den);
    }

public:
    fraction() = default;

    fraction(T n, T d = 1)
    {
        _num = n;
        _den = d;
    }

    fraction(const std::string n, const std::string d = "1")
    {
        _num = CONV_FUNC(n);
        _den = CONV_FUNC(d);
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

    fraction &operator/=(const T &rhs)
    {
        _den = _den * rhs;
        return *this;
    }

    fraction &operator+=(fraction const &rhs)
    {
        _num = _num * rhs._den + rhs._num * _den;
        _den = _den * rhs._den;
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
        fraction<T> f(_num, _den);
        f.simplify();
        return f.num() == 0 ? "0" : (std::to_string(f.num()) + (f.den() == 1 ? "" : "/" + std::to_string(f.den())));
    }
};

template <typename T>
bool operator==(const fraction<T> &lhs, const fraction<T> &rhs)
{
    fraction<T> lhs_c(lhs);
    fraction<T> rhs_c(rhs);
    lhs_c.simplify();
    rhs_c.simplify();
    return lhs_c.num() == rhs_c.num() && lhs_c.den() == rhs_c.den();
}

template <typename T>
bool operator!=(const fraction<T> &lhs, const fraction<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
fraction<T> operator-(fraction<T> lhs, const fraction<T> &rhs)
{
    return lhs -= rhs;
}

template <typename T>
fraction<T> operator+(fraction<T> lhs, const fraction<T> &rhs)
{
    return lhs += rhs;
}

template <typename T>
fraction<T> operator*(fraction<T> lhs, const fraction<T> &rhs)
{
    return lhs *= rhs;
}

template <typename T>
fraction<T> operator/(fraction<T> lhs, const fraction<T> &rhs)
{
    return lhs /= rhs;
}

template <typename T>
fraction<T> operator/(fraction<T> lhs, const T &rhs)
{
    return lhs /= rhs;
}

template <typename T>
fraction<T> *create_sequence(const unsigned int len)
{
    fraction<T> *s = new fraction<T>[len + 1];
    *(s + 0) = len;
    return s;
}

template <typename T>
void destroy_sequence(fraction<T> *s)
{
    delete s;
    //s = NULL;
}