#include "FileCrawler.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#include <sys/stat.h>
#endif

using namespace std;

FileCrawler::FileCrawler(const string& rootPath)
{
    rootDirectory = rootPath;
}

#ifdef _WIN32

void FileCrawler::crawlDirectory(
    const string& directory,
    vector<string>& files
) const
{
    string searchPath = directory + "\\*";

    WIN32_FIND_DATAA data;
    HANDLE handle = FindFirstFileA(
        searchPath.c_str(),
        &data
    );

    if (handle == INVALID_HANDLE_VALUE)
    {
        return;
    }

    do
    {
        string name = data.cFileName;

        if (name == "." || name == "..")
        {
            continue;
        }

        string path = directory + "\\" + name;

        if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            crawlDirectory(path, files);
        }
        else
        {
            files.push_back(path);
        }

    } while (FindNextFileA(handle, &data));

    FindClose(handle);
}

#else

void FileCrawler::crawlDirectory(
    const string& directory,
    vector<string>& files
) const
{
    DIR* dir = opendir(directory.c_str());

    if (dir == NULL)
    {
        return;
    }

    struct dirent* entry;

    while ((entry = readdir(dir)) != NULL)
    {
        string name = entry->d_name;

        if (name == "." || name == "..")
        {
            continue;
        }

        string path = directory + "/" + name;

        struct stat info;

        if (stat(path.c_str(), &info) != 0)
        {
            continue;
        }

        if (S_ISDIR(info.st_mode))
        {
            crawlDirectory(path, files);
        }
        else if (S_ISREG(info.st_mode))
        {
            files.push_back(path);
        }
    }

    closedir(dir);
}

#endif

vector<string> FileCrawler::getFiles() const
{
    vector<string> files;
    crawlDirectory(rootDirectory, files);
    return files;
}
