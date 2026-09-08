#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <string>
#include <vector>
#include <utility>

#include "InvertedIndex.h"
#include "DocumentManager.h"
#include "Tokenizer.h"

using namespace std;

class SearchEngine
{
private:
    const InvertedIndex& index;
    const DocumentManager& documents;
    Tokenizer tokenizer;

    vector<string> expandTerm(const string& term) const;

    vector<int> findMatchingDocuments(
        const vector<string>& terms
    ) const;

public:
    SearchEngine(
        const InvertedIndex& invertedIndex,
        const DocumentManager& documentManager
    );

    vector<pair<string, double>> search(
        const string& query
    ) const;
};

#endif
