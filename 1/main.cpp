#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>

using std::string;
using std::vector;

string vector_to_string(const vector<int> &v)
{
    string s;
    for (auto i : v)
    {
        s += std::to_string(i) + ' ';
    }
    return s;
}

int main(void)
{
    std::fstream f("1/input");
    if (!f.is_open())
    {
        std::cout << "Cannot open input file." << EOF;
        return 1;
    }

    vector<int> top{0, 0, 0};
    int acc = 0;
    for (string line; std::getline(f, line);)
    {
        // reached the end of a section of numbers
        if (line.empty())
        {
            // look for position 'i' in 'top' vector such that:
            //      top[i] < acc < top[i+1]
            // If found such a position, insert 'acc' there and
            // throw away the smallest element to keep the array
            // at size 3.
            for (int i = 0; i < 3; i++)
            {
                if (top[i] < acc)
                {
                    top.insert(top.begin() + i, acc);
                    top.pop_back();
                    break;
                }
            }
            acc = 0;
            continue;
        }
        // section of numbers is not over yet
        else
        {
            acc += std::stoi(line);
            continue;
        }
    }

    std::cout << "top: " << vector_to_string(top) << '\n';

    auto sum = std::accumulate(top.begin(), top.end(), decltype(top)::value_type(0));
    std::cout << "sum: " << sum << '\n';

    f.close();
    return 0;
}
