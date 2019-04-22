# Spear

Spear is a fast, lightweight, full-text indexer. Spear stores all information in memory making lookups very fast while also pesisting the index to disk. 

**Spear is still under development. Not all features are implemented or stable yet.**

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
spear> remove "to index"
spear> search "to index"
[]
```

# Key Features

- Full text indexing and searching
- Persisting data to disk
- Accessable over TCP connection
- Authentication
