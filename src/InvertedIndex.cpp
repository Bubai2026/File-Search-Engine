#include "InvertedIndex.h"

#include <cmath>

using namespace std;

void InvertedIndex::addDocument(
    int documentId,
    const vector<string>& tokens
)
{
    documentLength[documentId] =
        static_cast<int>(tokens.size());

    for (const string& token : tokens)
    {
        vector<int>& documents = index[token];

        if (documents.empty() ||
            documents.back() != documentId)
        {
            documents.push_back(documentId);
        }

        termFrequency[token][documentId]++;
    }
}

vector<int> InvertedIndex::search(const string& token) const
{
    auto it = index.find(token);

    if (it == index.end())
    {
        return vector<int>();
    }

    return it->second;
}

vector<string> InvertedIndex::getAllTokens() const
{
    vector<string> tokens;

    for (const auto& entry : index)
    {
        tokens.push_back(entry.first);
    }

    return tokens;
}

int InvertedIndex::getTermFrequency(
    const string& token,
    int documentId
) const
{
    auto tokenIt = termFrequency.find(token);

    if (tokenIt == termFrequency.end())
    {
        return 0;
    }

    auto documentIt = tokenIt->second.find(documentId);

    if (documentIt == tokenIt->second.end())
    {
        return 0;
    }

    return documentIt->second;
}

double InvertedIndex::getTF(
    const string& token,
    int documentId
) const
{
    int frequency = getTermFrequency(token, documentId);

    auto it = documentLength.find(documentId);

    if (it == documentLength.end() || it->second == 0)
    {
        return 0.0;
    }

    return static_cast<double>(frequency) / it->second;
}

int InvertedIndex::getDocumentFrequency(
    const string& token
) const
{
    auto it = index.find(token);

    if (it == index.end())
    {
        return 0;
    }

    return static_cast<int>(it->second.size());
}

double InvertedIndex::getIDF(
    const string& token,
    int totalDocuments
) const
{
    int documentFrequency = getDocumentFrequency(token);

    if (documentFrequency == 0 || totalDocuments == 0)
    {
        return 0.0;
    }

    return log(
        static_cast<double>(totalDocuments) /
        documentFrequency
    );
}

double InvertedIndex::getTFIDF(
    const string& token,
    int documentId,
    int totalDocuments
) const
{
    return getTF(token, documentId) *
           getIDF(token, totalDocuments);
}
