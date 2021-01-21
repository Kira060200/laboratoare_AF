#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <unordered_map>
#include <unordered_set>

using namespace std;

ifstream f ("cuvinte.in");
ofstream g ("cuvinte.out");

class Edge
{
    string src;
    string dst;
    int weight;
public:
    Edge (string s, string d, int w) : src (s), dst (d), weight (w) {}

    string get_src()
    {
        return src;
    }
    string get_dst()
    {
        return dst;
    }
    int get_weight()
    {
        return weight;
    }

    bool operator < (const Edge& ed) const
    {
        return weight < ed.weight;
    }
};

void read (int& n, vector<string>& wordList)
{
    string x;
    f >> n;
    getline (f, x);
    for (int i = 0; i < n; ++i)
    {
        getline (f, x);
        wordList.push_back (x);
    }
}

int repres (int u, vector<int>& father)
{
    while (father[u] != -1)
    {
        u = father[u];
    }
    return u;
}

void join (int ru, int rv, vector<int>& father, vector<int>& height)
{
    if (height[ru] > height[rv])
    {
        father[rv] = ru;
    }
    else
    {
        father[ru] = rv;
        if (height[ru] == height[rv])
        {
            height[rv]++;
        }
    }
}

void getEdges (int n, vector<string>& wordList, vector<Edge>& edgeList)
{
    int temp, tracker;
    //Levenshtein distance
    for (int i = 0; i < wordList.size() - 1; ++i)
    {
        string s = wordList[i];
        for (int j = i + 1; j < wordList.size(); ++j)
        {
            string t = wordList[j];
            int d[s.length() + 1][t.length() + 1];

            for (int l = 0; l <= s.length(); l++)
                for (int k = 0; k <= t.length(); k++)
                    d[l][k] = 0;

            for (int l = 1; l <= s.length(); l++)
                d[l][0] = l;
            for (int k = 1; k <= t.length(); k++)
                d[0][k] = k;

            for (int k = 1; k <= t.length(); k++)
            {
                for (int l = 1; l <= s.length(); l++)
                {
                    if (s[l - 1] == t[k - 1])
                    {
                        tracker = 0;
                    }
                    else
                    {
                        tracker = 1;
                    }
                    temp = min ( (d[l - 1][k] + 1), (d[l][k - 1] + 1) );
                    d[l][k] = min (temp, (d[l - 1][k - 1] + tracker) );
                }
            }
            edgeList.push_back (Edge (s, t, d[s.length()][t.length()]) );
        }
    }
}

void solve (int k, int n, vector<string>& wordList, vector<Edge>& edgeList)
{
    vector<int> father (wordList.size(), -1);
    vector<int> height (wordList.size(), 0);
    unordered_map<string, int> wordMap;
    for (int i = 0; i < wordList.size(); ++i)
    {
        wordMap.insert ({wordList[i], i});
    }

    sort (edgeList.begin(), edgeList.end() );
    int i = 0, j = 0;
    while (j < wordList.size() - k && i < edgeList.size() )
    {
        Edge ed = edgeList[i];
        int ru = repres (wordMap[ed.get_src()], father);
        int rv = repres (wordMap[ed.get_dst()], father);

        if (ru != rv)
        {
            join (ru, rv, father, height);
            ++j;
        }
        ++i;
    }

    unordered_map<int, unordered_set<string>> components;
    for (i = 0; i < father.size(); ++i)
    {
        if (father[i] == -1)
        {
            unordered_set<string> us;
            components.insert ({i, us});
        }
    }
    for (i = 0; i < father.size(); ++i)
    {
        int rep = repres (i, father);
        components[rep].insert (wordList[i]);
    }
    for (auto itr = components.begin(); itr != components.end(); ++itr)
    {
        for (auto sitr = itr->second.begin(); sitr != itr->second.end(); ++sitr)
        {
            g << *sitr << ' ';
        }
        g << '\n';
    }
}

int main()
{
    int n, k = 3;
    vector<Edge> edgeList;
    vector<string> wordList;

    read (n, wordList);

    getEdges (n, wordList, edgeList);

    solve (k, n, wordList, edgeList);

    return 0;
}
