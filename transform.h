#pragma once

def_t factorial(const def_t &big)
{
    def_t ret = 1;
    for (def_t i = 2; i <= big; i++)
        ret *= i;
    return ret;
}

fraction<def_t> *factorial_over_n(fraction<def_t> *u)
{
    const def_t u_length = u->num();
    fraction<def_t> *ret = new fraction<def_t>[u_length + 1];
    *(ret + 0) = *(u + 0);
    for (unsigned int i = 1; i <= u_length; i++)
        *(ret + i) = (*(u + i)) / fraction<def_t>(factorial(i));
    return ret;
}

fraction<def_t> *sequence_minus_n(fraction<def_t> *u)
{
    const def_t u_length = u->num();
    fraction<def_t> *ret = new fraction<def_t>[u_length + 1];
    *(ret + 0) = *(u + 0);
    for (unsigned int i = 1; i <= u_length; i++)
        *(ret + i) = (*(u + i)) - fraction<def_t>(i);
    return ret;
}

fraction<def_t> *sequence_minus_factorial_n(fraction<def_t> *u)
{
    const def_t u_length = u->num();
    fraction<def_t> *ret = new fraction<def_t>[u_length + 1];
    *(ret + 0) = *(u + 0);
    for (unsigned int i = 1; i <= u_length; i++)
        *(ret + i) = (*(u + i)) - fraction<def_t>(factorial(i));
    return ret;
}