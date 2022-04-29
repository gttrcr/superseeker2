#pragma once

#include <thread>
#include <tuple>

typedef long long int SEQ_T;

void set(SEQ_T **input, unsigned int seq, unsigned int pos, SEQ_T val)
{
    *(*(input + seq) + pos) = val;
}

SEQ_T get(SEQ_T **input, unsigned int seq, unsigned int pos)
{
    return *(*(input + seq) + pos);
}

SEQ_T get(SEQ_T *input, unsigned int pos)
{
    return *(input + pos);
}

SEQ_T get(SEQ_T *input, unsigned int pos, SEQ_T a, SEQ_T b, SEQ_T c, SEQ_T d, SEQ_T e)
{
    return a * pow(pow(b * get(input, pos), c) + d, e);
}

void set(unsigned int *input, unsigned int pos, unsigned int val)
{
    *(input + pos) = val;
}

void set(SEQ_T *input, unsigned int pos, SEQ_T val)
{
    *(input + pos) = val;
}

unsigned int get(unsigned int *input, unsigned int pos)
{
    return *(input + pos);
}

void print(SEQ_T **input, unsigned int seq)
{
    for (unsigned int i = 1; i <= get(input, seq, 0); i++)
        std::cout << get(input, seq, i) << " ";
}

void oeis_name(unsigned int *oeis_keys, const unsigned int oeis_index)
{
    std::string oeis_name = std::to_string(get(oeis_keys, oeis_index)).c_str();
    oeis_name.insert(oeis_name.begin(), 6 - oeis_name.size(), '0');
    oeis_name = "A" + oeis_name;
    std::cout << oeis_name;
}

std::vector<SEQ_T> u_times_b_test(SEQ_T *t, SEQ_T *u)
{
    SEQ_T a = 1;
    SEQ_T b = 1;
    SEQ_T c = 1;
    SEQ_T d = 0;
    SEQ_T e = 1;

    bool br = false;
    const unsigned int t_length = get(t, 0);
    SEQ_T b_tmp = get(t, 1) / get(u, 1, a, b, c, d, e);
    for (unsigned int n = 2; n < t_length && !br; n++)
    {
        b = get(t, n) / get(u, n, a, 1, c, d, e);
        if (b_tmp != b)
            br = true;
    }
    if (!br)
        return {a, b, c, d, e};

    return {};
}

std::vector<unsigned int> simple_search_result;
void simple_search(SEQ_T *t, SEQ_T **oeis_values, const unsigned int &oeis_db_s)
{
    std::cout << "simple search started" << std::endl;
    const SEQ_T t_length = get(t, 0);
    for (unsigned int i = 0; i < oeis_db_s; i++)
    {
        SEQ_T *u = *(oeis_values + i);
        if (get(u, 0) < t_length)
            continue;

        bool br = false;
        for (unsigned int k = 1; k <= t_length && !br; k++)
        {
            if (get(u, k) != get(t, k))
                br = true;
        }
        if (!br)
            simple_search_result.push_back(i);
    }
    std::cout << "simple search ended " << simple_search_result.size() << " results found" << std::endl;
}

std::vector<std::tuple<unsigned int, unsigned int>> sum_of_two_sequences_result;
void sum_of_two_sequences(SEQ_T *t, SEQ_T **oeis_values, const unsigned int &oeis_db_s)
{
    std::cout << "sum of two sequences started" << std::endl;
    const SEQ_T t_length = get(t, 0);
    for (unsigned int i1 = 0; i1 < oeis_db_s; i1++)
    {
        SEQ_T *u1 = *(oeis_values + i1);
        if (get(u1, 0) < t_length)
            continue;

        for (unsigned int i2 = i1; i2 < oeis_db_s; i2++)
        {
            SEQ_T *u2 = *(oeis_values + i2);
            if (get(u2, 0) < t_length)
                continue;

            bool br = false;
            for (unsigned int k = 1; k <= t_length && !br; k++)
            {
                if (get(u1, k) + get(u2, k) != get(t, k))
                    br = true;
            }
            if (!br)
                sum_of_two_sequences_result.push_back(std::make_tuple(i1, i2));
        }
    }
    std::cout << "sum of two sequences ended " << sum_of_two_sequences_result.size() << "pairs of sequences found" << std::endl;
}

std::vector<std::tuple<unsigned int, unsigned int>> product_of_two_sequences_result;
void product_of_two_sequences(SEQ_T *t, SEQ_T **oeis_values, const unsigned int &oeis_db_s)
{
    std::cout << "product of two sequences started" << std::endl;
    const SEQ_T t_length = get(t, 0);
    for (unsigned int i1 = 0; i1 < oeis_db_s; i1++)
    {
        SEQ_T *u1 = *(oeis_values + i1);
        if (get(u1, 0) < t_length)
            continue;

        for (unsigned int i2 = i1; i2 < oeis_db_s; i2++)
        {
            SEQ_T *u2 = *(oeis_values + i2);
            if (get(u2, 0) < t_length)
                continue;

            bool br = false;
            for (unsigned int k = 1; k <= t_length && !br; k++)
            {
                if (get(u1, k) * get(u2, k) != get(t, k))
                    br = true;
            }
            if (!br)
                product_of_two_sequences_result.push_back(std::make_tuple(i1, i2));
        }
    }
    std::cout << "product of two sequences ended " << product_of_two_sequences_result.size() << " pairs of sequences found" << std::endl;
}

std::vector<std::tuple<SEQ_T, SEQ_T, SEQ_T, SEQ_T, SEQ_T, unsigned int>> u_plus_d_result;
void u_plus_d(SEQ_T *t, SEQ_T **oeis_values, const unsigned int &oeis_db_s)
{
    std::cout << "u plus d started" << std::endl;
    const SEQ_T t_length = get(t, 0);
    for (unsigned int i = 0; i < oeis_db_s; i++)
    {
        SEQ_T *u = *(oeis_values + i);
        if (get(u, 0) < t_length)
            continue;

        SEQ_T a = 1;
        SEQ_T b = 1;
        SEQ_T c = 1;
        SEQ_T d = 0;
        SEQ_T e = 1;

        bool br = false;
        const unsigned int t_length = get(t, 0);
        SEQ_T d_tmp = get(t, 1) - get(u, 1, a, b, c, d, e);
        for (unsigned int n = 2; n < t_length && !br; n++)
        {
            d = get(t, n) - get(u, n, a, b, c, 0, e);
            if (d_tmp != d)
                br = true;
        }
        if (!br)
            u_plus_d_result.push_back(std::make_tuple(a, b, c, d, e, i));
    }

    std::cout << "u plus d ended " << u_plus_d_result.size() << " sequences found" << std::endl;
}

void investigation(SEQ_T *t, SEQ_T **oeis_values, const unsigned int &oeis_db_s)
{
    std::vector<std::thread> pool;
    pool.push_back(std::thread(simple_search, t, oeis_values, oeis_db_s));
    pool.push_back(std::thread(sum_of_two_sequences, t, oeis_values, oeis_db_s));
    pool.push_back(std::thread(product_of_two_sequences, t, oeis_values, oeis_db_s));
    pool.push_back(std::thread(u_plus_d, t, oeis_values, oeis_db_s));
    //pool.push_back(std::thread(u_times_b, t, oeis_values, oeis_db_s));

    for (unsigned int i = 0; i < pool.size(); i++)
        pool[i].join();

    //
    // for (unsigned int i = 0; i < oeis_db_s; i++)
    //{
    //    SEQ_T *u = *(oeis_values + i);
    //    if (get(u, 0) < t_length)
    //        continue;
    //
    //    std::vector<SEQ_T> test_ret = u_times_b_test(t, u);
    //    if (test_ret.size() != 0)
    //    {
    //        oeis_indexes.push_back(i);
    //        ret.push_back(test_ret);
    //    }
    //}
}