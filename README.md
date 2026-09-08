# C++ File Search Engine

A simple file search engine built in **C++** using an **inverted index** and **TF-IDF ranking**.

The project recursively scans text files, indexes their contents, and returns relevant documents for a search query based on TF-IDF scores.

---

## Features

- Recursive file crawling
- Text tokenization
- Inverted index
- Exact word search
- Prefix search using `*`
- TF-IDF based document ranking
- Command-line interface
- Configurable document directory
- C++11 compatible

---

## Project Architecture

```text
                    Documents
                        |
                        v
                  FileCrawler
                        |
                        v
                    Tokenizer
                        |
                        v
                DocumentManager
                        |
                        v
                  InvertedIndex
                        |
                        v
                   SearchEngine
                        |
                        v
                  TF-IDF Ranking
                        |
                        v
                  Search Results
```

---

## Project Structure

```text
FileSearchEngine/
│
├── CMakeLists.txt
├── README.md
│
├── include/
│   ├── FileCrawler.h
│   ├── Tokenizer.h
│   ├── DocumentManager.h
│   ├── InvertedIndex.h
│   └── SearchEngine.h
│
├── src/
│   ├── main.cpp
│   ├── FileCrawler.cpp
│   ├── Tokenizer.cpp
│   ├── DocumentManager.cpp
│   ├── InvertedIndex.cpp
│   └── SearchEngine.cpp
│
└── data/
    └── documents/
        ├── cpp.txt
        ├── dsa.txt
        └── notes/
            ├── dp.txt
            └── graph.txt
```

---

# How It Works

## 1. File Crawling

`FileCrawler` recursively traverses the specified directory and collects the paths of the files it finds.

For example:

```text
data/documents/
├── cpp.txt
├── dsa.txt
└── notes/
    ├── dp.txt
    └── graph.txt
```

The crawler assigns all discovered files to the indexing pipeline.

---

## 2. Tokenization

`Tokenizer` converts the contents of each file into individual tokens.

For example:

```text
C++ is a programming language.
```

is converted approximately into:

```text
c++
is
a
programming
language
```

The tokenizer also converts characters to lowercase so that searches are case-insensitive.

Programming-related characters such as:

```text
+
#
_
:
```

are preserved.

For example:

```text
C++
std::vector
unordered_map
```

can be indexed as:

```text
c++
std::vector
unordered_map
```

---

## 3. Document Management

`DocumentManager` assigns an integer ID to every document.

For example:

```text
0 -> data/documents/cpp.txt
1 -> data/documents/dsa.txt
2 -> data/documents/notes/dp.txt
3 -> data/documents/notes/graph.txt
```

The integer IDs are used by the inverted index instead of repeatedly storing complete file paths.

---

## 4. Inverted Index

The main data structure of the search engine is an **inverted index**.

Instead of scanning every document for every query, the index stores:

```text
word -> documents containing the word
```

For example:

```text
graph -> [1, 3]

c++ -> [0, 1]

dynamic -> [2]
```

This makes looking up a word much faster than scanning every file again.

The implementation uses C++ `unordered_map` for the index.

---

# 5. TF-IDF Ranking

After finding documents containing the search term, the search engine calculates a TF-IDF score for each matching document.

## Term Frequency

Term Frequency measures how often a term occurs in a document.

```text
TF = term frequency / total number of terms in the document
```

---

## Inverse Document Frequency

Inverse Document Frequency measures how common a term is across the complete document collection.

```text
IDF = log(total number of documents / number of documents containing the term)
```

A term appearing in many documents receives a lower IDF value.

A term appearing in fewer documents receives a higher IDF value.

---

## TF-IDF

The final score is:

```text
TF-IDF = TF × IDF
```

For a multi-term query, the scores contributed by the query terms are added together.

Documents with higher scores are displayed first.

---

# Search

## Exact Search

You can search for an exact indexed term.

Examples:

```text
c++
graph
algorithm
algorithms
```

For example:

```text
Enter search query (type exit to quit): graph

Search Results:
1. data\documents\notes\graph.txt  Score: ...
2. data\documents\dsa.txt          Score: ...
```

---

## Prefix Search

The project also supports simple prefix search using `*`.

Add `*` to the end of a search term:

```text
alg*
```

This matches indexed words beginning with:

```text
alg
```

For example:

```text
algorithm
algorithms
```

can both be matched by:

```text
alg*
```

The current implementation performs prefix matching against the indexed vocabulary. It does not use a Trie.

---

# Running the Project

## Requirements

- Windows or Linux
- MinGW/GCC or another C++ compiler
- C++11 support

---

## Compile

Using MinGW/GCC:

```text
g++ -std=c++11 -Iinclude src\main.cpp src\FileCrawler.cpp src\Tokenizer.cpp src\DocumentManager.cpp src\InvertedIndex.cpp src\SearchEngine.cpp -o search.exe
```

---

## Run

Run with the default document directory:

```text
search.exe
```

The default directory is:

```text
data\documents
```

You can also specify another directory:

```text
search.exe C:\path\to\documents
```

---

# Example

After running:

```text
search.exe
```

the program displays:

```text
Files indexed: 4

Enter search query (type exit to quit):
```

Example query:

```text
c++
```

Example result:

```text
Search Results:
1. data\documents\cpp.txt  Score: 0.0693147
2. data\documents\dsa.txt  Score: 0.0198042
```

Prefix search:

```text
alg*
```

can return documents containing words such as:

```text
algorithm
algorithms
```

---

# Data Structures Used

The project uses several fundamental C++ data structures:

### `vector`

Used for:

- Storing file paths
- Storing document IDs
- Storing tokens
- Storing search results

### `unordered_map`

Used for:

- Mapping document IDs to file paths
- Building the inverted index
- Storing term frequencies
- Storing document lengths

### `pair`

Used for storing:

```text
file path + TF-IDF score
```

---

# Algorithms Used

The main algorithms and concepts implemented are:

- Recursive directory traversal
- Text tokenization
- Hash-table based indexing
- Inverted indexing
- Term Frequency calculation
- Inverse Document Frequency calculation
- TF-IDF ranking
- Sorting search results
- Prefix matching

---

# Complexity

Let:

- `T` = total number of tokens across all documents
- `N` = number of documents
- `V` = number of unique tokens

## Indexing

Reading and tokenizing the documents takes approximately:

```text
O(T)
```

The inverted index uses `unordered_map`, giving approximately **O(1) average-case lookup** for a token.

## Exact Search

Looking up a token in the inverted index is approximately:

```text
O(1)
```

on average, excluding the time required to process the returned document list.

## Prefix Search

The current simple prefix search checks the indexed vocabulary, so it takes approximately:

```text
O(V)
```

for a prefix query.

## Ranking

TF-IDF ranking depends on:

- Number of matching documents
- Number of query terms

The implementation calculates the score for each matching document and then sorts the results.

---

# Technologies

- **C++**
- **C++11**
- **STL**
- `vector`
- `unordered_map`
- File handling
- Inverted Index
- TF-IDF
- Basic Information Retrieval concepts

---

# Future Improvements

The current version intentionally focuses on the core search-engine concepts.

Possible future improvements include:

- Boolean queries such as `AND`, `OR`, and `NOT`
- Trie-based prefix search
- Priority queue for efficient Top-K results
- Persistent index
- Incremental indexing
- Multithreaded indexing
- Better query parsing
- Search-result snippets
- Web interface
- REST API
- Cloud deployment

These features are not part of the current implementation.

---

# Purpose

This project was built to understand how a basic search engine works internally using fundamental **C++ data structures, algorithms, and information-retrieval techniques**.

The core pipeline is:

```text
Files
  ↓
File Crawling
  ↓
Tokenization
  ↓
Document Management
  ↓
Inverted Index
  ↓
Search
  ↓
TF-IDF
  ↓
Ranked Results
```

---

## Author

**Bubai Sou**

M.Tech Computer Science

---

## License

This project is intended for educational and portfolio purposes.