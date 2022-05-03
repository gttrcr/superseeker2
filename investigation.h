#pragma once

#include <thread>
#include <tuple>

void set(SEQ_INT **input, unsigned int seq, unsigned int pos, SEQ_INT val)
{
    *(*(input + seq) + pos) = val;
}

SEQ_INT get(SEQ_INT **input, unsigned int seq, unsigned int pos)
{
    return *(*(input + seq) + pos);
}

SEQ_INT get(SEQ_INT *input, unsigned int pos)
{
    return *(input + pos);
}

SEQ_INT get(SEQ_INT *input, unsigned int pos, SEQ_INT a, SEQ_F b, SEQ_INT c, SEQ_INT d, SEQ_INT e)
{
    return a * pow(pow(b * get(input, pos), c) + d, e);
}

void set(unsigned int *input, unsigned int pos, unsigned int val)
{
    *(input + pos) = val;
}

void set(SEQ_INT *input, unsigned int pos, SEQ_INT val)
{
    *(input + pos) = val;
}

unsigned int get(unsigned int *input, unsigned int pos)
{
    return *(input + pos);
}

void print(SEQ_INT **input, unsigned int seq)
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

std::vector<unsigned int> simple_search_result;
void simple_search(SEQ_INT *t, SEQ_INT **oeis_values, const unsigned int &oeis_db_s)
{
    std::cout << "simple search started" << std::endl;
    const SEQ_INT t_length = get(t, 0);
    for (unsigned int i = 0; i < oeis_db_s; i++)
    {
        SEQ_INT *u = *(oeis_values + i);
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
void sum_of_two_sequences(SEQ_INT *t, SEQ_INT **oeis_values, const unsigned int &oeis_db_s)
{
    std::cout << "sum of two sequences started" << std::endl;
    const SEQ_INT t_length = get(t, 0);
    for (unsigned int i1 = 0; i1 < oeis_db_s; i1++)
    {
        SEQ_INT *u1 = *(oeis_values + i1);
        if (get(u1, 0) < t_length)
            continue;

        for (unsigned int i2 = i1; i2 < oeis_db_s; i2++)
        {
            SEQ_INT *u2 = *(oeis_values + i2);
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
void product_of_two_sequences(SEQ_INT *t, SEQ_INT **oeis_values, const unsigned int &oeis_db_s)
{
    std::cout << "product of two sequences started" << std::endl;
    const SEQ_INT t_length = get(t, 0);
    for (unsigned int i1 = 0; i1 < oeis_db_s; i1++)
    {
        SEQ_INT *u1 = *(oeis_values + i1);
        if (get(u1, 0) < t_length)
            continue;

        for (unsigned int i2 = i1; i2 < oeis_db_s; i2++)
        {
            SEQ_INT *u2 = *(oeis_values + i2);
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

std::vector<std::tuple<SEQ_INT, SEQ_F, SEQ_INT, SEQ_INT, SEQ_INT, unsigned int>> u_plus_d_result;
void u_plus_d(SEQ_INT *t, SEQ_INT **oeis_values, const unsigned int &oeis_db_s)
{
    std::cout << "u plus d started" << std::endl;
    const SEQ_INT t_length = get(t, 0);
    for (unsigned int i = 0; i < oeis_db_s; i++)
    {
        SEQ_INT *u = *(oeis_values + i);
        if (get(u, 0) < t_length)
            continue;

        SEQ_INT a = 1;
        SEQ_F b = 1;
        SEQ_INT c = 1;
        SEQ_INT d = 0;
        SEQ_INT e = 1;

        bool br = false;
        const unsigned int t_length = get(t, 0);
        SEQ_INT d_tmp = get(t, 1) - get(u, 1, a, b, c, d, e);
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

std::vector<std::tuple<SEQ_INT, SEQ_F, SEQ_INT, SEQ_INT, SEQ_INT, unsigned int>> u_times_b_result;
void u_times_b(SEQ_INT *t, SEQ_INT **oeis_values, const unsigned int &oeis_db_s)
{
    std::cout << "u times b started" << std::endl;
    const SEQ_INT t_length = get(t, 0);
    for (unsigned int i = 0; i < oeis_db_s; i++)
    {
        SEQ_INT *u = *(oeis_values + i);
        if (get(u, 0) < t_length)
            continue;

        SEQ_INT a = 1;
        SEQ_F b = 1;
        SEQ_INT c = 1;
        SEQ_INT d = 0;
        SEQ_INT e = 1;

        bool br = false;
        if (get(u, 1, a, b, c, d, e) == 0)
            continue;
        const unsigned int t_length = get(t, 0);
        SEQ_F b_tmp = get(t, 1) / get(u, 1, a, b, c, d, e);
        for (unsigned int n = 2; n < t_length && !br; n++)
        {
            if (get(u, n, a, 1, c, d, e) == 0)
                br = true;
            b = (SEQ_F)get(t, n) / (SEQ_F)get(u, n, a, 1, c, d, e);
            if (b != 0)
            {
                if (b_tmp != b)
                    br = true;
            }
        }
        if (!br)
            u_times_b_result.push_back(std::make_tuple(a, b, c, d, e, i));
    }

    std::cout << "u times b ended " << u_times_b_result.size() << " sequences found" << std::endl;
}

std::vector<std::tuple<SEQ_INT, SEQ_F, SEQ_INT, SEQ_INT, SEQ_INT, unsigned int>> u_times_b_plus_d_result;
void u_times_b_plus_d(SEQ_INT *t, SEQ_INT **oeis_values, const unsigned int &oeis_db_s)
{
    std::cout << "u time b plus d started" << std::endl;
    const SEQ_INT t_length = get(t, 0);
    for (unsigned int i = 0; i < oeis_db_s; i++)
    {
        SEQ_INT *u = *(oeis_values + i);
        if (get(u, 0) < t_length)
            continue;

        SEQ_INT a = 1;
        SEQ_F b = 1;
        SEQ_INT c = 1;
        SEQ_INT d = 0;
        SEQ_INT e = 1;

        bool br = false;
        if (get(u, 1, a, b, c, d, e) == 0)
            continue;
        const unsigned int t_length = get(t, 0);
        SEQ_F b_tmp = get(t, 1) / get(u, 1, a, b, c, d, e);
        for (unsigned int n = 2; n < t_length && !br; n++)
        {
            if (get(u, n, a, 1, c, d, e) == 0)
                br = true;
            b = (SEQ_F)get(t, n) / (SEQ_F)get(u, n, a, 1, c, d, e);
            if (b != 0)
            {
                if (b_tmp != b)
                    br = true;
            }
        }
        if (!br)
            u_times_b_plus_d_result.push_back(std::make_tuple(a, b, c, d, e, i));
    }

    std::cout << "u time b plus d started " << u_times_b_plus_d_result.size() << " sequences found" << std::endl;
}

void investigation(SEQ_INT *t, SEQ_INT **oeis_values, const unsigned int &oeis_db_s)
{
    std::vector<std::thread> pool;
    pool.push_back(std::thread(simple_search, t, oeis_values, oeis_db_s));
    pool.push_back(std::thread(u_plus_d, t, oeis_values, oeis_db_s));
    pool.push_back(std::thread(u_times_b, t, oeis_values, oeis_db_s));
    pool.push_back(std::thread(u_times_b_plus_d, t, oeis_values, oeis_db_s));

    // pool.push_back(std::thread(product_of_two_sequences, t, oeis_values, oeis_db_s));
    // pool.push_back(std::thread(sum_of_two_sequences, t, oeis_values, oeis_db_s));

    for (unsigned int i = 0; i < pool.size(); i++)
        pool[i].join();
}