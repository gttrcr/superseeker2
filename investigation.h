#pragma once

#include <thread>
#include <future>
#include <map>

std::vector<unsigned int> simple_search_test(fraction *t, fraction **oeis_values, const unsigned int &oeis_db_size)
{
    std::vector<unsigned int> ret;
    BigInt t_length = (t + 0)->num();
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
            ret.push_back(i);
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

std::map<unsigned int, fraction> u_plus_d_test(fraction *t, fraction **oeis_values, const unsigned int &oeis_db_size)
{
    std::map<unsigned int, fraction> ret;
    BigInt t_length = (t + 0)->num();
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
            ret[i] = d_tmp;
    }

    return ret;
}

// std::vector<std::tuple<SEQ_INT, SEQ_F, SEQ_INT, SEQ_INT, SEQ_INT, unsigned int>> u_times_b_result;
// void u_times_b(SEQ_INT *t, SEQ_INT **oeis_values, const unsigned int &oeis_db_s)
//{
//     std::cout << "u times b started" << std::endl;
//     const SEQ_INT t_length = get(t, 0);
//     for (unsigned int i = 0; i < oeis_db_s; i++)
//     {
//         SEQ_INT *u = *(oeis_values + i);
//         if (get(u, 0) < t_length)
//             continue;
//
//         SEQ_INT a = 1;
//         SEQ_F b = 1;
//         SEQ_INT c = 1;
//         SEQ_INT d = 0;
//         SEQ_INT e = 1;
//
//         bool br = false;
//         if (get(u, 1, a, b, c, d, e) == 0)
//             continue;
//         const unsigned int t_length = get(t, 0);
//         SEQ_F b_tmp = get(t, 1) / get(u, 1, a, b, c, d, e);
//         for (unsigned int n = 2; n < t_length && !br; n++)
//         {
//             if (get(u, n, a, 1, c, d, e) == 0)
//                 br = true;
//             b = (SEQ_F)get(t, n) / (SEQ_F)get(u, n, a, 1, c, d, e);
//             if (b != 0)
//             {
//                 if (b_tmp != b)
//                     br = true;
//             }
//         }
//         if (!br)
//             u_times_b_result.push_back(std::make_tuple(a, b, c, d, e, i));
//     }
//
//     std::cout << "u times b ended " << u_times_b_result.size() << " sequences found" << std::endl;
// }
//
//   std::vector<std::tuple<SEQ_INT, SEQ_F, SEQ_INT, SEQ_INT, SEQ_INT, unsigned int>> u_times_b_plus_d_result;
//   void u_times_b_plus_d(SEQ_INT *t, SEQ_INT **oeis_values, const unsigned int &oeis_db_s)
//{
//       std::cout << "u time b plus d started" << std::endl;
//       const SEQ_INT t_length = get(t, 0);
//       for (unsigned int i = 0; i < oeis_db_s; i++)
//       {
//           SEQ_INT *u = *(oeis_values + i);
//           if (get(u, 0) < t_length)
//               continue;
//
//           SEQ_INT a = 1;
//           SEQ_F b = 1;
//           SEQ_INT c = 1;
//           SEQ_INT d = 0;
//           SEQ_INT e = 1;
//
//           bool br = false;
//           if (get(u, 1, a, b, c, d, e) == 0)
//               continue;
//           const unsigned int t_length = get(t, 0);
//           SEQ_F b_tmp = get(t, 1) / get(u, 1, a, b, c, d, e);
//           for (unsigned int n = 2; n < t_length && !br; n++)
//           {
//               if (get(u, n, a, 1, c, d, e) == 0)
//                   br = true;
//               b = (SEQ_F)get(t, n) / (SEQ_F)get(u, n, a, 1, c, d, e);
//               if (b != 0)
//               {
//                   if (b_tmp != b)
//                       br = true;
//               }
//           }
//           if (!br)
//               u_times_b_plus_d_result.push_back(std::make_tuple(a, b, c, d, e, i));
//       }
//
//       std::cout << "u time b plus d started " << u_times_b_plus_d_result.size() << " sequences found" << std::endl;
//   }

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
    std::cout << res.at(0).print() << std::endl;
    for (unsigned int i = 0; i < res.size(); i++)
        if (res.find(i) != res.end())
            std::cout << title << ": seq " << i << " d=" << res[i].print() << std::endl;
    print_mtx.unlock();
}

enum tests
{
    simple_search,
    u_plus_d,
};

void investigation(fraction *t, fraction **oeis_values, const unsigned int &oeis_db_size, std::vector<tests> filter_by_tests = {})
{
    std::vector<std::thread> pool;
    pool.push_back(std::thread([t, oeis_values, oeis_db_size]()
                               {
                                   std::cout<<"simple_search started"<<std::endl;
                                   std::vector<unsigned int> res = simple_search_test(t, oeis_values, oeis_db_size);
                                   std::cout<<"simple_search ended. Found "<<res.size()<<" results"<<std::endl;
                                   print_results(res, "simple_search"); }));
    pool.push_back(std::thread([t, oeis_values, oeis_db_size]()
                               {
                                   std::cout<<"u_plus_d started"<<std::endl;
                                   std::map<unsigned int, fraction> res = u_plus_d_test(t, oeis_values, oeis_db_size);
                                   std::cout<<"u_plus_d ended. Found "<<res.size()<<" results"<<std::endl;
                                   print_results(res, "u_plus_d"); }));

    for (unsigned int i = 0; i < pool.size(); i++)
        pool[i].join();
}