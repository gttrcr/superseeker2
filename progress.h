#include <iostream>
#include <map>
#include <mutex>

std::mutex _write;
class progress
{
private:
    unsigned int _lines;
    std::map<std::string, unsigned int> _names;
    std::map<std::string, unsigned int> _progresses;

    inline std::string replace_string_with_string(const std::string &str, const std::string &replace, const std::string &replacement)
    {
        std::string data(str);
        size_t pos = data.find(replace);
        while (pos != std::string::npos)
        {
            data.replace(pos, replace.size(), replacement);
            pos = data.find(replace, pos + replacement.size());
        }

        return data;
    }

    void set_cursor_pos(int XPos, int YPos)
    {
        printf("\033[%d;%dH", YPos + 1, XPos + 1);
    }

public:
    progress()
    {
        int a = system("clear");
        _lines = 0;
    }

    ~progress()
    {
        int a = system("clear");
        set_cursor_pos(0, 0);
    }

    void set_name(const std::string &name)
    {
        _write.lock();
        _names[name] = _lines;
        set_cursor_pos(0, _lines);
        std::cout << name << " [";
        for (unsigned int i = 0; i < 100; i++)
            std::cout << " ";
        std::cout << "]" << std::endl;
        _lines++;
        _write.unlock();
    }

    void set_value(const std::string &name, const unsigned int value)
    {
        _write.lock();
        _progresses[name] = value;
        set_cursor_pos(name.length() + 2, _names[name]);
        for (unsigned int i = 0; i < value; i++)
            std::cout << "=";
        if (value == 100)
            std::cout << "] DONE";
        std::cout << std::endl;
        _write.unlock();
    }
};