#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

#include "FileCrawler.h"
#include "Tokenizer.h"
#include "DocumentManager.h"
#include "InvertedIndex.h"
#include "SearchEngine.h"

using namespace std;

int main(int argc, char* argv[])
{
    // API mode:
    // search <directory> <query>
    //
    // Example:
    // search data/documents algorithm

    if (argc == 3)
    {
        string directory = argv[1];
        string query = argv[2];

        FileCrawler crawler(directory);
        vector<string> files = crawler.getFiles();

        DocumentManager documents;
        Tokenizer tokenizer;
        InvertedIndex index;

        for (const string& path : files)
        {
            ifstream file(path.c_str());

            if (!file.is_open())
            {
                continue;
            }

            int documentId =
                documents.addDocument(path);

            string line;
            string text;

            while (getline(file, line))
            {
                text += line;
                text += " ";
            }

            file.close();

            vector<string> tokens =
                tokenizer.tokenize(text);

            index.addDocument(
                documentId,
                tokens
            );
        }

        SearchEngine searchEngine(
            index,
            documents
        );

        vector<pair<string, double>> results =
            searchEngine.search(query);

        for (const auto& result : results)
        {
            cout << result.first
                 << "\t"
                 << result.second
                 << endl;
        }

        return 0;
    }

    // Normal interactive mode for local use.
    string directory = "data/documents";

    if (argc == 2)
    {
        directory = argv[1];
    }

    FileCrawler crawler(directory);
    vector<string> files = crawler.getFiles();

    DocumentManager documents;
    Tokenizer tokenizer;
    InvertedIndex index;

    for (const string& path : files)
    {
        ifstream file(path.c_str());

        if (!file.is_open())
        {
            continue;
        }

        int documentId =
            documents.addDocument(path);

        string line;
        string text;

        while (getline(file, line))
        {
            text += line;
            text += " ";
        }

        file.close();

        vector<string> tokens =
            tokenizer.tokenize(text);

        index.addDocument(
            documentId,
            tokens
        );
    }

    SearchEngine searchEngine(
        index,
        documents
    );

    cout << "Files indexed: "
         << documents.getDocumentCount()
         << endl;

    while (true)
    {
        string query;

        cout << endl;
        cout << "Enter search query (type exit to quit): ";
        getline(cin, query);

        if (query == "exit")
        {
            break;
        }

        vector<pair<string, double>> results =
            searchEngine.search(query);

        if (results.empty())
        {
            cout << "No results found." << endl;
            continue;
        }

        cout << endl;
        cout << "Search Results:" << endl;

        for (int i = 0; i < results.size(); i++)
        {
            cout << i + 1 << ". "
                 << results[i].first
                 << "  Score: "
                 << results[i].second
                 << endl;
        }
    }

    return 0;
}
