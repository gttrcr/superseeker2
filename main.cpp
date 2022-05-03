#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include <math.h>

#include "sequence.h"
#include "investigation.h"

inline bool oeis_db_exists(const std::string &path)
{
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

inline bool download_oeis_db(const std::string &path)
{
    return true;
}

bool oeis_db(const std::string &path)
{
    if (!oeis_db_exists(path))
    {
        std::cout << "oeis db does not exists in " << path << std::endl;
        std::cout << "downloading oeis db..." << std::endl;
        if (!download_oeis_db(path))
        {
            std::cout << "error downloading oeis db" << std::endl;
            return false;
        }
        else
            std::cout << "download completed" << std::endl;
    }
    else
    {
        std::cout << "oeis db already exists but it may be out of date" << std::endl;
        std::cout << "download oeis db anyway? [yY/nN]" << std::endl;
        std::string choice;
        std::cin >> choice;
        if (choice == "y" || choice == "Y")
        {
            std::cout << "downloading oeis db..." << std::endl;
            if (!download_oeis_db(path))
            {
                std::cout << "error downloading oeis db" << std::endl;
                return false;
            }
            else
                std::cout << "download completed" << std::endl;
        }
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

unsigned int oeis_db_size(const std::string &path)
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

bool load_oeis_db(const std::string &path, sequence *oeis_values, sequence &oeis_keys)
{
    unsigned int i = 0;
    std::ifstream input(path);
    std::vector<std::string> out;
    for (std::string line; getline(input, line);)
    {
        if (line[0] == '#')
            continue;

        tokenize(line, ' ', out);
        fraction f(std::stoi(out[0].substr(1)));
        oeis_keys.set(i, f);
        tokenize(out[1], ',', out);
        size_t s = out.size();
        //(oeis_values + i); //sequence(s);

        unsigned int e = 0;
        try
        {
            for (; e < s; e++)
                (oeis_values + i)->set(e, std::stoll(out[e]));
        }
        catch (...)
        {
            // std::cout << "cannot convert completely " << get(oeis_keys, i) << " (" << e << "/" << s << ") values " << out[out.size() - 1] << std::endl;
        }

        i++;
    }

    input.close();

    return true;
}

int main(int argc, char **argv)
{
    std::cout << "Started" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    std::string path = "stripped";
    // if (!oeis_db(path))
    //     return -1;

    std::cout << "Loading db..." << std::endl;
    unsigned int oeis_db_s = oeis_db_size(path);
    sequence *oeis_values = new sequence[oeis_db_s];
    sequence oeis_keys(oeis_db_s);
    if (!load_oeis_db(path, oeis_values, oeis_keys))
        return -1;

    auto end = std::chrono::high_resolution_clock::now();
    double time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Loaded in " << time_taken << " ms" << std::endl;

    unsigned int sequence_length = 8;
    SEQ_INT *t = new SEQ_INT[sequence_length];
    set(t, 0, sequence_length);
    set(t, 1, 0);
    set(t, 2, 6);
    set(t, 3, 30);
    set(t, 4, 152);
    set(t, 5, 512);
    set(t, 6, 1332);
    set(t, 7, 2976);
    set(t, 8, 6070);

    std::cout << "Investigating..." << std::endl;
    start = std::chrono::high_resolution_clock::now();
    // investigation(t, oeis_values, oeis_db_s);
    end = std::chrono::high_resolution_clock::now();
    time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "completed in " << time_taken << "ms" << std::endl;

    return 0;
}