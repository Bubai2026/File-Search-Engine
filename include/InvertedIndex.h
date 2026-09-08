#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class InvertedIndex
{
private:
    unordered_map<string, vector<int>> index;
    unordered_map<string, unordered_map<int, int>> termFrequency;
    unordered_map<int, int> documentLength;

public:
    void addDocument(
        int documentId,
        const vector<string>& tokens
    );

    vector<int> search(const string& token) const;
    vector<string> getAllTokens() const;

    int getTermFrequency(
        const string& token,
        int documentId
    ) const;

    double getTF(
        const string& token,
        int documentId
    ) const;

    int getDocumentFrequency(
        const string& token
    ) const;

    double getIDF(
        const string& token,
        int totalDocuments
    ) const;

    double getTFIDF(
        const string& token,
        int documentId,
        int totalDocuments
    ) const;
};

#endif
