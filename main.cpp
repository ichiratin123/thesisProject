#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include "sortedTrie.cpp"
#include "nonsortedTrie.cpp"
#include "compressed.cpp"
using namespace std;

int main()
{
    system("chcp 65001");
    TrieUnsortedArray trie1;
    TrieSortedMap trie2;
    CompressedTrie trie3;
    string word;
    // vector<string> files = {
    //     "E:\\code\\Thesis\\C++Code\\thesisProject\\data\\words.txt",
    //     "E:\\code\\Thesis\\C++Code\\thesisProject\\data\\Viet74K.txt",
    //     "E:\\code\\Thesis\\C++Code\\thesisProject\\data\\random1.txt",
    //     "E:\\code\\Thesis\\C++Code\\thesisProject\\data\\random2.txt",
    //     "E:\\code\\Thesis\\C++Code\\thesisProject\\data\\random3.txt"};

    vector<string> files = {
        "E:\\code\\Thesis\\C++Code\\thesisProject\\data\\words.txt",
        "E:\\code\\Thesis\\C++Code\\thesisProject\\data\\Viet74K.txt"};

    // vector<string> files = {
    //     "E:\\code\\Thesis\\C++Code\\thesisProject\\data\\random3.txt"};

    auto start1 = chrono::high_resolution_clock::now();
    for (const auto &filename : files)
    {
        ifstream file(filename);
        if (!file)
        {
            cerr << "File error: " << filename << "\n";
            return 1;
        }

        while (getline(file, word))
        {
            trie1.insert(word);
        }
        file.close();
    }

    auto end1 = chrono::high_resolution_clock::now();
    chrono::duration<double> insert1 = end1 - start1;
    cout << "\nInsert time of non-sorted array Trie: " << insert1.count() << " s";

    auto start2 = chrono::high_resolution_clock::now();
    for (const auto &filename : files)
    {
        ifstream file(filename);
        if (!file)
        {
            cerr << "File error: " << filename << "\n";
            return 1;
        }

        while (getline(file, word))
        {
            trie2.insert(word);
        }
        file.close();
    }

    auto end2 = chrono::high_resolution_clock::now();
    chrono::duration<double> insert2 = end2 - start2;
    cout << "\nInsert time of sorted array Trie: " << insert2.count() << " s";

    auto start3 = chrono::high_resolution_clock::now();
    for (const auto &filename : files)
    {
        ifstream file(filename);
        if (!file)
        {
            cerr << "File error: " << filename << "\n";
            return 1;
        }

        while (getline(file, word))
        {
            trie3.insert(word);
        }
        file.close();
    }

    auto end3 = chrono::high_resolution_clock::now();
    chrono::duration<double> insert3 = end3 - start3;
    cout << "\nInsert time of compressed Trie: " << insert3.count() << " s\n";

    while (true)
    {
        cout << "\nEnter word to search (-1 to break): ";
        getline(cin, word);

        if (word == "-1")
            break;

        trie1.measureSearchTime(word);
        trie2.measureSearchTime(word);
        trie3.measureSearchTime(word);
    }
    return 0;
}