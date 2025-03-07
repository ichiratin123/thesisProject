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

void insertWords(const vector<string> &files, TrieUnsortedArray &trie1, TrieSortedMap &trie2, CompressedTrie &trie3)
{
    string word;

    auto start1 = chrono::high_resolution_clock::now();
    for (const auto &f : files)
    {
        ifstream file(f);
        if (!file)
        {
            cerr << "file error: " << f << "\n";
            return;
        }

        while (getline(file, word))
        {
            trie1.insert(word);
        }
        file.close();
    }
    auto end1 = chrono::high_resolution_clock::now();
    chrono::duration<double> insert1 = end1 - start1;
    cout << "\nInsert time of NonSorted Array Trie: " << insert1.count() << " s";

    auto start2 = chrono::high_resolution_clock::now();
    for (const auto &f : files)
    {
        ifstream file(f);
        if (!file)
        {
            cerr << "file error: " << f << "\n";
            return;
        }

        while (getline(file, word))
        {
            trie2.insert(word);
        }
        file.close();
    }
    auto end2 = chrono::high_resolution_clock::now();
    chrono::duration<double> insert2 = end2 - start2;
    cout << "\nInsert time of Sorted Array Trie: " << insert2.count() << " s";

    auto start3 = chrono::high_resolution_clock::now();
    for (const auto &f : files)
    {
        ifstream file(f);
        if (!file)
        {
            cerr << "file error: " << f << "\n";
            return;
        }

        while (getline(file, word))
        {
            trie3.insert(word);
        }
        file.close();
    }
    auto end3 = chrono::high_resolution_clock::now();
    chrono::duration<double> insert3 = end3 - start3;
    cout << "\nInsert time of Compressed Trie: " << insert3.count() << " s\n";

    while (true)
    {
        cout << "\nEnter word to search (-1 to break): ";
        getline(cin, word);

        if (word == "-1")
            break;

        trie1.searchTime(word);
        trie2.searchTime(word);
        trie3.searchTime(word);
    }
    while (true)
    {
        char choice2;
        cout << "Do you want to print a Trie? (y/n): ";
        cin >> choice2;

        if (choice2 == 'y' || choice2 == 'Y')
        {
            int trieChoice;
            cout << "\nWhich Trie do you want to print?\n";
            cout << "==========================\n";
            cout << "1. Trie Unsorted Array (unordered_map)\n";
            cout << "2. Trie Sorted Array (map)\n";
            cout << "3. Compressed Trie with unorder_map\n";
            cout << "==========================\n";
            cout << "Enter choice (1/2/3): ";
            cin >> trieChoice;
            cout << "\n";
            switch (trieChoice)
            {
            case 1:
                trie1.printTrie();
                break;
            case 2:
                trie2.printTrie();
                break;
            case 3:
                trie3.printTrie();
                break;
            default:
                cout << "Error choice.\n";
            }
        }
        else
        {
            break;
        }
    }
}

int main()
{
    system("chcp 65001");

    TrieUnsortedArray trie1;
    TrieSortedMap trie2;
    CompressedTrie trie3;
    string word;
    int choice;

    while (true)
    {
        cout << "\n========== MENU ==========";
        cout << "\n1. Insert English words";
        cout << "\n2. Insert Vietnamese words";
        cout << "\n3. Insert Czech words";
        cout << "\n4. Insert Chinese words";
        cout << "\n5. Insert Random Words";
        cout << "\n6. Insert All";
        cout << "\n7. Insert Test words";
        cout << "\n8. End";
        cout << "\n==========================";
        cout << "\nYour choice: ";
        cin >> choice;
        cin.ignore();

        vector<string> files;

        switch (choice)
        {
        case 1:
            files = {"E:\\code\\Thesis\\C++Code\\thesisProject\\data\\words.txt"};
            insertWords(files, trie1, trie2, trie3);
            break;
        case 2:
            files = {"E:\\code\\Thesis\\C++Code\\thesisProject\\data\\Viet74K.txt"};
            insertWords(files, trie1, trie2, trie3);
            break;
        case 3:
            files = {"E:\\code\\Thesis\\C++Code\\thesisProject\\data\\czech.txt"};
            insertWords(files, trie1, trie2, trie3);
            break;
        case 4:
            files = {"E:\\code\\Thesis\\C++Code\\thesisProject\\data\\chinese.txt"};
            insertWords(files, trie1, trie2, trie3);
            break;
        case 5:
            files = {
                "E:\\code\\Thesis\\C++Code\\thesisProject\\data\\random1.txt",
                "E:\\code\\Thesis\\C++Code\\thesisProject\\data\\random2.txt",
                "E:\\code\\Thesis\\C++Code\\thesisProject\\data\\random3.txt"};
            insertWords(files, trie1, trie2, trie3);
            break;
        case 6:
            files = {
                "E:\\code\\Thesis\\C++Code\\thesisProject\\data\\words.txt",
                "E:\\code\\Thesis\\C++Code\\thesisProject\\data\\Viet74K.txt",
                "E:\\code\\Thesis\\C++Code\\thesisProject\\data\\czech.txt",
                "E:\\code\\Thesis\\C++Code\\thesisProject\\data\\chinese.txt",
                "E:\\code\\Thesis\\C++Code\\thesisProject\\data\\random1.txt",
                "E:\\code\\Thesis\\C++Code\\thesisProject\\data\\random2.txt",
                "E:\\code\\Thesis\\C++Code\\thesisProject\\data\\random3.txt"};
            insertWords(files, trie1, trie2, trie3);
            break;
        case 7:
            files = {"E:\\code\\Thesis\\C++Code\\thesisProject\\data\\test.txt"};
            insertWords(files, trie1, trie2, trie3);
            break;
        case 8:
            cout << "Exiting program\n";
            return 0;
        default:
            cout << "Error choice.\n";
        }
    }

    return 0;
}
