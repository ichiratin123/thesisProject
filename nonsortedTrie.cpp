#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <string>
#include <fstream>
#include <chrono>
using namespace std;

struct TrieNode
{
    bool isEnd;
    unordered_map<char, TrieNode *> children;

    TrieNode() : isEnd(false) {}
};

class TrieUnsortedArray
{
private:
    TrieNode *root;

public:
    TrieUnsortedArray()
    {
        root = new TrieNode();
    }

    void insert(const string &word)
    {
        TrieNode *node = root;
        for (char ch : word)
        {
            if (node->children.find(ch) == node->children.end())
            {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->isEnd = true;
    }

    bool search(const string &word)
    {
        TrieNode *node = root;
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

        cout << "NonSorted Array - Word '" << word << "': " << (found ? "Found" : "Not Found")
             << " (Time: " << duration.count() * 1000000 << " s)\n";

        return duration.count();
    }
};
