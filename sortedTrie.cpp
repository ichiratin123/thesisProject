#include <iostream>
#include <cstdlib>
#include <map>
#include <string>
#include <fstream>
#include <chrono>
using namespace std;

class TrieNode2
{
public:
    bool isEnd;
    map<char, TrieNode2 *> children;
    TrieNode2() : isEnd(false) {}
};

class TrieSortedMap
{
private:
    TrieNode2 *root;

    void print(TrieNode2 *node, string p, int d)
    {
        if (!node)
            return;

        for (const auto &i : node->children)
        {
            char key = i.first;
            TrieNode2 *child = i.second;
            string label = p + key;
            cout << string(d * 2, ' ') << "|-- " << key;
            if (child->isEnd)
                cout << " (end)";
            cout << endl;
            print(child, label, d + 1);
        }
    }

public:
    TrieSortedMap()
    {
        root = new TrieNode2();
    }

    void insert(const string &word)
    {
        TrieNode2 *node = root;
        for (char c : word)
        {
            if (node->children.find(c) == node->children.end())
            {
                node->children[c] = new TrieNode2();
            }
            node = node->children[c];
        }
        node->isEnd = true;
    }

    bool search(const string &word)
    {
        TrieNode2 *node = root;
        if (node == nullptr)
            return false;
        for (char c : word)
        {
            if (node->children.count(c) == 0)
                return false;
            node = node->children[c];
        }
        return node->isEnd;
    }

    void printTrie()
    {
        cout << "Trie (Unsorted Array):\n";
        print(root, "", 0);
    }

    double searchTime(const string &word)
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