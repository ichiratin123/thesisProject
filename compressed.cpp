#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <string>
#include <fstream>
#include <chrono>
using namespace std;

class TrieNode3
{
public:
    unordered_map<char, pair<string, TrieNode3 *>> children;
    bool isEnd;

    TrieNode3(bool isEnd = false) : isEnd(isEnd) {}
};

class CompressedTrie
{
private:
    TrieNode3 *root;

    void print(TrieNode3 *node, string p)
    {
        if (!node)
            return;

        for (const auto &i : node->children)
        {
            string label = i.second.first;
            TrieNode3 *child = i.second.second;
            cout << p << "|-- \"" << label << "\"";
            if (child->isEnd)
                cout << " (end)";
            cout << endl;
            print(child, p + "  ");
        }
    }

public:
    CompressedTrie()
    {
        root = new TrieNode3();
    }

    void insert(string word)
    {
        TrieNode3 *node = root;
        size_t i = 0;

        while (i < word.length())
        {
            char firstChar = word[i];

            if (node->children.find(firstChar) == node->children.end())
            {
                node->children[firstChar] = {word.substr(i), new TrieNode3(true)};
                return;
            }

            auto &start = node->children[firstChar];
            string &label = start.first;
            TrieNode3 *child = start.second;

            size_t j = 0;
            while (j < label.length() && i < word.length() && label[j] == word[i])
            {
                ++j;
                ++i;
            }

            if (j == label.length())
            {
                node = child;
            }
            else
            {
                string remainLabel = label.substr(j);
                string remainWord = word.substr(i);

                TrieNode3 *newChild = new TrieNode3();
                newChild->children[remainLabel[0]] = {remainLabel, child};

                if (!remainWord.empty())
                {
                    newChild->children[remainWord[0]] = {remainWord, new TrieNode3(true)};
                }
                else
                {
                    newChild->isEnd = true;
                }

                node->children[firstChar] = {label.substr(0, j), newChild};
                return;
            }
        }

        node->isEnd = true;
    }

    bool search(const string &word)
    {
        TrieNode3 *node = root;
        size_t i = 0;

        while (i < word.length())
        {
            char firstChar = word[i];

            if (node->children.find(firstChar) == node->children.end())
            {
                return false;
            }

            auto &start = node->children[firstChar];
            string &label = start.first;
            TrieNode3 *child = start.second;

            size_t j = 0;
            while (j < label.length() && i < word.length())
            {
                if (label[j] != word[i])
                    return false;
                ++j;
                ++i;
            }

            if (j == label.length())
            {
                node = child;
            }
            else
            {
                return false;
            }
        }

        return node->isEnd;
    }

    void printTrie()
    {
        cout << "Compressed Trie:\n";
        print(root, "");
    }

    double searchTime(const string &word)
    {
        auto start = chrono::high_resolution_clock::now();
        bool found = search(word);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> duration = end - start;

        cout << "Compressed Trie - Word '" << word << "': " << (found ? "Found" : "Not Found")
             << " (Time: " << duration.count() * 1000000 << " s)\n";

        return duration.count();
    }
};
