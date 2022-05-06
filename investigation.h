#pragma once

#include <thread>
#include <mutex>
#include <map>

#include "transform.h"

typedef std::vector<std::tuple<unsigned int, std::vector<fraction>>> out_type;

out_type simple_search_test(fraction *t, fraction **oeis_values, unsigned int *oeis_keys, const unsigned int &oeis_db_size)
{
    out_type ret;
    for (int indx = 0; indx < oeis_db_size; ++indx)
        delete oeis_values[indx];
    delete[] oeis_values;

    // const BigInt t_length = (t + 0)->num();
    // for (unsigned int i = 0; i < oeis_db_size; i++)
    //{
    //     fraction *u = *(oeis_values + i);
    //     if ((u + 0)->num() < t_length)
    //         continue;
    //
    //    bool br = false;
    //    for (unsigned int k = 1; k <= t_length && !br; k++)
    //    {
    //        if (*(u + k) != (*(t + k)))
    //            br = true;
    //    }
    //    if (!br)
    //    {
    //        std::vector<fraction> inner = {fraction(1)};
    //        ret.push_back(std::make_tuple(*(oeis_keys + i), inner));
    //    }
    //}

    return ret;
}
//
//// std::vector<std::tuple<unsigned int, unsigned int>> sum_of_two_sequences_result;
//// void sum_of_two_sequences(SEQ_INT *t, SEQ_INT **oeis_values, const unsigned int &oeis_db_s)
////{
////     std::cout << "sum of two sequences started" << std::endl;
////     const SEQ_INT t_length = get(t, 0);
////     for (unsigned int i1 = 0; i1 < oeis_db_s; i1++)
////     {
////         SEQ_INT *u1 = *(oeis_values + i1);
////         if (get(u1, 0) < t_length)
////             continue;
////
////         for (unsigned int i2 = i1; i2 < oeis_db_s; i2++)
////         {
////             SEQ_INT *u2 = *(oeis_values + i2);
////             if (get(u2, 0) < t_length)
////                 continue;
////
////             bool br = false;
////             for (unsigned int k = 1; k <= t_length && !br; k++)
////             {
////                 if (get(u1, k) + get(u2, k) != get(t, k))
////                     br = true;
////             }
////             if (!br)
////                 sum_of_two_sequences_result.push_back(std::make_tuple(i1, i2));
////         }
////     }
////     std::cout << "sum of two sequences ended " << sum_of_two_sequences_result.size() << "pairs of sequences found" << std::endl;
//// }
////
//// std::vector<std::tuple<unsigned int, unsigned int>> product_of_two_sequences_result;
//// void product_of_two_sequences(SEQ_INT *t, SEQ_INT **oeis_values, const unsigned int &oeis_db_s)
////{
////     std::cout << "product of two sequences started" << std::endl;
////     const SEQ_INT t_length = get(t, 0);
////     for (unsigned int i1 = 0; i1 < oeis_db_s; i1++)
////     {
////         SEQ_INT *u1 = *(oeis_values + i1);
////         if (get(u1, 0) < t_length)
////             continue;
////
////         for (unsigned int i2 = i1; i2 < oeis_db_s; i2++)
////         {
////             SEQ_INT *u2 = *(oeis_values + i2);
////             if (get(u2, 0) < t_length)
////                 continue;
////
////             bool br = false;
////             for (unsigned int k = 1; k <= t_length && !br; k++)
////             {
////                 if (get(u1, k) * get(u2, k) != get(t, k))
////                     br = true;
////             }
////             if (!br)
////                 product_of_two_sequences_result.push_back(std::make_tuple(i1, i2));
////         }
////     }
////     std::cout << "product of two sequences ended " << product_of_two_sequences_result.size() << " pairs of sequences found" << std::endl;
//// }
//
// out_type u_plus_d_test(fraction *t, fraction **oeis_values, unsigned int *oeis_keys, const unsigned int &oeis_db_size)
//{
//    out_type ret;
//    const BigInt t_length = (t + 0)->num();
//    for (unsigned int i = 0; i < oeis_db_size; i++)
//    {
//        fraction *u = *(oeis_values + i);
//        if ((u + 0)->num() < t_length)
//            continue;
//
//        bool br = false;
//        fraction d_tmp = *(t + 1) - *(u + 1);
//        for (unsigned int n = 2; n <= t_length && !br; n++)
//        {
//            fraction d = *(t + n) - *(u + n);
//            if (d_tmp != d)
//                br = true;
//        }
//        if (!br)
//        {
//            std::vector<fraction> inner = {d_tmp};
//            ret.push_back(std::make_tuple(*(oeis_keys + i), inner));
//        }
//    }
//
//    return ret;
//}
//
// out_type u_times_b_test(fraction *t, fraction **oeis_values, unsigned int *oeis_keys, const unsigned int &oeis_db_size)
//{
//    out_type ret;
//    const BigInt t_length = (t + 0)->num();
//    for (unsigned int i = 0; i < oeis_db_size; i++)
//    {
//        fraction *u = *(oeis_values + i);
//        if ((u + 0)->num() < t_length)
//            continue;
//
//        bool br = false;
//        if (*(u + 1) == 0)
//            continue;
//
//        fraction b_tmp = *(t + 1) / *(u + 1);
//        for (unsigned int n = 2; n < t_length && !br; n++)
//        {
//            if (*(u + n) == 0)
//                br = true;
//            fraction b = *(t + n) / *(u + n);
//            if (b_tmp != b)
//                br = true;
//        }
//        if (!br)
//        {
//            std::vector<fraction> inner = {b_tmp};
//            ret.push_back(std::make_tuple(*(oeis_keys + i), inner));
//        }
//    }
//
//    return ret;
//}

out_type linear(fraction *u, fraction **oeis_values, unsigned int *oeis_keys, const unsigned int &oeis_db_size)
{
    out_type ret;
    const BigInt u_length = u->num();
    for (unsigned int i = 0; i < oeis_db_size; i++)
    {
        fraction *o = *(oeis_values + i);
        if (o->num() < u_length)
            continue;

        bool br = false;
        fraction m_tmp = (*(u + 2) - *(u + 1)) / (*(o + 2) - *(o + 1));
        for (unsigned int n = 3; n <= u_length && !br; n++)
        {
            fraction m = (*(u + n) - *(u + 1)) / (*(o + n) - *(o + 1));
            if (m_tmp != m)
                br = true;
        }
        if (!br)
        {
            std::vector<fraction> inner = {m_tmp, *(u + 1) - m_tmp * *(o + 1)};
            ret.push_back(std::make_tuple(*(oeis_keys + i), inner));
        }
    }

    return ret;
}

out_type linear_shift(fraction *u, fraction **oeis_values, unsigned int *oeis_keys, const unsigned int &oeis_db_size)
{
    out_type ret;
    const BigInt u_length = u->num();
    for (unsigned int i = 0; i < oeis_db_size; i++)
    {
        for (unsigned int shift = 0; shift < 2; shift++)
        {
            fraction *o = *(oeis_values + i);
            if (o->num() < u_length + shift)
                continue;

            bool br = false;
            fraction m_tmp = (*(u + 2) - *(u + 1)) / (*(o + 2 + shift) - *(o + 1 + shift));
            for (unsigned int n = 3; n <= u_length && !br; n++)
            {
                fraction m = (*(u + n) - *(u + 1)) / (*(o + n + shift) - *(o + 1 + shift));
                if (m_tmp != m)
                    br = true;
            }
            if (!br)
            {
                std::vector<fraction> inner = {shift, m_tmp, *(u + 1) - m_tmp * *(o + 1 + shift)};
                ret.push_back(std::make_tuple(*(oeis_keys + i), inner));
            }
        }
    }

    return ret;
}

std::mutex print_mtx;
void print(out_type &v, const std::string &title = "")
{
    for (unsigned int i = 0; i < v.size(); i++)
    {
        std::cout << title << " " << std::get<0>(v[i]) << " ";
        std::vector<fraction> one = std::get<1>(v[i]);
        for (unsigned int j = 0; j < one.size(); j++)
            std::cout << one[j].print() << " ";
        std::cout << std::endl;
    }
}

enum tests
{
    simple_search,
    u_plus_d,
};

void investigation(fraction *u, fraction **oeis_values, unsigned int *oeis_keys, const unsigned int &oeis_db_size, std::vector<tests> filter_by_tests = {})
{
    std::vector<std::thread> pool;
    // pool.push_back(std::thread([t, oeis_values, oeis_keys, oeis_db_size]()
    //                            {
    //                                 out_type res = simple_search_test(t, oeis_values, oeis_keys, oeis_db_size);
    //                                 print_mtx.lock();
    //                                  std::cout<<"simple_search_test found "<<res.size()<<" results"<<std::endl;
    //                                  //print(res, "simple_search_test");
    //                                  print_mtx.unlock(); }));
    //  pool.push_back(std::thread([t, oeis_values, oeis_keys, oeis_db_size]()
    //                             {
    //                                 out_type res = u_plus_d_test(t, oeis_values, oeis_keys, oeis_db_size);
    //                                 print_mtx.lock();
    //                                 std::cout<<"u_plus_d_test ended found "<<res.size()<<" results"<<std::endl;
    //                                 //print(res, "u_plus_d_test");
    //                                 print_mtx.unlock(); }));
    //  pool.push_back(std::thread([t, oeis_values, oeis_keys, oeis_db_size]()
    //                             {
    //                                 out_type res = u_times_b_test(t, oeis_values, oeis_keys, oeis_db_size);
    //                                 print_mtx.lock();
    //                                 std::cout<<"u_times_b_test ended found "<<res.size()<<" results"<<std::endl;
    //                                 //print(res, "u_times_b_test");
    //                                 print_mtx.unlock(); }));
    // pool.push_back(std::thread([t, oeis_values, oeis_keys, oeis_db_size]()
    //                           {
    //                               out_type res = linear(t, oeis_values, oeis_keys, oeis_db_size);
    //                               print_mtx.lock();
    //                                std::cout << "linear ended found " << res.size() << " results" << std::endl;
    //                                print(res, "linear");
    //                                print_mtx.unlock(); }));
    pool.push_back(std::thread([u, oeis_values, oeis_keys, oeis_db_size]()
                               {
                                   out_type res = linear_shift(u, oeis_values, oeis_keys, oeis_db_size);
                                   print_mtx.lock();
                                   std::cout << "linear_shift ended found " << res.size() << " results" << std::endl;
                                   print(res, "linear_shift");
                                   print_mtx.unlock();
                                   
                                   fraction*  u_tr = factorial_over_n(u);
                                   res = linear_shift(u_tr, oeis_values, oeis_keys, oeis_db_size);
                                   print_mtx.lock();
                                   std::cout << "linear_shift (factorial_over_n) ended found " << res.size() << " results" << std::endl;
                                   print(res, "linear_shift (factorial_over_n)");
                                   print_mtx.unlock(); }));
    pool.push_back(std::thread([u, oeis_values, oeis_keys, oeis_db_size]()
                               {
                                   fraction* u_tr = sequence_minus_n(u);
                                   out_type res = linear_shift(u_tr, oeis_values, oeis_keys, oeis_db_size);
                                   print_mtx.lock();
                                   std::cout << "linear_shift (sequence_minus_n) ended found " << res.size() << " results" << std::endl;
                                   print(res, "linear_shift (sequence_minus_n)");
                                   print_mtx.unlock();
                                   
                                   u_tr = sequence_minus_factorial_n(u);
                                   res = linear_shift(u_tr, oeis_values, oeis_keys, oeis_db_size);
                                   print_mtx.lock();
                                   std::cout << "linear_shift (sequence_plus_n) ended found " << res.size() << " results" << std::endl;
                                   print(res, "linear_shift (sequence_plus_n)");
                                   print_mtx.unlock(); }));

    for (unsigned int i = 0; i < pool.size(); i++)
        pool[i].join();
}