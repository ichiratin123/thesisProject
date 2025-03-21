#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <Windows.h>
#include <locale>
#include <codecvt>

#include "sortedTrie.cpp"
#include "nonsortedTrie.cpp"
#include "compressed.cpp"

using namespace std;

string utf16_to_utf8(const wstring &s)
{
    wstring_convert<codecvt_utf8<wchar_t>> cv;
    return cv.to_bytes(s);
}

int wmain(int argc, wchar_t *argv[])
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    TrieUnsortedArray trie1;
    TrieSortedMap trie2;
    CompressedTrie trie3;
    string word;

    if (argc < 2)
    {
        wcerr << L"Usage: trieapp <data> <command> <word/number>\n";
        wcerr << L"EX:\ntrieapp data/test.txt -s hello\n";
        wcerr << L"trieapp data/test.txt -p 1\n";
        wcerr << L"1. unsorted trie\n";
        wcerr << L"2. sorted trie\n";
        wcerr << L"3. compressed trie\n";
        return 1;
    }

    string data = utf16_to_utf8(argv[1]);

    auto start1 = chrono::high_resolution_clock::now();
    ifstream file1(data);

    if (!file1)
    {
        cerr << "file error: " << data << "\n";
        return 1;
    }

    while (getline(file1, word))
    {
        trie1.insert(word);
    }
    file1.close();
    auto end1 = chrono::high_resolution_clock::now();
    chrono::duration<double> insert1 = end1 - start1;
    cout << "\nInsert time of NonSorted Array Trie: " << insert1.count() << " s";

    auto start2 = chrono::high_resolution_clock::now();
    ifstream file2(data);
    if (!file2)
    {
        cerr << "file error: " << data << "\n";
        return 1;
    }

    while (getline(file2, word))
    {
        trie2.insert(word);
    }
    file2.close();
    auto end2 = chrono::high_resolution_clock::now();
    chrono::duration<double> insert2 = end2 - start2;
    cout << "\nInsert time of Sorted Array Trie: " << insert2.count() << " s";

    auto start3 = chrono::high_resolution_clock::now();
    ifstream file3(data);
    if (!file3)
    {
        cerr << "file error: " << data << "\n";
        return 1;
    }

    while (getline(file3, word))
    {
        trie3.insert(word);
    }
    file3.close();
    auto end3 = chrono::high_resolution_clock::now();
    chrono::duration<double> insert3 = end3 - start3;
    cout << "\nInsert time of Compressed Trie: " << insert3.count() << " s\n\n";

    if (argc == 2)
    {
        return 0;
    }

    string cmm = utf16_to_utf8(argv[2]);
    if (cmm == "-s" && argc == 4)
    {

        wstring r;
        for (int i = 3; i < argc; i++)
        {
            if (i > 3)
                r += L" ";
            r += argv[i];
        }

        string s_word = utf16_to_utf8(r);

        cerr << "input: " << s_word << "\n\n";
        trie1.searchTime(s_word);
        trie2.searchTime(s_word);
        trie3.searchTime(s_word);
    }
    else if (cmm == "-p" && argc == 4)
    {

        string choice = utf16_to_utf8(argv[3]);
        if (choice == "1")
        {
            trie1.printTrie();
        }
        else if (choice == "2")
        {
            trie2.printTrie();
        }
        else
        {
            trie3.printTrie();
        }
    }
    else
    {
        cerr << "Error command";
        return 1;
    }

    return 0;
}
