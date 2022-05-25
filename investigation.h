#pragma once

#include <thread>
#include <mutex>
#include <map>

#include "transform.h"

typedef std::vector<std::tuple<unsigned int, std::vector<fraction<def_t>>>> out_type;

std::mutex print_mtx;
void print(const std::string &msg, const out_type &v = {}, const std::string &title = "")
{
    print_mtx.lock();
    std::cout << msg << std::endl;
    for (unsigned int i = 0; i < v.size(); i++)
    {
        std::cout << title << " oeis code: " << std::get<0>(v[i]) << " values [";
        std::vector<fraction<def_t>> one = std::get<1>(v[i]);
        for (unsigned int j = 0; j < one.size(); j++)
            std::cout << one[j].print() << (j < one.size() - 1 ? " " : "]");
        std::cout << std::endl;
    }
    print_mtx.unlock();
}

out_type linear_shift(fraction<def_t> *u, fraction<def_t> **oeis_values, unsigned int *oeis_keys, const unsigned int &oeis_db_size, const std::string &title = "")
{
    out_type ret;
    const def_t u_length = u->num();
    for (unsigned int i = 0; i < oeis_db_size; i++)
    {
        //fix shift>2
        for (unsigned int shift = 0; shift < 2; shift++)
        {
            fraction<def_t> *o = *(oeis_values + i);
            if (o->num() < u_length + shift)
                continue;

            bool br = false;
            fraction m_tmp = (*(u + 2) - *(u + 1)) / (*(o + 2 + shift) - *(o + 1 + shift));
            if (m_tmp.den() == 0)
                continue;

            for (unsigned int n = 3; n <= u_length && !br; n++)
            {
                fraction m = (*(u + n) - *(u + 1)) / (*(o + n + shift) - *(o + 1 + shift));
                if (m_tmp != m)
                    br = true;
            }
            if (!br)
            {
                std::vector<fraction<def_t>> inner = {shift, m_tmp, *(u + 1) - m_tmp * *(o + 1 + shift)};
                ret.push_back(std::make_tuple(*(oeis_keys + i), inner));
            }
        }
    }

    return ret;
}

void investigation(fraction<def_t> *u, fraction<def_t> **oeis_values, unsigned int *oeis_keys, const unsigned int &oeis_db_size)
{
    std::vector<std::thread> pool;
    pool.push_back(std::thread([u, oeis_values, oeis_keys, oeis_db_size]()
                               {
                                   out_type res = linear_shift(u, oeis_values, oeis_keys, oeis_db_size, "linear");
                                   print(std::to_string(res.size()), res, "linear_shift"); }));

    // pool.push_back(std::thread([u, oeis_values, oeis_keys, oeis_db_size]()
    //                            {
    //                                fraction<def_t> *u_tr = factorial_over_n(u);
    //                                out_type res = linear_shift(u_tr, oeis_values, oeis_keys, oeis_db_size, "fact");
    //                                print(std::to_string(res.size()), res, "linear_shift (factorial_over_n)"); }));

    // pool.push_back(std::thread([u, oeis_values, oeis_keys, oeis_db_size]()
    //                            {
    //                                fraction<def_t>* u_tr = sequence_minus_n(u);
    //                                out_type res = linear_shift(u_tr, oeis_values, oeis_keys, oeis_db_size);
    //                                print_mtx.lock();
    //                                std::cout << "linear_shift (sequence_minus_n) ended found " << res.size() << " results" << std::endl;
    //                                print(res, "linear_shift (sequence_minus_n)");
    //                                print_mtx.unlock();
    //
    //                                u_tr = sequence_minus_factorial_n(u);
    //                                res = linear_shift(u_tr, oeis_values, oeis_keys, oeis_db_size);
    //                                print_mtx.lock();
    //                                std::cout << "linear_shift (sequence_plus_n) ended found " << res.size() << " results" << std::endl;
    //                                print(res, "linear_shift (sequence_plus_n)");
    //                                print_mtx.unlock(); }));

    for (unsigned int i = 0; i < pool.size(); i++)
        pool[i].join();
}