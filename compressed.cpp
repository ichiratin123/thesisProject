#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <string>
#include <fstream>
#include <chrono>
using namespace std;

class Node
{
public:
    unordered_map<char, pair<string, Node *>> children;
    bool isEnd;

    Node(bool isEnd = false) : isEnd(isEnd) {}
};

class CompressedTrie
{
private:
    Node *root;

public:
    CompressedTrie()
    {
        root = new Node();
    }

    void insert(string word)
    {
        Node *node = root;
        size_t i = 0;

        while (i < word.length())
        {
            char firstChar = word[i];

            if (node->children.find(firstChar) == node->children.end())
            {
                node->children[firstChar] = {word.substr(i), new Node(true)};
                return;
            }

            auto &entry = node->children[firstChar];
            string &label = entry.first;
            Node *child = entry.second;

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

                Node *newChild = new Node();
                newChild->children[remainingLabel[0]] = {remainingLabel, child};

                if (!remainingWord.empty())
                {
                    newChild->children[remainingWord[0]] = {remainingWord, new Node(true)};
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
        Node *node = root;
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
            Node *child = entry.second;

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
