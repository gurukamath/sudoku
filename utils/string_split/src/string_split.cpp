#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>

using std::vector;
using std::set;
using std::find_if;

#include "string_split/string_split.hpp"

bool is_comma(char c)
{
    return c == ',';
}

bool is_number(char c)
{
    std::string lst {"0123456789"};
    return lst.find(c) < lst.length();
}

void pad_list(vector<int>& lst)
{
    vector<int> ret {0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (int i = 0; i != lst.size() && i != 9; ++i)
    {
        ret[i] = lst[i];
    }

    lst = ret;

}

vector<int> split_string(std::string s)
{
    vector<int> ret;

    for (int i = 0; i != s.size(); ++i)
    {
        if (is_number(s[i]))
        {
            ret.push_back((int)s[i] - 48);
        }
    }

    pad_list(ret);

    return ret;
}
