#pragma once

#include "fraction.h"

class sequence
{
private:
    fraction *_s;
    unsigned int _size;

public:
    sequence() = default;

    sequence(const unsigned int size)
    {
        _size = size;
        _s = new fraction[size];
    }

    const unsigned int get_size()
    {
        return _size;
    }

    void set(unsigned int pos, fraction val)
    {
        *(_s + pos) = val;
    }

    fraction get(unsigned int pos)
    {
        return *(_s + pos);
    }
};