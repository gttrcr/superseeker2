#pragma once

#include <thread>
#include <mutex>
#include <map>

#include "utils.h"

std::vector<unsigned int> simple_search_test(fraction *t, fraction **oeis_values, unsigned int *oeis_keys, const unsigned int &oeis_db_size)
{
    std::vector<unsigned int> ret;
    const BigInt t_length = (t + 0)->num();
    for (unsigned int i = 0; i < oeis_db_size; i++)
    {
        fraction *u = *(oeis_values + i);
        if ((u + 0)->num() < t_length)
            continue;

        bool br = false;
        for (unsigned int k = 1; k <= t_length && !br; k++)
        {
            if (*(u + k) != (*(t + k)))
                br = true;
        }
        if (!br)
            ret.push_back(*(oeis_keys + i));
    }

    return ret;
}

// std::vector<std::tuple<unsigned int, unsigned int>> sum_of_two_sequences_result;
// void sum_of_two_sequences(SEQ_INT *t, SEQ_INT **oeis_values, const unsigned int &oeis_db_s)
//{
//     std::cout << "sum of two sequences started" << std::endl;
//     const SEQ_INT t_length = get(t, 0);
//     for (unsigned int i1 = 0; i1 < oeis_db_s; i1++)
//     {
//         SEQ_INT *u1 = *(oeis_values + i1);
//         if (get(u1, 0) < t_length)
//             continue;
//
//         for (unsigned int i2 = i1; i2 < oeis_db_s; i2++)
//         {
//             SEQ_INT *u2 = *(oeis_values + i2);
//             if (get(u2, 0) < t_length)
//                 continue;
//
//             bool br = false;
//             for (unsigned int k = 1; k <= t_length && !br; k++)
//             {
//                 if (get(u1, k) + get(u2, k) != get(t, k))
//                     br = true;
//             }
//             if (!br)
//                 sum_of_two_sequences_result.push_back(std::make_tuple(i1, i2));
//         }
//     }
//     std::cout << "sum of two sequences ended " << sum_of_two_sequences_result.size() << "pairs of sequences found" << std::endl;
// }
//
// std::vector<std::tuple<unsigned int, unsigned int>> product_of_two_sequences_result;
// void product_of_two_sequences(SEQ_INT *t, SEQ_INT **oeis_values, const unsigned int &oeis_db_s)
//{
//     std::cout << "product of two sequences started" << std::endl;
//     const SEQ_INT t_length = get(t, 0);
//     for (unsigned int i1 = 0; i1 < oeis_db_s; i1++)
//     {
//         SEQ_INT *u1 = *(oeis_values + i1);
//         if (get(u1, 0) < t_length)
//             continue;
//
//         for (unsigned int i2 = i1; i2 < oeis_db_s; i2++)
//         {
//             SEQ_INT *u2 = *(oeis_values + i2);
//             if (get(u2, 0) < t_length)
//                 continue;
//
//             bool br = false;
//             for (unsigned int k = 1; k <= t_length && !br; k++)
//             {
//                 if (get(u1, k) * get(u2, k) != get(t, k))
//                     br = true;
//             }
//             if (!br)
//                 product_of_two_sequences_result.push_back(std::make_tuple(i1, i2));
//         }
//     }
//     std::cout << "product of two sequences ended " << product_of_two_sequences_result.size() << " pairs of sequences found" << std::endl;
// }

std::map<unsigned int, fraction> u_plus_d_test(fraction *t, fraction **oeis_values, unsigned int *oeis_keys, const unsigned int &oeis_db_size)
{
    std::map<unsigned int, fraction> ret;
    const BigInt t_length = (t + 0)->num();
    for (unsigned int i = 0; i < oeis_db_size; i++)
    {
        fraction *u = *(oeis_values + i);
        if ((u + 0)->num() < t_length)
            continue;

        bool br = false;
        fraction d_tmp = *(t + 1) - *(u + 1);
        for (unsigned int n = 2; n <= t_length && !br; n++)
        {
            fraction d = *(t + n) - *(u + n);
            if (d_tmp != d)
                br = true;
        }
        if (!br)
            ret[*(oeis_keys + i)] = d_tmp;
    }

    return ret;
}

std::map<unsigned int, fraction> u_times_b_test(fraction *t, fraction **oeis_values, unsigned int *oeis_keys, const unsigned int &oeis_db_size)
{
    std::map<unsigned int, fraction> ret;
    const BigInt t_length = (t + 0)->num();
    for (unsigned int i = 0; i < oeis_db_size; i++)
    {
        fraction *u = *(oeis_values + i);
        if ((u + 0)->num() < t_length)
            continue;

        bool br = false;
        if (*(u + 1) == 0)
            continue;

        fraction b_tmp = *(t + 1) / *(u + 1);
        for (unsigned int n = 2; n < t_length && !br; n++)
        {
            if (*(u + n) == 0)
                br = true;
            fraction b = *(t + n) / *(u + n);
            if (b_tmp != b)
                br = true;
        }
        if (!br)
            ret[*(oeis_keys + i)] = b_tmp;
    }

    return ret;
}

std::mutex print_mtx;
void print_results(std::vector<unsigned int> &res, const std::string &title = "")
{
    print_mtx.lock();
    for (unsigned int i = 0; i < res.size(); i++)
        std::cout << title << ": seq " << res[i] << std::endl;
    print_mtx.unlock();
}

void print_results(std::map<unsigned int, fraction> &res, const std::string &title = "")
{
    print_mtx.lock();
    for (const auto &pair : res)
        std::cout << title << ": seq " << pair.first << " d=" << pair.second.print() << std::endl;
    print_mtx.unlock();
}

enum tests
{
    simple_search,
    u_plus_d,
};

void investigation(fraction *t, fraction **oeis_values, unsigned int *oeis_keys, const unsigned int &oeis_db_size, std::vector<tests> filter_by_tests = {})
{
    std::vector<std::thread> pool;
    pool.push_back(std::thread([t, oeis_values, oeis_keys, oeis_db_size]()
                               {
                                   std::cout<<"simple_search started"<<std::endl;
                                   std::vector<unsigned int> res = simple_search_test(t, oeis_values, oeis_keys, oeis_db_size);
                                   std::cout<<"simple_search ended. Found "<<res.size()<<" results"<<std::endl;
                                   print_results(res, "simple_search"); }));
    pool.push_back(std::thread([t, oeis_values, oeis_keys, oeis_db_size]()
                               {
                                   std::cout<<"u_plus_d started"<<std::endl;
                                   std::map<unsigned int, fraction> res = u_plus_d_test(t, oeis_values, oeis_keys, oeis_db_size);
                                   std::cout<<"u_plus_d ended. Found "<<res.size()<<" results"<<std::endl;
                                   print_results(res, "u_plus_d"); }));
    pool.push_back(std::thread([t, oeis_values, oeis_keys, oeis_db_size]()
                               {
                                   std::cout<<"u_times_b started"<<std::endl;
                                   std::map<unsigned int, fraction> res = u_times_b_test(t, oeis_values, oeis_keys, oeis_db_size);
                                   std::cout<<"u_times_b ended. Found "<<res.size()<<" results"<<std::endl;
                                   print_results(res, "u_times_b"); }));

    for (unsigned int i = 0; i < pool.size(); i++)
        pool[i].join();
}