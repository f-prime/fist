# Spear

Spear is a fast, lightweight, full-text index server. Spear stores all information in memory making lookups very fast while also pesisting the index to disk. The index can be accessed over a TCP connection and all data returned is valid JSON.

**Spear is still heavily under development. Not all features are implemented or stable yet.**

# Motivation

The motivation for this project came while I was trying to build a search engine for audio files. The goal was to be able to search the files by the words spoken in the audio. Naturally, this meant that I needed to index a lot of data, and I needed to be able to do it very quickly. I also needed a light weight solution that was easy to setup in 
any kind of environment without the need for heavy configuration. Just compile and deploy. 

This is where Spear comes in. Spear is intended to be used in situations like this where a full-text index is needed and where speed and efficieny are important. It is designed to be light weight and easy to get up and running in minutes. Spear works as intended out of the box without the need for futher configuration. 

# Build

```
make build
./bin/spear
```

# Example Usage

Commands can be sent over Telnet or using the `spear-cli.py` tool.  

Commands: `INDEX`, `SEARCH`, `DELETE`

```
spear> INDEX document_1 Some text that I want to index
INDEXED
spear> INDEX document_2 Some other text that I want to index
spear> SEARC I want to index
["document_1", "document_2"]
spear> DELETE to index
spear> SEARCH to index
[]
```

# Key Features

- Full text indexing and searching
- Persisting data to disk
- Accessable over TCP connection
