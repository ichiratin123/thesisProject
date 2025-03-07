#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <string>
#include <fstream>
#include <chrono>
using namespace std;

class TrieNode
{
public:
    bool isEnd;
    unordered_map<char, TrieNode *> children;

    TrieNode() : isEnd(false) {}
};

class TrieUnsortedArray
{
private:
    TrieNode *root;

    void print(TrieNode *node, string p, int d)
    {
        if (!node)
            return;

        for (const auto &i : node->children)
        {
            char key = i.first;
            TrieNode *child = i.second;
            string label = p + key;
            cout << string(d * 2, ' ') << "|-- " << key;
            if (child->isEnd)
                cout << " (end)";
            cout << endl;
            print(child, label, d + 1);
        }
    }

public:
    TrieUnsortedArray()
    {
        root = new TrieNode();
    }

    void insert(const string &word)
    {
        TrieNode *node = root;
        for (char c : word)
        {
            if (node->children.find(c) == node->children.end())
            {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isEnd = true;
    }

    bool search(const string &word)
    {
        TrieNode *node = root;
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
        cout << "Trie (Sorted Array):\n";
        print(root, "", 0);
    }

    double searchTime(const string &word)
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
