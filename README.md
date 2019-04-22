# Spear

Spear is a fast, lightweight, full-text search engine. Spear uses in-memory data structures to make index lookups blazing fast, and also persists information to the disk.

**Spear is still under development. Not all features are implemented or stable yet.**

# Why use Spear?

Spear is useful when full-text search is needed in a limited resources environment. 

# Build

```
make build
./bin/spear
```

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
