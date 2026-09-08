#include "DocumentManager.h"

using namespace std;

int DocumentManager::addDocument(const string& path)
{
    int id = static_cast<int>(documentPaths.size());

    documentPaths.push_back(path);
    idToPath[id] = path;

    return id;
}

string DocumentManager::getPath(int documentId) const
{
    auto it = idToPath.find(documentId);

    if (it == idToPath.end())
    {
        return "";
    }

    return it->second;
}

int DocumentManager::getDocumentCount() const
{
    return static_cast<int>(documentPaths.size());
}
