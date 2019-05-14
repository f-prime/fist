# Fist - (F)ull-text (i)ndex (s)erver (t) 

Fist is a fast, lightweight, full-text search and index server. Fist stores all information in memory making lookups very fast while also persisting the index to disk. The index can be accessed over a TCP connection and all data returned is valid JSON.

**Fist is still heavily under development. Not all features are implemented or stable yet.**

# Motivation

Most software that requires full-text search is not really that complicated and does not need an overly complex solution. Using a complex solution often times leads to headaches. 
Setting up Elasticsearch when Elasticsearch really isn't needed for the particular application costs more time and money to maintain. 

This is where Fist comes in. Fist is intended to be extremely easy to deploy and integrate into your application. Just start the Fist server and start sending commands.

# Build

```
make build
./bin/fist
```

# Run Tests

```
./bin/fist test
```

# Example Usage

Commands can be sent over using the `fist-cli.py` CLI tool.  

Commands: `INDEX`, `SEARCH`, `DELETE`

```
fist> INDEX document_1 Some text that I want to index
INDEXED
fist> INDEX document_2 Some other text that I want to index
fist> SEARCH I want to index
["document_1", "document_2"]b
fist> DELETE I want to index
fist> SEARCH I want to index
[]
```

# Key Features

- Full text indexing and searching
- Persisting data to disk
- Accessable over TCP connection
