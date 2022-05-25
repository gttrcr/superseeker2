#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include <stdio.h>
#include <curl/curl.h>
#include <string>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>

#include "fraction.h"
#include "investigation.h"

inline bool oeis_db_exists(const std::string &path)
{
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

inline bool download_oeis_db(const std::string &path)
{
    std::cout << "downloading oeis db..." << std::endl;
    CURL *curl;
    FILE *fp;
    CURLcode res;
    std::string url = "http://oeis.org/stripped.gz";
    char outfilename[FILENAME_MAX] = "stripped.gz";
    char decompress[FILENAME_MAX] = "stripped";
    curl = curl_easy_init();
    if (curl)
    {
        fp = fopen(outfilename, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }

    if (res != CURLE_OK)
    {
        std::cout << "error downloading oeis db " << res << std::endl;
        return false;
    }

    std::cout << "download completed" << std::endl;

    std::cout << "decompressing oeis db..." << std::endl;
    std::ifstream file(outfilename, std::ios_base::in | std::ios_base::binary);
    boost::iostreams::filtering_streambuf<boost::iostreams::input> inbuf;
    inbuf.push(boost::iostreams::gzip_decompressor());
    inbuf.push(file);
    std::istream instream(&inbuf);
    std::ofstream f(path);
    f << instream.rdbuf();
    file.close();
    f.close();

    return true;
}

bool oeis_db(const std::string &path)
{
    if (!oeis_db_exists(path))
    {
        std::cout << "oeis db does not exists in " << path << std::endl;
        return download_oeis_db(path);
    }
    else
    {
        std::cout << "oeis db already exists but it may be out of date" << std::endl;
        std::cout << "download oeis db anyway? [yY/nN]" << std::endl;
        std::string choice;
        std::cin >> choice;
        if (choice == "y" || choice == "Y")
            return download_oeis_db(path);
    }

    return true;
}

void tokenize(const std::string str, const char delim, std::vector<std::string> &out)
{
    out.clear();
    std::stringstream ss(str);
    std::string s;
    while (std::getline(ss, s, delim))
        if (s != "")
            out.push_back(s);
}

unsigned int get_oeis_db_size(const std::string &path)
{
    unsigned int oeis_db_size = 0;
    std::ifstream input(path);
    std::vector<std::string> out;
    for (std::string line; getline(input, line);)
    {
        if (line[0] == '#')
            continue;
        oeis_db_size++;
    }
    input.close();

    return oeis_db_size;
}

bool load_oeis_db(const std::string &path, fraction<def_t> **oeis_values, unsigned int *oeis_keys, const unsigned int &oeis_db_size)
{
    unsigned int i = 0;
    unsigned int ok = 0;
    unsigned int ko = 0;
    std::ifstream input(path);
    std::vector<std::string> out;
    for (std::string line; getline(input, line);)
    {
        if (line[0] == '#')
            continue;

        if (i % 10000 == 0)
            std::cout << (float)i * 100.0 / oeis_db_size << "%" << std::endl;

        tokenize(line, ' ', out);
        *(oeis_keys + i) = std::stoi(out[0].substr(1));
        tokenize(out[1], ',', out);
        size_t s = out.size();

        unsigned int max_convertible_size = 0;
        try
        {
            for (; max_convertible_size < s; max_convertible_size++)
                fraction<def_t> f(out[max_convertible_size]);
        }
        catch (const std::exception)
        {
            ko += (s - max_convertible_size);
            ok += s;
        }

        *(oeis_values + i) = new fraction<def_t>[max_convertible_size + 1];
        fraction<def_t> sf(max_convertible_size);
        *(*(oeis_values + i) + 0) = sf;

        for (unsigned int k = 0; k < max_convertible_size; k++)
            *(*(oeis_values + i) + (k + 1)) = fraction<def_t>(out[k]);

        i++;
    }

    std::cout << "Errors " << (float)ko / (float)ok * 100.0 << std::endl;
    input.close();

    return true;
}

int main(int argc, char **argv)
{
    std::cout << "Started" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    std::string path = "stripped";
    if (!oeis_db(path))
        return -1;

    std::cout << "Loading db..." << std::endl;
    unsigned int oeis_db_size = get_oeis_db_size(path);
    fraction<def_t> **oeis_values = new fraction<def_t> *[oeis_db_size];
    unsigned int *oeis_keys = new unsigned int[oeis_db_size];
    if (!load_oeis_db(path, oeis_values, oeis_keys, oeis_db_size))
        return -1;

    auto end = std::chrono::high_resolution_clock::now();
    double time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Loaded in " << time_taken << " ms" << std::endl;

    unsigned int sequence_length = 10;
    fraction<def_t> *t = new fraction<def_t>[sequence_length + 1];
    *(t + 0) = fraction<def_t>(sequence_length);
    *(t + 1) = fraction<def_t>(1234 + 2);
    *(t + 2) = fraction<def_t>(1234 + 3);
    *(t + 3) = fraction<def_t>(1234 + 5);
    *(t + 4) = fraction<def_t>(1234 + 7);
    *(t + 5) = fraction<def_t>(1234 + 11);
    *(t + 6) = fraction<def_t>(1234 + 13);
    *(t + 7) = fraction<def_t>(1234 + 17);
    *(t + 8) = fraction<def_t>(1234 + 19);
    *(t + 9) = fraction<def_t>(1234 + 23);
    *(t + 10) = fraction<def_t>(1234 + 29);

    // fix constant sequence
    //*(t + 1) = fraction(1234);
    //*(t + 2) = fraction(1234);
    //*(t + 3) = fraction(1234);
    //*(t + 4) = fraction(1234);
    //*(t + 5) = fraction(1234);
    //*(t + 6) = fraction(1234);
    //*(t + 7) = fraction(1234);
    //*(t + 8) = fraction(1234);
    //*(t + 9) = fraction(1234);
    //*(t + 10) = fraction(1234);

    std::cout << "Investigating..." << std::endl;
    start = std::chrono::high_resolution_clock::now();
    investigation(t, oeis_values, oeis_keys, oeis_db_size);
    end = std::chrono::high_resolution_clock::now();
    time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "completed in " << time_taken << "ms" << std::endl;

    return 0;
}