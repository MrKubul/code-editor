#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#define NO_OF_CHARS 256

using namespace std;

void badCharHeuristic(const string &str, int size, int badchar[NO_OF_CHARS])
{
    for (int i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;

    for (int i = 0; i < size; i++)
        badchar[(int)str[i]] = i;
}

vector<int> search(const string &txt, const string &pat)
{
    int m = pat.size();
    int n = txt.size();

    int badchar[NO_OF_CHARS];

    vector<int> results;

    badCharHeuristic(pat, m, badchar);

    int s = 0; 
               
    while (s <= (n - m))
    {
        int j = m - 1;

        while (j >= 0 && pat[j] == txt[s + j])
            j--;

        if (j < 0)
        {
            results.emplace_back(s);
            s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
        }
        else
        {
            s += max(1, j - badchar[txt[s + j]]);
        }
    }

    return results;
}