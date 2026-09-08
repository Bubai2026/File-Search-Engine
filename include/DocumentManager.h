#ifndef DOCUMENT_MANAGER_H
#define DOCUMENT_MANAGER_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class DocumentManager
{
private:
    vector<string> documentPaths;
    unordered_map<int, string> idToPath;

public:
    int addDocument(const string& path);
    string getPath(int documentId) const;
    int getDocumentCount() const;
};

#endif
