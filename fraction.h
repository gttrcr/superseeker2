#pragma once

typedef long long int SEQ_INT;
typedef float SEQ_F;

class fraction
{
private:
    SEQ_INT _num;
    SEQ_INT _den;

public:
    fraction(SEQ_INT num = 0, SEQ_INT den = 1)
    {
        _num = num,
        _den = den;
    }
};