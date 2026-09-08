#include "Tokenizer.h"

#include <cctype>

using namespace std;

static bool isTokenCharacter(char ch)
{
    return isalnum(static_cast<unsigned char>(ch)) ||
           ch == '+' ||
           ch == '#' ||
           ch == '_' ||
           ch == ':' ||
           ch == '*';
}

vector<string> Tokenizer::tokenize(const string& text) const
{
    vector<string> tokens;
    string current;

    for (char ch : text)
    {
        if (isTokenCharacter(ch))
        {
            current += static_cast<char>(
                tolower(static_cast<unsigned char>(ch))
            );
        }
        else if (!current.empty())
        {
            tokens.push_back(current);
            current.clear();
        }
    }

    if (!current.empty())
    {
        tokens.push_back(current);
    }

    return tokens;
}
