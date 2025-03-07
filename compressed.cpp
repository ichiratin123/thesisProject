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

    void printChildren(TrieNode3 *node, string prefix)
    {
        if (!node)
            return;

        for (const auto &entry : node->children)
        {
            string label = entry.second.first;
            TrieNode3 *child = entry.second.second;
            cout << prefix << "|-- \"" << label << "\"";
            if (child->isEnd)
                cout << " (END)";
            cout << endl;
            printChildren(child, prefix + "  ");
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

            auto &entry = node->children[firstChar];
            string &label = entry.first;
            TrieNode3 *child = entry.second;

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
                string remainingLabel = label.substr(j);
                string remainingWord = word.substr(i);

                TrieNode3 *newChild = new TrieNode3();
                newChild->children[remainingLabel[0]] = {remainingLabel, child};

                if (!remainingWord.empty())
                {
                    newChild->children[remainingWord[0]] = {remainingWord, new TrieNode3(true)};
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

            auto &entry = node->children[firstChar];
            string &label = entry.first;
            TrieNode3 *child = entry.second;

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
        cout << "Compressed Trie Structure:\n";
        printChildren(root, "");
    }

    double measureSearchTime(const string &word)
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
