#pragma once

#include "fraction.h"
std::string print(fraction *t)
{
    std::string ret = "";
    for (unsigned int i = 1; i <= t->num(); i++)
        ret += (t + i)->print() + " ";
    return ret;
}