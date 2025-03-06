#include <iostream>
#include <cstdlib>
#include <map>
#include <string>
#include <fstream>
#include <chrono>
using namespace std;

struct TrieNode2
{
    bool isEnd;
    map<char, TrieNode2 *> children;
    TrieNode2() : isEnd(false) {}
};
class TrieSortedMap
{
private:
    TrieNode2 *root;

public:
    TrieSortedMap()
    {
        root = new TrieNode2();
    }

    void insert(const string &word)
    {
        TrieNode2 *node = root;
        for (char ch : word)
        {
            if (node->children.find(ch) == node->children.end())
            {
                node->children[ch] = new TrieNode2();
            }
            node = node->children[ch];
        }
        node->isEnd = true;
    }

    bool search(const string &word)
    {
        TrieNode2 *node = root;
        if (node == nullptr)
            return false;
        for (char ch : word)
        {
            if (node->children.count(ch) == 0)
                return false;
            node = node->children[ch];
        }
        return node->isEnd;
    }
    double measureSearchTime(const string &word)
    {
        auto start = chrono::high_resolution_clock::now();
        bool found = search(word);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> duration = end - start;

        cout << "Sorted Array - Word '" << word << "': " << (found ? "Found" : "Not Found")
             << " (Time: " << duration.count() * 1000000 << " s)\n";

        return duration.count();
    }
};