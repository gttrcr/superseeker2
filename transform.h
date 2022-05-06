#pragma once

BigInt factorial(const BigInt &big)
{
    BigInt ret = 1;
    for (BigInt i = 2; i <= big; i++)
        ret *= i;
    return ret;
}

fraction *factorial_over_n(fraction *u)
{
    const BigInt u_length = u->num();
    fraction *ret = new fraction[u_length.to_int() + 1];
    *(ret + 0) = *(u + 0);
    for (unsigned int i = 1; i <= u_length; i++)
        *(ret + i) = (*(u + i)) / factorial(i);
    return ret;
}

fraction *sequence_minus_n(fraction *u)
{
    const BigInt u_length = u->num();
    fraction *ret = new fraction[u_length.to_int() + 1];
    *(ret + 0) = *(u + 0);
    for (unsigned int i = 1; i <= u_length; i++)
        *(ret + i) = (*(u + i)) - i;
    return ret;
}

fraction *sequence_minus_factorial_n(fraction *u)
{
    const BigInt u_length = u->num();
    fraction *ret = new fraction[u_length.to_int() + 1];
    *(ret + 0) = *(u + 0);
    for (unsigned int i = 1; i <= u_length; i++)
        *(ret + i) = (*(u + i)) - factorial(i);
    return ret;
}