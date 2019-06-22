# Fist - (F)ull-(t)ext (i)ndex (s)erver 

Fist is a fast, lightweight, full-text search and index server. Fist stores all information in memory making lookups very fast while also persisting the index to disk. The index can be accessed over a TCP connection and all data returned is valid JSON.

**Fist is still heavily under development. Not all features are implemented or stable yet.**

Join the chat on slack [here](https://join.slack.com/t/fist-global/shared_invite/enQtNjc1MzgxMDc0NzI2LTI1ZWY5ODg0ZWEyNGM1OWVhY2MyOGIxMzYyODM1MjJjOWM4ZDkwZjlhNjg2MTYyMTkzZGEwMTdlNTAzNTA2NjM)

# Motivation

Most software that requires full-text search is not really that complicated and does not need an overly complex solution. Using a complex solution often times leads to headaches. 
Setting up Elasticsearch when Elasticsearch really isn't needed for the particular application costs more time and money to maintain. 

This is where Fist comes in. Fist is intended to be extremely easy to deploy and integrate into your application. Just start the Fist server and start sending commands.

# Build and start Fist server

```
make build
./bin/fist
Fist started at localhost:5575
```

# Run Tests

```
./bin/fist test
```

# Example Usage

Commands can be sent over a TELNET connection

Commands: `INDEX`, `SEARCH`, `EXIT`

```
telnet localhost 5575
Trying ::1...
telnet: connect to address ::1: Connection refused
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
INDEX document_1 Some text that I want to index
Text has been indexed
INDEX document_2 Some other text that I want to index
Text has been indexed
SEARCH I want to index
["document_1","document_2"]
EXIT
Bye
```

# Key Features

- Full text indexing and searching
- Persisting data to disk
- Accessable over TCP connection
