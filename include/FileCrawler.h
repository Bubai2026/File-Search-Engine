#ifndef FILE_CRAWLER_H
#define FILE_CRAWLER_H

#include <string>
#include <vector>

using namespace std;

class FileCrawler
{
private:
    string rootDirectory;

    void crawlDirectory(
        const string& directory,
        vector<string>& files
    ) const;

public:
    FileCrawler(const string& rootPath);

    vector<string> getFiles() const;
};

#endif
