# Spear

Spear is a fast, lightweight, full-text search and index server. Spear stores all information in memory making lookups very fast while also pesisting the index to disk. The index can be accessed over a TCP connection and all data returned is valid JSON.

**Spear is still heavily under development. Not all features are implemented or stable yet.**

# Motivation

Most software that requires full-text search is not really that complicated thus it does not need a complex solution. Using a complex solution often times tends to create headaches. 
Setting up Elasticsearch when Elasticsearch really isn't needed for the particular application costs more time and money to maintain. 

This is where Spear comes in. Spear is intended to be extremely easy to deploy and integrate into your application. Just start the Spear server and start sending commands.

# Build

```
make build
./bin/spear
```

# Run Tests

```
./bin/spear test
```

# Example Usage

Commands can be sent over using the `spear-cli.py` CLI tool.  

Commands: `INDEX`, `SEARCH`, `DELETE`

```
spear> INDEX document_1 Some text that I want to index
INDEXED
spear> INDEX document_2 Some other text that I want to index
spear> SEARCH I want to index
["document_1", "document_2"]b
spear> DELETE I want to index
spear> SEARCH I want to index
[]
```

# Key Features

- Full text indexing and searching
- Persisting data to disk
- Accessable over TCP connection
