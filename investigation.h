#pragma once

#include <thread>
#include <mutex>
#include <map>

#include "transform.h"
#include "progress.h"

typedef std::vector<std::tuple<unsigned int, std::vector<fraction<def_t>>>> out_type;

std::mutex print_mtx;
void print(const std::string &title = "", const out_type &v = {}, const std::string &msg = "")
{
    print_mtx.lock();
    std::cout << title << " " << v.size() << " results" << std::endl;
    for (unsigned int i = 0; i < v.size(); i++)
    {
        std::cout << msg << "\t oeis code: " << std::get<0>(v[i]) << " values [";
        std::vector<fraction<def_t>> one = std::get<1>(v[i]);
        for (unsigned int j = 0; j < one.size(); j++)
            std::cout << one[j].print() << (j < one.size() - 1 ? " " : "]");
        std::cout << std::endl;
    }
    print_mtx.unlock();
}

out_type linear_shift(fraction<def_t> *u, fraction<def_t> **oeis_values, unsigned int *oeis_keys, const unsigned int &oeis_db_size, const std::string &name, progress *prog = nullptr)
{
    out_type ret;
    const def_t u_length = u->num();
    for (unsigned int i = 0; i < oeis_db_size; i++)
    {
        for (unsigned int shift = 0; shift < 10; shift++)
        {
            fraction<def_t> *o = *(oeis_values + i);
            if (o->num() < u_length + shift)
                continue;

            bool br = false;
            fraction<def_t> m_tmp = (*(u + 2) - *(u + 1)) / (*(o + 2 + shift) - *(o + 1 + shift));
            if (m_tmp.den() == 0)
                continue;

            for (unsigned int n = 3; n <= u_length && !br; n++)
            {
                fraction<def_t> m = (*(u + n) - *(u + 1)) / (*(o + n + shift) - *(o + 1 + shift));
                if (m_tmp != m)
                    br = true;
            }
            if (!br)
            {
                std::vector<fraction<def_t>> inner = {shift, m_tmp, *(u + 1) - m_tmp * *(o + 1 + shift)};
                ret.push_back(std::make_tuple(*(oeis_keys + i), inner));
            }
        }

        if (prog != nullptr && i % 1000 == 0)
            prog->set_value(name, (float)i / oeis_db_size * 100.0);
    }

    return ret;
}

out_type combination_linear_shift(fraction<def_t> *u, fraction<def_t> **oeis_values, unsigned int *oeis_keys, const unsigned int &oeis_db_size, const std::string &name, progress *prog = nullptr)
{
    out_type ret;
    const def_t u_length = u->num();
    unsigned int shift = 0;
    for (unsigned int i = 0; i < oeis_db_size; i++)
    {
        fraction<def_t> *oi = *(oeis_values + i);
        if (oi->num() < u_length)
            continue;

        for (unsigned int j = i + 1; j < oeis_db_size; j++)
        {
            fraction<def_t> *oj = *(oeis_values + j);
            if (oj->num() < u_length)
                continue;

            fraction<def_t> *o = create_sequence<def_t>(u_length);
            for (unsigned int k = 1; k < u_length; k++)
            {
                fraction<def_t> f = *(oi + k);
                f += *(oj + k);
                *(o + k) = f;
            }

            //// for (unsigned int shift = 0; shift < 1; shift++)
            ////{
            //// if (oi->num() < u_length + shift)
            ////    continue;

            bool br = false;
            fraction<def_t> m_tmp = (*(u + 2) - *(u + 1)) / (*(o + 2) - *(o + 1));  //memory leak!
            if (m_tmp.den() == 0)
                continue;

            for (unsigned int n = 3; n <= u_length && !br; n++)
            {
                fraction<def_t> m = (*(u + n) - *(u + 1)) / (*(o + n + shift) - *(o + 1 + shift));
                if (m_tmp != m)
                    br = true;
            }
            if (!br)
            {
                std::vector<fraction<def_t>> inner = {*(oeis_keys + j), shift, m_tmp, *(u + 1) - m_tmp * *(o + 1 + shift)};
                ret.push_back(std::make_tuple(*(oeis_keys + i), inner));
            }
            //}

            destroy_sequence(o);
        }

        if (prog != nullptr && i % 1000 == 0)
            prog->set_value(name, (float)i / oeis_db_size * 100.0);
    }

    return ret;
}

void investigation(fraction<def_t> *u, fraction<def_t> **oeis_values, unsigned int *oeis_keys, const unsigned int &oeis_db_size)
{
    progress *prog = new progress;
    std::vector<std::thread> pool;
    std::map<std::string, out_type> results;
    pool.push_back(std::thread([u, oeis_values, oeis_keys, oeis_db_size, prog, &results]()
                               {
                                   std::string name = "lnear";
                                   prog->set_name(name);
                                   prog->set_value(name, 0);
                                   out_type res = linear_shift(u, oeis_values, oeis_keys, oeis_db_size, name, prog);
                                   results["lnear"] = res; }));
    pool.push_back(std::thread([u, oeis_values, oeis_keys, oeis_db_size, prog, &results]()
                               {
                                    std::string name = "combi";
                                    prog->set_name(name);
                                    prog->set_value(name, 0);
                                    out_type res = combination_linear_shift(u, oeis_values, oeis_keys, oeis_db_size, name, prog);
                                    results["combi"] = res; }));

    pool.push_back(std::thread([u, oeis_values, oeis_keys, oeis_db_size, prog, &results]()
                               {
                                   std::string name = "l_fon";
                                   prog->set_name(name);
                                   prog->set_value(name, 0);
                                   fraction<def_t> *u_tr = factorial_over_n(u);
                                   out_type res = linear_shift(u_tr, oeis_values, oeis_keys, oeis_db_size, name, prog);
                                   results["l_fon"] = res; }));

    for (unsigned int i = 0; i < pool.size(); i++)
        pool[i].join();

    for (const auto &pair : results)
        print(pair.first, pair.second);
}