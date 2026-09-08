#include "SearchEngine.h"

#include <algorithm>

using namespace std;

SearchEngine::SearchEngine(
    const InvertedIndex& invertedIndex,
    const DocumentManager& documentManager
)
    : index(invertedIndex),
      documents(documentManager)
{
}

vector<string> SearchEngine::expandTerm(
    const string& term
) const
{
    vector<string> matchingTerms;

    if (!term.empty() &&
        term[term.size() - 1] == '*')
    {
        string prefix =
            term.substr(0, term.size() - 1);

        vector<string> allTokens =
            index.getAllTokens();

        for (const string& token : allTokens)
        {
            if (token.compare(0, prefix.size(), prefix) == 0)
            {
                matchingTerms.push_back(token);
            }
        }
    }
    else
    {
        matchingTerms.push_back(term);
    }

    return matchingTerms;
}

vector<int> SearchEngine::findMatchingDocuments(
    const vector<string>& terms
) const
{
    vector<int> documentsFound;

    for (const string& term : terms)
    {
        vector<string> matchingTerms =
            expandTerm(term);

        for (const string& matchingTerm : matchingTerms)
        {
            vector<int> documentIds =
                index.search(matchingTerm);

            for (int documentId : documentIds)
            {
                if (find(
                        documentsFound.begin(),
                        documentsFound.end(),
                        documentId
                    ) == documentsFound.end())
                {
                    documentsFound.push_back(documentId);
                }
            }
        }
    }

    return documentsFound;
}

vector<pair<string, double>> SearchEngine::search(
    const string& query
) const
{
    vector<pair<string, double>> results;

    vector<string> terms =
        tokenizer.tokenize(query);

    if (terms.empty())
    {
        return results;
    }

    int totalDocuments =
        documents.getDocumentCount();

    vector<int> matchingDocuments =
        findMatchingDocuments(terms);

    for (int documentId : matchingDocuments)
    {
        double score = 0.0;

        for (const string& term : terms)
        {
            vector<string> matchingTerms =
                expandTerm(term);

            for (const string& matchingTerm : matchingTerms)
            {
                score += index.getTFIDF(
                    matchingTerm,
                    documentId,
                    totalDocuments
                );
            }
        }

        results.push_back(
            make_pair(
                documents.getPath(documentId),
                score
            )
        );
    }

    sort(
        results.begin(),
        results.end(),
        [](const pair<string, double>& a,
           const pair<string, double>& b)
        {
            if (a.second != b.second)
            {
                return a.second > b.second;
            }

            return a.first < b.first;
        }
    );

    return results;
}
