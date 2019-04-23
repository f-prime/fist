# Spear

Spear is a fast, lightweight, full-text index server. Spear stores all information in memory making lookups very fast while also pesisting the index to disk. The index can be accessed over a TCP connection and all data returned is valid JSON.

**Spear is still heavily under development. Not all features are implemented or stable yet.**

# Motivation

The motivation for this project came while trying to create a way to search images containing text. There needed to be a way to look up the images by the words within the images that were read using OCR and inserted into another database. 
I didn't need something as complex as Lucene for this, all I needed was a way to index the references to images located in another database.

This is where Spear comes in. Spear is intended to be used in situations like this where a full-text index is needed, but a complete full-text search engine is not needed.

Spear has three goals: 

1. To be very fast
2. To be very lightweight and efficient
3. To be very easy to integrate into existing projects

# Build

```
make build
./bin/spear
```

# Example Usage

Commands: `index`, `search`, `delete`

```
spear> index "25" "Some text to index"
spear> index "26" "Some other text to index"
spear> search "to index"
["25", "26"]
spear> delete "to index"
spear> search "to index"
[]
```

# Key Features

- Full text indexing and searching
- Persisting data to disk
- Accessable over TCP connection
- Authentication
